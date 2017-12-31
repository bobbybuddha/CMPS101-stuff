// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 5 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// FindComponents.c
// Top level client for Graph assignment that implements DFS
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){

   // Declare in FILE and out FILE pointers 
   FILE *in, *out;
   int n = 0; // number of vertices
   int u = 0; // origin vertex
   int v = 0; // terminus vertex
   int numNil = 0; // number of nill parents
   char* num = NULL;   
   char line[MAX_LEN]; // line to be read in

   // check command line for correct number of arguments
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   fgets(line,MAX_LEN,in);
   n = atoi(line);  // converts ASCII to integer

   Graph G = newGraph(n);
   List L = newList(); 

   // make L consist of ascending order of vertices
   for (int i = 1; i <= n; i++)
      append(L,i); 

   fgets(line,MAX_LEN,in);
   num = strtok(line," "); // first vertex
   u = atoi(num); 
   num = strtok(NULL," "); 
   v = atoi(num);  // second vertex
   num = NULL; 

   if (u != 0 && v != 0)
      addArc(G,u,v);  

   // add edges until dummy line
   while(u != 0 && v != 0){
      fgets(line,MAX_LEN,in);
      num = strtok(line," "); // to get first number
      u = atoi(num); 
      num = strtok(NULL," "); 
      v = atoi(num); 
      num = NULL; 
      if (u != 0 || v != 0)   
         addArc(G,u,v); 
   }

   // print adjacency list to output file
   fprintf(out,"Adjacency list representation of G:\n"); 
   printGraph(out,G);
   fprintf(out,"\n");  

   // get vertices in topologically sorted order
   DFS(G,L); 
   G = transpose(G); 
   DFS(G,L); 

   moveFront(L); 
   // count number of nill parents
   for (int i = 0; i < n; i++){
      if (getParent(G,get(L)) == NIL)
         numNil++; 
      moveNext(L); 
   }

   fprintf(out,"G contains %d strongly connected components:",numNil); 

   List T = newList(); // for keeping track of vertices in topological order
   moveBack(L); 
   // print strongly connected components in topologically sorted order
   for (int i = 1; i <= numNil; i++){
      fprintf(out,"\nComponent %d: ",i);
      while(index(L) != -1 && getParent(G,get(L)) != NIL){
         prepend(T,get(L)); // prepend everything that comes after NIL parent
         movePrev(L);  
      } 
      prepend(T,get(L)); // for NIL parent
      movePrev(L); // update cursor
      printList(out,T); // print component
      clear(T); // clear T for next SCC
   }
   // close files
   fclose(in); 
   fclose(out); 
   // free object pointers
   freeGraph(&G); 
   freeList(&L);
   freeList(&T);  

   return(0); 
}



