// Name: Bobby Singh Dhillon
// CruzID: bosdhill
// ID number: 1594478
// Assignment Name: Programming Assignment 3 - Matrix Operators
// File: MatrixTest.java 
// Description: 
//-----------------------------------------------------------------------------
// MatrixTest.java tests the Matrix class.
//-----------------------------------------------------------------------------

import java.util.Random;

// indexing errors...
public class MatrixTest{

	public static void main(String[] args){


   // System.out.println(someFunc4()); 

	// my tests
	Matrix A = new Matrix(10);
    Matrix B = new Matrix(15);
    Matrix C = null; 
    Matrix D = new Matrix(2); 


    D.changeEntry(1,1,1); 
    D.changeEntry(1,2,1); 
    D.changeEntry(2,1,1); 
    D.changeEntry(2,2,1); 

    System.out.println("D:\n" + D); 
   	D = D.mult(D); // one off 
   	System.out.println("D * D:\n" + D);
   	System.out.println("D + D:\n" + D.add(D) + 
        "\nNNZ: " + D.add(D).getNNZ()); 
   	C = D.add(D);
   	System.out.println("2D - D:\n" + C.sub(D)); 
   	System.out.println("C = D - 2D:\n" + D.sub(C));
   	System.out.println("D + C:\n" +  D.add(D.sub(C)) + 
        "\nnum entries: " + D.add(D.sub(C)).getNNZ());
   	System.out.println("D - D:\n" + D.sub(D) + 
        "\nnum entries: " + D.sub(D).getNNZ()); 


	Random rand = new Random();
	int n; 

	// 3 x 3 matrix 
	Matrix o = new Matrix(3); 

	// adding entries 
	o.changeEntry(1,1,2); 
	o.changeEntry(3,1,5); 
	o.changeEntry(1,2,4.5); 

	System.out.println("A:\n" + o); 

	o.changeEntry(1,1,3); 
	System.out.println("A:\n" + o);

	System.out.println(o.equals(o)); 

//	System.out.println(someFunc()); 

	o.changeEntry(1,1,0);
	System.out.println("NNZ: " + o.getNNZ());
	o.changeEntry(3,1,0);
	System.out.println("NNZ: " + o.getNNZ());
	o.changeEntry(1,2,0); 
	System.out.println("NNZ: " + o.getNNZ());
	o.changeEntry(1,1,0);  
	System.out.print("A:\n" + o);
	System.out.println("NNZ: " + o.getNNZ());

	// transposing matrix 
	Matrix t = o.transpose(); 

    System.out.println("T(A):\n" + t);

    System.out.println("T(A) NNZ: " + t.getNNZ()); 

    // cant add if zero
    Matrix Z = t.add(o); 
    System.out.println("T(A) + A:\n" + Z);

    Z = t.sub(o); 
    System.out.println("T(A) - A:\n" + Z);   

	o = new Matrix(6); 

	// creating randomly generated matrix
	for (int i = 1; i <= o.getSize(); i++){

		for (int j = 1; j <= o.getSize(); j++){

			n = rand.nextInt(i + j) + i; 

			o.changeEntry(i ,j , n); 
		}
	}

	// testing tranpose
	System.out.println("B:\n"+ o); 
	System.out.println("T(B):\n"+ o.transpose());

	System.out.println("T(B) * B:\n" + o.mult(o.transpose())); 

	// 3 x 3 

	Matrix k = new Matrix(2); 

	k.changeEntry(1,1,1); 
	k.changeEntry(1,2,0); 
	k.changeEntry(2,1,1); 
	k.changeEntry(2,2,2); 

	System.out.println("N:\n" + k);
	// problem in multiply
	System.out.println("N*N:\n" + k.mult(k));

	System.out.println("2N:\n" + k.scalarMult(2)); 

	System.out.println("-2N:\n" + k.scalarMult(-2));

	Z = k.scalarMult(-1); 

	System.out.println("Z:\n" + Z);

	System.out.println("Z - Z:\n" + Z.add(Z));  

	// System.out.println(someFunc2());
	// System.out.println(someFunc3()); 
	// System.out.println(someFunc4());  

	System.out.println("O:\n" + o); 

	o.changeEntry(1,1,2.42); 

	o.changeEntry(2,1,2.2321); 

	System.out.println("O:\n" + o); 

	A = new Matrix(10);


    A.changeEntry(1, 1, 2.1);
    A.changeEntry(2, 2, 1);
    A.changeEntry(3, 3, 1);
    A.changeEntry(1, 1, 1.2);
    A.changeEntry(2, 2, 5);


    A.changeEntry(1, 2, 2);
 	A.changeEntry(3, 1, 7);
	A.changeEntry(3, 3, 9);
    A.changeEntry(3, 2, 8);
    A.changeEntry(1, 3, 3);
    A.changeEntry(2, 1, 4);
    System.out.print(A); 
    System.out.print("A*A:\n" + A.mult(A)); 




    B.changeEntry(1, 1, 1);
    B.changeEntry(2, 2, 1); // changeEntry is fucked again...
    System.out.println("B:\n" + B); 
    System.out.println("A:\n" + A); 
    C = A.mult(B);
    System.out.println("C:\n" + C); 


	}

// 	static int someFunc2(){
//  		Matrix A = new Matrix(10);
//         A.changeEntry(2, 1, 2);
//         A.changeEntry(3, 1, 5);
//         A.changeEntry(1, 2, 2);
//         A.changeEntry(1, 3, 5);
//         A.changeEntry(1, 1, 4);
//         A.changeEntry(2, 2, 2);
//         A.changeEntry(2, 5, 0);
//         A.changeEntry(2, 3, 0);
//         A.changeEntry(3, 3, 5);

//         System.out.println(A); 
//         if (A.getNNZ() != 7) return 1;
//         A.changeEntry(1, 3, 0);
//         A.changeEntry(3, 1, 0);
//         A.changeEntry(3, 3, 0); // supposedly fucks up here
//         System.out.println(A); 
//         if (A.getNNZ() != 4) return 2;
//         A.changeEntry(7, 6, 42);
//         A.changeEntry(10, 1, 24);
//         if (A.getNNZ() != 6) return 3;
//         A.changeEntry(7, 6, 0);
//         if (A.getNNZ() != 5) return 4;
//         A.makeZero();
//         A.changeEntry(5, 5, 5);
//         if (A.getNNZ() != 1) return 5;
//         return 6; 
// 	}


// 	static int someFunc3(){
// 		Matrix A = new Matrix(10);
//         Matrix B = new Matrix(10);
//         A.changeEntry(1, 1, 1);
//         A.changeEntry(2, 2, 1);
//         A.changeEntry(3, 3, 1);
//         Matrix C = A.mult(A);
//         if (C.getNNZ() != 3) return 1;
//         A.changeEntry(1, 1, 1);
//         A.changeEntry(1, 2, 2);
//         A.changeEntry(1, 3, 3);
//         A.changeEntry(2, 1, 4);
//         A.changeEntry(2, 2, 5);
//         A.changeEntry(2, 3, 6);
//         A.changeEntry(3, 1, 7);
//         A.changeEntry(3, 2, 8);
//         A.changeEntry(3, 3, 9);
//         B.changeEntry(1, 1, 1);
//         B.changeEntry(2, 2, 1); // changeEntry is fucked again...

//         System.out.println("B:\n" + B); 
//         System.out.println("A:\n" + A); 
//         C = A.mult(B);
//         System.out.println("C:\n" + C);
//         System.out.println(C.getNNZ());
//         if (C.getNNZ() != 6) return 2;
//         return 3; 
// 	}

