// Main

#include <stdio.h>
#include <stdlib.h>
#include "ask9.h"


int main()
{

  printf("\n");

  int V,S;
  int x,y,i,j,ver[MAXVERTEX],p,f,e,**edge;
  char str[11];
  // str = string where x-y (edge) is stored
  // I suppose that x & y have <=5 digits

  Graph graph;
  Graph revG;


  fscanf(stdin, "%d", &V);
  printf("------------------------------\n");
  printf("Number of vertices: %d\n\n",V);
  if (V>MAXVERTEX)
  {
    printf ("Gave too many vertices\n\n");
    return 1;
  }


  edge = malloc( (MAXVERTEX*(MAXVERTEX-1))*sizeof(int *) ); //max edges in directed G = n(n-1)
  if(edge==NULL)
  {
  	printf ("ERROR: Malloc returned NULL");
  	return 23;
  }
  for (i=0 ; i<(MAXVERTEX*(MAXVERTEX-1)) ; ++i)
  {
  	edge[i] = calloc (2 , sizeof(int));
  	if (edge==NULL)
  	{
  		printf ("ERROR: Malloc returned NULL");
  		return 23;
	   }
  }


  graph = GRAPHinit(graph,V);

  for(i=0 ; i<V ; ++i)
    ver[i] = -1;

  e=0;
  p=0;
  while(fscanf(stdin, "%s", str)!=EOF)
  {
    x=0; y=0;
    i=0;
    while(str[i]!='-')
    {
      x = x*10 + (str[i]-48);
      ++i;
    }
    ++i;
    while(str[i]!='\0')
    {
      y = y*10 + (str[i]-48);
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
      ++e;
      graph = GRAPHedge(graph,x,y,ver);
    }
  }

  printf("Number of edges: %d\n",e);
  showGRAPH(graph,ver);
  printf("------------------------------\n");

  printf("\n------------------------------\n");
  printf("DFS output:\n");
  DepthFirst(graph,ver,e,edge);
  printf("\n------------------------------\n\n");

  printf("\n------------------------------\n");
  printf("Topological Sorting:\n");
  BreadthTopSort(graph,ver);
  printf("\n------------------------------\n\n");



  revG = GRAPHinit(revG,V);
  revG = GraphReverse(graph,revG,ver);
  printf("\n------------------------------\n");
  printf("REVERSED GRAPH:\n");
  showGRAPH(revG,ver);
  printf("------------------------------\n");

  printf("\n------------------------------\n");
  printf("STRONGLY CONNECTED COMPONENTS:");
  StrongComponents(revG,ver);
  printf("\n------------------------------\n");

  printf("\n\n");
  return 0;
}
