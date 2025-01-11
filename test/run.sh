#!/bin/bash

nasm -f macho64 output.asm -o output.o
ld -o output output.o -macosx_version_min 10.7 -no_pie
chmod +x ./output
arch -x86_64 ./output
rm -f ./output ./output.o