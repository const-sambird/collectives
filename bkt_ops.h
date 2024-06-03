#ifndef _H_BKT_OPS
#define _H_BKT_OPS
void bkt_allgather(float *vec, int size, int rank, int num_ranks);
void bkt_reduce_scatter(float *vec, int size, int rank, int num_ranks);
int get_subset_size(int idx, int size, int max_idx);
#endif

