#!/usr/bin/bash

PROJECT_ROOT=$(dirname "$0")/..
source "$PROJECT_ROOT"/settings.sh

for MODULE in "${MODULES[@]}"; do
    if [ -d "$PROJECT_ROOT/modules/$MODULE" ] &&
           [ -d "$PROJECT_ROOT/modules/$MODULE/obj" ] &&
           [ -n "$(ls -A "$PROJECT_ROOT/modules/$MODULE/obj")" ];
    then
        rm "$PROJECT_ROOT/modules/$MODULE/obj"/*
    else
        printf "clean module: %s\n" $MODULE
    fi
done

if [ -n "$(ls -A "$OBJECT_DIR")" ]; then rm "$OBJECT_DIR"/*; else echo "clean obj"; fi
if [ -n "$(ls -A "$OUTPUT_DIR")" ]; then rm "$OUTPUT_DIR"/*; else echo "clean out"; fi
if ! [ -e "$BUILD_DIR/$MAPFILE" ]; then rm "$BUILD_DIR/$MAPFIlE"; else echo "clean map"; fi

echo "$BUILD_DIR/$MAPFILE"

printf "Cleaned\n"

