#!/bin/bash

declare -a OPERATIONS=("bcast" "reduce" "scatter" "gather" "allgather" "reduce_scatter" "allreduce")
declare -a SIZES=("short" "long" "builtin")
# declare -a OPERATIONS=("bcast" "reduce" "scatter" "gather" "allgather" "allreduce")
# declare -a OPERATIONS=("reduce" "reduce_scatter" "bcast" "allreduce" "allgather")
# declare -a OPERATIONS=("bcast")
# declare -a SIZES=("short")


#DATA_SIZES="1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648"
#NUM_DATA_SIZES=12

DATA_SIZES="1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728"
NUM_DATA_SIZES=8

# DATA_SIZES="1024, 2048"
# NUM_DATA_SIZES=2

