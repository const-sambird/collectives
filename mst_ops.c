#include "mst_ops.h"
#include "vec_ops.h"
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

void mst_bcast(float *vec, int size, int rank, int root, int left, int right)
{
    if (left == right) return;
    int mid = (left + right) / 2;
    int dest;

    if (root <= mid) {
        dest = right;
    } else {
        dest = left;
    }

    if (rank == root)
        MPI_Send(vec, size, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);

    if (rank == dest)
        MPI_Recv(vec, size, MPI_FLOAT, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


    if (rank <= mid && root <= mid) {
        mst_bcast(vec, size, rank, root, left, mid);
    } else if (rank <= mid && root > mid) {
        mst_bcast(vec, size, rank, dest, left, mid);
    } else if (rank > mid && root <= mid) {
        mst_bcast(vec, size, rank, dest, mid + 1, right);
    } else if (rank > mid && root > mid) {
        mst_bcast(vec, size, rank, root, mid + 1, right);
    }
}

void mst_reduce(float *vec, int size, int rank, int root, int left, int right)
{
    if (left == right) return;
    int mid = (left + right) / 2;
    int src;

    if (root <= mid) {
        src = right;
    } else {
        src = left;
    }

    if (rank <= mid && root <= mid) {
        mst_reduce(vec, size, rank, root, left, mid);
    } else if (rank <= mid && root > mid) {
        mst_reduce(vec, size, rank, src, left, mid);
    } else if (rank > mid && root <= mid) {
        mst_reduce(vec, size, rank, src, mid + 1, right);
    } else if (rank > mid && root > mid) {
        mst_reduce(vec, size, rank, root, mid + 1, right);
    }

    if (rank == src)
        MPI_Send(vec, size, MPI_FLOAT, root, 0, MPI_COMM_WORLD);
    if (rank == root) {
        float *tmp = (float*) malloc(size * sizeof(float));
        MPI_Recv(tmp, size, MPI_FLOAT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        elementwise_add(vec, tmp, size);
        free(tmp);
    }
}

// TEMPORARY
void tmp_print_arr(char *name, int rank, float *arr, int len)
{   
    printf("%s for rank %d : [ ", name, rank);
    for (int i = 0; i < len; ++i) {
        if (arr[i] == -1) {
            printf("        x,");
        } else {
            printf(" %f,", arr[i]);
        }
    }   
    
    printf(" ]\n");
}

void mst_scatter(float *vec, int size, int rank, int root, int left, int right)
{
    if (left == right) return;
    int mid = (left + right) / 2;
    int dest;

    if (root <= mid) {
        dest = right;
    } else {
        dest = left;
    }

    if (root <= mid) {
        if (rank == root) { 
            printf("rank %d sending to %d from offset %d a total of %d elements: left %d, mid %d, right %d\n", rank, dest, ((mid + 1) * size), (right - (mid + 1) + 1) * size, left, mid, right);
            tmp_print_arr("data sending", rank, vec + ((mid + 1) * size), (right - (mid + 1) + 1) * size);
            MPI_Send(vec + ((mid + 1) * size), (right - (mid + 1) + 1) * size, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
        }
        if (rank == dest) {
            printf("rank %d receiving from %d into offset %d a total of %d elements: left %d, mid %d, right %d\n", rank, root, ((mid + 1) * size), (right - (mid + 1) + 1) * size, left, mid, right);
            MPI_Recv(vec + ((mid + 1) * size), (right - (mid + 1) + 1) * size, MPI_FLOAT, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else {
        if (rank == root) {
            printf("rank %d sending to %d from offset %d a total of %d elements: left %d, mid %d, right %d\n", rank, dest, 0, (mid - left + 1) * size, left, mid, right);
            tmp_print_arr("data sending", rank, vec + (left * size), (mid - left + 1) * size);
            MPI_Send(vec + (left * size), (mid - left + 1) * size, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
        }
        if (rank == dest) {
            printf("rank %d receiving from %d into offset %d a total of %d elements: left %d, mid %d, right %d\n", rank, root, 0, (mid - left + 1) * size, left, mid, right);
            MPI_Recv(vec + (left * size), (mid - left + 1) * size, MPI_FLOAT, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rank <= mid && root <= mid) {
        mst_scatter(vec, size, rank, root, left, mid);
    } else if (rank <= mid && root > mid) {
        mst_scatter(vec, size, rank, dest, left, mid);
    } else if (rank > mid && root <= mid) { 
        mst_scatter(vec, size, rank, dest, mid + 1, right);
    } else if (rank > mid && root > mid) {
        mst_scatter(vec, size, rank, root, mid + 1, right);
    }
}

void mst_gather(float *vec, int size, int rank, int root, int left, int right)
{
    if (left == right) return;
    int mid = (left + right) / 2;
    int src;

    if (root <= mid) {
        src = right;
    } else {
        src = left;
    }

    if (rank <= mid && root <= mid) {
        mst_gather(vec, size, rank, root, left, mid);
    } else if (rank <= mid && root > mid) {
        mst_gather(vec, size, rank, src, left, mid);
    } else if (rank > mid && root <= mid) {
        mst_gather(vec, size, rank, src, mid + 1, right);
    } else if (rank > mid && root > mid) {
        mst_gather(vec, size, rank, root, mid + 1, right);
    }

    if (root <= mid) {
        if (rank == src) {
            tmp_print_arr("data sending", rank, vec + ((mid + 1) * size), (right - (mid + 1) + 1) * size);
            MPI_Send(vec + ((mid + 1) * size), (right - (mid + 1) + 1) * size, MPI_FLOAT, root, 0, MPI_COMM_WORLD);
        }
        if (rank == root)
            MPI_Recv(vec + ((mid + 1) * size), (right - (mid + 1) + 1) * size, MPI_FLOAT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        if (rank == src) {
            tmp_print_arr("data sending", rank, vec + (left * size), (mid - left + 1) * size);
            MPI_Send(vec + (left * size), (mid - left + 1) * size, MPI_FLOAT, root, 0, MPI_COMM_WORLD);
        }
        if (rank == root)
            MPI_Recv(vec + (left * size), (mid - left + 1) * size, MPI_FLOAT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

