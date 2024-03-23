#!/usr/bin/bash


# set project root directory
PROJECT_ROOT=$(dirname "$0")/../
export PROJECT_ROOT

# source project and build settings
source "$PROJECT_ROOT"/settings.sh
printf "Settings sourced\n"


# check project configuration
if [ -z "$PROJECT_NAME" ]; then printf "No PROJECT_NAME was set"; exit 1; fi
if [ -z "$CC" ]; then CC="/usr/bin/arm-none-eabi-gcc"; fi
if [ -z "$LD" ]; then CC="/usr/bin/arm-none-eabi-gcc"; fi
if [ -z "$DEVICE" ]; then printf "No DEVICE was set"; exit 1; fi
if [ -z "$CPU" ]; then printf "No CPU was set"; exit 1; fi
if [ -z "$MAPFILE" ]; then printf "No MAPFILE was set"; exit 1; fi
if [ -z "$LINKERSCRIPT" ] || [ "$LINKERSCRIP" = "modules/mcu/<linkerscript>" ]; then printf "No linkerscript was set"; exit 1; fi
if [ -z "$MEMORY_START_ADDR" ]; then printf "No start address was set"; exit 1; fi
if [ -z "$MODULES" ]; then printf "Module list is empty"; exit 1; fi


# Creating build directory if not exists
mkdir -p "$OUTPUT_DIR"
mdkir -p "$OBJECT_DIR"


printf "Start building project %s\n" "$PROJECT_NAME"
printf "Compiling modules...\n"

# compile each module
for MODULE in $MODULES; do
    # if module directory exists, and module contaings a module script then execute
    if [ -d "$PROJECT_ROOT/modules/$MODULE" ] &&  [ -f "$PROJECT_ROOT/modules/$MODULE/module.sh" ]; then
        pushd "$(dirname "$MODULE")" || exit 1
        bash module.sh
        popd || exit 1
    else
        printf "No module was found by the name of %s" "$MODULE"
    fi
done
printf "Compilation finished...\n"

# link all module objects
pushd "$PROJECT_ROOT" || exit 1
printf "Linking object files...\n"
make all
popd || exit 1

printf "Build completed!\n"

