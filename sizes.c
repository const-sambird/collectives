#include "sizes.h"

/**
 * SIZE UTILITIES FOR COLLECTIVES
 *
 * some collective operations will reuse input buffers as output
 * buffers, but won't fill their entire capacity. alternatively,
 * in some collective operations, some ranks don't yield any
 * output whatsoever!
 *
 * example 1: scatter
 * for a scatter operation, we might scatter the data [1, 2, 3, 4]
 * to 4 ranks. if rank 0 is the root, rank 3 might have an output
 * [4, x, x, x] - but these last three entries aren't really a part
 * of the output, so we ought to ignore them.
 *
 * example 2: gather
 * for a gather operation, only the root has interesting output--
 * the other ranks are only sending data, they do not receive.
 * we need not concern ourselves with checking for correctness.
 *
 * these functions have the interface
 * int test_COLLECTIVE_output_size(int input_size, int rank, int root_rid, int num_ranks)
 * > int input_size - how many elements the input has, in the largest case
 *                    (consider a broadcast operation - the root might have
 *                    input size 16, but no other ranks have inputs, as they
 *                    only receive. but we'd still pass 16 here)
 * > int rank       - which rank are we?
 * > int root_rid   - which rank is the root? (is it us?)
 * > int num_ranks  - how many ranks total are there?
 * < returns int    - the output size, or 0 if there is no output expected
 *                    from this rank.
 *
 * @author Sam Bird <sam.bird@ou.edu>
 */

int test_bcast_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    return input_size;
}

int test_reduce_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    if (rank == root_rid)
        return input_size / num_ranks;
    return 0;
}

int test_scatter_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    return input_size / num_ranks;
}

int test_gather_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    if (rank == root_rid)
        return input_size;
    return 0;
}

int test_allgather_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    return input_size;
}

int test_reduce_scatter_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    return input_size / num_ranks;
}

int test_allreduce_output_size(int input_size, int rank, int root_rid, int num_ranks)
{
    return input_size / num_ranks;
}

