#!/bin/bash
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=2
#SBATCH --mem=1G
#SBATCH --output=reduce_short_stdout.txt
#SBATCH --error=reduce_short_stderr.txt
#SBATCH --time=00:10:00
#SBATCH --job-name=collective_reduce_short
#SBATCH --mail-user=sam.bird@ou.edu
#SBATCH --mail-type=ALL
#SBATCH --chdir=/home/sbird/collectives/tests/reduce_short
module load OpenMPI
mpirun reduce_short.mpi
