#!/bin/bash

#make && gcc main.c -L. -lftprintf
make debug && gcc -g -O0 main.c -L. -lftprintf
#make && gcc -fsanitize=address -g -O0 main.c -L. -lftprintf
