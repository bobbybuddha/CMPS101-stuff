// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 2 -- List ADT
// Description: 
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev; 
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node iterator;
   int length;
   int index; 
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL; 
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
   List L; // Create new ListObj* 
   L = malloc(sizeof(ListObj)); // allocate enough memory for one ListObj struct
   L->front = L->back = L->iterator = NULL;
   L->length = 0;
   L->index = -1; 
   return(L); // return new ListObj
}

// freeList()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL){ // Passes in List* => ListObj**, passing address of pointer 

	// if **ListObj (double pointer) != NULL and *ListObj != NULL (pointer)
   if(pL !=NULL && *pL != NULL) { 
		
		// while the length is not 0
   		// have to use length, no direct access 
		while( length(*pL) > 0 ) { 
			deleteFront(*pL); 
      }
      //free the pointer to List
      free(*pL);
      *pL = NULL;
   }
}

// Access functions ----------------------------------------------------------

// Returns the number of elements in this List.
// Post: Integer is returned representing length of 
// the list
int length(List L){
	if (L == NULL){
		printf("List Error: calling length() on NULL List reference\n"); 
		exit(1); 
	}
	return(L->length); 
}

// If cursor is defined, returns the index of the 
// cursor element, otherwise returns -1 
// Pre: iterator is referencing List element
// Post: Returns data contained in element, otherwise
// returns -1
int index(List L){
	if (L == NULL){
		printf("List Error: calling index() on NULL List reference\n"); 
		exit(1); 
	}
	return(L->index); 
}

