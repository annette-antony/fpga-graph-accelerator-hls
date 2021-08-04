#include <iostream>
#include <string>
#include"bfs_h.h"
using namespace std;
void shortest(int *col, int *nzr, int *d, int *visited, int *q, int src)
{
#pragma HLS INTERFACE s_axilite port=return bundle=sqrt
#pragma HLS INTERFACE m_axi depth=27444 port=col offset=slave bundle=input
#pragma HLS INTERFACE m_axi depth=4722 port=nzr offset=slave bundle=input
#pragma HLS INTERFACE m_axi depth=4721 port=d offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=4721 port=visited offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=4721 port=q offset=slave bundle=output
#pragma HLS INTERFACE s_axilite port=col
#pragma HLS INTERFACE s_axilite port=nzr
#pragma HLS INTERFACE s_axilite port=d
#pragma HLS INTERFACE s_axilite port=visited
#pragma HLS INTERFACE s_axilite port=q

    int f=0,u, v, x, count,i;
    u = src;
    q[f] = src;

    for (count = 0; count < V ; count++)
    {
    u = q[count];
    visited[u] = 1;
    x = nzr[u+1];
    inner:for(v = nzr[u]; v<x ; v++)
    {
        if (!visited[col[v]] &&  (d[u] + 1 < d[col[v]]))
       {
        f=f+1;
        d[col[v]] = d[u] + 1;
        q[f] = col[v];
        visited[col[v]] = 1;
       }
    }
    }
}
