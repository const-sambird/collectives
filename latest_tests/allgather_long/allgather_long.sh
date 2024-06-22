#!/bin/bash
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=2
#SBATCH --mem=1G
#SBATCH --output=allgather_long_stdout.txt
#SBATCH --error=allgather_long_stderr.txt
#SBATCH --time=00:10:00
#SBATCH --job-name=collective_allgather_long
#SBATCH --mail-user=sam.bird@ou.edu
#SBATCH --mail-type=ALL
#SBATCH --chdir=/home/sbird/collectives/tests/allgather_long
module load OpenMPI
mpirun allgather_long.mpi
