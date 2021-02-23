#define MAXVERTEX 20

typedef int Vertex;

typedef enum {FALSE, TRUE} Boolean;

typedef struct edge {
   Vertex endpoint;
   struct edge *nextedge;
} Edge;

typedef struct graph {
   int n;     /* number of vertices in the graph */
   Edge *firstedge[MAXVERTEX];
} Graph;
