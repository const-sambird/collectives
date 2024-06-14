#ifndef _H_COLLECTIVE_OPS
#define _H_COLLECTIVE_OPS
int bcast_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int bcast_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int reduce_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int reduce_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int scatter_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int scatter_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int gather_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int gather_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int allgather_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int allgather_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int reduce_scatter_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int reduce_scatter_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int allreduce_short(float *input, float **output, int size, int root_rid, int rank, int num_procs);
int allreduce_long(float *input, float **output, int size, int root_rid, int rank, int num_procs);
#endif

