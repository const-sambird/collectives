#include "mst_ops.h"
#include "bkt_ops.h"
#include "mpi.h"
#include <stdlib.h>

/*
 * COLLECTIVE OPERATIONS
 * (that are not MPI builtins)
 *
 * all collectives have the interface
 * int COLLECTIVE_SIZE(float *input, float **output, int size, int root_rid, int rank, int num_procs)
 * > float *input   - the input buffer. may also be utilised as the output buffer
 * < float **output - a pointer to the output buffer. an array SHOULD be passed here, but
 *                    we may free that array and pass a pointer back to the input array
 *                    (or an offset from the start of the input array)
 * > int size       - the size of the input data
 * > int root_rid   - the rank of the root process
 * > int num_procs  - how many ranks are in this communicator
 * < returns int    - 0 if we used the output array (ie, this is a pointer to a separate
 *                    output array, so it contains memory that needs to be freed). 1 if
 *                    we are simply returning a pointer to the input array (or an offset
 *                    thereof), so it does not need to be freed separately
 *
 * in the naming scheme, COLLECTIVE is the name of a collective (bcast, reduce, gather, scatter,
 * etc) and SIZE is the length it is optimised for (short or long). if SIZE is 'builtin' this is
 * a special case where we use the builtin function from mpi.h (see builtin_ops.c)
 *
 * @author Sam Bird <sam.bird@ou.edu>
 */

int bcast_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_bcast(input, size, rank, root_rid, 0, num_procs - 1);
    free(*output);
    *output = input;
    return 1;
}

int bcast_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_scatter(input, size, rank, root_rid, 0, num_procs - 1);
    bkt_allgather(input, size, rank, num_procs);
    free(*output);
    *output = input;
    return 1;
}

int reduce_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_reduce(input, size, rank, root_rid, 0, num_procs - 1);
    free(*output);
    *output = input;
    return 1;
}

int reduce_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    bkt_reduce_scatter(input, size, rank, num_procs);
    mst_gather(input, size, rank, root_rid, 0, num_procs - 1);
    free(*output);
    *output = input;
    return 1;
}

int scatter_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_scatter(input, size, rank, root_rid, 0, num_procs - 1);
    free(*output);
    *output = input;
    return 1;
}

int scatter_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    // sending individual messages
    if (rank == root_rid) {
        for (int i = 0; i < num_procs; ++i) {
            if (i == rank) continue;
            MPI_Send(input + (i * sizeof(float)), get_subset_size(i, size, num_procs), MPI_FLOAT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(input + (rank * sizeof(float)), get_subset_size(rank, size, num_procs), MPI_FLOAT, root_rid, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    free(*output);
    *output = input + (rank * (size / num_procs) * sizeof(float));
    return 1;
}

int gather_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_gather(input, size, rank, root_rid, 0, num_procs - 1);
    free(*output);
    *output = input;
    return 1;
}

int gather_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    // sending individual messages
    if (rank == root_rid) {                                                                                
        for (int i = 0; i < num_procs; ++i) {                                                              
            if (i == rank) continue;                                                                       
            MPI_Recv(input + (i * sizeof(float)), get_subset_size(i, size, num_procs), MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        }
    } else {                                                                                               
        MPI_Send(input + (rank * sizeof(float)), get_subset_size(rank, size, num_procs), MPI_FLOAT, root_rid, 0, MPI_COMM_WORLD); 
    }

    free(*output);
    *output = input;
    return 1;
}

int allgather_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_gather(input, size, rank, root_rid, 0, num_procs - 1);
    mst_bcast(input, size, rank, root_rid, 0, num_procs - 1);

    free(*output);
    *output = input;
    return 1;
}

int allgather_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    bkt_allgather(input, size, rank, num_procs);

    free(*output);
    *output = input;
    return 1;
}

int reduce_scatter_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_reduce(input, size, rank, root_rid, 0, num_procs - 1);
    mst_scatter(input, size, rank, root_rid, 0, num_procs - 1);

    free(*output);
    *output = input;
    return 1;
}

int reduce_scatter_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    bkt_reduce_scatter(input, size, rank, num_procs);

    free(*output);
    *output = input;
    return 1;
}

int allreduce_short(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    mst_reduce(input, size, rank, root_rid, 0, num_procs - 1);
    mst_bcast(input, size, rank, root_rid, 0, num_procs - 1);

    free(*output);
    *output = input;
    return 1;
}

int allreduce_long(float *input, float **output, int size, int root_rid, int rank, int num_procs)
{
    bkt_reduce_scatter(input, size, rank, num_procs);
    bkt_allgather(input, size, rank, num_procs);

    free(*output);
    *output = input;
    return 1;
}

