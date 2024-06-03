#!/bin/bash
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --nodes=2
#SBATCH --ntasks=40
#SBATCH --ntasks-per-node=20
#SBATCH --output=mpi_%J_stdout.txt
#SBATCH --error=mpi_%J_stderr.txt
#SBATCH --time=30:00
#SBATCH --job-name=bcast_short
#SBATCH --mail-user=sam.bird@ou.edu
#SBATCH --mail-type=ALL
#SBATCH --chdir=/home/sbird/collectives

module load OpenMPI
mpirun bcast_short.mpi
