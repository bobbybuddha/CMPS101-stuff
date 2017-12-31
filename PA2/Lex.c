// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 2 -- List ADT
// Description: 
//-----------------------------------------------------------------------------
// Lex.c
// Client for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

// define aribitrary max length per string 
#define MAX_LEN 160

int main(int argc, char* argv[]){

	// File pointers 
	FILE *inFile, *outFile; 
	char strIn[MAX_LEN];
	int arrLen = 0;  

	// if command line doesn't have 3 arguments
	if (argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	// open input file and output file 
	inFile = fopen(argv[1], "r"); 
	outFile = fopen(argv[2], "w");

	// check if inFile and outFile are pointing to NULL
	if(inFile == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(outFile == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	} 
    // while its not the end of file
	while(!feof(inFile)){
   	// read into string 
		fgets(strIn, MAX_LEN, inFile);
 		arrLen++;  // inc count for size of array 
   	}

   	// create an array of char pointers 
   	char strArr[arrLen][MAX_LEN]; 

   // reset file pointer to beginning 
   	fseek(inFile, 0, SEEK_SET); 


   	// read in strings into the character Array 
   	for (int i = 0; i < arrLen - 1; i++) {
   		// read in strings to string Array
   		fgets(strIn, MAX_LEN, inFile); 
   		strcpy(strArr[i], strIn); 
   	}

   	// create a new List
   	List L = newList(); 

   	// start at index 0
   	append(L, 0); 
   	int j = 0; // for index in L
   	int k = 0; // result of strcmp

   	// sort indirectly 
   	for (int i = 1; i < arrLen; i++){
   		// move cursor to back
   		moveBack(L); 
   		while (index(L) >= 0){
   			// get index of L
   			j = get(L); 
			k = strcmp(strArr[i],strArr[j]); 

			// if current string is less than or 
			// equal to string of index List
   			if (k < 0){
   				// move down the list 
   				movePrev(L); 
   			}
   			else
   				break; 
   		}

   		// if cursor is undefined, prepend
   		if (index(L) == -1) 
   			prepend(L, i); 
   		// else if index is still zero and string
   		// is less than string in L, prepend
   		else if (index(L) == 0 && k < 0)
   			prepend(L, i); 
   		else // otherwise, insert after  
   			insertAfter(L, i); 
	}

	// move to front of List
	moveFront(L); 

	// write sorted array to outFile
	for (int i = 0; i < length(L); i++){
   		fprintf(outFile,"%s", strArr[get(L)]);
   		moveNext(L); 
	}

   	fclose(inFile); 
   	fclose(outFile); 

   	freeList(&L);

   return(0);
}
