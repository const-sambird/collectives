#include "bkt_ops.h"
#include "mpi.h"
#include <stdlib.h>

/*
 * COLLECTIVE OPERATIONS
 * (that are MPI builtins)
 *
 * all collectives have the interface
 * int COLLECTIVE_SIZE(float *input, float *output, int size, int root_rid, int rank, int num_procs)
 * > float *input   - the input buffer. may also be utilised as the output buffer
 * < float *output  - a pointer to the output buffer. an array SHOULD be passed here, but
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
 * in this file, all collectives have size 'builtin', meaning they are the operations
 * provided by mpi.h. for collectives optimised for long or short vectors, see
 * collective_ops.c.
 *
 * @author Sam Bird <sam.bird@ou.edu>
 */

int bcast_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    MPI_Bcast(input, size, MPI_FLOAT, root_rid, MPI_COMM_WORLD);
    free(output);
    output = input;
    return 1;
}

int reduce_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    MPI_Reduce(input, output, size, MPI_FLOAT, MPI_SUM, root_rid, MPI_COMM_WORLD);
    return 0;
}

int scatter_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    MPI_Scatter(input, size / num_procs, MPI_FLOAT, output, get_subset_size(rank, size, num_procs), MPI_FLOAT, root_rid, MPI_COMM_WORLD);
    return 0;
}

int gather_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    MPI_Gather(input, get_subset_size(rank, size, num_procs), MPI_FLOAT, output, size / num_procs, MPI_FLOAT, root_rid, MPI_COMM_WORLD);
    return 0;
}

int allgather_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    MPI_Allgather(input, get_subset_size(rank, size, num_procs), MPI_FLOAT, output, size / num_procs, MPI_FLOAT, MPI_COMM_WORLD);
    return 0;
}

int reduce_scatter_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    int recvcounts[num_procs];
    for (int i = 0; i < num_procs; ++i)
        recvcounts[i] = 1;
    MPI_Reduce_scatter(input, output, recvcounts, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    return 0;
}

int allreduce_builtin(float *input, float *output, int size, int root_rid, int rank, int num_procs)
{
    MPI_Allreduce(input, output, get_subset_size(rank, size, num_procs), MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    return 0;
}

