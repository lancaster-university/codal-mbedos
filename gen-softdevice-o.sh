#!/bin/sh

f=_$(basename "$1" | sed -e 's/\./_/g')
srec_cat -Output softdevice.c -C-Array $f -PREfix '__attribute__((section(".softdevice"))) __attribute__((used))' $1 -Intel
arm-none-eabi-gcc -s -c softdevice.c
