#ifndef _H_SIZES
#define _H_SIZES

int test_bcast_output_size(int input_size, int rank, int root_rid, int num_ranks);
int test_reduce_output_size(int input_size, int rank, int root_rid, int num_ranks);
int test_scatter_output_size(int input_size, int rank, int root_rid, int num_ranks);
int test_gather_output_size(int input_size, int rank, int root_rid, int num_ranks);
int test_allgather_output_size(int input_size, int rank, int root_rid, int num_ranks);
int test_reduce_scatter_output_size(int input_size, int rank, int root_rid, int num_ranks);
int test_allreduce_output_size(int input_size, int rank, int root_rid, int num_ranks);

#endif

