// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 4 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
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
	int* distance;
	// other fields
	int vertices; 
	int edges; 
	int source; 
} GraphObj; 

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object, with n vertices and of size 0
Graph newGraph(int n){
	Graph G; 
	G = malloc(sizeof(GraphObj)); 

	if (n > 0){
		// allocate memory for color, parent, distance and array of Lists
		// memory i'm allocating is not 
		G->L = (List *)malloc((n + 1) * sizeof(List));
		G->color = malloc((n + 1) * sizeof(char));
		G->parent = malloc((n + 1) * sizeof(int));
		G->distance = malloc((n + 1) * sizeof(int));   

		// maybe dont need to intialize it to w, nil and inf in constructor
		for (int i = 1; i < n + 1; i++){
			G->L[i] = newList();
			// all intialized to NIL since BFS yet to be 
			// called
			G->color[i] = NIL; 
			G->parent[i] = NIL; 
			G->distance[i] = INF;  
		}
		G->vertices = n;  
	} // else make them size 1
	G->edges = 0; 
	G->source = NIL; 

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
		free(G->distance);
		// make null
 		G->color = NULL; 
		G->parent = NULL; 
		G->distance = NULL;
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

// getSource()
// Returns the most recent source vertex or NIL if BFS() has yet to be called
int getSource(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n"); 
		exit(1); 
	}
	return(G->source); 
}

//write these after BFS
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

// getDist()
// pre: 1 <= u <= getOrder(G)
// Returns distance from most recent source vertex to u, or returns INF if 
// BFS() has yet to be called
int getDist(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDist() on NULL Graph reference\n"); 
		exit(1); 
	}

	if (1 <= u && u <= getOrder(G))
		return(G->distance[u]); 
	else{
		printf("Graph Error: u is out of bounds\n"); 
		exit(1); 
	}
}

// getPath()
// pre: 1 <= u <= getOrder(G)
// gets shortest path from current source vertex to u, or returns NIL if 
// BFS() has yet to be called 
void getPath(List L, Graph G, int u){

	if (G == NULL){
		printf("Graph Error: calling getPath() on NULL Graph reference\n"); 
		exit(1); 	
	}
	if (L == NULL){
		printf("Graph Error: calling getPath() on NULL List reference\n"); 
		exit(1); 	
	}

	if (u == G->source){
		append(L,G->source);
	}
	else if (getParent(G,u) == NIL){
		append(L,NIL);  
	}
	else{
		getPath(L,G,getParent(G,u));
		append(L,u);  
	}
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// sets G to be the null graph
void makeNull(Graph G){
	if (G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference\n"); 
		exit(1); 
	}

	List L = NULL; 
	// delete elements, not deallocate
	for (int i = 1; i < getOrder(G) + 1; i++){
		L = G->L[i]; 
		clear(L); // clear each List
		// resetting everything to NIL
		G->color[i] = NIL;  
		G->parent[i] = NIL; 
		G->distance[i] = NIL; 
	}

	G->edges = 0; 
	G->source = NIL; 
}

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

// BFS()
// pre: 1 <= s <= getOrder(G)
// finds shortest path from the source vertex s to all other vertices in G,
// whether G is directed or undirected. Sets s as current source vertex.
void BFS(Graph G, int s){
	if (G == NULL){
		printf("Graph Error: calling BFS() on NULL Graph reference\n"); 
		exit(1); 
	}
	if (s >= 1 && s <= getOrder(G)){
		// create new List to serve as Queue
		List Queue = newList();
		List adjList = NULL; 
		int u = 0; 
		int v = 0; 
		G->source = s;

		// set default values
		for (int i = 1; i < getOrder(G) + 1; i++){

			if (i != G->source){
				G->color[i] = 'w'; 
				G->distance[i] = INF; 
				G->parent[i] = NIL; 
			}
		} 

		G->color[s] = 'g'; 
		G->distance[s] = 0; 
		G->parent[s] = NIL; 

		append(Queue,s); 
		while (length(Queue) != 0){ 
			moveFront(Queue); 
			u = get(Queue); // gets u, dequeues
			deleteFront(Queue); 
			adjList = G->L[u]; // gets adjList of u
			moveFront(adjList); // start at beginning at adjacency list
			while(index(adjList) != -1){
				v = get(adjList); 

				if (G->color[v] == 'w'){
					G->color[v] = 'g'; 
					G->distance[v] = G->distance[u] + 1; 
					G->parent[v] = u; 
					append(Queue,v); 
				}
				moveNext(adjList); 
			}
			G->color[u] = 'b'; 
		}
		freeList(&Queue); 
	}
	else{
		printf("Graph Error: source vertex s is out of bounds\n"); 
		exit(1); 
	}
}

// Other operations ----------------------------------------------------------- 

// printGraph()
// Writes out adjacency list representation of G to file pointed to by out
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference\n"); 
		exit(1); 
	}      

	List adjList = NULL; // for syntax simplification

	for (int i = 1; i < getOrder(G) + 1; i++){
		adjList = (List)G->L[i]; 
		fprintf(out,"%d: ",i);
		printList(out,adjList);
		fprintf(out,"\n"); 
	}
	adjList = NULL; 
}


