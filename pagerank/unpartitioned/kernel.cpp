#include <iostream>
#include"header.h"
using namespace std;
void spmvector(float   val[MAX], int row[MAX], int col[MAX],float   p_new[N],float   p[N]);
extern "C++"{
void pagerank(float*graphp, float *pf)
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=16 port=graphp  bundle=input1
#pragma HLS INTERFACE m_axi depth=4 port=pf  bundle=input1
#pragma HLS INTERFACE s_axilite port=graphp
#pragma HLS INTERFACE s_axilite port=pf

	int i, j;
	int m=0;
	float   val[MAX];
	int row[MAX];
	int col[MAX];
	int out_link[N]={0};
	float   damp=(1 - 0.85) / N;
	float graph[N][N];
	float p[N];
	int kk=0;

    memcpy(p,(const float*) pf, N *sizeof(float));
    memcpy(graph,(const float*) graphp, N *N*sizeof(float));



	loop_outlink:for (i=0; i<N; i++) //counting number of outlinks
	{
		pagerank_label1:for(j=0; j<N; j++)
		{
			if(graph[i][j]!=0)
			{
				out_link[i]++;
			}
		}
	}
	pagerank_label0:for (i=0; i<N; i++)
	{
		if (out_link[i] == 0)
		{
			loop_dang:for (j=0; j<N; j++) //initializing the dangling nodes
			{

				graph[i][j] = 1.0 / N;
				val[m]=graph[i][j];
				row[m]=j;
				col[m]=i;
				m++;
			}
		}
		else
		{
			loop_norm:for (j=0; j<N; j++) //normalizing the nodes and converting adjacency matrix to COO format
			{
				if (graph[i][j] != 0)
				{

					graph[i][j] = graph[i][j] / out_link[i];
					val[m]=graph[i][j];
					row[m]=j;
					col[m]=i;
					m++;
				}
			}
		}
	}

	outer_loop:for (m=0; m<20; m++)
	{
		float   p_new[N]= {0};
		spmvector(val,row,col,p_new,p); //SpMV
		loop_add_const:for(i=0; i<N; i++) //computing pagerank values with damping factor
		{
		 	p[i] =( 0.85 * p_new[i] )+ damp;
		}
	}



    memcpy(pf,(const float*) p, N *sizeof(float));
    memcpy(graphp,(const float*) graph, N *N*sizeof(float));

}




void spmvector(float   val[MAX], int row[MAX], int col[MAX],float   p_new[N],float   p[N])
{
	spmvector_label1:for ( int i=0; i<MAX; i++)
	{
		p_new[row[i]] += (val[i] * p[col[i]]);
	}
}
}
