#!/bin/bash

if [ -z "$ASSIGNMENT3_ROOT" ]
then
    echo "ASSIGNMENT3_ROOT is not set"
    exit 1
fi

export CG_Project_ROOT=$ASSIGNMENT3_ROOT/CG_Project && \

# Generate build script
cd $CG_Project_ROOT && \
if [ ! -d build ]; then
    mkdir build
fi
cd build && \
cmake ../ -DCMAKE_INSTALL_PREFIX=$CG_Project_ROOT && \

# Build and install the program
make -j4 && \
make install && \

# Run the program
cd ../bin && \
./CG_Project
