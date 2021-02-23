#define MAXVERTEX 20
#include <stdio.h>
#include <stdlib.h>
#include "ask10.h"
#include "Item.h"

Boolean visited[MAXVERTEX];
Boolean guard;
static link head;
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

Edge* AdjList(int end)
{
    Edge* node;
    node = malloc(sizeof(Edge));
    node->endpoint = end;
    node->nextedge = NULL;
    return node;
}


Graph GRAPHedge(Graph graph, int x, int y, int ver[MAXVERTEX])
{
  Edge* node;
  int i;

  node = AdjList(y);
  i=0;
  while(ver[i]!=x)
    {++i;}
  node->nextedge = graph.firstedge[i];
  graph.firstedge[i] = node;

  node = AdjList(x);
  i=0;
  while(ver[i]!=y)
    {++i;}
  node->nextedge = graph.firstedge[i];
  graph.firstedge[i] = node;

  return graph;
}

////////////////////////////////////////////////////////////////////////////////

void showGRAPH(Graph graph, int ver[MAXVERTEX])
{
    int i;
    struct edge* move;
    for (i = 0 ; i<(graph.n) ; ++i)
    {
        move = graph.firstedge[i];
        printf("\nAdjacency list for vertex *%d*\n ", ver[i]);
        while (move)
        {
            printf("%d ", move->endpoint);
            move = move->nextedge;
            if (move)
              printf("-> ");
        }
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////////////

link NEW(Item item, link next)
  { link x = malloc(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
  }

void STACKinit()
  { head = NULL; }


int STACKempty()
  { return head == NULL; }


void STACKpush(Item item)
  { head = NEW(item, head); }


Item STACKpop()
  { Item item = head->item;
    link t = head->next;
    free(head);
    head = t;
    return item;
  }

void TraverseSPC(Graph G, Vertex v, int ver[MAXVERTEX], int end)
{
  Vertex w,i,j,e,pop;
  Edge *curedge;

  if(guard==FALSE)
  {
    for(i=0 ; i<G.n ; ++i)
    if(ver[i]==v)
      break;

    //printf("Pushed: %d\n",v);
    STACKpush(v);

    visited[i]=TRUE;
    //printf("%d ", v);

    if(v==end)
    {
      guard=TRUE;
      return;
    }


    curedge=G.firstedge[i];      /* curedge is a pointer to the first edge (v,_) of V */
    while (curedge)
    {
      w=curedge->endpoint;       /* w is a successor of v and (v,w) is the current edge */
      for(j=0 ; j<G.n ; ++j)
        if(ver[j]==w)
          break;
      if (!visited[j])
      {
        TraverseSPC(G, w, ver, end);
        if(guard==TRUE)
          return;
      }
      else if((curedge->nextedge)==NULL)
      {
        pop = STACKpop();
        //printf("Popped: %d\n",pop);
      }
      curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
    }
  }
  else
    return;
}

void PrintSTACK()
{
  int v;
  v=STACKpop();
  if(!STACKempty())
    PrintSTACK();
  printf("%d ",v);
}

void SimplePathCheck(Graph G, int ver[MAXVERTEX], int start, int end)
{
  Vertex v;

  STACKinit();

  guard=FALSE;
  for (v=0; v < G.n; v++)
    visited[v]=FALSE;

  TraverseSPC(G, start, ver, end);

  if(guard==FALSE)
    printf("There is no such path\n");
  else
  {
    PrintSTACK();
    printf("\n");
  }

}

////////////////////////////////////////////////////////////////////////////////
