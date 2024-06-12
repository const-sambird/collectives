#ifndef _H_BUILTIN_OPS
#define _H_BUILTIN_OPS
int bcast_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
int reduce_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
int scatter_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
int gather_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
int allgather_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
int reduce_scatter_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
int allreduce_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs);
#endif