// Returns front element. 
// Pre: len > 0
int front(List L){
	if (L == NULL){
		printf("List Error: calling front() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) > 0) 
		return(L->front->data); 
	else{
		printf("List Error: calling front() on empty List reference\n"); 
		exit(1); 
	}
}

// Returns back element. 
// Pre: len > 0
int back(List L){
	if (L == NULL){
		printf("List Error: calling back() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) > 0)
		return(L->back->data); 
	else{
		printf("List Error: calling back() on empty List reference\n"); 
		exit(1); 
	}
}

// Returns cursor element.
// Pre: len > 0, index() >= 0
int get(List L){
	if (L == NULL){
		printf("List Error: calling get() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) > 0 && index(L) >= 0)
		return(L->iterator->data); 
	else{
		printf("List Error: calling get() on empty List reference or" 
			" cursor is undefined\n"); 
		exit(1); 
	} 

}

// Returns true iff this List and L are the  same 
// integer sequence. The cursors of either List are 
// not used in the comparison of the respective
// Lists. 
int equals(List A, List B){
	if (A == NULL || B == NULL){
		printf("List Error: calling equals() on NULL List reference(s)\n"); 
		exit(1); 
	}

	// if lengths of Lists are not the same, 
	// return false 
	if (length(A) != length(B))
		return(0); 

	// make iterators for both Lists
	Node thisIterator = A->front; 
	Node thatIterator = B->front; 

	// while loop to iterator over both Lists simultaneously
	// and check if their respective elements are equal
	while (thisIterator != NULL && thatIterator != NULL){

		if (thisIterator->data != thatIterator->data){
			thisIterator = thatIterator = NULL; 
			return(0); 
		}

		// update otherwise
		thisIterator = thisIterator->next; 
		thatIterator = thatIterator->next; 
	}
	return(1); 
}

// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state. 
void clear(List L){
	if (L == NULL){
		printf("List Error: calling clear() on NULL List reference\n"); 
		exit(1); 
	}

	// delete all elements of List
	while (length(L) > 0) {
		deleteFront(L); 
	}

	// set fields to original state
	L->length = 0; 
	L->index = -1; 
	L->front = L->back = L->iterator = NULL; 
}

// If List is non-empty, places the cursor under the 
// front element, else does nothing. 
void moveFront(List L){
	if (L == NULL){
		printf("List Error: calling moveFront() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) > 0){
		L->iterator = L->front; 
		L->index = 0; 
	}
}

// If List is non-empty, places the cursor under the back
// element, otherwise does nothing. 
void moveBack(List L){
	if (L == NULL){
		printf("List Error: calling moveBack() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) > 0) {
		L->iterator = L->back; 
		L->index = length(L) - 1; 
	}
}

// If cursor is defined and not at front, moves cursor one 
// step toward front of this List, if cursor is defined and 
// at front, it becomes undefined, else cursor does nothing.
void movePrev(List L){
	if (L == NULL){
		printf("List Error: calling movePrev() on NULL List reference\n"); 
		exit(1); 
	}
	// if iterator is defined and index is nonzero
	// move cursor back one node
	if (L->iterator != NULL && L->index != 0){
		L->iterator = L->iterator->prev; 
		L->index = L->index - 1; 
	}
	// else make it undefined 
	else if (L->index == 0){
		L->iterator = NULL; 
		L->index = -1; 
	}

}

// If cursor is defined and not at back, moves cursor one step
// toward back of this List, if cursor is defined and at back, 
// cursor becomes undefined, if cursor is undefined does nothing. 
void moveNext(List L){
	if (L == NULL){
		printf("List Error: calling moveNext() on NULL List reference\n"); 
		exit(1); 
	}
	// if iterator is defined and index is not at end of List
	// move cursor forward one node
	if (L->iterator != NULL && index(L) != length(L) - 1){
		L->iterator = L->iterator->next; 
		L->index++; 
	}
	// else make it undefined 
	else if (index(L) == length(L) - 1){
		L->iterator = NULL; 
		L->index = -1; 
	}
}

// Insert new element into this List. If List is non-empty, 
// insertion takes place before front element. 
// f -> f' 
void prepend(List L, int data){
	if (L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n"); 
		exit(1); 
	}

	// create a new List node 
	Node N = newNode(data); 

	// if length of List is zero,
	// make front and back point at new node 
	if (length(L) == 0)
		L->front = L->back = N; 
	else{ // else make N new front and update index
		N->next = L->front; 
		L->front->prev = N; 
		L->front = N; 

		if (index(L) != -1)
			L->index++;
	}
	L->length++;

	N = NULL;   
}

// Insert new element into this List. If List is non-empty, 
// insertion takes place after back element. 
// maybe free newNode
// b' -> b
void append(List L, int data){

	if (L == NULL){
		printf("List Error: calling append() on NULL List reference\n"); 
		exit(1); 
	} 
	// create a new List node 
	Node N = newNode(data); 

	// if length of List is zero,
	// make front and back point at new node
	if (length(L) == 0){
		L->front = L->back = N; 
	}
	else{ // else make N new back
		L->back->next = N; 
		N->prev = L->back;  
		L->back = N; 
	}
	L->length++; 

	N = NULL; 
}

// Insert new element before cursor. 
// Pre: len > 0, index() >= 0
void insertBefore(List L, int data){
	if (L == NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) == 0){
		printf("List Error: calling insertBefore() on empty List\n"); 
		exit(1); 
	}
	// if index is zero, prepend 
	if (index(L) == 0)
		prepend(L, data); 
	// else if there are more than 1 nodes and
	// the index is greater than zero, 
	// add it before underscored element
	else if (length(L) > 0 && index(L) > 0){

		Node N = newNode(data); 

		N->prev = L->iterator->prev; 
		L->iterator->prev->next = N; 
		N->next = L->iterator; 
		L->iterator->prev = N; 

		L->index++; 
		L->length++;
	}
}

// Inserts new element after cursor. 
// Pre: len > 0, index() >= 0
void insertAfter(List L, int data){
	if (L == NULL){
		printf("List Error: calling insertAfter() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) == 0){
		printf("List Error: calling insertAfter() on empty List\n"); 
		exit(1); 
	}
	// if index is at end of list, prepend **
	if (index(L) == length(L) - 1)
		append(L, data); 
	// else if there are more than 1 nodes and
	// the index is greater than or equaal to zero, 
	// add it after underscored element
	else if (length(L) > 0 && index(L) >= 0){

		Node N = newNode(data); 

		N->next = L->iterator->next; 
		L->iterator->next->prev = N; 
		N->prev = L->iterator; 
		L->iterator->next = N;

		L->length++;
	}
}

// Deletes the front element
// Pre: len > 0 
void deleteFront(List L) {
	Node N = NULL; 

	if (L == NULL){
		printf("List Error: calling deleteFront() on NULL List reference\n"); 
		exit(1); 
	}
	if(length(L) == 0){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
  	}

	N = L->front;

	// if index is zero, make cursor off end  
	if (index(L) == 0)
		L->iterator = NULL; 
	// update front to front next
	if (length(L) > 1){
		L->front = L->front->next;
	}
	else // its length is 1, set to NULL
		L->front = L->back = NULL;

	L->index--; 
	L->length--; 
	freeNode(&N); 
}

// Deletes the back element
// Pre: len > 0
void deleteBack(List L){

	if (L == NULL){
		printf("List Error: calling deleteBack() on NULL List reference\n"); 
		exit(1); 
	}
	if(length(L) == 0){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
  	}

	Node N = L->back; 

	// if index is at end of List, make
	// cursor undefined 
	if (index(L) == length(L) - 1) {
		L->iterator = NULL; 
		L->index = -1; 
	}
	// update back to back prev 
	if (length(L) > 1){
		L->back = L->back->prev;
	}
	else // its length is 1, set to NULL
		L->front = L->back = NULL;

	L->length--; 
	freeNode(&N); 
}

// Deletes cursor element, making cursor undefined. 
// Pre: length()>0, index()>=0
// this is giving me leaks 
void delete(List L){
	if (L == NULL ){
		printf("List Error: calling delete() on NULL List reference\n"); 
		exit(1); 
	}
	if (length(L) == 0){
		printf("List Error: calling delete() on an empty List\n"); 
		exit(1); 
	}
	if (index(L) == -1){
		printf("List Error: calling delete() on undefined List cursor\n"); 
		exit(1); 
	}

	// to delete element
	Node N = NULL; 

	// delete front if cursor underscores front
	if (index(L) == 0)
		deleteFront(L); 
	// delete back if cursor underscores back
	else if (index(L) == length(L) - 1)
		deleteBack(L); 
	// otherwise, get node to be deleted and 
	// adjust the prev and next Nodes 
	else if (length(L) > 0 && index(L) > 0){

		// get element to be deleted 
		N = L->iterator; 

		L->iterator->prev->next = L->iterator->next; 
		L->iterator->next->prev = L->iterator->prev; 

		L->iterator = NULL; 
		L->index = -1; 
		L->length--;

		freeNode(&N); 
	}

}

// Other operations ----------------------------------------------------------- 

// Prints data elements in L to an output file. 
void printList(FILE* out, List L){

	if (out == NULL){
		printf("List Error: calling printList() on NULL FILE reference\n"); 
		exit(1);
	}
	if (L == NULL){
		printf("List Error: calling printList() on NULL List reference\n"); 
		exit(1);
	}

	// print out empty string 
	if (length(L) == 0)
		fprintf(out, " "); 

	// start node at front of List
	Node N = NULL; 
	N = L->front; 

	// print out until next to last 
	while (N->next != NULL){
		fprintf(out, "%d ", N->data); 
		N = N->next;
	}
	
	// print out last elt without subsequent space
	fprintf(out, "%d", N->data); 

	N = NULL; 

}

// Returns a new List representing the same integer 
// sequence as this List. The cursor in the new list 
// is undefined, regardless of the state of the cursor 
// in this List. This List is unchanged. 
List copyList(List L){
	if (L == NULL ){
		printf("List Error: calling copyList() on NULL List reference\n"); 
		exit(1); 
	}
	// create new list
	List nL = newList(); 

	// return empty list if L is empty
	if (length(L) == 0)
		return(nL);

	Node N = NULL; 
	N = L->front; 

	// iterate over source List and append each node value
	// to list copy
	while(N != NULL) {
		append(nL, N->data); 
		N = N->next; 
	}
	return(nL); 
}

// Extra operations ----------------------------------------------------------- 

// Returns a new List that is a concatentation of 
// elements starting in A and ending in B. 
List concatList(List A, List B){
	if (A == NULL || B == NULL){
		printf("List Error: calling concatList() on NULL List reference(s)\n"); 
		exit(1); 
	}

	// make copy of List A and List B
	List cA = copyList(A); 
	List cB = copyList(B); 

	// make last node of the "first half" of 
	// the new list point to first node of 
	// "last half" and vice versa
	cA->back->next = cB->front; 
	cB->front->prev = cA->back; 

	// now cA will be the concatenation of 
	// cA and cB
	return(cA); 
}