/* prime.cpp
 * Author: Henry(Trey) Cook
 * Date: 9/21/2014
 * 
 * Description: This cpp file contains a program that allows the user to choose
 * a number and an algorithm to perform on that number. Both algorithms will
 * take that number and produce an array filled with all the prime numbers 
 * smaller than the given number. The user can also select whether to print the
 * array to the screen or not.
 */

#include <iostream>
#include <math.h>
// the following directive allows you to use the user-defined class called Timer
#include "timer.h"   

using namespace std; 

/*** Clarifying Comments *******************************************************
* The below two lines are the function signatures of the algorithms that you are
* supposed to implement. The parameter array[] accepts an array as an argument
* (see prime in the main function).  Passing an array as an argument to a 
* function passes a reference (actually pointer) to the original array and 
* allows the function to modify the contents of the passed array; this is 
* similar to how lists are handled when passing them as arguments to a pass to 
* functions in Python.  For example is you pass in prime as an argument to 
* sieveErat, if you change the value array[4] inside of the sieveErat function, 
* the change will be made to prime[4] since array is a reference to prime.  
*
* parameter NUM is the number n you retrieved from the user
* parameter SIZE is the size of the array.
*
* Note: both algorithms fill an array with all the found prime values. Since the
* array[] parameter modifies the original passed argument you can use it to 
* store your found values into the prime array
*
* Note: the Trial Division algorithm will require you to find the square root of
* a value.  The C++ function that computes the square root of a number is sqrt()
* look up the sqrt function and the library that should be included in the C++ 
* reference at http://en.cppreference.com/w/
*
*******************************************************************************/ 

int findPrime(string array[], int SIZE, int prime);
void sieveErat(int array[], const int NUM, const int SIZE, Timer theTimer);
void trialDivision(int array[], const int NUM, const int SIZE);

int main() {
  
	int *prime;     // a pointer that will be used to dynamically create an array
	int size = 0;   // variable that would be used to set the size of the array
	int n = 0;		// the number that will designate which prime numbers to find
	int algorithm;  // a number that will be used to choose which algorithm to use on n
	char print;		// a character that the user uses to choose whether to print the array or not
	char userContinue;
	Timer myTimer;  // a Timer class object that you will use to time your algorithms

  

  /*** Your Code *********************************************
  * place your code that asks for user input here.  you are
  * going to need these value to set the size of array prime
  * as well as the number n and selected algorithm
  *
  * Note: when setting the variable size, it should be 
  * at least twice the value of the number n you received
  * from the user
  ***********************************************************/ 

	// Prompts the user to enter the integer that will be calculated upon and
	// store this integer in variable 'n'.
	do{
		cout << "Enter a non-zero integer n for which you want to find all the prime numbers smaller than: ";
		cin >> n;
		cout << endl;
	} while (n < 0);

	// Initializes size as double n.
	size = n * 2;

	// Prompts the user to decide which algorithm to choose and then store a value check 
	do{
		cout << "Now, decide which algorithm to use to find the prime numbers:" << endl;
		cout << "1. Find by Trial Division (enter 1 to choose this)" << endl;
		cout << "2. Find by Sieve of Eratosthemes (enter 2 to choose this)" << endl;
		cout << "Enter 1 or 2 for your choice: ";
		cin >> algorithm;
		cout << endl;
	} while ((algorithm != 1) && (algorithm != 2));

	do{
		cout << "Do you want to print the list of prime numbers to the screen?" << endl;
		cout << "Enter 'y' for yes or 'n' for no: ";
		cin >> print;
		cout << endl;
	} while ((print != 'y') && (print != 'Y') && (print != 'N') && (print != 'n'));


  /*** Clarifying Comments *****************************************************
  * the following statement creates an array using dynamic memory.  Make sure
  * you set size to a non-zero value.  Note: although prime is an array created
  * using a pointer and dynamic memory, it can be used like a regular array,
  * that is, you can assign values to prime using an index, for example:
  * 
  *      prime[3] = 7; 
  * 
  * and you can also read from the array using an index:
  * 
  *      cout << prime[3];
  *      prime[2] = prime[1] + prime[0]
  *      cout << prime[2];
  *****************************************************************************/
  prime = new int[size];
 
  
  /*** Your Code *********************************************
  * place your code that times the execution of the algorithms
  * implemented by trialDivision() and sieveErat()
  ***********************************************************/ 
  switch (algorithm){
  case 1:{
	  myTimer.Start();
	  trialDivision(prime, n, size);
	  myTimer.Stop();
	  cout << "Trial Division method on number " << n << " took " << myTimer.Seconds() << " seconds to complete." << endl;
	  break; }
  case 2:{
	  myTimer.Start();
	  sieveErat(prime, n, size, myTimer);
	  myTimer.Stop();
	  cout << "Sieve of Eratosthenes method on number " << n << " took " << myTimer.Seconds() << " seconds to complete." << endl;
	  break; }
  default:
	  cout << "Something has gone terribly wrong." << endl;
  }

  if ((print == 'y') | (print == 'Y')){
	  for (int item = 0; item < size; item++){
		  if (prime[item] != -842150451){
			  cout << "Array item " << item + 1 << ": " << prime[item] << endl;
		  }
	  }
  }


  
  /*** Clarifying Comments *****************************************************
  * for all things created using dynamic memory, you should also free up the
  * that memory when done using it (see the following statement).  
  *****************************************************************************/
  delete [] prime;
  

  return 0;  
}



