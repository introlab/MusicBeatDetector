#!/bin/bash

if [ ! -f ./libopenblas.a ]; then
    make USE_THREAD=0
fi
