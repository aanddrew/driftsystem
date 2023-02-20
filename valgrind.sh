#!/bin/bash
valgrind --leak-check=full --suppressions=./sdl_valgrind_supp.supp ./drift "$@"
