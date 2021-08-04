#define N 4720 //size of the matrix
#define MAX 27444//no of elements
#define THRESHOLD 2287 //should be a factor of N

void spmvector(float *val, int *row, int *col, float *p, float *p_new);
void pagerank(float val[MAX], int row[MAX], int col[MAX], int csr[N+1],float p[N]);
