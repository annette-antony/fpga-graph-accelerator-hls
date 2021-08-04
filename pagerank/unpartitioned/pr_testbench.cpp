#include <iostream>
#include <stdlib.h>
#include"pr_h.h"
#include <chrono>
using namespace std;
using nano_s = std::chrono::nanoseconds;


int main()
{

	//double p[N]={0};
	float p[N];
	int i,j;
	//double graph[N][N]={{0,1,1,0},{0,0,0,1},{1,1,0,1},{0,0,1,0}};
	for (i=0; i<N; i++) //initial pagerank values
	{
		p[i] = 1.0 / N;
	}

	float  graph[N][N]={{0,1,1,0},{0,0,0,1},{1,1,0,1},{0,0,1,0}};;
    float graph1[N*N];
    int kk=0;
    for(int ii=0; ii<N;ii++)
    {
        for(int jj=0; jj<N;jj++)
        {

        graph1[kk]=graph[ii][jj];
        kk++;
        }
    }
    auto t1 = std::chrono::steady_clock::now();
	pagerank(graph1,p);
    auto t2 = std::chrono::steady_clock::now();
    auto d_nano = std::chrono::duration_cast<nano_s>( t2 - t1 ).count();
    std::cout<<"d_nano:   " << d_nano << "\n";



	 for(int ii=0; ii<N;ii++)
	    {
	        for(int jj=0; jj<N;jj++)
	        {

	        graph[ii][jj]=graph1[kk];
	        kk++;
	        }
	    }




	for ( i=0;i<N;i++)
	{
		for (j=0;j<N;j++)
		{
			std::cout<<"Graph"<<"["<<i<<"]"<<"["<<j<<"]"<<"="<<graph[i][j]<<"\n";

		}
	}



	for ( i=0;i<N;i++)
	{
		std::cout<<"value of p for "<<i<<" is ="<<p[i]<<"\n";
	}

	float  sum=0;


	for ( i=0;i<N;i++)
	{
		std::cout<<"value of p for "<<i<<" is ="<<p[i]<<"\n";
		sum=sum+p[i];
	}

	std::cout<<"value of SUM is ="<<sum<<"\n";




	return 0;
}
