#!/bin/bash

source ./op_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        for (( i = 0 ; i < 30 ; i++)); do
            sbatch /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
        done
    done
done

echo "scheduled runs!"

