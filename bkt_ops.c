#include "bkt_ops.h"
#include "vec_ops.h"
#include "mpi.h"
#include <stdlib.h>

int get_subset_size(int idx, int size, int num_ranks) {
    if (idx + 1 == num_ranks)
        return size - (idx * (size / num_ranks));
    return size / num_ranks;
}

void bkt_allgather(float *vec, int size, int rank, int num_ranks)
{
    int prev = rank - 1;
    if (prev < 0) prev = num_ranks - 1;
    int next = rank + 1;
    if (next == num_ranks) next = 0;

    int current = rank;

    MPI_Request request;
   
    for (int i = 0; i < num_ranks - 1; ++i) {
        MPI_Isend(vec + (current * sizeof(float)), get_subset_size(current, size, num_ranks), MPI_FLOAT, next, 0, MPI_COMM_WORLD, &request);

	current = current - 1;
	if (current < 0) current = num_ranks - 1;
	MPI_Recv(vec + (current * sizeof(float)), get_subset_size(current, size, num_ranks), MPI_FLOAT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Wait(&request, MPI_STATUS_IGNORE);
    }
}

void bkt_reduce_scatter(float *vec, int size, int rank, int num_ranks)
{
    float *tmp = (float*) calloc((size / num_ranks) + 1, sizeof(float));
    int prev = rank - 1;
    if (prev < 0) prev = num_ranks - 1;
    int next = rank + 1;
    if (next == num_ranks) next = 0;

    MPI_Request request;

    int current = next;
    for (int i = num_ranks - 2; i >= 0; --i) {
        MPI_Isend(vec + (current * sizeof(float)), get_subset_size(current, size, num_ranks), MPI_FLOAT, prev, 0, MPI_COMM_WORLD, &request);
	current = current + 1;
	if (current == num_ranks) current = 0;
	MPI_Recv(tmp, get_subset_size(current, size, num_ranks), MPI_FLOAT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	elementwise_add(vec + (current * sizeof(float)), tmp, get_subset_size(current, size, num_ranks));

        MPI_Wait(&request, MPI_STATUS_IGNORE);
    }

    free(tmp);
}

