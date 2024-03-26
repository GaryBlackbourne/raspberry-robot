#!/usr/bin/bash

PROJECT_ROOT=$(dirname "$0")/..
source "$PROJECT_ROOT"/settings.sh

if [ -f "$OUTPUT_DIR/program.bin" ] && [ -n "$MEMORY_START_ADDR" ]; then 
  st-flash write "$OUTPUT_DIR/program.bin" "$MEMORY_START_ADDR"
else
  printf "No binary in %s, or memory start address is not set." $OUTPUT_DIR
  exit 1
fi
