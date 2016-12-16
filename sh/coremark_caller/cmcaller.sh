#!/bin/sh
# lightweight script to execute CoreMark benchmark

echo "Caller Skript for CoreMark benchmark:'"

# output all command line options 
numberOfThreads="1"
architectureType=""

cd coremark_v1.0 #enter coremark directory

while getopts ':chkt:x:' OPTION ; do
  case "$OPTION" in
    c) echo "make clean"
       make PORT_DIR=linux64 clean
    ;;
    h) echo "The following commands are provided:"
       echo "-c    ... make clean"
       echo "-k    ... make check"
       echo "-t N  ... Multithread mode: Execute CoreMark with N threads in parallel."
    ;;
    k) echo "make check"
       make PORT_DIR=linux64 check
    ;;
    t) echo "make with $OPTARG threads"
       numberOfThreads=$OPTARG
    ;;
    x) if [ "64" = $OPTARG ]; then
          echo "make on 64-bit architecture" 
          architectureType="64"
       else
          echo make on 32-bit architecture
          architectureType=""
       fi
    ;;
    \?) echo "unknown option: -$OPTARG"
        echo "Try '$0 -h' for more information"
    ;;
    :) echo "Oprion -$OPTARG requires an argument"
    ;; 
  esac
done

make PORT_DIR=linux$architectureType REBUILD=1 XCFLAGS="-DMULTITHREAD=$numberOfThreads -DUSE_PTHREAD"
cp run1.log ../run1_"$numberOfThreads"threads.log
cp run2.log ../run2_"$numberOfThreads"threads.log

cd .. #leave coremark directory
