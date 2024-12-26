#!/bin/bash

# Halts the script if any command returns a non-zero status
set -e

cd ../
SOURCE_DIR=`pwd`
cd -

BOOL_VARS=`cmake -L .. | grep BOOL | cut -d'=' -f1 | cut -d':' -f1`
echo $BOOL_VARS

# Convert the string to an array

VARS=($BOOL_VARS)
# Calculate the number of combinations (2^N, where N is the number of variables)
NUM_VARS=${#VARS[@]}
NUM_COMBINATIONS=$((2**NUM_VARS))

# Iterate through each combination
for ((i=0; i<NUM_COMBINATIONS; i++)); do
    CMAKE_FLAGS=""
    FOLDER_NAME=""
    # Generate the ON/OFF combination for each variable
    for ((j=0; j<NUM_VARS; j++)); do
        if (( (i >> j) & 1 )); then
            CMAKE_FLAGS+="-D${VARS[j]}=ON "
            FOLDER_NAME+="1"
        else
            CMAKE_FLAGS+="-D${VARS[j]}=OFF "
            FOLDER_NAME+="0"
        fi
    done
    
    # Print or run the CMake command
    mkdir -p $FOLDER_NAME
    cd $FOLDER_NAME
    echo "cmake ${SOURCE_DIR} $CMAKE_FLAGS"
    cmake ${SOURCE_DIR} $CMAKE_FLAGS
    # Uncomment the next line to actually run the CMake command
    make -j 40
    cd ..
done