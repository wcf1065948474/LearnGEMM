#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

const int PFIRST = 40;
const int PLAST = 800;
const int PINC = 40;

const int M = -1;
const int N = -1;
const int K = -1;

const int NREPEATS = 2;

const int LDA = -1;
const int LDB = -1;
const int LDC = -1;

#define A(i, j) a[(i)*lda + (j)]
#define B(i, j) b[(i)*ldb + (j)]
#define C(i, j) c[(i)*ldc + (j)]
#define abs(x) ((x) < 0.0 ? -(x) : (x))

void OLD_MMult(int, int, int, double *, int, double *, int, double *, int);
void NEW_MMult(int, int, int, double *, int, double *, int, double *, int);

#endif