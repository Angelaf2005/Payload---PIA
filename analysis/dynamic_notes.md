### Observaciones del Análisis Dinámico

**Binario Analizado:**  /bin/client 

**Comando Ejecutado:** ./bin/client 127.0.0.1 8080

**Servidor de Prueba:** Servidor Python 3.x, puerto 8080.

**Comportamiento Observado:**
1.  El payload estableció inmediatamente una conexión TCP/IP al puerto 8080.
2.  Se envió una solicitud HTTP con el método GET y la ruta `/status`.
3.  El servidor respondió con el código 200 OK y el cuerpo "Servicio en l¿'09ínea".
4.  El payload procesó la respuesta y terminó su ejecución.

**Comportamiento Anticipado vs. Observado:**
El comportamiento es **el esperado**, cumpliendo con los requisitos del proyuecto: el cliente realiza una única petición GET y no intenta persistencia, ejecución de comandos remotos, o exfiltración de datos. La comunicación de red es limpia y se limita a la solicitud HTTP.

**Evidencias Asociadas:** 
* Capturas de Wireshark y evidencias: [../evidence/dynamic_analysis](../evidence/dynamic_analysis/)
* Logs del cliente: analysis/dynamic_log.txt