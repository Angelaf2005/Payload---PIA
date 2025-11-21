# Report_Draft
## Resumen Ejecutivo
El análisis completo del payload evaluado confirma que se trata de un cliente HTTP benigno diseñado exclusivamente para realizar verificaciones de estado mediante una solicitud GET a la ruta /status en un servidor local. El examen estático mostró un binario simple, sin funciones ocultas ni capacidades ofensivas, mientras que las pruebas dinámicas validaron un comportamiento transparente, limitado y sin exfiltración de datos. La arquitectura del código prioriza simplicidad, uso controlado de recursos y validación de parámetros. Los riesgos asociados —principalmente fallos de conexión, validación de entrada y bloqueo por operaciones de red— fueron mitigados de forma proporcional al propósito del laboratorio. En conjunto, la evidencia técnica respalda que el payload es seguro, ético y adecuado para entornos controlados de prueba, cumpliendo con los requisitos del proyecto y sirviendo como base para la entrega final
## Descipcion del payload y limites eticos
El payload realiza una petición HTTP GET  /status de un servidor local por defecto en 127.0.0.1:8080 (la dirección IP puede modificarse mediante un parámetro en el cliente), con el objetivo de comprobar el estado/latido del servicio de manera segura y no intrusiva; su comportamiento esta diseñado para ser benigno —solo solicita información de estado—, maneja respuestas esperadas y manejo básico de errores para evitar bloqueos, y no envía ni extrae datos sensibles ni ejecuta operaciones remotas en el servidor.
## Diseño e implementación 
### Resumen de estructuras
- sockaddr_in server_addr: Estructura de la familia IPv4 usada para almacenar la dirección del servidor (IP y puerto). Se inicializa en la pila (server_addr{}) y se configura con sin_family, sin_port (con htons) y sin_addr (via inet_pton).
- Socket (int sock): Descriptor de archivo entero devuelto por socket(AF_INET, SOCK_STREAM, 0). Representa la conexión TCP al servidor destino.
- Buffer para recepción (char buffer[4096]): Array estático en la pila usado para leer datos desde el socket con recv. Se reserva un byte extra para añadir el terminador \0.

- Funciones de soporte:
    - runClient(const std::string& ip, int& port): crea el socket, conecta, envía la petición HTTP GET y consume la respuesta en un loop de recv.
    - validarIP(const std::string& ip): valida la dirección IPv4 usando std::regex.
    - validarPuerto(int port): verifica rango válido del puerto (1–65535).
- Interfaz de línea de comandos: main obtiene ip y port desde argv, convierte y valida antes de llamar al cliente.

### Manejo de memoria
- Locación en pila: El programa evita la asignación dinámica explícita (no hay new, malloc ni contenedores que hagan heap internamente en el fragmento dado), por lo que toda la memoria temporal clave (estructuras y buffer) está en la pila y se libera automáticamente al salir de cada función.
- Recursos del sistema: El recurso principal que requiere liberación explícita es el descriptor de socket sock. El código llama a close(sock) al final de runClient para liberar el descriptor; sin embargo, hay casos en los que los errores se imprimen pero no se hace return o close inmediatamente (por ejemplo, si socket() falla el valor de sock es negativo y no debe cerrarse; si connect() falla, el descriptor sí existe y debería cerrarse antes de salir).
- Recepción de datos: recv escribe hasta sizeof(buffer) - 1 bytes y el código añade '\0' en buffer[bytesReceived], asegurando nul-terminación para impresión segura. Se debe controlar el caso de recv que devuelve -1 (error) para evitar usar un índice negativo.
- Ausencia de fugas de heap: Dado que no hay heap usage en el código actual, no hay fugas de heap; sin embargo, el manejo de recursos del sistema (sockets) debe ser robusto ante errores para evitar descriptores abiertos.

### Decisiones clave

- Uso de BSD sockets (AF_INET, SOCK_STREAM): decisión simple y portátil para una conexión TCP IPv4. Trade-off: no hay soporte directo para IPv6; si se requiere compatibilidad IPv6, convendría usar getaddrinfo en lugar de inet_pton y sockaddr_in.

