// Main

#include <stdio.h>
#include <stdlib.h>
#include "ask10.h"


int main()
{

  char file[50];
  printf("\nGive file to open\n");
  scanf("%s",file);
  printf("\n");
  int V;
  int x,y,i,j,ver[MAXVERTEX],p,f,S,E;

  FILE *fp;

  char str[11];
  // str = string where x-y (edge) is stored
  // I suppose that x & y have <=5 digits

  Graph graph;

  fp = fopen(file, "r");

  fscanf(fp,"%d",&V);
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

  p=0;
  while(fscanf(fp, "%s", str)!=EOF)
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
      graph = GRAPHedge(graph,x,y,ver);
  }
  fclose(fp);

  showGRAPH(graph,ver);
  printf("-----------------------------\n");


  printf("\n-----------------------------\n");
  printf("Give Startpoint & Endpoint\n");
  fscanf(stdin,"%d",&S);
  fscanf(stdin,"%d",&E);
  printf("\nSimplePathCheck:\n");
  SimplePathCheck(graph,ver,S,E);
  printf("-----------------------------\n");


  printf("\n");

  return 0;
}
