#!/bin/sh

cd ./build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG -S ../
make
./alloc