- Validación con std::regex: se eligió una expresión regular para validar la sintaxis de la IPv4 antes de intentar conectar. Ventaja: evita intentos de conexión con entradas mal formadas; contrapartida: std::regex puede ser más pesado en rendimiento y tamaño binario. Alternativa ligera: validar con inet_pton y revisar su resultado.

- Bloqueo y E/S sincrónica: el cliente usa llamadas bloqueantes (connect, send, recv) en un solo hilo —sencillo y predictible— pero en redes lentas puede bloquear la ejecución; si se necesita mayor robustez o concurrencia, considerar timeouts, select/poll o sockets no bloqueantes.

- Buffer fijo de 4096 bytes: elección práctica para la mayoría de respuestas de /status. Ventaja: simplicidad; riesgo: respuestas extremadamente grandes requerirían múltiples iteraciones (ya soportadas por el loop) pero si la respuesta excede repetidamente este tamaño puede impactar memoria/latencia. Tamaño configurable sería una mejora.

- Construcción manual de la petición HTTP: se arma una petición HTTP/1.1 simple con Connection: close para forzar cierre del socket tras la respuesta (facilita limpieza de recursos). Trade-off: no hay parsing HTTP avanzado ni manejo de chunked transfer-encoding; para interacciones más complejas convendría usar una librería HTTP o implementar parsing más completo.

- Conversión de puerto con std::atoi: método sencillo pero sin comprobación de errores detallada (si argv[2] no es numérico atoi devuelve 0). Se decidió validar el rango con validarPuerto, pero std::stoi con manejo de excepciones daría validación más estricta.

- Manejo de errores básico y salida inmediata: el programa imprime errores y usa exit(1) en validaciones críticas (IP/puerto). Decisión orientada a simplicidad en herramientas de línea de comandos; para una biblioteca o servicio se preferiría propagar errores con códigos y mensajes detallados.

- Seguridad y benignidad: el payload está diseñado como health-check benigno (solo GET /status) sin envío de datos sensibles ni ejecución remota. No obstante, por seguridad operativa se asume uso en entornos controlados y se recomienda validar explícitamente los endpoints y emplear TLS si se comunican secretos o en redes inseguras.
## Procedimiento de pruebas 
### Resumen
Antes de cada prueba se crea (o se vuelve a poner) una snapshot de la máquina virtual que se usará para evitar estados residuales. Verificar que la VM esté configurada en red interna (NAT/host-only/solo-interna según tu entorno) para asegurar que las pruebas se ejecutan en un entorno controlado.
El flujo de cada prueba es: (1) compilar el cliente con la modificación a probar, (2) poner en ejecución un servidor local que responda a GET /status, (3) ejecutar el binario cliente con los parámetros de la prueba, (4) recolectar evidencias (logs, pcap, capturas) y (5) comparar el comportamiento obtenido con el esperado. Al final se documentan resultados y se restaura la snapshot si procede. 
### Resultados
#### Recolección
* cliente_stdout: Salida estándar del cliente.
* Server_stdout: Salida estándar del servidor.
* Archivos .pcap: Evidencia de funcionamiento.
* Evidencias: Capturas de pantalla para registro de evidencias en /evidence
* Registro en test.md
## Análisis estático
El binario fue cargado en Ghidra y se identificó que está compilado en C++ con dependencias estándar, sin símbolos externos ni componentes ocultos. La vista de strings muestra principalmente rutas del sistema y funciones de la STL, sin presencia de cadenas sospechosas ni indicios de persistencia o capacidades ofensivas.
El grafo de funciones refleja un flujo simple y lineal: lectura de argumentos, creación del socket, conexión al servidor, envío de una solicitud HTTP GET a /status, recepción de la respuesta y cierre del proceso.
No se observaron llamadas a API inusuales, cifrado, manipulación de archivos ni lógica no documentada. En conjunto, los hallazgos estáticos indican que el binario implementa únicamente la funcionalidad esperada de cliente HTTP y no presenta comportamientos adicionales.
## Análisis dinámico
Durante la ejecución del binario /bin/client utilizando el comando ./bin/client 127.0.0.1 8080 y un servidor de prueba en Python, se observó que el comportamiento del payload fue consistente con lo esperado. El cliente estableció una conexión TCP al puerto 8080 y realizó una única solicitud HTTP GET hacia la ruta /status. El servidor respondió correctamente con un código 200 OK y el mensaje "Servicio en línea", tras lo cual el payload procesó la respuesta y finalizó su ejecución sin intentar acciones adicionales.

