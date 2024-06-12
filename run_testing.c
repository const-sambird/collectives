#include "mpi.h"
#include "collective_ops.h"
#include "vec_ops.h"
#include "builtin_ops.h"
#include "test_ops.h"
#include <stdio.h>
#include <stdlib.h>

#define STR_(X) #X
#define STR(X) STR_(X)

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

    float *baseline_arr = (float*) calloc(DATA_SIZE, sizeof(float));
    float *testcase_arr = (float*) calloc(DATA_SIZE, sizeof(float));
    float *result_arr = (float*) calloc(DATA_SIZE, sizeof(float));

    fill_with_invalid(result_arr, 0, DATA_SIZE);

    COLLECTIVE(baseline_arr, testcase_arr, DATA_SIZE, my_rank, num_procs);
    int opr = OPERATION(testcase_arr, result_arr, DATA_SIZE, 0, my_rank, num_procs);

    MPI_Finalize();

    print_arr("expected result", my_rank, baseline_arr, DATA_SIZE);
    print_arr("testcase result", my_rank, result_arr, DATA_SIZE);
    
    int num_mismatched = 0;

    for (int i = 0; i < DATA_SIZE; ++i) {
        if (baseline_arr[i] != result_arr[i])
            ++num_mismatched;
    }

    if (num_mismatched > 0) {
        printf("--- FAILED: rank %d had %d incorrect values\n", my_rank, num_mismatched);
    } else {
        printf("--- SUCCESS: rank %d completed without issues\n", my_rank);
    }

    free(baseline_arr);
    free(testcase_arr);
    if (opr == 0)
        free(result_arr);

    return 0;
}
