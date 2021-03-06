#!/bin/bash

USAGE="\n USAGE: ./run-dim_sequential.sh prog num_threads\n
        prog        -> omp program name\n"

if (test $# -lt 1 || test $# -gt 1)
then
        echo -e $USAGE
        exit 0
fi



prv2dim $1 dim_sequential.dim
translate_to_mpismpss_trace.py -s dim_sequential.dim -d dim_parallel.trf
trf2trf dim_parallel.trf dim_parallel.dim
dimemas_simulation_ncores.py dim_parallel.dim 3
