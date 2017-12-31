// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 4 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// FindPath.c
// Top level client for Graph assignment
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){

   // Declare in FILE and out FILE pointers 
   FILE *in, *out;
   int n = 0;
   int u = 0; 
   int v = 0;
   char* num = NULL;   
   // line to be read in
   char line[MAX_LEN];

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

   fgets(line,MAX_LEN,in);
   num = strtok(line," "); // first vertex
   u = atoi(num); 
   num = strtok(NULL," "); 
   v = atoi(num);  // second vertex
   num = NULL; 

   if (u != 0 && v != 0)
      addEdge(G,u,v);  

   // add edges until dummy line
   while(u != 0 && v != 0){
      fgets(line,MAX_LEN,in);
      num = strtok(line," "); // to get first number
      u = atoi(num); 
      num = strtok(NULL," "); 
      v = atoi(num); 
      num = NULL; 
      if (u != 0 || v != 0)   
         addEdge(G,u,v); 
   }

   // print adjacency list to output file
   printGraph(out,G); 

   fgets(line,MAX_LEN,in);
   num = strtok(line," "); // first vertex
   u = atoi(num); 
   num = strtok(NULL," "); 
   v = atoi(num);  // second vertex
   num = NULL; 

   while(u != 0 && v != 0){

      if (u != 0 || v != 0){
         // call BFS on u and v 
         BFS(G,u);
         fprintf(out,"\nThe distance from %d to %d is ",u,v); 
         if (getDist(G,v) == INF)
            fprintf(out, "infinity");
         else 
            fprintf(out,"%d",getDist(G,v));
         if (getDist(G,v) == INF)
            fprintf(out, "\nNo %d-%d path exists",u,v);
         else{
            fprintf(out,"\nA shortest %d-%d path is: ",u,v);
            getPath(L,G,v);
            printList(out,L);
            fprintf(out,"\n");
            freeList(&L); 
            L = newList(); 
         }
      } 
      fgets(line,MAX_LEN,in);
      num = strtok(line," "); // first vertex
      u = atoi(num); 
      num = strtok(NULL," "); 
      v = atoi(num);  // second vertex
      num = NULL;
   }
 
   fclose(in); 
   fclose(out); 

   return(0); 
}