No se detectaron comportamientos anómalos como persistencia, comandos remotos o exfiltración de datos. La comunicación se mantuvo limpia y estrictamente limitada a la petición HTTP prevista en el diseño del proyecto. Las evidencias incluyen capturas de tráfico y logs asociados al análisis.
## Riesgos identificados y mitigaciones aplicadas
**1. Falla en la creación o conexión del socket:**

Existe la posibilidad de que el socket no se cree correctamente (socket() devuelve < 0) o que la conexión al servidor falle (connect() < 0), por causas como puerto ocupado, servidor no activo o IP incorrecta.
- Impacto: el cliente no podrá comunicarse con el servidor y la ejecución puede terminar sin liberar el descriptor o sin reportar claramente la causa.
- Mitigación aplicada: se implementan verificaciones de error con mensajes en std::cerr que informan al usuario sobre el fallo. El código también cierra el socket al final de la ejecución, reduciendo el riesgo de fugas de recursos. Para robustez adicional, se podría mejorar retornando en cada error crítico o integrando manejo RAII.

**2. Validación insuficiente de entrada (IP y puerto)**

Los parámetros del usuario (ip, port) pueden ser inválidos o estar fuera de rango. Si no se validaran, podría producirse un intento de conexión fallido o comportamiento indefinido.
- Impacto: posibles errores en tiempo de ejecución o conexiones a direcciones no deseadas.
- Mitigación aplicada: se implementaron funciones validarIP() y validarPuerto() para garantizar que las direcciones IP cumplan con el formato IPv4 y que los puertos estén en el rango permitido (1–65535). Si las validaciones fallan, el programa termina de forma segura (exit(1)).

**3. Bloqueo por operaciones de red (socket bloqueante)**

Las llamadas a connect(), send() y recv() son bloqueantes. Si el servidor no responde o la red tiene problemas, el cliente puede quedar esperando indefinidamente.
- Impacto: congelamiento del proceso o tiempos de espera excesivos.
- Mitigación aplicada: se considera un riesgo aceptable para el entorno de laboratorio (localhost), donde la latencia es mínima. Para entornos reales, se recomienda agregar setsockopt() con SO_RCVTIMEO y SO_SNDTIMEO para limitar el tiempo de espera.

**4.Riesgo de lectura incompleta o corrupción de buffer**

El uso de un buffer de tamaño fijo (char buffer[4096]) implica que si el servidor envía más datos, estos se recibirán en varias iteraciones de recv(). Si no se agregara el terminador '\0', podrían imprimirse caracteres no válidos.
- Impacto: salida corrupta o comportamiento indefinido en impresión.
- Mitigación aplicada: el código añade buffer[bytesReceived] = '\0' en cada iteración, asegurando que la cadena esté correctamente terminada y evitando lecturas fuera de rango.

**5.Falta de soporte para IPv6 o DNS**

La conexión está limitada a direcciones IPv4 y requiere que el usuario proporcione la IP explícita.
- Impacto: el cliente no podría probar servidores con nombres de dominio o direcciones IPv6.
- Mitigación aplicada: riesgo documentado y aceptado dado que el objetivo del proyecto es realizar pruebas locales controladas en 127.0.0.1.

**6.Ausencia de cifrado o autenticación**

El payload usa HTTP sin TLS, lo que en un entorno abierto podría exponer información de conexión.
- Impacto: potencial exposición del tráfico si se ejecutara fuera del entorno local.
- Mitigación aplicada: se define que el uso es benigno y local, con comunicación únicamente sobre 127.0.0.1, sin transmisión de datos sensibles, por lo que el riesgo se considera nulo en el contexto de pruebas.

## Trabajo pendiente y plan para la entrega final
- Finalización de reporte del proyecto.
- Elaboración de cumplimiento etico y de seguridad.
- Comprobación de pruebas realizadas en entornos seguros. 
- Elaborar procedimiento de restauración de snapshot.
- Revisión de cumplimiento de todos los entregables del proyecto. 
