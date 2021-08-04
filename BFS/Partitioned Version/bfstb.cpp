#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <string.h>
#include<fstream>
#include "bfsh.h"
using namespace std;
using nano_s = std::chrono::nanoseconds;
int graph[V+1][V+1]={0};
int q[V]={0},row[E]={0}, col[E]={0}, nzr[V+2]={0}, visited[V+1]={0};
int main()
{

	int i,j,m=0;
		int start = 8;
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
	    	  		graph[node1][node2]=1;
	    	  		graph[node2][node1]=1;
	    	  	}
	    	  	fclose(fp);
	    	  	//fp = fopen("chesapeake.mtx","r");
	    		//fscanf(fp,"%d%d", &node1, &node2);
	    	  	//row[0]= node2;
	    	  	//fclose(fp);
	    	  	    nzr[0] = 0;
	    	  	    for(int i=1;i<V+1;i++)
	    	  	    {
	    	  	        nzr[i] = m;
	    	  	        for(int j=1;j<V+1;j++)
	    	  	        {
	    	  	            if(graph[i][j]!=0)
	    	  	            {
	    	  	                row[m]=i;
	    	  	                col[m]=j;
	    	  	                m++;
	    	  	            }
	    	  	        }
	    	  	    }
	    	  	    nzr[V+1]=E;

	    auto t1 = std::chrono::steady_clock::now();
        bfs(col,nzr,q,visited,start);
        auto t2 = std::chrono::steady_clock::now();
        auto d_nano = std::chrono::duration_cast<nano_s>( t2 - t1 ).count();
        std::cout<<"\n"<<"d_nano:   " << d_nano << "\n";

        ofstream a;
        a.open("writebfs.txt");
        for(i = 0;i<V;i++)
        a<<q[i]<<"\n";
        a.close();
        return 0;
    }


void bfs(int *col, int *nzr, int *q, int *visited, int src)
{
	int f=0, i, u, x, y, deg, front, sd, count;
	u = src;
	q[f] = src;
	visited[u] = 1;
	int c[maxdeg], qu[maxdeg], vis[maxdeg];
	f++;

	for (count = 0; count < V ; count++)
	    {
	    u = q[count];
	    x = nzr[u];
	    y = nzr[u+1];
	    deg = y-x;

	    int *ptr = &col[x];

	    memcpy(c,ptr,  deg* sizeof(int));
	    global_to_local:for(i=0;i<deg;i++)
	    {
	      vis[i]=visited[c[i]];
	    }

	    front = part(c,qu,vis,u,deg,front);

	    local_to_global:for(i=0;i<deg;i++)
	    {
	      visited[c[i]]=vis[i];
	    }
	    qlocal_to_global:for(i=0;i<front;i++)
	    {
	        q[f+i]=qu[i];
	    }
	    f=f+front;
	    }
}
