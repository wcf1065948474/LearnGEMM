#include <cstdlib>
#include <sys/time.h>
#include <ctime>
#include <iostream>
#include "parameters.hpp"

void copy_matrix(int m, int n, double *a, int lda, double *b, int ldb)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            B(i, j) = A(i, j);
        }
    }
}

void random_matrix(int m, int n, double *a, int lda)
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            A(i, j) = 2.0 * drand48() - 1.0; //[-1.0, 1.0]
        }
    }
}

double compare_matrices(int m, int n, double *a, int lda, double *b, int ldb)
{
    int i, j;
    double max_diff = 0.0, diff;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            diff = abs(A(i, j) - B(i, j));
            max_diff = (diff > max_diff ? diff : max_diff);
        }
    }

    return max_diff;
}

static double gtod_ref_time_sec = 0.0;
double dclock()
{
    double the_time, norm_sec;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    if (gtod_ref_time_sec == 0.0)
        gtod_ref_time_sec = (double)tv.tv_sec;

    norm_sec = (double)tv.tv_sec - gtod_ref_time_sec;

    the_time = norm_sec + tv.tv_usec * 1.0e-6;

    return the_time;
}

int main()
{
    int p, m, n, k, lda, ldb, ldc, rep;
    double dtime, avg_dtime_old, avg_dtime_new, diff;
    double *a, *b, *c, *cref, *cold;

    for (p = PFIRST; p <= PLAST; p += PINC)
    {
        m = (M == -1 ? p : M);
        n = (N == -1 ? p : N);
        k = (K == -1 ? p : K);

        lda = (LDA == -1 ? k : LDA);
        ldb = (LDB == -1 ? n : LDB);
        ldc = (LDC == -1 ? n : LDC);

        a = (double *)malloc(m * lda * sizeof(double));
        b = (double *)malloc(k * ldb * sizeof(double));
        c = (double *)malloc(m * ldc * sizeof(double));
        cold = (double *)malloc(m * ldc * sizeof(double));
        cref = (double *)malloc(m * ldc * sizeof(double));

        /* Generate random matrices A, B, Cold */
        random_matrix(m, k, a, lda);
        random_matrix(k, n, b, ldb);
        random_matrix(m, n, cold, ldc);

        copy_matrix(m, n, cold, ldc, cref, ldc);

        avg_dtime_old = 0.0;
        for (rep = 0; rep < NREPEATS; rep++)
        {
            copy_matrix(m, n, cold, ldc, cref, ldc);
            dtime = dclock();
            OLD_MMult(m, n, k, a, lda, b, ldb, cref, ldc);
            dtime = dclock() - dtime;
            avg_dtime_old += dtime;
        }

        avg_dtime_new = 0.0;
        for (rep = 0; rep < NREPEATS; rep++)
        {
            copy_matrix(m, n, cold, ldc, c, ldc);
            dtime = dclock();
            NEW_MMult(m, n, k, a, lda, b, ldb, c, ldc);
            dtime = dclock() - dtime;
            avg_dtime_new += dtime;
        }

        diff = compare_matrices(m, n, c, ldc, cref, ldc);

        std::cout << m << " " << n << " " << k << " " << avg_dtime_old/NREPEATS << " " << avg_dtime_new/NREPEATS << " " << diff << std::endl;

        free(a);
        free(b);
        free(c);
        free(cold);
        free(cref);
    }
    return 0;
}