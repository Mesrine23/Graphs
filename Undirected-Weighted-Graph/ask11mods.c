#include <stdio.h>
#include <stdlib.h>
#include "ask11.h"
#define INF 100

Boolean visited[MAXVERTEX];

////////////////////////////////////////////////////////////////////////////////

struct graph GRAPHinit(struct graph graph, int V)
{
  graph.n = V;

  int i;
  for (i=0 ; i<V ; ++i)
    graph.firstedge[i] = NULL;

  return graph;
}

////////////////////////////////////////////////////////////////////////////////

Edge* AdjList(int end, int w)
{
    Edge* node;
    node = malloc(sizeof(Edge));
    node->endpoint = end;
    node->weight = w;
    node->nextedge = NULL;
    return node;
}


Graph GRAPHedge(Graph graph, int x, int y, int w, int ver[20])
{
  Edge* node;
  int i;

  node = AdjList(y,w);
  i=0;
  while(ver[i]!=x)
    {++i;}
  node->nextedge = graph.firstedge[i];
  graph.firstedge[i] = node;

  node = AdjList(x,w);
  i=0;
  while(ver[i]!=y)
    {++i;}
  node->nextedge = graph.firstedge[i];
  graph.firstedge[i] = node;

  return graph;
}

////////////////////////////////////////////////////////////////////////////////

void showGRAPH(Graph graph, int ver[20])
{
    int i;
    struct edge* move;
    for (i = 0 ; i<(graph.n) ; ++i)
    {
        move = graph.firstedge[i];
        printf("\nAdjacency list for vertex *%d*\n ", ver[i]);
        while (move)
        {
            printf("(%d,%d) ", move->endpoint, move->weight);
            move = move->nextedge;
            if (move)
              printf("-> ");
        }
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////////////

int Minimum(Edge *head, int ver[MAXVERTEX], int min, int *minV, int limit)
{
  Edge *move;
  int v;

  move=head;
  while(move)
  {
    for(v=0; v<limit ; ++v)
    {
      if((move->endpoint)==ver[v])
      {
        if(visited[v]==TRUE)
          break;
        else
        {
          if((move->weight)<min)
          {
            min=move->weight;
            *minV=move->endpoint;
            break;
          }
        }
      }
    }
    move = move->nextedge;
  }

  return min;
}

void MinimumSpanningTree(Graph G, int ver[MAXVERTEX])
{
  int v,f=0;
  int min,minV,start,minTEMP,sum=0;

  for (v=1 ; v<G.n ; ++v)
    visited[v]=FALSE;
  visited[0]=TRUE;

  while(f!=1)
  {
    f=1;
    min=INF;
    for(v=0 ; v<G.n ; ++v)
    {
      if(visited[v]==TRUE)
      {
        minTEMP = Minimum(G.firstedge[v],ver,min,&minV,G.n);
        if(minTEMP<min)
        {
          min=minTEMP;
          start=ver[v];
        }
      }
    }
    //markin endpoint(=minV) as visited
    for(v=0 ; v<G.n ; ++v)
    {
      if(ver[v]==minV)
        visited[v]=TRUE;
    }
    //sum of weights;
    sum += min;
    //printf edge + weight
    printf("%d - %d  [%d]\n",start,minV,min);
    //if not all vertices are visited then we enter loop again
    for(v=0 ; v<G.n ; ++v)
    {
      if(visited[v]==FALSE)
        f=0;
    }
  }
  printf("\nSum of weights: %d\n",sum);
}

////////////////////////////////////////////////////////////////////////////////
