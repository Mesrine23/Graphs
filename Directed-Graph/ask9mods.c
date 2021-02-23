#include <stdio.h>
#include <stdlib.h>
#include "ask9.h"
#include "QueueInterface.h"

Boolean visited[MAXVERTEX];
int toporder[MAXVERTEX];
int PREcount=0,POSTcount=0;
int pre[MAXVERTEX],post[MAXVERTEX];
int TypeEdge[MAXVERTEX*(MAXVERTEX-1)];

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

void TypeEdgePrint(int ver[MAXVERTEX], int **edge, int e)
{

  int v,i,j,x,y;

  for(v=0 ; v<e ; ++v)
  {
    x=edge[v][0];
    y=edge[v][1];
    if(TypeEdge[v]==0)
    {
      i=0;  //find "x" in ver
      while(1)
      {
        if(x==ver[i])
          break;
        else
          ++i;
      }

      j=0; //find "y" in ver
      while(1)
      {
        if(y==ver[j])
          break;
        else
          ++j;
      }

      if (post[i]<post[j])
        printf("%d -> %d : Back Edge\n",x,y);
      else if (pre[i]>pre[j])
        printf("%d -> %d : Cross Edge\n",x,y);
      else
        printf("%d -> %d : Forward Edge\n",x,y);
    }
    else
      printf("%d -> %d : Tree Edge\n",x,y);
  }
}

void Traverse(Graph G, Vertex v, int ver[MAXVERTEX], int **edge)
{
  Vertex w,i,j,e;
  Edge *curedge;

  for(i=0 ; i<G.n ; ++i)
    if(ver[i]==v)
      break;

  visited[i]=TRUE;
  pre[i]=PREcount++;
  printf("%d ", v);

  curedge=G.firstedge[i];      /* curedge is a pointer to the first edge (v,_) of V */
  while (curedge)
  {
    w=curedge->endpoint;       /* w is a successor of v and (v,w) is the current edge */
    for(j=0 ; j<G.n ; ++j)
      if(ver[j]==w)
        break;
    if (!visited[j])
    {
      e=0;
      while(1)
      {
        if((edge[e][0]==v) && (edge[e][1]==w))
        {
          TypeEdge[e]=1;
          break;
        }
        else
          ++e;
      }
      Traverse(G, w, ver, edge);
    }
    curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
  }
  post[i]=POSTcount++;
}


void DepthFirst(Graph G, int ver[MAXVERTEX], int e, int **edge)
{

  Vertex v;
  int i;

  for(i=0 ; i<(MAXVERTEX*(MAXVERTEX-1)) ; ++i)
    TypeEdge[i]=0;

  for (v=0; v < G.n; v++)
  {
    pre[v]=-1;
    post[v]=-1;
    visited[v]=FALSE;
  }

  for (v=0; v < G.n; v++)
    if (!visited[v])
      {Traverse(G, ver[v], ver, edge);}

  printf("\n");

  TypeEdgePrint(ver,edge,e);
}

////////////////////////////////////////////////////////////////////////////////

void InitializeQueue(Queue *Q)
{
    Q->Front=NULL;
    Q->Rear=NULL;
}

void Insert(ItemType R, Queue *Q)
{
   QueueNode *Temp;

   Temp=(QueueNode *)malloc(sizeof(QueueNode));

   if (Temp==NULL){
      printf("System storage is exhausted");
   } else {
      Temp->Item=R;
      Temp->Link=NULL;
      if (Q->Rear==NULL){
         Q->Front=Temp;
         Q->Rear=Temp;
      } else {
         Q->Rear->Link=Temp;
         Q->Rear=Temp;
      }
   }
}

void Remove(Queue *Q, ItemType *F)
{
   QueueNode *Temp;


   if (Q->Front==NULL){
      printf("attempt to remove item from an empty queue");
   } else {
      *F=Q->Front->Item;
      Temp=Q->Front;
      Q->Front=Temp->Link;
      free(Temp);
      if (Q->Front==NULL) Q->Rear=NULL;
   }
}

int Empty(Queue *Q)
{
   return(Q->Front==NULL);
}


