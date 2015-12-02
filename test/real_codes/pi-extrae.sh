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
OMP_NUM_THREADS=$2 ./pi-omp $1

prv2dim pi-omp.prv dim_sequential.dim
translate_to_mpismpss_trace.py -s dim_sequential.dim -d dim_parallel.trf
trf2trf dim_parallel.trf dim_parallel.dim
dimemas_simulation_ncores.py dim_parallel.dim $2
