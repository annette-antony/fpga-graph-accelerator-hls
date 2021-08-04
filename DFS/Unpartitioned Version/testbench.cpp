#include "header.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include <fstream>
#include<string.h>
#include <chrono>
using namespace std;
using nano_s = std::chrono::nanoseconds;
int d[node]={0};
int u[edge];
int v[edge];
int main()
{
	int m=0;
	FILE *fp = fopen("edgelist.txt","r");
	char line[100];
	if((fp = fopen("edgelist.txt","r")) == NULL)
	{
		fprintf(stderr,"[Error] Cannot open the file");
		exit(1);
	}
	int node1, node2;
	while(!feof(fp))
	{
		fscanf(fp,"%d%d", &node1, &node2);
		u[m]=node1;
		v[m]=node2;
		m++;
		v[m]=node1;
		u[m]=node2;
		m++;
	}
	fclose(fp);
	  auto t1 = std::chrono::steady_clock::now();
	  dfs(u,v,d);
	  auto t2 = std::chrono::steady_clock::now();
	  auto d_nano = std::chrono::duration_cast<nano_s>( t2 - t1 ).count();
	  printf("d_nano:  %u \n", d_nano);

	  for(int k=0;k<node;k++)
	  {
	  	printf("%d ",d[k]);
	  }
		ofstream a;
		a.open("writedfs.txt");
		for(int k = 0;k<node;k++)
		a<<d[k]<<"\n";
		a.close();
	return 0;
}
