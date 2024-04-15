#!/usr/bin/bash

PROJECT_ROOT=$(dirname "$0")/..
source "$PROJECT_ROOT"/settings.sh

if [ -f "$OUTPUT_DIR/program.elf" ]; then 
    arm-none-eabi-gdb -ex 'target extended-remote localhost:3333' "$OUTPUT_DIR"/program.elf
else
  printf "No binary in %s." "$OUTPUT_DIR"
  exit 1
fi
