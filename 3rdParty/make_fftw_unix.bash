#!/bin/bash

if [ ! -f ./build/lib/libfftw3f.a ]; then
    ./configure --enable-float --prefix=$PWD/build && make && make install
fi
