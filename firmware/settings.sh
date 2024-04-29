#!/usr/bin/bash

if [ "$0" = "$BASH_SOURCE" ]; then
    echo "Error: Script must be sourced"
    exit 1
fi

printf "Source settings...\n"

# Project name
PROJECT_NAME="movement-control-firmware"

# Toolchain settings
CC="/usr/bin/arm-none-eabi-gcc"
LD="/usr/bin/arm-none-eabi-gcc"

# Compilation and linking settings
DEVICE="STM32F103xB"
CPU="cortex-m3"
MAPFILE="program.map"
LINKERSCRIPT="modules/mcu/STM32F103C8TX_FLASH.ld"
MEMORY_START_ADDR="0x08000000"


# Directory settings
BUILD_DIR="$PROJECT_ROOT"/build
OBJECT_DIR="$BUILD_DIR"/obj
OUTPUT_DIR="$BUILD_DIR"/out

# Debug level and optimalization
OPTIMALIZATION=0

# Modules that are included in a build
# The order goes by descending priority, so the FIRST item has the BIGGEST priority,
# and the LAST item has the LOWEST priority
MODULES=(
    "mcu"
    "FreeRTOS"
    "hal"
    "main"
    "vl53l1"
)

# general compiler options
COMPILER_FLAGS=(
    "-D$DEVICE"            # specify target MCU
    "-Wall"                # enable all warnings
    "-Wextra"
    "-ggdb"                
    "-mcpu=$CPU"           # specify CPU core
    "--specs=nano.specs"   # better newlib implementation (not nosys.specs)
    "-mthumb"              # use thumb instructions
    "-mfloat-abi=soft"     # application binary interface with floating points. 
                           # hard -> compiler using fp instructions,
                           # softfp -> allows fp instructions but maintains compatibility;
    "-ffunction-sections"
    "-fdata-sections"
    "-O0"
)

# Add optimalization and debutg level flags
if [ $OPTIMALIZATION -eq 0 ]; then
    COMPILER_FLAGS+=("-g3") # use maximum amount of info for debugger
    COMPILER_FLAGS+=("-ggdb") # add info for gdb
    COMPILER_FLAGS+=("-O0")
fi

COMPILER_FLAGS+=("-O""$OPTIMALIZATION")
# -O3 -> performance
# -Os -> size

# general linker options
LINKER_FLAGS=(
    "-mcpu=$CPU"           # specify CPU core
    "--specs=nano.specs"   # better newlib implementation (not nosys.specs)
    "-mthumb"              # use thumb instructions
    "-mfloat-abi=soft"     # application binary interface with floating points. 
    "-Wl,-T\"$LINKERSCRIPT\""  # specify linker script
    "-Wl,-Map=$OUTPUT_DIR/$MAPFILE"    # specify .map file
    "-Wl,--gc-sections"    # linker doesnt link dead code
    "-Wl,-lc"
    "-Wl,-lm" # add -l switches and
    "-Wl,-static"              # static linking?
)

LD_FLAGS="${LINKER_FLAGS[@]}"
GCC_FLAGS="${COMPILER_FLAGS[@]}"


# Export necessary build environment settings
export PROJECT_NAME

export BUILD_DIR
export OBJECT_DIR
export OUTPUT_DIR

export MODULES

export CC
export LD

export GCC_FLAGS
export LD_FLAGS

export MEMORY_START_ADDR