/*** Your Code *****************************************************************
* Here is where you can define the functions that implement the Trial Division 
* and Sieve of Eratosthenes algorithms.  You may choose to give the signatures
* above main() bodies, or leave the signatures in place and define the functions
* here.
*******************************************************************************/ 

// Trial by Division implementation
void trialDivision(int array[], const int NUM, const int SIZE)
{
	int k;
	/* If the user entered 2 for n, then simply return this statement since
	 * a prime number must be an integer greater than 1. */
	if (NUM <= 2){
		cout << "There are no prime numbers less than 2" << endl;
	}
	/* If the user entered 3, simply return an array with 2 in it, since the
	 * square root of 3 being less than two will not function correctly in the 
	 * main loop. */
	else if (NUM == 3){
		array[0] = 2;
		k = 1;
	}
	/* If the user entered 4, return an array with 2 and 3 in it, for the same
	 * reason as with 3. */
	else if (NUM == 4){
		array[0] = 2;
		array[1] = 3;
		k = 2;
	}
	/* This houses the main body of the loop now that the special cases have been
	 * passed by. */
	else{
		array[0] = 2;
		array[1] = 3;
		k = 2;
		for (int i = 5; i < NUM; i++)						// For every number i less than the user-entered number and larger than 5 (due to the special cases)
		{
			bool isPrime = true;							// Test value initialization to track whether a number is prime or not within the loop
			float sqrtNum = sqrt(i);						// Stores the square root of the current i
			for (int j = 2; j <= sqrtNum; j++)				// For every number j between 2 and the square root of the current i
			{				
				if (i % j == 0)								// Test if i divided by j returns a remainder 
				{							
					isPrime = false;						// and if not, set isPrime to false				
				}
			}

			if (isPrime != false)							// Test if isPrime was set to false in previous loop
			{
				array[k] = i;								// If it wasn't, set the current array location to the current i
				k++;										// Increment k to the next array location to prepare for next iteration
			}
		}
	}
	 
	return;
}

//Sieve of Eratosthenes
void sieveErat(int array[], const int NUM, const int SIZE, Timer theTimer)
{
	char *intArray;										
	intArray = new char[NUM-1];								// Declare a temporary dynamic array to hold list of possible prime numbers
	int p = 2;												// Initialize P as 2, since that is the first prime regardless
	bool breakTime = false;
	Timer myTimer;

	for (int i = 0, k=2; i < NUM-1; i++, k++)
	{
		intArray[i] = ' ';									// Fills dynamic array with blank characters which will be placeholder for a possible mark
	}

	//theTimer.Start();
	for (int i = 2, k = 0; i < NUM-1; i++)					// For each number in the array
	{					
		if (intArray[i] != 'p')								// If the number has not been marked (meaning it is prime)
		{
			for (int j = p+p; j < NUM - 1; j = j + p)		// For each multiple of that prime
			{
				intArray[j] = 'p';							// Mark it as non-prime
			}
			array[k] = i;									// Place the prime in the main array
			p = i;											// Set P to this new prime
			k++;											// Increment to the next location in the main array
		}	
	}
	//theTimer.Stop();
	//cout << "time for " << NUM << " is " << theTimer.Seconds() << endl;
	delete[] intArray;
}