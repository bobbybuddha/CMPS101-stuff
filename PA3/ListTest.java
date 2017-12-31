// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 3 - Matrix Operators
// File: ListTest.java 
// Description: 
// -----------------------------------------------------------------------------
//  A test client for the List ADT. 
// -----------------------------------------------------------------------------

public class ListTest{
	
	public static void main(String[] args){

		List N = new List(); 

		N.append(1);


		System.out.println("First:" + N); 


		N.moveFront(); 
		N.deleteFront(); 
		N.prepend(2); 

		System.out.println("Second:" + N); 

		List K = new List(); 
		List L = new List(); 

		for (int i = 0; i < 3; i++){
			K.append(i); 
			L.append(i); 
		}

		System.out.println(K.equals(L));

		List A = new List();
		List B = new List();

		for(int i=1; i<=20; i++){
		 A.append(i);
		 B.prepend(i);
		}
		System.out.println(A);
		System.out.println(B);

		for(A.moveFront(); A.index()>=0; A.moveNext()){
		 System.out.print(A.get()+" ");
		}
		System.out.println();
		for(B.moveBack(); B.index()>=0; B.movePrev()){
		 System.out.print(B.get()+" ");
		}
		System.out.println();

		A.moveFront();
		for(int i=0; i<5; i++) A.moveNext(); // at index 5
		A.insertBefore(-1);                  // at index 6
		for(int i=0; i<9; i++) A.moveNext(); // at index 15
		A.insertAfter(-2);
		for(int i=0; i<5; i++) A.movePrev(); // at index 10
		A.delete();
		System.out.println(A);
		System.out.println(A.length());
		A.clear();
		System.out.println(A.length());
	}
}