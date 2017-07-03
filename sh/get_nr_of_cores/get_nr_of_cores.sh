#!/bin/bash
# lightweight script to get number of CPU cores from system

echo "Script to get number of cores from system: $0"

NR_OF_CORES=2
USE_CORES=1

NR_OF_CORES=$(nproc)

# check if calling nproc has successfully worked
if [ "$?" -eq "0" ]; then
    if [ "$NR_OF_CORES" -ge "1" ]; then
        USE_CORES=$[$NR_OF_CORES-1]
    fi
fi

echo "Number of system cores: "$NR_OF_CORES
echo "Use cores: "$USE_CORES

exit 0
