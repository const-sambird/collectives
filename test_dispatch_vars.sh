#!/bin/bash

declare -a OPERATIONS=("bcast" "reduce" "scatter" "gather" "allgather" "allreduce" "reduce_scatter")
declare -a SIZES=("short" "long" "builtin")
# declare -a OPERATIONS=("bcast")
# declare -a SIZES=("builtin")

DATA_SIZE=16
