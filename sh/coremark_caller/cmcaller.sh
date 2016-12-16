#!/bin/sh
# lightweight script to execute CoreMark benchmark
# CoreMark must be locatet in $coreMarkLocation

echo "Caller Skript for CoreMark benchmark:'"

# output all command line options
coreMarkLocation="./coremark_v1.0"
numberOfThreads="1"
architectureType="64"
clean="off"
check="off"
runBench="on"

cd $coreMarkLocation #enter coremark directory

while getopts ':chkt:x:' OPTION ; do
  case "$OPTION" in
    c) clean="on"
       runBench="off"
    ;;
    h) echo "The following commands are provided:"
       echo "-c    ... make clean"
       echo "-k    ... make check"
       echo "-l32  ... Execute CoreMark on linux 32-bit system"
       echo "-t N  ... Multithread mode: Execute CoreMark with N threads in parallel."
       runBench="off"
    ;;
    k) check="on"
       runBench="off"
    ;;
    l) if [ "32" = $OPTARG ]; then
          echo "make on 32-bit architecture" 
          architectureType=""
       else
          echo make on 64-bit architecture
          architectureType="64"
       fi
    ;;
    t) echo "make with $OPTARG threads"
       numberOfThreads=$OPTARG
    ;;
    \?) echo "unknown option: -$OPTARG"
        echo "Try '$0 -h' for more information"
        runBench="off"
    ;;
    :) echo "Oprion -$OPTARG requires an argument"
       runbench="off"
    ;; 
  esac
done


if [ "on" = $runBench ]; then
   echo "RUN COREMARK BENCHMARK!" 
   echo "Architecture type: $architectureType"
   echo "Number of threads: $numberOfThreads" 
   make PORT_DIR=linux$architectureType REBUILD=1 XCFLAGS="-DMULTITHREAD=$numberOfThreads -DUSE_PTHREAD"
   cp run1.log ../run1_"$numberOfThreads"threads.log
   cp run2.log ../run2_"$numberOfThreads"threads.log
else
   if [ "on" = $clean ]; then
      echo "make clean:"
      make PORT_DIR=linux$architectureType clean
   fi
   if [ "on" = $check ]; then
      echo "make check:"
      make PORT_DIR=linux$architectureType check
   fi
fi

cd .. #leave coremark directory

