#!/bin/bash

rm -rf ./linked
module load OpenMPI

source ./op_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        mkdir -p ./linked/"$operation"_"$size"
        mpicc -DDATA_SIZES="$DATA_SIZES" -DNUM_DATA_SIZES="$NUM_DATA_SIZES" -DOPERATION="$operation"_"$size" run_timing.c mst_ops.c bkt_ops.c collective_ops.c vec_ops.c builtin_ops.c -o ./linked/"$operation"_"$size"/"$operation"_"$size".mpi
        echo "#!/bin/bash" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --partition=normal"  >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --exclusive" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --nodes=2" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --ntasks=32" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --ntasks-per-node=16" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --mem=16G" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --output=""$operation"_"$size""_stdout.txt" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --error=""$operation"_"$size""_stderr.txt" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --time=01:00:00" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --job-name=collective_""$operation"_"$size" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --mail-user=sam.bird@ou.edu" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --mail-type=ALL" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --chdir=/home/sbird/collectives/linked/""$operation"_"$size" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "module load OpenMPI" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
	echo "mpirun ""$operation"_"$size"".mpi" >> ./linked/"$operation"_"$size"/"$operation"_"$size".sh
    done
done

