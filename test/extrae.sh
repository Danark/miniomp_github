export EXTRAE_CONFIG_FILE=./extrae.xml
export LD_PRELOAD=${EXTRAE_HOME}/lib/libseqtrace.so
export EXECUTABLE="./test_loop-omp"
# This is taken by extrae.xml

${EXECUTABLE}
