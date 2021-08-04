#include "header.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
using namespace std;
using nano_s = std::chrono::nanoseconds;
float graph[N][N]={0};
float p[N]={0};
float val[MAX];
int row[MAX];
int col[MAX];
int out_link[N]={0};
int csr[N+1]={0};//elements in each row
int main()
{

	int i,j,m=0;
	FILE *fp = fopen("3elt.mtx","r");
	char line[100];
	if((fp = fopen("3elt.mtx","r")) == NULL)
	{
		fprintf(stderr,"[Error] Cannot open the file");
		exit(1);
	}
	int node1, node2;
	while(!feof(fp))
	{
		fscanf(fp,"%d%d", &node1, &node2);
		graph[node1-1][node2-1]=1;
		graph[node2-1][node1-1]=1;
	}
	fclose(fp);

	for (i=0; i<N; i++) //initial pagerank values
	{
		p[i] = 1.0 / N;
	}

	//int k=1;
	for (i=0; i<N; i++) //counting number of outlinks
	{
		for(j=0; j<N; j++)
		{
			if(graph[i][j]!=0)
			{
				out_link[i]++;
			}
		}
	}
	for (i=0; i<N; i++)
	{
	  csr[i]=m;
		/*if (out_link[i] == 0)
		{
			for (j=0; j<N; j++) //initializing the dangling nodes
			{
				graph[i][j] = 1.0 / N;
				val[m]=graph[i][j];
				row[m]=j;
				col[m]=i;
				m++;
			}
		}
		else
		{*/
			for (j=0; j<N; j++) //normalizing the nodes and converting adjacency matrix to COO format
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
		//}
	}
	csr[i]=m;
	auto t1 = std::chrono::steady_clock::now();
	pagerank(val,row,col,csr,p);
	auto t2 = std::chrono::steady_clock::now();
	auto d_nano = std::chrono::duration_cast<nano_s>( t2 - t1 ).count();
	std::cout<<"d_nano:   " << d_nano << "\n";
	float sum=0;
	for (i=0;i<N;i++)
	{
		//printf("%f \n",p[i]);
		sum=sum+p[i];
	}
	printf("Sum=%f \n",sum);
	ofstream a;
	a.open("writepagerank.txt");
	for(i = 0;i<N;i++)
	a<<p[i]<<"\n";
	a.close();
	return 0;
}

void pagerank(float val[MAX], int row[MAX], int col[MAX], int csr[N+1], float p[N])
{
	int i, j, m=0;
	float d=0.85;
	float p_new[N]={0};
	float d_constant=(1.0 - d) / N;
	float val1[THRESHOLD]={0};
	int col1[THRESHOLD]={0};
	int row1[THRESHOLD]={0};
	int partition=0;
	for (m=0; m<1; m++)
	{
	  partition=0;
		pagerank_label1:for (i=0; i<N; i++) //initializing p_new to 0
		{
			p_new[i] = 0.0;
		}
		pagerank_label2:for(j=0;j<2;j++)
		{
		    partitioning1:for(i=0;i<THRESHOLD;i++)
		    {
		        val1[i]=val[i+j*THRESHOLD];
		        row1[i]=row[i+j*THRESHOLD];
		        col1[i]=col[i+j*THRESHOLD];
		        //printf("val=%f, row=%d, col=%d, i=%d, j=%d, THRESHOLD=%d, partition=%d\n",val1[i],row1[i],col1[i],i,j,THRESHOLD,partition);
		    }
		    //printf("\n");
		    spmvector(val1,row1,col1,p,p_new);
		    //printf("partition = %d \n\n", partition);
		    partition++;
		}
		/*if(MAX%THRESHOLD!=0)
		{
		  partitioning2:for(i=0;i<MAX%THRESHOLD;i++)
		  {
		    val1[i]=val[i+j*THRESHOLD];
		    row1[i]=row[i+j*THRESHOLD];
		    col1[i]=col[i+j*THRESHOLD];
		    //printf("val=%f, row=%d, col=%d, i=%d, j=%d, THRESHOLD=%d, partition=%d\n",val1[i],row1[i],col1[i],i,j,THRESHOLD,partition);
		  }
		  //printf("\n");
		  spmvector(val1,row1,col1,MAX%THRESHOLD,p,p_new);
		}*/
		pagerank_label3:for(i=0; i<N; i++) //computing pagerank values with damping factor
		{
		 	p[i] = d * p_new[i] + d_constant;
		}
	}

}
