#ifndef _H_BUILTIN_OPS
#define _H_BUILTIN_OPS
void bcast_builtin(float *data, int size, int root_rid, int rank, int num_procs);
void reduce_builtin(float *data, int size, int root_rid, int rank, int num_procs);
void scatter_builtin(float *data, int size, int root_rid, int rank, int num_procs);
void gather_builtin(float *data, int size, int root_rid, int rank, int num_procs);
void allgather_builtin(float *data, int size, int root_rid, int rank, int num_procs);
void reduce_scatter_builtin(float *data, int size, int root_rid, int rank, int num_procs);
void allreduce_builtin(float *data, int size, int root_rid, int rank, int num_procs);
#endif

