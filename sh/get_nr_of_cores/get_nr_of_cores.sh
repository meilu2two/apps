#!/bin/bash
# lightweight script to get number of CPU cores from system and
# decrement by one so that there is always one free core during
# compiling anything

echo "Script to get number of cores from system: $0"

#Function return number of usable cores to complie
get_nr_of_cores_to_compile() {
    #echo "Running function 'get_nr_of_cores_to_compile()'"
    NR_OF_CORES=2
    USE_CORES=1

    NR_OF_CORES=$(nproc)
    #echo "System cores available: $NR_OF_CORES"

    # check if calling nproc has successfully worked
    if [ "$?" -eq "0" ]; then
        if [ "$NR_OF_CORES" -ge "1" ]; then
            USE_CORES=$[NR_OF_CORES-1]
            #echo "Use cores: $USE_CORES"
        fi
    fi

    return $USE_CORES
}

get_nr_of_cores_to_compile
NR_OF_CORES_TO_COMPILE=$?
echo "It's recommended to compile with $NR_OF_CORES_TO_COMPILE cores."
