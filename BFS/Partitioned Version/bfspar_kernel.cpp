#include <iostream>
#include <string>
#include"bfspar_h.h"
using namespace std;


int part(int *c, int *dis, int *qu, int *vis, int source, int srcdist, int degree, int front)
{
#pragma HLS INTERFACE s_axilite port=return bundle=sqrt
#pragma HLS INTERFACE m_axi depth=9 port=c offset=slave bundle=input
#pragma HLS INTERFACE m_axi depth=9 port=dis offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=9 port=qu offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=9 port=vis offset=slave bundle=output
#pragma HLS INTERFACE s_axilite port=source
#pragma HLS INTERFACE s_axilite port=srcdist
#pragma HLS INTERFACE s_axilite port=degree
#pragma HLS INTERFACE s_axilite port=front
#pragma HLS INTERFACE s_axilite port=c
#pragma HLS INTERFACE s_axilite port=dis
#pragma HLS INTERFACE s_axilite port=qu
#pragma HLS INTERFACE s_axilite port=vis

	int v;
	front=0;
	neighbors:for(v = 0; v<degree ; v++)
	{
	 if (!vis[v] &&  (srcdist + 1 < dis[v]))
	 {
		 dis[v] = srcdist + 1;
	     vis[v] = 1;
	     qu[front] = c[v];
	     front++;
	 }
	}

	return front;
}


