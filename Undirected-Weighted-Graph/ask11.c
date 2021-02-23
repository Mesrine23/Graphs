#include <stdio.h>
#include <stdlib.h>
#include "ask11.h"

int main()
{

  printf("\n");

  char str[17];
  int V,x,y,w,i,j,p,e,f;
  int ver[MAXVERTEX],edge[MAXVERTEX*(MAXVERTEX-1)][2],wght[MAXVERTEX*(MAXVERTEX-1)];
  Graph graph;


  fscanf(stdin, "%d", &V);
  printf("------------------------------\n");
  printf("Number of vertices: %d\n\n",V);
  if (V>MAXVERTEX)
  {
    printf ("Gave too many vertices\n\n");
    return 1;
  }

  graph = GRAPHinit(graph,V);

  for(i=0 ; i<V ; ++i)
    ver[i] = -1;

  e=0;
  p=0;
  while(fscanf(stdin, "%s", str)!=EOF)
  {
    x=0; y=0, w=0;
    i=0;

    while(str[i]!='-')
    {
      x = x*10 + (str[i]-48);
      ++i;
    }
    ++i;
    while(str[i]!='-')
    {
      y = y*10 + (str[i]-48);
      ++i;
    }
    ++i;
    while(str[i]!='\0')
    {
      w = w*10 + (str[i]-48);
      ++i;
    }

    if(p==0)
    {
      ver[p]=x;
      ++p;
      ver[p]=y;
    }
    else
    {
      f=0;

      for(j=0 ; j<=p ; ++j)
      {
        if(x==ver[j])
        {
          f=1;
          break;
        }
      }
      if (f==0)
      {
        ++p;
        ver[p]=x;
      }

      f=0;

      for(j=0 ; j<=p ; ++j)
      {
        if(y==ver[j])
        {
          f=1;
          break;
        }
      }
      if (f==0)
      {
        ++p;
        ver[p]=y;
      }
    }
    if (x!=y)
    {
      edge[e][0]=x;
      edge[e][1]=y;
      wght[e]=w;
      ++e;
      graph = GRAPHedge(graph,x,y,w,ver);
    }
  }

  printf("Number of edges: %d\n",e);
  showGRAPH(graph,ver);

  /*
          !!!Try below loop to check the given data as: x -> y [w]!!!

  printf("\n");
  for(i=0 ; i<e ; ++i)
  {
    printf("%d -> %d  [%d]\n",edge[i][0],edge[i][1],wght[i]);
  }
  */

  printf("------------------------------\n");

  printf("\n------------------------------\n");
  printf("Minumum Spanning Tree (MST):\n");
  MinimumSpanningTree(graph,ver);
  printf("------------------------------\n");


  printf("\n\n");
  return 0;
}
