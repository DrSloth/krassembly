#!/bin/bash

for i in ./tests/*; do
    gcc ./src/string_utils.c ./$i -o ./target/test_tmp -std=c99 -O2 -m64 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual \
        -Wstrict-prototypes -Wmissing-prototypes &&
    ./target/test_tmp > /dev/null || exit 1;
done;
