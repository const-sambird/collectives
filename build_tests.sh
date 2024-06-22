#!/bin/bash

rm -rf ./tests
module load OpenMPI

source ./test_dispatch_vars.sh

for operation in "${OPERATIONS[@]}"; do
    for size in "${SIZES[@]}"; do
        mkdir -p ./tests/"$operation"_"$size"
        mpicc -DDATA_SIZE="$DATA_SIZE" -DCOLLECTIVE=test_"$operation" -DOPERATION="$operation"_"$size" run_testing.c mst_ops.c bkt_ops.c collective_ops.c vec_ops.c builtin_ops.c test_ops.c sizes.c -o ./tests/"$operation"_"$size"/"$operation"_"$size".mpi
        echo "#!/bin/bash" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --partition=normal"  >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
        #echo "#SBATCH --exclusive" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --nodes=2" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --ntasks=4" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --ntasks-per-node=2" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
        echo "#SBATCH --mem=1G" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --output=""$operation"_"$size""_stdout.txt" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --error=""$operation"_"$size""_stderr.txt" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --time=00:10:00" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --job-name=collective_""$operation"_"$size" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --mail-user=sam.bird@ou.edu" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --mail-type=ALL" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "#SBATCH --chdir=/home/sbird/collectives/tests/""$operation"_"$size" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "module load OpenMPI" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
	echo "mpirun ""$operation"_"$size"".mpi" >> ./tests/"$operation"_"$size"/"$operation"_"$size".sh
    done
done

