#include "prpar_h.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


void spmvector(float *valx, int *rowx, int *colx, float *px, float *p_newx) //matrix multiplication
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=4720 port=valx  bundle=input1
#pragma HLS INTERFACE m_axi depth=4720 port=rowx  bundle=input1
#pragma HLS INTERFACE m_axi depth=4720 port=colx  bundle=input1
#pragma HLS INTERFACE m_axi depth=4725 port=px  bundle=output1
#pragma HLS INTERFACE m_axi depth=4725 port=p_newx  bundle=output1
#pragma HLS INTERFACE s_axilite port=valx
#pragma HLS INTERFACE s_axilite port=rowx
#pragma HLS INTERFACE s_axilite port=colx
#pragma HLS INTERFACE s_axilite port=px
#pragma HLS INTERFACE s_axilite port=p_newx
  int i;
  int row[THRESHOLD],col[THRESHOLD];
  float p[N],p_new[N],val[THRESHOLD];
  memcpy(val,(const float*) valx, THRESHOLD *sizeof(float));
  memcpy(row,(const int*) rowx, THRESHOLD *sizeof(int));
  memcpy(col,(const int*) colx, THRESHOLD *sizeof(int));
  memcpy(p,(const int*) px, N *sizeof(float));
  memcpy(p_new,(const float*) p_newx, N*sizeof(float));
	spmvector_label0:for ( i=0; i<THRESHOLD; i++)
	{
		p_new[row[i]] += (val[i] * p[col[i]]);
		//printf("%f %d %d %f %f %d %d\n",val[i],row[i],col[i],p_new[row[i]],p[col[i]],i,parti);
	}
	//printf("\n");
	memcpy(px,(const float*) p, N *sizeof(float));
	memcpy(p_newx,(const float*) p_new, N *sizeof(float));
}
