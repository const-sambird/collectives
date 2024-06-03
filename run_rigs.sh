#!/bin/bash

source ./op_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        sbatch ./linked/"$operation"_"$size"/"$operation"_"$size".sh
    done
done

echo "scheduled runs!"

