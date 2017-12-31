// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 4 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// GraphClient.c
// Test file for Graph.c and Graph.h
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "Graph.h"

// // failed tests
// int DG_getDIST(Graph *pA){
// Graph A = *pA; 
//   for (int i = 1; i <= 100; i++){
//    if (getDist(A, i) != INF){
//        return 1;
//    } 

//    printf(" %d ",i);
//  }
//   addArc(A, 64, 4);
//   addArc(A, 64, 3);
//   addArc(A, 42, 2);
//   addArc(A, 2, 64);
//   addArc(A, 4, 2);
//   addArc(A, 3, 42);
//   BFS(A, 64);
//   if (getDist(A, 64) != 0) return 2;
//   if (getDist(A, 2) != 2) return 3;
//   BFS(A, 4);
//   if (getDist(A, 42) != 4) return 4;
//   if (getDist(A, 43) != INF) return 5;
//   BFS(A, 99);
//   if (getDist(A, 64) != INF) return 6;
//   return 0;
// } // passes this now

int DG_getPath(Graph *pA,List *pL, List *cL){
Graph A = *pA;
List L = *pL; 
List C = *cL;
     addArc(A, 64, 4);
     addArc(A, 64, 3);
     addArc(A, 42, 2);
     addArc(A, 2, 64);
     addArc(A, 4, 2);
     addArc(A, 3, 42);
     BFS(A, 3);
     getPath(L, A, 64);
     append(C, 3);
     append(C, 42);
     append(C, 2);
     append(C, 64);
     if (!equals(L, C)) return 1;
     moveFront(L);
     BFS(A, 2);
     getPath(L, A, 2);
     append(C, 2);
     if (!equals(L, C)) return 2;
     getPath(L, A, 99);
     if (equals(L, C)) return 3;
     clear(L);
     clear(C);
     append(C, NIL);
     BFS(A, 99);
     getPath(L, A, 2);
     if (!equals(C, L)) return 4;
     return 0;
}

int UG_getDist(Graph *pA){
Graph A = *pA; 
     for (int i = 1; i <= 100; i++)
       if (getDist(A, i) != INF) return 1;
     addEdge(A, 64, 4);
     addEdge(A, 64, 3);
     addEdge(A, 42, 2);
     addEdge(A, 2, 64);
     addEdge(A, 4, 2);
     addEdge(A, 3, 42);
     BFS(A, 64);
     if (getDist(A, 64) != 0) return 2;
     if (getDist(A, 2) != 1) return 3;
     BFS(A, 4);
     if (getDist(A, 42) != 2) return 4;
     if (getDist(A, 43) != INF) return 5;
     BFS(A, 99);
     if (getDist(A, 64) != INF) return 6;
     return 0;
}

int UG_getPath(Graph *pA,List *pL,List *cL){
Graph A = *pA; 
List L = *pL; 
List C = *cL; 

     addEdge(A, 64, 4);
     addEdge(A, 64, 3);
     addEdge(A, 42, 2);
     addEdge(A, 2, 64);
     addEdge(A, 4, 2);
     addEdge(A, 3, 42);
     BFS(A, 3);
     getPath(L, A, 64);
     append(C, 3);
     append(C, 64);
     if (!equals(L, C)) return 1;
     moveFront(L);
     BFS(A, 2);
     getPath(L, A, 2);
     append(C, 2);
     if (!equals(L, C)) return 2;
     getPath(L, A, 99);
     if (equals(L, C)) return 3;
     clear(L);
     clear(C);
     append(C, NIL);
     BFS(A, 99);
     getPath(L, A, 2);
     if (!equals(C, L)) return 4;
     return 0;
}

int main(int argc, char* argv[]){
   Graph G = NULL; 

   G = newGraph(10); 

   // printf("\nOrder: %d size: %d source: %d", getOrder(G), getSize(G), getSource(G)); 
   Graph A = newGraph(100);
   List L = newList(); 
   List C = newList();


   printf("Failed test 2: %d\n", DG_getPath(&A,&L,&C));   

   // G = newGraph(10);
   // List path = newList();  

   // // printf("\nOrder: %d size: %d source: %d", getOrder(G), getSize(G), getSource(G));

   // addEdge(G,1,2); 
   // addEdge(G,1,3); 
   // addEdge(G,2,4);
   // addEdge(G,2,5); 
   // addEdge(G,2,6);
   // addEdge(G,3,4);
   // addEdge(G,4,5);
   // addEdge(G,5,6);        
   // printGraph(stdout,G);

   // printf("BFS Test:\n");  

   // BFS(G,1); 


   // printf("The shortest path is:\n"); 
   // getPath(path,G,5); 
   // printList(stdout,path); 




   freeGraph(&G);
   freeList(&L); 
   freeList(&C);  

   freeGraph(&A); 
   return(0); 
}