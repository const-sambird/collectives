#include "mst_ops.h"
#include "bkt_ops.h"
#include "mpi.h"

void bcast_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_bcast(data, size, rank, root_rid, 0, num_procs - 1);
}

void bcast_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_scatter(data, size, rank, root_rid, 0, num_procs - 1);
    bkt_allgather(data, size, rank, num_procs);
}

void reduce_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_reduce(data, size, rank, root_rid, 0, num_procs - 1);
}

void reduce_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    bkt_reduce_scatter(data, size, rank, num_procs);
    mst_gather(data, size, rank, root_rid, 0, num_procs - 1);
}

void scatter_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_scatter(data, size, rank, root_rid, 0, num_procs - 1);
}

void scatter_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    // sending individual messages
    if (rank == root_rid) {
        for (int i = 0; i < num_procs; ++i) {
            if (i == rank) continue;
            MPI_Send(data + (i * sizeof(float)), get_subset_size(i, size, num_procs), MPI_FLOAT, i, rank, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(data + (rank * sizeof(float)), get_subset_size(rank, size, num_procs), MPI_FLOAT, root_rid, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void gather_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_gather(data, size, rank, root_rid, 0, num_procs - 1);
}

void gather_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    // sending individual messages
    if (rank == root_rid) {                                                                                
        for (int i = 0; i < num_procs; ++i) {                                                              
            if (i == rank) continue;                                                                       
            MPI_Recv(data + (i * sizeof(float)), get_subset_size(i, size, num_procs), MPI_FLOAT, i, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        }
    } else {                                                                                               
        MPI_Send(data + (rank * sizeof(float)), get_subset_size(rank, size, num_procs), MPI_FLOAT, root_rid, rank, MPI_COMM_WORLD); 
    }
}

void allgather_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_gather(data, size, rank, root_rid, 0, num_procs - 1);
    mst_bcast(data, size, rank, root_rid, 0, num_procs - 1);
}

void allgather_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    bkt_allgather(data, size, rank, num_procs);
}

void reduce_scatter_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_reduce(data, size, rank, root_rid, 0, num_procs - 1);
    mst_scatter(data, size, rank, root_rid, 0, num_procs - 1);
}

void reduce_scatter_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    bkt_reduce_scatter(data, size, rank, num_procs);
}

void allreduce_short(float *data, int size, int root_rid, int rank, int num_procs)
{
    mst_reduce(data, size, rank, root_rid, 0, num_procs - 1);
    mst_bcast(data, size, rank, root_rid, 0, num_procs - 1);
}

void allreduce_long(float *data, int size, int root_rid, int rank, int num_procs)
{
    bkt_reduce_scatter(data, size, rank, num_procs);
    bkt_allgather(data, size, rank, num_procs);
}

