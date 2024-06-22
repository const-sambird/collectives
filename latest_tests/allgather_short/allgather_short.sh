#!/bin/bash
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=2
#SBATCH --mem=1G
#SBATCH --output=allgather_short_stdout.txt
#SBATCH --error=allgather_short_stderr.txt
#SBATCH --time=00:10:00
#SBATCH --job-name=collective_allgather_short
#SBATCH --mail-user=sam.bird@ou.edu
#SBATCH --mail-type=ALL
#SBATCH --chdir=/home/sbird/collectives/tests/allgather_short
module load OpenMPI
mpirun allgather_short.mpi
