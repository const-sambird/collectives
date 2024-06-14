#include "mpi.h"
#include "collective_ops.h"
#include "vec_ops.h"
#include "builtin_ops.h"
#include <stdio.h>
#include <stdlib.h>

#define STR_(X) #X
#define STR(X) STR_(X)

int main(int argc, char **argv)
{
#ifndef OPERATION
    printf("--- FAILED: no collective defined. what do you want to time?\n");
    return 0;
#endif
#ifndef DATA_SIZES
    printf("--- FAILED: no DATA_SIZES list defined. i need one or more data sizes to benchmark\n");
    return 0;
#endif
#ifndef NUM_DATA_SIZES
#define NUM_DATA_SIZES 1
    printf("--- WARN: NUM_DATA_SIZES not provided. only the first size in DATA_SIZES will be benchmarked\n");
#endif

    int data_sizes[] = { DATA_SIZES };
    double bench_timings[NUM_DATA_SIZES];

    int my_rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    float *input_arr;
    float **output_arr;

    for (int i = 0; i < NUM_DATA_SIZES; ++i) {
        int data_size = data_sizes[i];
        input_arr = (float*) calloc(data_size, sizeof(float));
        *output_arr = (float*) calloc(data_size, sizeof(float));

        if (input_arr == NULL || output_arr == NULL) {
            printf("--- FAILED: rank %d couldn't allocate sufficient memory for size %d\n", my_rank, data_size);
            return 1;
        }

        fill_with_invalid(output_arr, 0, data_size);

        if (my_rank == 0)
            fill_sequences(data_size, 0, input_arr);

        MPI_Barrier(MPI_COMM_WORLD);

        double tic = MPI_Wtime();
        int opr = OPERATION(input_arr, output_arr, data_size, 0, my_rank, num_procs);
        double toc = MPI_Wtime();

        bench_timings[i] = toc - tic;
        free(input_arr);
        if (opr == 0)
            free(*output_arr);
    }
 
    MPI_Finalize();

    char filename[30];
    snprintf(filename, 30, STR(OPERATION) "_%d.txt", my_rank);
    FILE *outfile = fopen(filename, "w");
    for (int i = 0; i < NUM_DATA_SIZES; ++i) {
        fprintf(outfile, "%d,%f\n", data_sizes[i], bench_timings[i]);
    }
    fclose(outfile);

    printf("--- SUCCESS: rank %d completed all processes\n", my_rank);

    return 0;
}

