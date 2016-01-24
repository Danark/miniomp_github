#!/bin/bash

USAGE="\n USAGE: ./pi-extrae.sh precision num_threads\n
        precision   -> number of decimals\n
        num_threads -> number of threads\n"

if (test $# -lt 2 || test $# -gt 2 )
then
        echo -e $USAGE
        exit 0
fi

#export LD_PRELOAD=$EXTRAE_HOME/lib/libomptrace.so
export LD_PRELOAD=${EXTRAE_HOME}/lib/libseqtrace.so
export EXTRAE_CONFIG_FILE=./extrae.xml
OMP_NUM_THREADS=$2 ./pi2-omp $1


