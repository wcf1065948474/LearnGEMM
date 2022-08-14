#include "parameters.hpp"

#if defined(OLD_MMult_0)
#define FUNC_NAME OLD_MMult
#elif defined(NEW_MMult_0)
#define FUNC_NAME NEW_MMult
#endif

void FUNC_NAME(int m, int n, int k, double *a, int lda,
               double *b, int ldb,
               double *c, int ldc)
{
    int i, j, p;

    for (j = 0; j < n; j++)
    {
        for (i = 0; i < m; i++)
        {
            for (p = 0; p < k; p++)
            {
                C(i, j) = C(i, j) + A(i, p) * B(p, j);
            }
        }
    }
}
