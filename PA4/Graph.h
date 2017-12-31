// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 4 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"


// macros ---------------------------------------------------------------------
#define UNDEF -1
#define NIL  0

// Exported type --------------------------------------------------------------

// Used for type definition 
typedef struct GraphObj* Graph;

// Constructors-Destructors --------------------------------------------------- 

// newGraph()
// Returns reference to new empty Graph object, with n vertices and of size 0
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph *pG, and Graph pG to NULL
void freeGraph(Graph* pG);

// Access functions ----------------------------------------------------------

// getOrder()
// Returns number of vertices in this Graph
int getOrder(Graph G);

// getSize()
// Returns number of edges in this Graph
int getSize(Graph G);

// getSource()
// Returns the most recent source vertex or NIL if BFS() has yet to be called
int getSource(Graph G);

// getParent()
// pre: 1 <= u <= getOrder(G)
// Returns parent vertex of u, or returns NIL if BFS() has yet to be called
int getParent(Graph G, int u);

// getDist()
// pre: 1 <= u <= getOrder(G)
// Returns distance from most recent source vertex to u, or returns INF if 
// BFS() has yet to be called
int getDist(Graph G, int u);

// getPath()
// pre: 1 <= u <= getOrder(G)
// gets shortest path from current source vertex to u, or returns NIL if 
// BFS() has yet to be called 
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// makeNull()
// sets G to be the null graph
void makeNull(Graph G);

// addEdge()
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// adds u to v's adjacency list and v to u's adjacency list
void addEdge(Graph G, int u, int v);

// addArc()
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// adds v to u's adjacency list
void addArc(Graph G, int u, int v);

// BFS()
// pre: 1 <= s <= getOrder(G)
// finds shortest path from the source vertex s to all other vertices in G,
// whether G is directed or undirected. Sets s as current source vertex.
void BFS(Graph G, int s);

// Other operations ----------------------------------------------------------- 

// printGraph()
// Writes out adjacency list representation of G to file pointed to by out
void printGraph(FILE* out, Graph G);

#endif