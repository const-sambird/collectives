#!/bin/bash

declare -a OPERATIONS=("bcast" "reduce" "scatter" "gather" "allgather" "reduce_scatter" "allreduce")
declare -a SIZES=("short" "long" "builtin")
# declare -a OPERATIONS=("reduce" "reduce_scatter" "bcast" "allreduce" "allgather")
# declare -a SIZES=("long")

DATA_SIZES="1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728"
NUM_DATA_SIZES=8

# DATA_SIZES="1024, 2048"
# NUM_DATA_SIZES=2

