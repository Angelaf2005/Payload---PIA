#!/bin/sh

SRC="./src/client.cpp"
OUT_DIR="./bin"
OUT="$OUT_DIR/client"

# comprobación simple de g++
if ! command -v g++ >/dev/null 2>&1; then
	echo "Error: g++ no está instalado. Instálalo (es requisito del proyecto)."
	exit 1
fi

mkdir -p "$OUT_DIR"

# Version release
echo "Compilando $SRC -> ${OUT}_release_x64"
g++ "$SRC" -o "${OUT}_release_x64" -O2 

# Version debug
echo "Compilando versión debug $SRC -> ${OUT}_debug_x64"
g++ "$SRC" -o "${OUT}_debug_x64" -g

if [ $? -eq 0 ]; then
	echo "Compilación exitosa: " && ls "$OUT_DIR"
else
	echo "Error en la compilación."
	exit 1
fi
