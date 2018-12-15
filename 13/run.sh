#!/bin/bash

#if [ ! -f a.out ]; then
#	gcc a.c
#fi
gcc -g a.c

ROWS=$(wc -l $1 | cut -d ' ' -f 1)
COLS=$(awk '{print length + 1}' $1 | sort -n | tail -1)
./a.out $1 $ROWS $COLS

