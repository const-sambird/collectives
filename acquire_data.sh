#!/bin/bash

source ./op_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        for (( i = 0 ; i < 30 ; i++)); do
            for (( rank = 0 ; rank < 32 ; rank++ )); do
                cat /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size"_rank_"$rank"_run_"$i".txt >> ./results/"$operation"_"$size".txt
                if [ $? -ne 0 ]; then
                    break
                fi
            done
        done
    done
done

