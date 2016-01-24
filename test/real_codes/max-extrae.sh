#!/bin/bash

USAGE="\n USAGE: ./pi-extrae.sh precision num_threads\n
        precision   -> number of decimals\n
        num_threads -> number of threads\n"



#export LD_PRELOAD=$EXTRAE_HOME/lib/libomptrace.so
export LD_PRELOAD=${EXTRAE_HOME}/lib/libseqtrace.so
export EXTRAE_CONFIG_FILE=./extrae.xml
OMP_NUM_THREADS=$2 ./max-omp $1 $2 $3


