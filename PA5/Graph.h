// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 5 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT that implements DFS
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

// getParent()
// pre: 1 <= u <= getOrder(G)
// Returns parent vertex of u, or returns NIL if DFS() has yet to be called
int getParent(Graph G, int u);

// getDiscover()
// pre: 1 <= u <= getOrder(G)
// returns the discovery time of u, or returns UNDEF if DFS() has 
// yet to be called
int getDiscover(Graph G, int u);

// getFinish()
// pre: 1 <= u <= getOrder(G)
// returns the finish time of u, or returns UNDEF if DGS() has yet to be called
int getFinish(Graph G, int u); 

// Manipulation procedures ----------------------------------------------------

// addEdge()
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// adds u to v's adjacency list and v to u's adjacency list
void addEdge(Graph G, int u, int v);

// addArc()
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// adds v to u's adjacency list
void addArc(Graph G, int u, int v);

// DFS()
// pre: length(S) == getOrder(G), S consists of a permutation of vertices of G
// Runs DFS on G, where the outer for loop visits vertices in ordering they 
// consist of in S
void DFS(Graph G, List S); 

// Other operations ----------------------------------------------------------- 

// tranpose()
// returns the tranpose of graph G
Graph transpose(Graph G); 

// copyGraph()
// returns a copy of graph G
Graph copyGraph(Graph G); 

// printGraph()
// Writes out adjacency list representation of G to file pointed to by out
void printGraph(FILE* out, Graph G);

#endif