#!/bin/bash

make && gcc -fsanitize=address -g -O0 main.c -L. -lftprintf
