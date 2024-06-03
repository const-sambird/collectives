#ifndef _H_MST_OPS
#define _H_MST_OPS
void mst_bcast(float *vec, int size, int rank, int root, int left, int right);
void mst_reduce(float *vec, int size, int rank, int root, int left, int right);
void mst_scatter(float *vec, int size, int rank, int root, int left, int right);
void mst_gather(float *vec, int size, int rank, int root, int left, int right);
#endif