void BreadthTopSort(Graph G, int ver[MAXVERTEX])
{

  int predecessorcount[MAXVERTEX];    /* number of predecessors of each vertex */

  Queue Q;
  Vertex v, succ;
  Edge *curedge;
  int place,test,i,j;

  /* initialize all the predecessor counts to 0  */
  for (v=0; v < G.n; v++)
    predecessorcount[v]=0;

  /* increase the predecessor count for each vertex that is a successor of another one */
  for (v=0; v < G.n; v++)
  {
    curedge = G.firstedge[v];
    while(curedge)
    {
      test = curedge->endpoint;
      for(i=0 ; i<MAXVERTEX ; ++i)
      {
        if (test==ver[i])
        {
          ++predecessorcount[i];
          break;
        }
      }
      curedge = curedge->nextedge;
    }
  }


  /* initialize a queue */
  InitializeQueue(&Q);

  /* place all vertices with no predecessors into the queue */
  for (v=0; v < G.n; v++)
    if (predecessorcount[v]==0)
      Insert(ver[v], &Q);

  /* start the breadth-first traversal */
  place=-1;
  while (!Empty(&Q))
  {
    /* visit v by placing it into the topological order */
    Remove(&Q, &v);
    place++;
    toporder[place]=v;

    for(j=0 ; j<G.n ; ++j)
      if(ver[j]==v)
        break;
    /* traverse the list of successors of v */
    for (curedge=G.firstedge[j]; curedge; curedge=curedge->nextedge)
    {
       /* reduce the predecessor count for each successor */
       succ=curedge->endpoint;
       for(i=0 ; i < G.n ; ++i)
       {
         if(ver[i]==succ)
         {
          predecessorcount[i]--;
          break;
         }
       }
       if (predecessorcount[i]==0)
         /* succ has no further predecessors, so it is ready to process */
         Insert(ver[i], &Q);
    }
  }

  for(i=0 ; i < G.n ; ++i)
    printf("%d ",toporder[i]);

}

////////////////////////////////////////////////////////////////////////////////

Graph GraphReverse(Graph graph, Graph newG, int ver[MAXVERTEX])
{
  int i,test;
  Edge *curedge;

  for(i=0 ; i < graph.n ; ++i)
  {
    curedge = graph.firstedge[i];
    while(curedge)
    {
      newG = GRAPHedge(newG , curedge->endpoint , ver[i] , ver);
      curedge = curedge->nextedge;
    }
  }

  return newG;
}

////////////////////////////////////////////////////////////////////////////////

void TraverseSC(Graph G, Vertex v, int ver[MAXVERTEX])
{
  Vertex w,i,j,e;
  Edge *curedge;

  for(i=0 ; i<G.n ; ++i)
    if(ver[i]==v)
      break;

  visited[i]=TRUE;
  printf("%d ", v);

  curedge=G.firstedge[i];      /* curedge is a pointer to the first edge (v,_) of V */
  while (curedge)
  {
    w=curedge->endpoint;       /* w is a successor of v and (v,w) is the current edge */
    for(j=0 ; j<G.n ; ++j)
      if(ver[j]==w)
        break;
    if (!visited[j])
      TraverseSC(G, w, ver);
    curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
  }
}

void StrongComponents(Graph G, int ver[MAXVERTEX])
{
  Vertex v;
  int maxV,max,f=0,i,j,temp,tempPOST[MAXVERTEX];
  Edge *tempEDGE;

  for (v=0; v < G.n; v++)
    visited[v]=FALSE;

//start SORT
  for(i=0 ; i<G.n ; ++i)
    tempPOST[i]=post[i];

  for (i=1 ; i < G.n ; i++)
  {
    for (j=((G.n)-1) ; j >= i ; j--)
    {
      if(tempPOST[j-1]<tempPOST[j])
      {
        temp=tempPOST[j];
        tempPOST[j]=tempPOST[j-1];
        tempPOST[j-1]=temp;

        temp=ver[j];
        ver[j]=ver[j-1];
        ver[j-1]=temp;

        tempEDGE=G.firstedge[j-1];
        G.firstedge[j-1]=G.firstedge[j];
        G.firstedge[j]=tempEDGE;
      }
    }
  }
//end SORT
for (v=0; v < G.n; v++)
  if (!visited[v])
    {
      printf("\n");
      TraverseSC(G, ver[v], ver);
    }


}

////////////////////////////////////////////////////////////////////////////////
