#include "mpi.h"
#include "collective_ops.h"
#include "vec_ops.h"
#include "builtin_ops.h"
#include "test_ops.h"
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
#ifndef RUN_INDEX
#define RUN_INDEX 0
    printf("--- WARN: RUN_INDEX not defined. are we not looping? defaulting to 0.\n");
#endif

    int data_sizes[] = { DATA_SIZES };
    double bench_timings[NUM_DATA_SIZES];

    int my_rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    float *input_arr;
    float **output_arr;
    float *dummy_baseline;
    float *res;

    for (int i = 0; i < NUM_DATA_SIZES; ++i) {
        int data_size = data_sizes[i];
        input_arr = (float*) calloc(data_size, sizeof(float));
        res = (float*) calloc(data_size, sizeof(float));
        dummy_baseline = (float*) calloc(data_size, sizeof(float));
        output_arr = &res;

        if (input_arr == NULL || output_arr == NULL) {
            printf("--- FAILED: rank %d couldn't allocate sufficient memory for size %d\n", my_rank, data_size);
            return 1;
        }

        COLLECTIVE(dummy_baseline, input_arr, data_size, my_rank, num_procs);

        MPI_Barrier(MPI_COMM_WORLD);

        double tic = MPI_Wtime();
        int opr = OPERATION(input_arr, output_arr, data_size, 0, my_rank, num_procs);
        double toc = MPI_Wtime();

        bench_timings[i] = toc - tic;
        free(input_arr);
        free(dummy_baseline);
        if (opr == 0)
            free(*output_arr);
    }
 
    MPI_Finalize();

    char filename[50];
    snprintf(filename, 50, STR(OPERATION) "_rank_%d_run_%d.csv", my_rank, RUN_INDEX);
    FILE *outfile = fopen(filename, "w");
    for (int i = 0; i < NUM_DATA_SIZES; ++i) {
        fprintf(outfile, "%d,%f\n", data_sizes[i], bench_timings[i]);
    }
    fclose(outfile);

    printf("--- SUCCESS: rank %d completed all processes\n", my_rank);

    return 0;
}

