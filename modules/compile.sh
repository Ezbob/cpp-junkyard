#!/bin/bash

CCXX=clang++
MODPATH="."
SRC_DIR="src"

echo "Compiling application and modules..."

function precompile_mods_to_pcm {
    echo "$CCXX -fmodules-ts --precompile -o $2 $1"
}

function compile_mods {
    echo "$CCXX -fmodules-ts -c $1 -o $2"
}

function compile_exec {
    echo "$CCXX -fmodules-ts -fprebuilt-module-path=$MODPATH $1 $2"
}


pushd $SRC_DIR

echo "Precompiling modules..."
for mod_lib in $(ls *.cppm); do
    filename=${mod_lib%.*}
    echo $(precompile_mods_to_pcm $mod_lib "$filename.pcm")
    $(precompile_mods_to_pcm $mod_lib "$filename.pcm")
done

echo "Creating objects from precompiled modules..."
for mod_lib in $(ls *.pcm); do
    filename=${mod_lib%.*}
    echo $(compile_mods $mod_lib "$filename.o")
    $(compile_mods $mod_lib "$filename.o")
done

echo "Linking and creating executable"
echo compile_exec "$(ls *.o)" "$(ls *.cpp)"
$(compile_exec "$(ls *.o)" "$(ls *.cpp)")

popd

echo "Done."