	// static int someFunc4(){
 //        Matrix A = new Matrix(10);
 //        Matrix B = new Matrix(15);
 //        Matrix C = null; 
 //        A.changeEntry(1, 1, 1);
 //        B.changeEntry(1, 1, 1);
 //        //if (A.equals(B)) return 1;
 //        B = new Matrix(10);
 //        A.changeEntry(1, 1, 1);
 //        A.changeEntry(1, 3, 1);
 //        B.changeEntry(1, 1, 1);
 //        B.changeEntry(1, 3, 1);
 //        //if (!A.equals(B)) return 2;
 //        A.changeEntry(1, 3, 0);
 //        //if (A.equals(B)) return 3;
 //        A.changeEntry(1, 1, 0);
 //        B.makeZero();
 //        A.changeEntry(10, 10, 10);
 //        B.changeEntry(10, 10, 10);
 //        //if (!A.equals(B)) return 4;
 //        A = new Matrix(9);
 //        B = new Matrix(9);
 //        int valcount = 1;
 //        for (int j = 1; j <= 3; j++) {
 //          for (int k = 1; k <= 3; k++) {
 //            // hint: this is 1-10000 left-to-right row-by-row
 //            A.changeEntry(j, k, valcount++);
 //          }
 //          B.changeEntry(j, j, 1); // hint: this is the identity matrix
 //        }
 //        System.out.println("A:\n" + A); 
 //        C = A.scalarMult(2);
 //        if (!C.equals(A.add(A))) return 5;
 //        C = A.scalarMult(-2);
 //        System.out.println("C:\n" + C); 
 //        System.out.println("-4A:\n" + A.sub(A).sub(A).sub(A)); // if all zero rows, 
 //        if (!C.equals(A.sub(A).sub(A).sub(A))) return 6;
 //        C = A.mult(B);
 //        if (!C.equals(A)) return 7;
 //        return 0; 
	// }

// 	static int someFunc5(){
// 		Matrix A = new Matrix(10);
//         A.changeEntry(2, 1, 2);
//         A.changeEntry(3, 1, 5);
//         A.changeEntry(1, 2, 2);
//         A.changeEntry(1, 3, 5);
//         A.changeEntry(1, 1, 4);
//         A.changeEntry(2, 2, 2);
//         A.changeEntry(2, 5, 0);
//         A.changeEntry(2, 3, 0);
//         A.changeEntry(3, 3, 5);
//         if (A.getNNZ() != 7) return 1;
//         A.changeEntry(1, 3, 0);
//         A.changeEntry(3, 1, 0);
//         A.changeEntry(3, 3, 0);
//         if (A.getNNZ() != 4) return 2;
//         A.changeEntry(7, 6, 42);
//         A.changeEntry(10, 1, 24);
//         if (A.getNNZ() != 6) return 3;
//         A.changeEntry(7, 6, 0);
//         if (A.getNNZ() != 5) return 4;
//         A.makeZero();
//         A.changeEntry(5, 5, 5);
//         if (A.getNNZ() != 1) return 5;

//         return 420; 
// 	}

// 	static int someFunc6(){
//         Matrix A = new Matrix(10);
//         Matrix B = new Matrix(10);
//         Matrix C = null; 
//         A.changeEntry(1, 1, -4);
//         A.changeEntry(1, 2, -2);
//         A.changeEntry(1, 3, 0);
//         A.changeEntry(2, 5, 4);
//         A.changeEntry(2, 1, -2);
//         A.changeEntry(3, 1, 2);
//         A.changeEntry(2, 2, -2);
//         A.changeEntry(3, 3, 0);
//         C = A.sub(A);
//        if (C.getNNZ() != 0 || A.getNNZ() != 6) return 1;
//         B.changeEntry(1, 1, -4);
//         B.changeEntry(1, 2, 0);
//         B.changeEntry(2, 1, 0);
//         B.changeEntry(2, 2, -2);
//         B.changeEntry(2, 4, 2);
//         B.changeEntry(3, 1, 2);
//         B.changeEntry(3, 2, 2);
//         B.changeEntry(7, 8, 5);
//         C = A.sub(B);
//         if (C.getNNZ() != 6) return 2;
//         return 12; 
// 	}


}