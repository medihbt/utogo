#!/bin/bash

BASE_SRC_DIR=../../src/libunilist
BASE_UDATA_SRC_DIR=../../src/udata
DEBUG_DATA_DIR=../dbg_samples

gcc -g $BASE_SRC_DIR/*.c $BASE_UDATA_SRC_DIR/*.c libunilist_debug.c -o debug-example.elf
echo "Test run:"
./debug-example.elf $DEBUG_DATA_DIR/main.scene