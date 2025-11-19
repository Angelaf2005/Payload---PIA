# Proyecto PIA — Equipo Trueno

## 🎯 Objetivo
Simular un payload educativo en C++ que realice una petición GET controlada a un servidor interno, sin persistencia ni exfiltración.

## 🖥️ Plataforma objetivo
- Linux
- Arquitectura x64
- Compilador: g++ (C++11 o superior)
- Intérprete: Python 3.x

## ⚙️ Instrucciones para clonar el repositorio

```bash
git clone https://github.com/Angelaf2005/Payload---PIA.git
```

## Compilación

**Manera recomendada:** El proyecto incluye un script de automatización para generar los binarios necesarios. 

Usando build.sh:
```bash
chmod +x build.sh
./build.sh
```

**Manera manual:** Desde el directorio del proyecto:
```bash
g++ ./src/client.cpp -o ./bin/client -O2
```

### Inicio del Servidor de Control (Python)
El servidor se utiliza para simular la respuesta.

Ejecuta el servidor en el puerto 8080 (o el que se defina)
   ```bash
   python3 src/server/server.py 8080
   ```
El servidor mostrará: "Servidor HTTP escuchando en el puerto 8080..."

## Ejecución

```bash
./bin/client_release_x64 127.0.0.1 8080
```

## Ejemplo de Respuesta
```bash
HTTP/1.0 200 OK
Server: SimpleHTTP/0.6 Python/3.10.12
Date: Wed, 19 Nov 2025 00:40:22 GMT
Content-type: text/plain; charset=utf-8

Servicio en línea
```


## Enlace a TEAM_PLAN
Enlace: [TEAM_PLAN](/submissions/tarea5/TEAM_PLAN.md)