#!/bin/bash

# declare -a OPERATIONS=("bcast" "reduce" "scatter" "gather" "allgather" "allreduce" "reduce_scatter")
# declare -a SIZES=("short" "long" "builtin")
declare -a OPERATIONS=("reduce" "allreduce" "reduce_scatter")
declare -a SIZES=("long")


DATA_SIZE=16
