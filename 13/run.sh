#!/bin/bash

if [ ! -f both.out ]; then
	gcc both.c -O3 -o both.out
fi
#gcc -g a.c

ROWS=$(wc -l $1 | cut -d ' ' -f 1)
COLS=$(awk '{print length + 1}' $1 | sort -n | tail -1)
./both.out $1 $ROWS $COLS

