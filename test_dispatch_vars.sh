#!/bin/bash

declare -a OPERATIONS=("bcast" "reduce" "scatter" "gather" "allgather" "reduce_scatter")
# declare -a SIZES=("short" "long" "builtin")
# declare -a OPERATIONS=("reduce_scatter" "allreduce" "allgather")
declare -a SIZES=("builtin")

DATA_SIZE=16
