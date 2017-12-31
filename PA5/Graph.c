// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 5 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT that implements DFS
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
	// declare pointers to arrays
	List* L; 
	char* color; 
	int* parent;
	int* d;
	int* f; 
	// other fields
	int vertices; 
	int edges; 
} GraphObj; 

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object, with n vertices and of size 0
Graph newGraph(int n){
	Graph G; 
	G = malloc(sizeof(GraphObj)); 

	// allocate memory for color, parent, distance and array of Lists
	// memory i'm allocating is not 
	G->L = (List *)malloc((n + 1) * sizeof(List));
	G->color = malloc((n + 1) * sizeof(char));
	G->parent = malloc((n + 1) * sizeof(int));
	G->d = malloc((n + 1) * sizeof(int));
	G->f = malloc((n + 1) * sizeof(int));     

	// maybe dont need to intialize it to w, nil and inf in constructor
	for (int i = 1; i < n + 1; i++){
		G->L[i] = newList();
		// all intialized to NIL since DFS yet to be 
		// called
		G->color[i] = NIL; 
		G->parent[i] = NIL; 
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;   
	}
	G->vertices = n;  
	G->edges = 0; 

	return(G); 
}

// FIX LATER
// freeGraph()
// Frees all heap memory associated with Graph *pG, and Graph pG to NULL
// note: only need to worry about L
void freeGraph(Graph* pG){
	// to simplify syntax
	Graph G = *pG;
	List* L = NULL;  

	if (pG != NULL && *pG != NULL){
		// deallocating array of Lists
		for (int i = 1; i < getOrder(*pG) + 1; i++){
			L = &(G->L[i]);  // was G->L[i]
			freeList(L); 
		}
		// free parent pointer
		free(G->L); 
		// free other arrays
		free(G->color); 
		free(G->parent); 
		free(G->d);
		free(G->f); 
		// make null
 		G->color = NULL; 
		G->parent = NULL; 
		G->d = NULL;
		G->f = NULL; 
		G->L = NULL;
		// finally free G  
		free(G);
		G = NULL;
	}
}

// Access functions ----------------------------------------------------------

// getOrder()
// Returns number of vertices in this Graph
int getOrder(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n"); 
		exit(1); 
	}
	return(G->vertices); 
}

// getSize()
// Returns number of edges in this Graph
int getSize(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n"); 
		exit(1); 
	}
	return(G->edges); 
}

// getParent()
// pre: 1 <= u <= getOrder(G)
// Returns parent vertex of u, or returns NIL if BFS() has yet to be called
int getParent(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (1 <= u && u <= getOrder(G))
		return(G->parent[u]); 
	else{
		printf("Graph Error: u is out of bounds\n"); 
		exit(1); 
	}
}

// getDiscover()
// pre: 1 <= u <= getOrder(G)
// returns the discovery time of u, or returns UNDEF if DFS() has 
// yet to be called
int getDiscover(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (1 <= u && u <= getOrder(G))
		return(G->d[u]); 
	else{
		printf("Graph Error: u is out of bounds\n"); 
		exit(1); 
	}
}

// getFinish()
// pre: 1 <= u <= getOrder(G)
// returns the finish time of u, or returns UNDEF if DGS() has yet to be called
int getFinish(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getFinish() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (1 <= u && u <= getOrder(G))
		return(G->f[u]); 
	else{
		printf("Graph Error: u is out of bounds\n"); 
		exit(1); 
	}
}

// Manipulation procedures ----------------------------------------------------

// addEdge()
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// adds u to v's adjacency list and v to u's adjacency list
void addEdge(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)){
		List adjList = G->L[u]; 

		// go to u's adjacency list
		moveFront(adjList);

		while (index(adjList) != -1){
			if (v > get(adjList))
				moveNext(adjList); 
			else
				break; 
		} 
		if (index(adjList) == -1)
			append(adjList,v); 
		else // it's not off end
			insertBefore(adjList,v);

		adjList = NULL; 
		adjList = G->L[v]; 

		// go to u's adjacency list
		moveFront(adjList);

		while (index(adjList) != -1){
			if (u > get(adjList))
				moveNext(adjList); 
			else
				break; 
		} 
		if (index(adjList) == -1){
			append(adjList,u); 
		}
		else // it's not off end
			insertBefore(adjList,u);
		G->edges++;   
	}
	else{
		printf("Graph Error: u or v is out of bounds\n"); 
		exit(1); 
	}

}

