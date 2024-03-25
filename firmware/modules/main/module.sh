#!/usr/bin/bash

# create directory
mkdir -p obj/ || exit 1

# Compile module
#make clean
make -j"$(nproc)" || exit 1
