#ifndef _H_COLLECTIVE_OPS
#define _H_COLLECTIVE_OPS
void bcast_short(float *data, int size, int root_rid, int rank, int num_procs);
void bcast_long(float *data, int size, int root_rid, int rank, int num_procs);
void reduce_short(float *data, int size, int root_rid, int rank, int num_procs);
void reduce_long(float *data, int size, int root_rid, int rank, int num_procs);
void scatter_short(float *data, int size, int root_rid, int rank, int num_procs);
void scatter_long(float *data, int size, int root_rid, int rank, int num_procs);
void gather_short(float *data, int size, int root_rid, int rank, int num_procs);
void gather_long(float *data, int size, int root_rid, int rank, int num_procs);
void allgather_short(float *data, int size, int root_rid, int rank, int num_procs);
void allgather_long(float *data, int size, int root_rid, int rank, int num_procs);
void reduce_scatter_short(float *data, int size, int root_rid, int rank, int num_procs);
void reduce_scatter_long(float *data, int size, int root_rid, int rank, int num_procs);
void allreduce_short(float *data, int size, int root_rid, int rank, int num_procs);
void allreduce_long(float *data, int size, int root_rid, int rank, int num_procs);
#endif

