#!/bin/bash

# This is a script to assemble and link x86 assembly to run on macOS ARM (using Rosetta 2)

nasm -f macho64 -o output.o ../cmake-build-debug/output.asm

clang -arch x86_64 -o output output.o

chmod +x ./output

arch -x86_64 ./output