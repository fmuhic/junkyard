#!/bin/sh

cd ./build
~/software/cmake/bin/cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../
make
cd ..
