#include "mpi.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mst_ops.h"
#include "vec_ops.h"
#include "collective_ops.h"

#define DATA_SIZE 1000

int verify_output(int size, float *result)
{
    for (int i = 0; i < size; ++i) {
        if (result[i] != i)
	    return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int my_rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    float *to_bcast = (float*) calloc(DATA_SIZE, sizeof(float));

    if (my_rank == 0)
    	fill_sequences(DATA_SIZE, 0, to_bcast);

    clock_t tic = clock();

    bcast_short(to_bcast, DATA_SIZE, 0, my_rank, num_procs);

    clock_t toc = clock();

    if (verify_output(DATA_SIZE, to_bcast) < 0) {
        printf("--- FAILED in %f seconds", (double) (toc - tic) / CLOCKS_PER_SEC);
    } else {
        printf("--- SUCCESS in %f seconds", (double) (toc - tic) / CLOCKS_PER_SEC);
    }

    MPI_Finalize();

    free(to_bcast);

    return 0;
}

