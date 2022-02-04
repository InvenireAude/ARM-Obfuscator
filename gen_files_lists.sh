#!/bin/bash

gen(){

    FILENAME=CMakeLists.${1}.files.txt

    echo "add_library(${1} ${3}" > $FILENAME
    find ${2} -name '*.cpp' >> $FILENAME
    echo ")">>$FILENAME
}

gen ARMOB-Tools src/tools OBJECT
gen ARMOB-Elf   src/elf   OBJECT
gen ARMOB-Asm   src/asm   OBJECT
