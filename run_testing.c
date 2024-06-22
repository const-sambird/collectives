#include "mpi.h"
#include "collective_ops.h"
#include "vec_ops.h"
#include "builtin_ops.h"
#include "test_ops.h"
#include "sizes.h"
#include <stdio.h>
#include <stdlib.h>

#define STR_(X) #X
#define STR(X) STR_(X)

#define OUTSIZE_(X) X ## _output_size
#define OUTSIZE(X) OUTSIZE_(X)

void print_arr(char *name, int rank, float *arr, int len)
{
    printf("%s for rank %d : [ ", name, rank);
    for (int i = 0; i < len; ++i) {
        if (arr[i] == -1) {
	    printf("        x,");
	} else {
	    printf(" %f,", arr[i]);
	}
    }

    printf(" ]\n");
}

int main(int argc, char **argv)
{
#ifndef COLLECTIVE
    printf("--- FAILED: no collective defined. what do you want to test?\n");
    return 0;
#endif
#ifndef OPERATION
    printf("--- FAILED: please pass the name of the function to call (see collective_ops.h)\n");
    return 0;
#endif
#ifndef DATA_SIZE
#define DATA_SIZE 16
    printf("--- INFO: using default DATA_SIZE of 16 as no alternative was specified\n");
#endif

    int my_rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int outsize = OUTSIZE(COLLECTIVE)(DATA_SIZE, my_rank, 0, num_procs);

    float *baseline_arr = (float*) calloc(DATA_SIZE, sizeof(float));
    float *testcase_arr = (float*) calloc(DATA_SIZE, sizeof(float));
    float *res = (float*) calloc(DATA_SIZE, sizeof(float));
    float **result_arr = &res;

    fill_with_invalid(*result_arr, 0, DATA_SIZE);

    COLLECTIVE(baseline_arr, testcase_arr, DATA_SIZE, my_rank, num_procs);
    int opr = OPERATION(testcase_arr, result_arr, DATA_SIZE, 0, my_rank, num_procs);

    MPI_Finalize();

    if (outsize > 0) {    
        int num_mismatched = 0;

        for (int i = 0; i < outsize; ++i) {
            if (baseline_arr[i] != (*result_arr)[i])
                ++num_mismatched;
        }

        print_arr("expected result", my_rank, baseline_arr, outsize); 

        if (num_mismatched > 0) {
            print_arr("testcase result", my_rank, *result_arr, DATA_SIZE);
            printf("--- FAILED: rank %d had %d incorrect values\n", my_rank, num_mismatched);
        } else {
            print_arr("testcase result", my_rank, *result_arr, outsize);
            printf("--- SUCCESS: rank %d completed without issues\n", my_rank);
        }
    } else {
        printf("-- PASS: rank %d has no output for collective %s\n", my_rank, STR(COLLECTIVE));
    }

    printf("rank %d attempting to free baseline arr at %p\n", my_rank, (void*) baseline_arr);
    free(baseline_arr);
    printf("rank %d attempting to free testcase arr at %p\n", my_rank, (void*) testcase_arr);
    free(testcase_arr);
    if (opr == 0) {
        printf("rank %d attempting to free result arr at %p\n", my_rank, (void*) *result_arr);
        free(*result_arr);
    }

    return 0;
}

