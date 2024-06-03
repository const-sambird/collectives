#include "bkt_ops.h"
#include "mpi.h"

void bcast_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    MPI_Bcast(data, size, MPI_FLOAT, root_rid, MPI_COMM_WORLD);
}

void reduce_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    MPI_Reduce(data, data, size, MPI_FLOAT, MPI_SUM, root_rid, MPI_COMM_WORLD);
}

void scatter_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    MPI_Scatter(data, size / num_procs, MPI_FLOAT, data, get_subset_size(rank, size, num_procs), MPI_FLOAT, root_rid, MPI_COMM_WORLD);
}

void gather_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    MPI_Gather(data, get_subset_size(rank, size, num_procs), MPI_FLOAT, data, size / num_procs, MPI_FLOAT, root_rid, MPI_COMM_WORLD);
}

void allgather_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    // TODO
    return;
}

void reduce_scatter_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    // TODO
    return;
}

void allreduce_builtin(float *data, int size, int root_rid, int rank, int num_procs)
{
    // TODO
    return;
}

