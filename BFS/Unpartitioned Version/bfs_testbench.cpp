#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"bfs_h.h"
using namespace std;
int graph[V+1][V+1]={0};
int *q;
int *visited;
int *row, *col;
int *nzr;
int main()
{
	int i;
	int src = 1;
	q = new int [V];
	visited = new int [V+1];
	row = new int [E];
	col = new int [E];
	nzr = new int [V+2];
	for(i=1;i<V+1;i++)
	{
		visited[i] = 0;
		}
  FILE *fp = fopen("nodes.txt","r");
  char line[100];
  	  if((fp = fopen("nodes.txt","r")) == NULL)
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
  	int m = 0, j;
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
  	 for(i=0;i<E;i++)
  	 {
  		 cout<<row[i]<<" ";
  	 }
  	 cout<<endl;
  	for(i=0;i<E;i++)
  	  	 {
  	  		 cout<<col[i]<<" ";
  	  	 }
  	cout<<endl;
  	cout<<endl;
  	for(i=0;i<V+2;i++)
  	  	  	 {
  	  	  		 cout<<nzr[i]<<" ";
  	  	  	 }
  	cout<<endl;
  	for(i=0;i<V+1;i++)
  	  	  	  	 {
  	  	  	  		 cout<<nzr[i+1]-nzr[i]<<" ";
  	  	  	  	 }

   shortest(col, nzr, visited, q, src);
  cout<<"\n BFS traversal is"<<endl;
	for(i=1;i<V+1;i++)
	{
	  cout<<q[i]<<endl;
	}
	delete [] d, q, visited, row, col, nzr;
	return 0;

}