// addArc()
// pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// adds v to u's adjacency list
void addArc(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)){

		List adjList = G->L[u]; 

		// go to u's adjacency list
		moveFront(adjList);

		while (index(adjList) != -1){
			if (v > get(adjList))
				moveNext(adjList); 
			else
				break; 
		} 
		if (index(adjList) == -1)
			append(adjList,v); 
		else // it's not off end
			insertBefore(adjList,v); 
		G->edges++; 
	}
	else{
		printf("Graph Error: u or v is out of bounds\n"); 
		exit(1); 
	}
}

// DFS()
// pre: length(S) == getOrder(G), S consists of a permutation of vertices of G
// Runs DFS on G, where the outer for loop visits vertices in ordering they 
// consist of in S
void DFS(Graph G, List S){
	if (G == NULL){
		printf("Graph Error: calling DFS() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (G == NULL){
		printf("Graph Error: calling DFS() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(S) == getOrder(G)){
		// assuming List S contains the n ordering of vertices to be visited

		// make all vertices white, in no particular order
		for (int i = 1; i < getOrder(G) + 1; i++){
			G->color[i] = 'w'; 
			G->parent[i] = NIL;
		}

		int time = 0;
		int u = 0;  
		// append a dummy value in order to keep track of 
		// Stack half of List S and vertex ordering of List S
		append(S,-1); 
		// goes from 1 to n
		for(int i = 0; i < getOrder(G); i++){ 
			moveFront(S);
			// as vertices are retrieved from front, 
			// delete them from front, which 
			// should delete n front elements of List S
			if (index(S) != -1){
				u = get(S);
				moveNext(S); 
				deleteFront(S);
				if (G->color[u] == 'w')
					 Visit(G,u,&time,S); 
			}
		}
		deleteFront(S); // delete dummy value
	}
	else{
		printf("Graph Error: length of List less than order of Graph\n"); 
		exit(1); 
	}
}

// Other operations ----------------------------------------------------------- 

// Visit()
// helper function for DFS(), is recursively called until DFS tree for nil 
// parent x is constructed
void Visit(Graph G, int x, int* time, List S){
	if (G == NULL){
		printf("Graph Error: calling DFS() on NULL Graph reference\n"); 
		exit(1); 
	}
	int y = 0;
	// x has been discovered
	G->color[x] = 'g'; 
	G->d[x] = ++(*time);
	moveFront(G->L[x]); 
	// while there are still vertices in adj[x]
	while(index(G->L[x]) != -1){
		y = get(G->L[x]); 
		if (G->color[y] == 'w'){
			G->parent[y] = x; 
			Visit(G,y,time,S); // visit y if undiscovered
		} 
		moveNext(G->L[x]); 
	}
	G->color[x] = 'b';
	G->f[x] = ++(*time);
	// add to Stack, which will be in reverse order
	moveFront(S); 
	// go to dummy value
	while(get(S) != -1 && index(S) != -1)
		moveNext(S);
	// insert after dummy value
	insertAfter(S,x); 
}

// tranpose()
// returns the tranpose of graph G
Graph transpose(Graph G){
	if (G == NULL){
		printf("Graph Error: calling tranpose() on NULL Graph reference\n"); 
		exit(1); 
	}
	// construct newGraph
	Graph tG = newGraph(getOrder(G));
	int v = 0;  // terminus, will be origin for edges of tG 

	for (int i = 1; i < getOrder(G) + 1; i++){
		// move to front of adjacency list of i
		moveFront(G->L[i]); 
		// iterate through adjacent vertices of i
		while(index(G->L[i]) != -1){
			v = get(G->L[i]);
			// add edge from v to i
			addArc(tG,v,i); 
			moveNext(G->L[i]); 
		}
	}
	return(tG); 
}

// copyGraph()
// returns a copy of graph G
Graph copyGraph(Graph G){
	if (G == NULL){
		printf("Graph Error: calling copyGraph() on NULL Graph reference\n"); 
		exit(1); 
	}
	// construct newGraph
	Graph cG = newGraph(getOrder(G)); 
	int v = 0; // terminus

	for (int i = 1; i < getOrder(G) + 1; i++){
		// move to front of adjacency list of i
		moveFront(G->L[i]); 
		// iterate through adjacent vertices of i
		while(index(G->L[i]) != -1){
			v = get(G->L[i]);
			// add edge from i to v
			addArc(cG,i,v); 
			moveNext(G->L[i]); 
		}
	}
	return(cG); 
}

// printGraph()
// Writes out adjacency list representation of G to file pointed to by out
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference\n"); 
		exit(1); 
	}      
	// for syntax simplification
	List adjList = NULL; 

	for (int i = 1; i < getOrder(G) + 1; i++){
		adjList = (List)G->L[i]; 
		fprintf(out,"%d: ",i);
		printList(out,adjList);
		fprintf(out,"\n"); 
	}
	adjList = NULL; 
}