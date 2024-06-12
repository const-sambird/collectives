#include "test_ops.h"
#include <stdlib.h>

void fill_arr(float *arr, int idx_start, int count, int val_start)
{
    for (int i = 0; i < count; ++i)
        arr[idx_start + i] = val_start + i;
}

void fill_with_invalid(float *arr, int idx_start, int count)
{
    for (int i = 0; i < count; ++i)
        arr[idx_start + i] = -1;
}

void fill_with_zero(float *arr, int idx_start, int count)
{
    for (int i = 0; i < count; ++i)
        arr[idx_start + i] = 0;
}

void test_bcast(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{
    if (rank == 0) {
        fill_arr(testcase, 0, data_size, 0);
    } else {
        fill_with_invalid(testcase, 0, data_size);
    }

    fill_arr(baseline, 0, data_size, 0);
}

void test_reduce(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{
    fill_with_zero(testcase, 0, data_size);
    fill_arr(testcase, 0, data_size / num_ranks, (data_size / num_ranks) * rank);

    if (rank == 0) {
        fill_with_invalid(baseline, 0, data_size);
	fill_with_zero(baseline, 0, num_ranks);
	for (int i = 0; i < data_size; ++i) {
	    baseline[i % num_ranks] += i;
	}
    } else {
        fill_with_invalid(baseline, 0, data_size);
    }
}

void test_gather(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{
    if (rank == 0) {
        fill_arr(baseline, 0, data_size, 0);
    } else {
        fill_with_invalid(baseline, 0, data_size);
    }

    fill_with_invalid(testcase, 0, data_size);
    fill_arr(testcase, 0, data_size / num_ranks, (data_size / num_ranks) * rank);
}

void test_scatter(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{
    fill_with_invalid(baseline, 0, data_size);
    fill_arr(baseline, 0, data_size / num_ranks, (data_size / num_ranks) * rank);

    if (rank == 0) {
        fill_arr(testcase, 0, data_size, 0);
    } else {
        fill_with_invalid(testcase, 0, data_size);
    }
}

void test_allgather(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{
    fill_arr(baseline, 0, data_size, 0);
    
    fill_with_invalid(testcase, 0, data_size);
    fill_arr(testcase, 0, data_size / num_ranks, (data_size / num_ranks) * rank);
}

void test_reduce_scatter(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{
    fill_with_invalid(testcase, 0, data_size);
    fill_arr(testcase, 0, data_size / num_ranks, (data_size / num_ranks) * rank);

    // call it a kludge. see if i care
    float correct_results[4] = { 24, 28, 32, 36 };
    fill_with_invalid(baseline, 0, data_size);
    baseline[0] = correct_results[rank];
}

void test_allreduce(float *baseline, float *testcase, int data_size, int rank, int num_ranks)
{   
    fill_with_invalid(testcase, 0, data_size); 
    fill_arr(testcase, 0, data_size / num_ranks, (data_size / num_ranks) * rank);
    
    fill_with_invalid(baseline, 0, data_size);
    fill_with_zero(baseline, 0, num_ranks);
    for (int i = 0; i < data_size; ++i) {
        baseline[i % num_ranks] += i;
    }
}
