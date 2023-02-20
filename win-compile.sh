#!/bin/bash
gcc -Wall -Wextra -Wpedantic -Wformat \
	-g \
	--std=c99 \
	-Isrc \
	-Ilibs/include \
	-Llibs \
	$(find . | grep -e '.*\.c$') \
	-o build/windows/drift.exe \
	-lm \
	-lSDL2 \
	-lopengl32 \
	-DGLEW_STATIC \
	-DSDL_MAIN_HANDLED

mkdir -p build/windows
cp libs/SDL2.dll build/windows/
cp -r assets build/windows