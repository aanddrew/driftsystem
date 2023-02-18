#!/bin/bash
gcc -Wall -Wextra -Wpedantic \
	--std=c99 \
	-Isrc \
	$(find . | grep -e '.*\.c$') \
	-o drift \
	-lm \
	-lSDL2 
