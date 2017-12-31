// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 3 - Matrix Operators
// File: Matrix.java 
// Description: 
//-----------------------------------------------------------------------------
// The Matrix class is used to represent matrices and various operations on 
// them. It implements fast run times assuming the matrices are sparse. 
//-----------------------------------------------------------------------------

public class Matrix{

	private class Entry{

		// fields
		int col; 
		double val; 

		// Constructor for the Entry class
		Entry(int col, double val){
			this.col = col;
			this.val = val; 
		}

		// determines whether data of two 
		// entries are equal,
		// col and data must be the same
		public boolean equals(Object o){
	 		if (o instanceof Entry){
				Entry temp = (Entry)o; 
				return temp.val == this.val && 
				temp.col == this.col;  
			}
			else
				return false; 
		}

		// Overloaded toString method 
		// prints (col, val)
		public String toString(){
			return "(" + col + ", " + val + ")"; 
		}
	}

	// Fields
	private int size; 
 	private int nnzEntries; 
	private List [] mat; 


	// Constructor
	// Makes a new n x n zero Matrix. pre: n>=1
	Matrix(int n){
		if (n >= 1){

			size = n; 
			nnzEntries = 0; 
			// make a new matrix of n Lists
			mat = new List[size];

			// instantiate array
			for (int i = 0; i < size; i++)
				mat[i] = new List(); 
			
		}
		else throw new RuntimeException("Error," + 
			" Matrix size must be non-zero"); 
	}

	// Access functions

	// Returns n, the number of rows and columns of this Matrix
	int getSize(){
		return size; 
	} 

	// Returns the number of non-zero entries in this Matrix
	int getNNZ(){
		return nnzEntries; 
	}

	// overrides Object's equals() method
 	public boolean equals(Object x){

 		if (x instanceof Matrix){

 			Matrix temp = (Matrix)x; 

 			if (temp.getSize() != this.getSize())
 				return false; 

 			// iterate through each matrix row and 
 			// check if rows are the same
 			for (int i = 0; i < this.getSize(); i++){
 				// checks if corresponding Lists contain same 
 				// sequence of Entry objects
 				if (!this.mat[i].equals(temp.mat[i]))
 					return false;  
 			}
 			return true; 
 		}
 		return false; 
 	}

	// Manipulation procedures

	// sets this Matrix to the zero state
	void makeZero(){
		nnzEntries = 0; 
		// make a new matrix of n Lists
		mat = new List[size];

		// create new mat
		for (int i = 0; i < size; i++)
			mat[i] = new List(); 
	}

