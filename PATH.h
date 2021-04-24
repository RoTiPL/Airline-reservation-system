#ifndef PATH_H
#define PATH_H

#include "STRUCT.h"
#include "RESERVATION.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_DIS 3000
#define ALPHA_TO_NUM 97
#define SPEED 500
#define INT_MAX 2147483647
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 26  
#define INF 30000    

int number_visiting_citys();
void CreateGraph(Graph*, int);
void AddEdge(Graph*, int**, int, int);
int IsEdge(Graph*, int, int);
void CreateCity(int**, int);
float** CreatePathGraph(Graph*, int, int);
int choose(int[], int, int[]);
int shortest_path_time(Graph*, int***, int, int ,int, RNode*);
void SearchPath(int, int, RNode*);

#endif