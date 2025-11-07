# TEST
---
## Test N1 - 06/11/2025
### Entorno de pruebas
- **Sistema operativo:** Debian (Kali Linux 2024.3)
- **Arquitectura:** x86_64 (64-bits)
- **Compilador:** g++ 14.2.0
- **Ruta del binario:** /bin/client
- **Adaptador:** Red interna

### Caso de prueba
- **Descripción:** Verificar funcionamiento minimo del cliente.
- **Compilación:** `g++ client.cpp -o client`
- **Comando ejecutado:** `./client 127.0.0.1 8080`
- **Entrada:** `127.0.0.1, 80`
- **Estado:** Exitoso
- **Resultado:**
```
HTTP/1.0 200 OK
Server: SimpleHTTP/0.6 Python/3.12.6
Date: Fri, 07 Nov 2025 03:00:56 GMT
Content-type: text/plain; charset=utf-8

Servicio en línea  
```

### Evidencias / Resultados
- **Captura 1:** [compilación](/evidence/test_n1/evidence_01_06112025.png)
- **Captura 2:** [ejecución](/evidence/test_n1/evidence_02_06112025.png)
- **Captura 3:** [servidor](/evidence/test_n1/evidence_03_06112025.png)
