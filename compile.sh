#!/bin/bash
gcc -Wall -Wextra -Wpedantic -Wformat \
	-g \
	--std=c99 \
	-Isrc \
	$(find . | grep -e '.*\.c$') \
	-o drift \
	-lm \
	-lSDL2 \
	-lGLEW \
	-lGL

