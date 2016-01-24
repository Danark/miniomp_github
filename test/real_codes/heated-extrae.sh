#!/bin/bash

USAGE="\n USAGE: ./pi-extrae.sh num_threads\n
        num_threads -> number of threads\n"

if (test $# -lt 1 || test $# -gt 1 )
then
        echo -e $USAGE
        exit 0
fi

#export LD_PRELOAD=$EXTRAE_HOME/lib/libomptrace.so
export LD_PRELOAD=${EXTRAE_HOME}/lib/libseqtrace.so
export EXTRAE_CONFIG_FILE=./extrae.xml
OMP_NUM_THREADS=$1 ./hated_plate_local-omp 


