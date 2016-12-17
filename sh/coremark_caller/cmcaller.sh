#!/bin/bash
# lightweight script to execute CoreMark benchmark
# CoreMark must be locatet in $coreMarkLocation

echo "Caller Skript for CoreMark benchmark:'"

coreMarkLocation="./coremark_v1.0"
numberOfThreads="1"
architectureType="64"
clean="off"
check="off"
runBench="on"
multiRunModeWithMaxThreads="1";

# ----- Processing options and associated arguments -----
while getopts ':chkl:m:t:' OPTION ; do
  case "$OPTION" in
    c) clean="on"
       runBench="off"
    ;;
    h) echo "The following commands are provided:"
       echo "      ... without options executes benchmark with 1 thread on 64-bit system"
       echo "-c    ... make clean"
       echo "-k    ... make check"
       echo "-l32  ... Execute CoreMark on linux 32-bit system"
       echo "-m N  ... Multi run mode: Execute CoreMark several times from 1 to N threads."
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
    m) multiRunModeWithMaxThreads=$OPTARG
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

executeBench() {
   archType=$1
   nrOfThreads=$2

   echo "RUN COREMARK BENCHMARK!" 
   echo "Architecture type: $archType"
   echo "Number of threads: $nrOfThreads" 

   make PORT_DIR=linux$archType REBUILD=1 XCFLAGS="-DMULTITHREAD=$nrOfThreads -DUSE_PTHREAD"
   if [ "1" = $nrOfThreads ]; then
      cp run1.log ../run1_"$nrOfThreads"thread.log
      cp run2.log ../run2_"$nrOfThreads"thread.log
   else
      cp run1.log ../run1_"$nrOfThreads"threads.log
      cp run2.log ../run2_"$nrOfThreads"threads.log
   fi
}

cd $coreMarkLocation #enter coremark directory

if [ "on" = $runBench ]; then
   if [ "1" = $multiRunModeWithMaxThreads ]; then
      executeBench $architectureType $numberOfThreads
   else
      array=( 1 2 4 6 8 12 16 24 32 48 64 128 )
      for nrOfThreads in ${array[*]}
      do
         if [ $nrOfThreads -le $multiRunModeWithMaxThreads ]; then
            #echo $nrOfThreads
            executeBench $architectureType $nrOfThreads
         fi
      done 
   fi
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
