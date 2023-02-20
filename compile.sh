#!/bin/bash
gcc -Wall -Wextra -Wpedantic -Wformat \
	-g \
	--std=c99 \
	-Isrc \
	-Ilib/include \
	$(find . | grep -e '.*\.c$') \
	-o drift \
	-lm \
	-lSDL2 \
	-lGL \
	-DGLEW_STATIC

