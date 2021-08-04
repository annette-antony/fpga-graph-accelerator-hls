#include "header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void dfs(int u[edge],int v[edge],int d[node])
{
	int top=-1;
	int top1=-1;
	int visited[node]={0};
	int stack[edge];
	int s=u[0];
	stack[++top] = s;

	  for(int j=0;j<=node;j++){
	    s = stack[top--];
	    if(visited[s]==0)
	           {
	    visited[s] = 1;
	            d[++top1]=s;

	           }
	        for(int i=edge-1;i>=0;i--)
	        {
	            if((u[i] == s) && (visited[v[i]] == 0)&&(!v[j]==0)){
	                stack[++top] = v[i];
	            }
	        }
	    }
}

