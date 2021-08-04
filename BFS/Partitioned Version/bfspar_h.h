#pragma once

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#define V 4720		 //maximum 20,000
#define E 27444   //maximum 1,000,000
#define INFINITY 9999
#define maxdeg 9
int part(int *c, int *dis, int *qu, int *vis, int source, int srcdist, int degree, int front);
void shortest(int *col, int *nzr, int *d, int *q, int *visited, int src);
