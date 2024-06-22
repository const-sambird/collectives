#!/bin/bash
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=2
#SBATCH --mem=1G
#SBATCH --output=gather_long_stdout.txt
#SBATCH --error=gather_long_stderr.txt
#SBATCH --time=00:10:00
#SBATCH --job-name=collective_gather_long
#SBATCH --mail-user=sam.bird@ou.edu
#SBATCH --mail-type=ALL
#SBATCH --chdir=/home/sbird/collectives/tests/gather_long
module load OpenMPI
mpirun gather_long.mpi
