#!/bin/bash

rm -rf /scratch/sbird/linked
module load OpenMPI

source ./op_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        for (( i = 0 ; i < 30 ; i++ )); do
            mkdir -p /scratch/sbird/linked/"$i"/"$operation"_"$size"
            mpicc -DDATA_SIZES="$DATA_SIZES" -DNUM_DATA_SIZES="$NUM_DATA_SIZES" -DOPERATION="$operation"_"$size" -DCOLLECTIVE=test_"$operation" -DRUN_INDEX="$i" run_timing.c mst_ops.c bkt_ops.c collective_ops.c vec_ops.c builtin_ops.c test_ops.c -o /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".mpi
            echo "#!/bin/bash" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
            echo "#SBATCH --partition=normal"  >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
            echo "#SBATCH --exclusive" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
            echo "#SBATCH --nodes=8" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
            echo "#SBATCH --ntasks=32" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --ntasks-per-node=4" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
            echo "#SBATCH --mem=16G" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --output=""$operation"_"$size""_stdout.txt" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --error=""$operation"_"$size""_stderr.txt" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --time=00:05:00" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --job-name=""$operation"_"$size"_"$i" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --mail-user=sam.bird@ou.edu" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --mail-type=ALL" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "#SBATCH --chdir=/scratch/sbird/linked/"$i"/""$operation"_"$size" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "module load OpenMPI" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
	    echo "mpirun ""$operation"_"$size"".mpi" >> /scratch/sbird/linked/"$i"/"$operation"_"$size"/"$operation"_"$size".sh
        done
    done
done

