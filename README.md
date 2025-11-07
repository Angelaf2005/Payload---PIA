# Proyecto PIA — Equipo Trueno

## 🎯 Objetivo
Simular un payload educativo en C++ que realice una petición GET controlada a un servidor interno, sin persistencia ni exfiltración.

## 🖥️ Plataforma objetivo
- Linux
- Arquitectura x64
- Compilador: g++ (C++11 o superior)

## ⚙️ Instrucciones para clonar el repositorio

```bash
git clone https://github.com/Angelaf2005/Payload---PIA.git
```

## Compilación
Desde el directorio del proyecto:
```
g++ ./src/client.cpp -o ./bin/client
```

Usando build.sh:
```
chmod +x build.sh
./build.sh
```

## Ejecución
Desde el directorio donde se guardó el binario:
```
./client 127.0.0.1 8080
```


### Inicio del Servidor de Control (Python)
El servidor se utiliza para simular la respuesta.

Ejecuta el servidor en el puerto 8080 (o el que se defina)
   ```bash
   python3 src/server.py 8080
   ```
El servidor mostrará: "Servidor HTTP escuchando en el puerto 8080..."

## Enlace a TEAM_PLAN
Enlace: [TEAM_PLAN](/submissions/tarea5/TEAM_PLAN.md)