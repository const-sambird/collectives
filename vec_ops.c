#include "vec_ops.h"

// a = a + b
void elementwise_add(float *a, float *b, int size)
{
    for (int i = 0; i < size; ++i)
        a[i] = a[i] + b[i];
}

void fill_sequences(int size, int start, float *dst)
{
    for (int i = 0; i < size; ++i)
        dst[i] = (float) (i + start);
}

