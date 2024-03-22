#!/usr/bin/bash

PROJECT_ROOT=$(dirname "$0")/../
source "$PROJECT_ROOT"/settings.sh

if [ -f "$(OUTPUT_DIR)/program.bin" ] && [ -n "$MEMORY_START_ADDRESS" ]; then 
  st-flash write "$(OUTPUT_DIR)/program.bin" "$(MEMORY_START_ADDRESS)"
fi
