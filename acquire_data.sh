#!/bin/bash

source ./op_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        for (( i = 0 ; i < 30 ; i++)); do
            for (( rank = 0 ; rank < 32 ; rank++ )); do
                cat /home/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size"_rank_"$rank"_run_"$i".csv >> ./results/"$operation"_"$size".csv
                #if [ $? -ne 0 ]; then
                #    break
                #fi
            done
        done
    done
done

