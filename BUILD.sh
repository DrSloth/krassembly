#!/bin/sh

set -xe

gcc ./src/string_utils.c ./src/main.c -o ./target/krassembly -std=c99 -O2 -m64 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual \
    -Wstrict-prototypes -Wmissing-prototypes
