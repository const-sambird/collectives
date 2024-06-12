#ifndef _H_TEST_OPS
#define _H_TEST_OPS

void fill_with_invalid(float *arr, int idx_start, int count);

void test_bcast(float *baseline, float *testcase, int data_size, int rank, int num_ranks);
void test_gather(float *baseline, float *testcase, int data_size, int rank, int num_ranks);
void test_scatter(float *baseline, float *testcase, int data_size, int rank, int num_ranks);
void test_reduce(float *baseline, float *testcase, int data_size, int rank, int num_ranks);
void test_allgather(float *baseline, float *testcase, int data_size, int rank, int num_ranks);
void test_reduce_scatter(float *baseline, float *testcase, int data_size, int rank, int num_ranks);
void test_allreduce(float *baseline, float *testcase, int data_size, int rank, int num_ranks);

#endif

