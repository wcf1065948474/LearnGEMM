#include "parameters.hpp"

#if defined(OLD_MMult_1)
#define FUNC_NAME OLD_MMult
#elif defined(NEW_MMult_1)
#define FUNC_NAME NEW_MMult
#endif

void AddDot(int, double *, double *, int, double *);

void FUNC_NAME(int m, int n, int k, double *a, int lda,
               double *b, int ldb,
               double *c, int ldc)
{
    int i, j;

    for (i = 0; i < m; i += 1)
    {
        for (j = 0; j < n; j += 1)
        {
            AddDot(k, &A(i, 0), &B(0, j), ldb, &C(i, j));
        }
    }
}

#define Y(i) y[(i)*incx]

void AddDot(int k, double *x, double *y, int incx, double *gamma)
{
    int p;
    for (p = 0; p < k; p++)
    {
        *gamma += x[p] * Y(p);
    }
}
