#!/bin/bash

rm /scratch/sbird/linked/"$2"/"$1"/*.txt
sbatch /scratch/sbird/linked/"$2"/"$1"/"$1".sh
echo Rerunning /scratch/sbird/linked/"$2"/"$1"/"$1".sh

