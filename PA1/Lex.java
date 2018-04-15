// Assignment Name: Programming Assignment 1 -- List ADT
// File: Lex.java 
// Description: 
//-----------------------------------------------------------------------------
// Lex.java is the client that implements the List ADT  in order to sort the 
// elements of an input array, read as strings from a file, indirectly. 
//-----------------------------------------------------------------------------


import java.io.*; 
import java.util.*; 

public class Lex{

	public static void main(String[] args) throws IOException{

		// first check if args.length is within bounds
		if (args.length != 2) {
         // report to std err
			System.err.println("Warning, insufficient command " + 
				"line arguments");
			System.exit(420);  
		}

        // intialize inFile and outFile objects with args[0] and args[1]
        // being the file names

		Scanner inFile = new Scanner(new File(args[0]));
		PrintWriter outFile = new PrintWriter(new FileWriter(args[1]));  
		String [] strArr = null; 


		// create a new array list 
		ArrayList<String> readIn = new ArrayList<String>(); 

		while (inFile.hasNextLine()) {

			// read in line and add to array list
			readIn.add(inFile.nextLine());
		}

		// get array version of all elements 
		strArr = new String[readIn.size()]; 
		strArr = readIn.toArray(strArr);

		// create a new List
		List L = new List(); 

		// start at index 0
		L.append(0); 
		int j = 0; 

		for (int i = 1; i < strArr.length; i++) {

			// move cursor to back
			L.moveBack(); 

			while (L.index() >= 0) {

				// get current index in List
				j = L.get();

				// if current string is less than or equal to List string
				if (strArr[i].compareTo(strArr[j]) < 0){

					// move down the list 
					L.movePrev(); 
				}
				else
					break; 
			}

			// if cursor is undefined, that means it was less than everything
			// in List, so it will be the new front 
			if (L.index() == -1){
				L.prepend(i); 
			} // else if index is still 0 and the str[i] is less than front
			// it becomes new front 
			else if (L.index() == 0 && strArr[i].compareTo(strArr[j]) < 0)
				L.prepend(i); 
			else // otherwise, just insert it after whatever it was not less than
				L.insertAfter(i); 

		}


	  	// start at front 
		L.moveFront(); 

      	// writing to file
		for (int i = 0; i < L.length(); i++) {
         	// write to file 
			outFile.println(strArr[L.get()]); 
			L.moveNext(); 
		}

		inFile.close();
		outFile.close();
	}
}
