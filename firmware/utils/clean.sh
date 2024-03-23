#!/usr/bin/bash

PROJECT_ROOT=$(dirname "$0")/../
source "$PROJECT_ROOT"/settings.sh

rm "$OBJECT_DIR/*"
rm "$WOUTPUT_DIR/*"
rm "$MAPFIlE"