	// returns a new Matrix having the same entries as this Matrix 
	Matrix copy(){
		if (this.getNNZ() == 0 || this.getSize() == 0)
			return new Matrix(this.getSize()); 

		Matrix matCopy = new Matrix(this.getSize()); 
		Entry temp;  

		for (int i = 0; i < this.getSize(); i++){

			mat[i].moveFront(); 

			while (mat[i].index() != -1){

				temp = (Entry)mat[i].get(); 
				// append entry to matCopy
				matCopy.changeEntry(++i,temp.col,temp.val);
				--i; 
				mat[i].moveNext(); 
			}

		}
		return matCopy; 
	}

	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x) {
		// increment nnzEntries for each entry added
		if (i >= 1 && i <= this.getSize() 
			&& j >= 1 && j <= this.getSize()){
			// adjust row index to make it base zero
			i -= 1;
			Entry e = null;
			boolean found = false;

			mat[i].moveFront();

			// if the length is greater than 0
			if (mat[i].length() > 0)
				e = (Entry)mat[i].get();
			// check if it needs to be placed before first entry
			if (mat[i].length() > 0 && x != 0 && j < e.col ){
				mat[i].prepend(new Entry(j,x));
				found = true;  
				nnzEntries++; 
				
			}else{
			// other wise, iterate through list to find where 
			// it should be placed
				while (mat[i].index() != -1 && !found){
					// iterate until you find position for it
					e = (Entry)mat[i].get(); 
					if (e.col == j){
						if (x != 0){ // replace if not 0
							mat[i].insertAfter(new Entry(j,x));
							mat[i].delete(); 
							found = true;  
							break;
						}else{ // else remove it
							mat[i].delete(); 
							nnzEntries--; 
							found = true; 
							break;
						}
					} // if j is less than entry's column, break
					if (j < e.col)
						break; 
					// else keep iterating until its bigger than e.col
					mat[i].moveNext(); 
				}


				// check if index == -1 => it wasnt found
				if (mat[i].index() == -1 && !found){
					if (x != 0){ // means it goes at end of list
						mat[i].append(new Entry(j,x)); 
						nnzEntries++; 
					}
				}

				// if it breaks before j > e.col
				if (mat[i].index() != -1 && !found){
					if (x != 0){ // insert before whatever it was <
						mat[i].insertBefore(new Entry(j,x)); 
						found = true; 
						nnzEntries++; 
					}
				}

			}
		}
		else throw new RuntimeException("Error, out of Matrix_ bounds");
	}

	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x){

		Matrix scaled = new Matrix(this.getSize());
		Entry temp;

		if (x == 0 || this.getNNZ() == 0)
			return scaled;

		if (this.getSize() > 0){

			// Outer loop runs n times, inner loop 
			// runs a fraction of a times, where sum
			// of inner loop runs sums to a
			// thus runs in O(n + a)

			for (int i = 0; i < this.getSize(); i++){

				// start at front of row vector
				mat[i].moveFront(); 

				while (mat[i].index() != -1){ 
					// multiply it
					temp = (Entry)mat[i].get(); 
					scaled.changeEntry(++i,temp.col, x*temp.val); 
					--i; // decrement for base 0
					mat[i].moveNext();  
				}
			}
		}
		return scaled; 
	}


	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize() == M.getSize()
	Matrix add(Matrix M){
		if (this.getSize() == M.getSize()){
			Matrix sum = new Matrix(this.getSize());

			// Make copy of this object so it won't be changed
			Matrix C = this.copy();  

			// add corresponding rows
			for (int i = 0; i < this.getSize(); i++){
				sum.mat[i] = sum.addRows(C.mat[i], M.mat[i]);  
			}
			return sum; 
		}
		else throw new RuntimeException("Error, matrix M is different size"); 
	}

	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize() == M.getSize()
	// pass in val by reference
	Matrix sub(Matrix M){
		if (this.getSize() == M.getSize()){
			Matrix sub = new Matrix(this.getSize());

			// Make copy of this object so it won't be changed
			Matrix C = this.copy();  

			// subtract corresponding rows
			for (int i = 0; i < this.getSize(); i++)
				sub.mat[i] = sub.subRows(C.mat[i], M.mat[i]); 
			return sub; 
		}
		else throw new RuntimeException("Error, matrix M is different size"); 
	}

	// returns a new Matrix that is the transpose of this
	// (across main diagonal since square matrices only)
	// going to have to shift array like in scalar mult
	Matrix transpose(){

		Matrix T = new Matrix(this.getSize()); 
		Entry temp = null; 

		// iterate over this list and add Aij as Aji in 
		// new matrix
		for (int i = 0; i < this.getSize(); i++){
			mat[i].moveFront(); 
			while (mat[i].index() != -1){
				temp = (Entry)mat[i].get(); 
				T.changeEntry(temp.col,++i,temp.val);
				--i;  
				mat[i].moveNext(); 
			}
		}

		return T; 
	}

	// returns a new Matrix that is the product of this Matrix with M 
	// pre: getSize() == M.getSize()
	Matrix mult(Matrix M){

		if (this.getSize() != M.getSize())
			throw new RuntimeException("Error, matrix M is different size"); 

		Matrix prod = new Matrix(this.getSize());  
		// transpose Matrix M
		Matrix T = M.transpose(); 
		double val = 0;
		int row, col;  

		// iterate through both lists and multiply 
		// corresponding col vectors of this and 
		// row vectors of M
		for (int i = 0; i < this.getSize(); i++){
			row = i + 1; 
			for (int j = 0; j < M.getSize(); j++){ 
				val = dot(this.mat[i],T.mat[j]);
				col = j + 1;  
				if (val != 0) 
					prod.changeEntry(row,col, val);
			} 
		}
		return prod; 
	}

	// Other functions
	
	// overrides Object's toString() method
	public String toString(){

		StringBuilder output = new StringBuilder(); 

		if (this.getNNZ() == 0 || this.getSize() == 0)
			return ""; 

		int i = 0; 

		for (; i < this.getSize(); i++){

			if (mat[i].length() != 0)
				output.append((i + 1) + ": " + mat[i] + "\n");
		}

		return output.toString();  
	}

	// multiples corresponding elements of P and Q 
	// while summing the resulting products, 
	// then returns the sum
	private static double dot(List P, List Q) { 
		if (P.length() == 0 || Q.length() == 0)
			return 0; 

		double sum = 0; 
		// move cursors to front
		P.moveFront(); 
		Q.moveFront(); 

		Entry e1, e2; 
		e1 = e2 = null; 

		// Aij * Bij + Ai,j+1 * Bi,j+1 + . . . + Ai,n * Bi,n
		// has to traverse list until it finds it
		while(P.index() != -1 && Q.index() != -1){

			e1 = (Entry)P.get(); 
			e2 = (Entry)Q.get();

			// if P's col is less, move P up, 
			// and then sum of that product is
			// assumed to be zero
			if (e1.col < e2.col)
				P.moveNext();
			// same but for Q's col
			else if (e2.col < e1.col)
				Q.moveNext();
			else{// else they're equal 
				sum += e1.val * e2.val; 
				P.moveNext(); 
				Q.moveNext(); 
			}
		}
		return sum; 
	}

	// P + Q
	// have to find way to keep track of nnz
	private List addRows(List P, List Q){

		// if both lengths are zero, implies 
		// both are all zero, return null 
		if (P.length() == 0 && Q.length() == 0) 
			return new List();

		// create new sum of rows 
		List sumRow = new List(); 

		Entry tempP = null; 
		Entry tempQ = null; 

		P.moveFront(); 
		Q.moveFront(); 

		// iterate over lists and add corresponding entries
		// while larger list is not off end
		while(P.index() != -1 && Q.index() != -1){

			tempP = (Entry)P.get();
			tempQ = (Entry)Q.get();



			// if columns are the same, append sum of them
			if (tempP.col == tempQ.col){
				if (tempP.val + tempQ.val != 0){
					sumRow.append(new Entry(tempP.col, tempP.val + tempQ.val));
					this.nnzEntries++; 
				}
				P.moveNext(); 
				Q.moveNext();
			}
			// else if P col < Q col, append P entry first then Q entry
			else if (tempP.col < tempQ.col){
				sumRow.append(new Entry(tempP.col, tempP.val));
				this.nnzEntries++; 
				P.moveNext(); 
			}
			else{ // else do it other way around
				sumRow.append(new Entry(tempQ.col, tempQ.val));
				this.nnzEntries++; 
				Q.moveNext();    
			}
 
		}

		// if one of them is still not off end
		// add rest of entries from P or Q into 
		// sumRows
		if (P.index() >= 0 && Q.index() == -1){
			while(P.index() != -1){
				tempP = (Entry)P.get(); 
				sumRow.append(new Entry(tempP.col, tempP.val));
				this.nnzEntries++;  
				P.moveNext();  
			}
		}
		else if (P.index() == -1 && Q.index() >= 0){
			while(Q.index() != -1){
				tempQ = (Entry)Q.get(); 
				sumRow.append(new Entry(tempQ.col, tempQ.val));
				this.nnzEntries++; 
				Q.moveNext();  
			}
		}

		return sumRow; 
	}

	// P - Q
	// have to find way to keep track of nnz
	private List subRows(List P, List Q){
		// if both lengths are zero, implies 
		// both are all zero, return null 
		if (P.length() == 0 && Q.length() == 0)
			return new List();
		

		// create new difference of rows 
		List subRow = new List(); 

		Entry tempP = null; 
		Entry tempQ = null; 

		P.moveFront(); 
		Q.moveFront(); 

		// iterate over lists and add corresponding entries
		// while larger list is not off end
		while(P.index() != -1 && Q.index() != -1){

			tempP = (Entry)P.get();
			tempQ = (Entry)Q.get(); 

			// if columns are the same, append difference of them
			if (tempP.col == tempQ.col){
				if (tempP.val - tempQ.val != 0){
					subRow.append(new Entry(tempP.col, tempP.val - tempQ.val));
					this.nnzEntries++;
				}
				P.moveNext(); 
				Q.moveNext();
			}
			// else if P col < Q col, append P entry first then Q entry
			else if (tempP.col < tempQ.col){
				subRow.append(new Entry(tempP.col, tempP.val));
				this.nnzEntries++;  
				P.moveNext();  
			}
			else{ // else do it other way around
				subRow.append(new Entry(tempQ.col, 0 - tempQ.val));
				this.nnzEntries++; 
				Q.moveNext(); 
			}
 
		}

		// if one of them is still not off end
		// add rest of entries from P or Q into 
		// subRows
		if (P.index() >= 0 && Q.index() == -1){
			while(P.index() != -1){
				tempP = (Entry)P.get(); 
				subRow.append(new Entry(tempP.col, tempP.val));
				this.nnzEntries++; 
				P.moveNext();  
			}
		}
		else if (P.index() == -1 && Q.index() >= 0){
			while(Q.index() != -1){
				tempQ = (Entry)Q.get(); 
				subRow.append(new Entry(tempQ.col, 0 - tempQ.val));
				this.nnzEntries++; 
				Q.moveNext();  
			}
		}

		return subRow;
	}

}