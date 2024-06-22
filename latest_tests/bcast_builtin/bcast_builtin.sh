#!/bin/bash
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=2
#SBATCH --mem=1G
#SBATCH --output=bcast_builtin_stdout.txt
#SBATCH --error=bcast_builtin_stderr.txt
#SBATCH --time=00:10:00
#SBATCH --job-name=collective_bcast_builtin
#SBATCH --mail-user=sam.bird@ou.edu
#SBATCH --mail-type=ALL
#SBATCH --chdir=/home/sbird/collectives/tests/bcast_builtin
module load OpenMPI
mpirun bcast_builtin.mpi