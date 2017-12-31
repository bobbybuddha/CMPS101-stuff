// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 3 - Matrix Operators
// File: Sparse.java 
// Description: 
//-----------------------------------------------------------------------------
// Sparse is the top level client that implements Matrix.java. It performs
// various operations on input Matrices, where the size and non zero entries 
// are read in from a file. The results are then written to an output file. 
//-----------------------------------------------------------------------------

import java.io.*; 
import java.util.*; 

public class Sparse{

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
		// open input and output file 
		Scanner inFile = new Scanner(new File(args[0]));
		PrintWriter outFile = new PrintWriter(new FileWriter(args[1]));  
		String [] strArr = null; 

		// uncomment out later 
		// create a new array list 
		ArrayList<String> readIn = new ArrayList<String>(); 

		// get first line of file
		readIn.add(inFile.nextLine());

		// gets line at first index 
		String line = readIn.get(0); 

		// need to convert to int
		// assume they're not single digit
		// tokenize string 
		String[] splitS = line.split(" "); 
		int n = Integer.parseInt(splitS[0]); // gets n
		int a = Integer.parseInt(splitS[1]); // gets a
		int b = Integer.parseInt(splitS[2]); // gets b
		int i, j; 
		double v;  
		// to skip newline 
		inFile.nextLine(); 

		// create Matrices
		Matrix A = new Matrix(n); 
		Matrix B = new Matrix(n); 

		// adding in Matrix A's entries
		// reading out a entries
		for (int k = 0; k < a; k++){

			line = inFile.nextLine();
			splitS = line.split(" ");
			i = Integer.parseInt(splitS[0]); // gets n
		    j = Integer.parseInt(splitS[1]); // gets a
			v = Double.parseDouble(splitS[2]); // value

			A.changeEntry(i,j,v); 
		}
		inFile.nextLine();

		// reading out b entries
		for (int k = 0; k < b; k++){

			line = inFile.nextLine();
			splitS = line.split(" ");
			i = Integer.parseInt(splitS[0]); // gets n
		    j = Integer.parseInt(splitS[1]); // gets a
			v = Double.parseDouble(splitS[2]); // value

			B.changeEntry(i,j,v);
		}


		// writing to outfile
		outFile.println("A has " + a + " non-zero entries:\n" + A);
		outFile.println("B has " + b + " non-zero entries:\n" + B);
		outFile.println("(1.5)*A =\n" + A.scalarMult(1.5));
		outFile.println("A+B =\n" + A.add(B));
		outFile.println("A+A =\n" + A.add(A));
		outFile.println("B-A =\n" + B.sub(A));
		outFile.println("A-A =\n" + A.sub(A));
		outFile.println("Transpose(A) =\n" + A.transpose());
		outFile.println("A*B =\n" + A.mult(B));
		outFile.println("B*B =\n" + B.mult(B));

		inFile.close();
		outFile.close();
	}
}