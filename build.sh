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

echo "Compilando $SRC -> $OUT"
g++ "$SRC" -o "$OUT"

if [ $? -eq 0 ]; then
	echo "Compilación OK: $OUT"
else
	echo "Error en la compilación."
	exit 1
fi
