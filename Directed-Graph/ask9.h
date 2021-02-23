#include "GraphTypes.h"
struct graph GRAPHinit(struct graph ,int);
struct graph GRAPHedge(struct graph, int, int, int*);
void showGRAPH(struct graph,int *);
void DepthFirst(Graph, int*, int, int **);
void BreadthTopSort(struct graph, int*);
struct graph GraphReverse(struct graph, struct graph, int*);
void StrongComponents(Graph, int *);
