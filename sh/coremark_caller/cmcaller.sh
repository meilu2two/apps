#!/bin/sh
# lightweight script to execute CoreMark benchmark
# CoreMark must be locatet in $coreMarkLocation

echo "Caller Skript for CoreMark benchmark:'"

coreMarkLocation="./coremark_v1.0"
numberOfThreads="1"
architectureType="64"
clean="off"
check="off"
runBench="on"

# ----- Processing options and associated arguments -----
while getopts ':chkl:t:' OPTION ; do
  case "$OPTION" in
    c) clean="on"
       runBench="off"
    ;;
    h) echo "The following commands are provided:"
       echo "      ... without options executes benchmark with 1 thread on 64-bit system"
       echo "-c    ... make clean"
       echo "-k    ... make check"
       echo "-l32  ... Execute CoreMark on linux 32-bit system"
       echo "-t N  ... Multithread mode: Execute CoreMark with N threads in parallel."
       exit 1
    ;;
    k) check="on"
       runBench="off"
    ;;
    l) if [ "32" = $OPTARG ]; then
          architectureType=""
       else
          architectureType="64"
       fi
    ;;
    t) numberOfThreads=$OPTARG
    ;;
    \?) echo "unknown option: -$OPTARG"
        echo "Try '$0 -h' for more information"
        exit 2
    ;;
    :) echo "Oprion -$OPTARG requires an argument"
       exit 3
    ;; 
  esac
done
# ----- Processing end -----

# ***** Executing Benchmark *****
cd $coreMarkLocation #enter coremark directory

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
# ***** Executing end *****

exit 0
