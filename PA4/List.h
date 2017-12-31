// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 4 -- Graph ADT
// Description: 
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type --------------------------------------------------------------
// Used for type definition 
typedef struct ListObj* List;

// Constructors-Destructors --------------------------------------------------- 

// newQueue()
// Returns reference to new empty List object. 
List newList(void); 

// freeList()
// Frees all heap memory associated with List *pQ, and List *pQ to NULL
void freeList(List* pL);

// Access functions ----------------------------------------------------------

// Returns the number of elements in this List.
// Post: Integer is returned representing length of 
// the list
int length(List L);

// If cursor is defined, returns the index of the 
// cursor element, otherwise returns -1 
// Pre: iterator is referencing List element
// Post: Returns data contained in element, otherwise
// returns -1
int index(List L);

// Returns front element. 
// Pre: len > 0
int front(List L);

// Returns back element. 
// Pre: len > 0
int back(List L);

// Returns cursor element.
// Pre: len > 0, index() >= 0
int get(List L);

// Returns true iff this List and L are the  same 
// integer sequence. The cursors of either List are 
// not used in the comparison of the respective
// Lists. 
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state. 
void clear(List L);

// If List is non-empty, places the cursor under the 
// front element, else does nothing. 
void moveFront(List L);

// If List is non-empty, places the cursor under the back
// element, otherwise does nothing. 
void moveBack(List L);

// If cursor is defined and not at front, moves cursor one 
// step toward front of this List, if cursor is defined and 
// at front, it becomes undefined, else cursor does nothing.
void movePrev(List L);


// If cursor is defined and not at back, moves cursor one step
// toward back of this List, if cursor is defined and at back, 
// cursor becomes undefined, if cursor is undefined does nothing. 
void moveNext(List L);

// Insert new element into this List. If List is non-empty, 
// insertion takes place before front element. 
// f -> f' 
void prepend(List L, int data);

// Insert new element into this List. If List is non-empty, 
// insertion takes place after back element. 
// b' -> b
void append(List L, int data);

// Insert new element before cursor. 
// Pre: len > 0, index() >= 0
void insertBefore(List L, int data);

// Inserts new element after cursor. 
// Pre: len > 0, index() >= 0
void insertAfter(List L, int data);

// Deletes the front element
// Pre: len > 0 
void deleteFront(List L);

// Deletes the back element
// Pre: len > 0
void deleteBack(List L);

// Deletes cursor element, making cursor undefined. 
// Pre: length()>0, index()>=0
void delete(List L);

// Other operations ----------------------------------------------------------- 

// Prints data elements in L on an output file. 
void printList(FILE* out, List L);

// prints the L to the file pointed to by out,
// formatted as a space-separated string.
List copyList(List L);

// Extra operations ----------------------------------------------------------- 

// Returns a new List that is a concatentation of 
// elements starting in A and ending in B. 
List concatList(List A, List B);

#endif
