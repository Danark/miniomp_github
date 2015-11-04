prv2dim test_loop-omp.prv dim_sequential.dim
translate_to_mpismpss_trace.py -s dim_sequential.dim -d dim_parallel.trf
trf2trf dim_parallel.trf dim_parallel.dim
dimemas_simulation_ncores.py dim_parallel.dim 3

