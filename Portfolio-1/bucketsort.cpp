/*
 * ENB241 Assignment 1: Bucket sorting
 * Name: Terrance Ockendon
 * Student Number: n8560641
 *
 * Known limitations:
 *	-Cannot process negative integers, however there is checking in place to prevent
 *   negatives being run in the program.
 *	-Bucket size is limited to 20 rows deep therefore no more than 20 numbers should
 *   should be entered into program. Otherwise the bucket array would need to be 
 *   dynamically allocated to overcome this issue.
 *  -If a char type variable is entered into the input it will either be converted
 *   from ascii to int, or the program will crash.
 */

#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;


// Constants
//=============================================================================
const unsigned int NUM_BINS = 10;   // Number of bucket bins. Fixed at 10.
const unsigned int ARRAY_SIZE = 20; // Maximum number of integers that can be entered.

// Function Declarations
//=============================================================================

// bucketSort - Performs the bucket sort algorithm on the array.
//  Precondition:  Valid array and length.
//  Postcondition: Contents of array sorted.
void bucketSort(unsigned int array[], const unsigned int length);


// getMaxDigits - Get the maximum number of digits of the numbers in the passed array.
//  Precondition:  Valid array and length.
//  Postcondition: Max number of digits returned.
unsigned int getMaxDigits(const unsigned int array[], const unsigned int length);


// getNthDigit - Get the Nth digit of a number.
//  Precondition:  N > 0
//  Postcondition: Nth digit of number returned.
unsigned int getNthDigit(unsigned int array_element, unsigned int number_place);


// toBucket - Distribute the contents of the given array into the appropriate bucket based off the Nth digit.
//  Precondition:  Bucket is initialised.
//  Postcondition: Sorts array cells to bucket nth column according to nth digit.
void toBucket(const unsigned int array[], unsigned int bucket[][NUM_BINS], const unsigned int digit_place, const unsigned int length, unsigned int c[] );


// fromBucket - Collect the contents of the given buckets into the array.
//  Precondition:  Number of cells occupied in each bucket.
//  Postcondition: Array is sorted according to nth digit. 
void fromBucket(unsigned int array[], unsigned int bucket[][NUM_BINS], unsigned int c[] );


// printArray - Prints the contents of the array to the screen.
//  Precondition:  Array filled with bucket data.
//  Postcondition: Array is printed to screen.
void printArray(const unsigned int array[], const unsigned int length);


// printBuckets - Prints the contents of the buckets to the screen.
//  Precondition:  Bucket filled with array data and number of cells occupied in each bucket column.
//  Postcondition: Bucket is printed to screen.
void printBuckets(unsigned int bucket[][NUM_BINS], const unsigned int length,  unsigned int c[], const unsigned int nth_digit );



// Functions
//=============================================================================

int main(int argc, char *argv[])
{
	unsigned int length;
	unsigned int ii;
	// test variable is of type int to allow it to be a negative number for error
	// checking. This ensures no negative numbers are in the program when it
	// begins sorting buckets.
	int test;
	// The two if/else statements below check to see if any numbers where entered
	// when the bucketSort was initialised in the command line and if so input
	// them into the array. Otherwise the program will ask the user how many 
	// values to enter and then iterately take inputs for each element.
															
															// Requirement 1.
	if(argc > 1)											
	{
		length = argc-1;
	}
	else
	{
		cout << "Number of inputs: ";
		cin >> length;
	}
	unsigned int array[length];
	if(argc > 1)
	{
		for(ii = 1; ii <= length; ii++)
		{
			test = atoi(argv[ii]);
			// test for negative integer
			if(test < 0)
			{
				cout << "Please enter a non-negative integers" << endl;
				cout << endl;
				// program ends because negative integer detected.
				return 0;
			}
			// if the integer is non-negative then is casted into unsigned int array.
			array[ii-1] = test;
			
		}
	}
	else
	{
		cout << "Enter " << length << " numbers:";
		cout << endl;
		for( ii = 0; ii < length; ii++)
		{
			cin >> test;
			// test for negative integer and request user input non-negative if negative
			while(test < 0 )
			{
				cout << "Please enter a non-negative integer" << endl;
				cout << "Enter " << length-ii << " more number(s):";
				cout << endl;
				cin >> test;
			}
			// if the integer is non-negative then is casted into unsigned int array.
			array[ii] = test;				
		}
	}
															// Requirement 2.
	cout << "Initial array: " << endl;					
	for( ii = 0; ii < length; ii++)
	{
		cout << array[ii] << " ";
	}
	cout << endl << endl;
	
	// Bucket sort function begins here:
	bucketSort(array, length);
	
}

void bucketSort(unsigned int array[], const unsigned int length)
//-----------------------------------------------------------------------------
{
	unsigned int bucket[length][NUM_BINS];
	unsigned int max_digit;
	unsigned int nth_digit;
	int x, ii, jj;
	// The declared 'c' unsigned int array below is for keeping track of how 
	// many numbers are in each bin.
	unsigned int c[NUM_BINS];

	// Sets bucket to 0 for all elements:
	for(ii = 0; ii < length; ii++)
	{
		for(jj = 0; jj < NUM_BINS; jj++)
		{
			bucket[ii][jj]=0;
		}
	}
	// Finds max number of digits:
	max_digit = getMaxDigits(array, length);	
															// Requirement 3.
	cout << "Maximum number of digits: " << max_digit << endl;
	cout << endl;
	// Loops through the remaining sorting and printing functions for max_digit times:
															// Requirement 4.	
	for(nth_digit = 1; nth_digit <= max_digit; nth_digit++)
	{
		toBucket( array, bucket, nth_digit, length, c );
		fromBucket( array, bucket, c );
															// Requirement 5.
		printBuckets( bucket, length, c, nth_digit );
		printArray( array, length ); 
	}
															// Requirement 6.
	cout << "Sorted array: " << endl;					
	for( ii = 0; ii < length; ii++)
	{
		cout << array[ii] << " " ;
	}
	cout << endl << endl;
}

unsigned int getMaxDigits(const unsigned int array[], const unsigned int length)
//-----------------------------------------------------------------------------
{
	unsigned int remainder = 1;
	unsigned int max_digit = 0;
	unsigned int highest_number = 1;
	unsigned int digit_place = 1;
	unsigned int ii;

	// Finds the highest number in the array:
	for( ii = 0; ii < length; ii++)
	{
		if(highest_number < array[ii])
		{
			highest_number = array[ii];
		}
	}
	
	// While loop iterates until to find how many digits the highest number has.
	// Once the remainder is found to be 0 then maximum digits has been found, the
	// loop works by dividing by powers of ten until the power of ten exceeds the 
	// value of the highest number. This gives it a decimal value. Floor is then
	// used to ensure that the number does not round up to 1. max_digit is
	// incremented evey time the loop completes, this counts the digits. 
	while (remainder != 0)
	{
	        remainder = (unsigned int) floor(highest_number/digit_place);
		digit_place*=10;
		max_digit++;
	}
	max_digit-=1;
	
	return max_digit;	

}

void toBucket(const unsigned int array[], unsigned int bucket[][NUM_BINS], const unsigned int digit_place, const unsigned int length, unsigned int c[])
//-----------------------------------------------------------------------------
{
	unsigned int ii,jj;
	unsigned int nth_digit;
	
	// This loop sets the number of numbers in a bin to zero:
	for( ii = 0; ii < NUM_BINS; ii++)
	{
		c[ii] = 0;
	}
	// This loop sorts the digit place of a number to its respective bin: 
	for( int jj =  0; jj < length; jj++)
	{
		nth_digit = getNthDigit(array[jj], digit_place);
		// bucket[row][column] where columns go from 0-9 and row will always be 20 deep because
		// predined parameters of the task state an array size of 20.
		bucket[c[nth_digit]][nth_digit]=array[jj];
		// Incremented to move the the next spot down in the bin:
		++c[nth_digit];
	}
}

unsigned int getNthDigit(unsigned int array_element, unsigned int number_place)
//-----------------------------------------------------------------------------
{

	unsigned int ii;
	unsigned int power_ten = 1;
	
	// loop is used to get the power ten used to target the nth digit:
	for( ii = 0; ii < number_place; ii++)
	{
		power_ten*=10;
	}
	
	// returns the value of the nth digit for a number:
	// array_element%power_ten returns the remainder, but does not segregate a sole number totally
	// therefore the remainder is divided by a power of ten one magnitude less to return a number 
	// with a decimal value. We do not need the decimal part as it will give a false value for the
	// number place we are trying to identify, therefore the value is floored and the correct digit
	// is revealed.
	return (unsigned int) floor((array_element%power_ten)/(power_ten/10));
}

void fromBucket(unsigned int array[], unsigned int bucket[][NUM_BINS], unsigned int c[] )
//-----------------------------------------------------------------------------
{
	unsigned int ii, jj;
	unsigned int ll = 0;

	for(ii = 0; ii < NUM_BINS; ii++)
	{
		// Checks to see if any numbers are in bin:
		if(c[ii] > 0 )
		{
			// If numbers are in bin loops for the number of numbers in bin:
			for( jj = 0; jj < c[ii]; jj++)
			{
				// Sends value of selected bucket number to bin:
				array[ll]=bucket[jj][ii];
				// Used to move to next element of array:
				ll++;
			}
		}
	}
}

void printArray(const unsigned int array[], const unsigned int length)
//-----------------------------------------------------------------------------
{
	int ii;
	// Prints all numbers in order in array
	for( ii = 0; ii < length; ii++)
	{
		cout << array[ii] << " ";
	}
	cout << endl << endl;
}

void printBuckets(unsigned int bucket[][NUM_BINS], const unsigned int length,  unsigned int c[], const unsigned int nth_digit )
//-----------------------------------------------------------------------------
{

	int ii, jj, kk;
	int x = 1; int tens_place = 1;
	// Finds the bin with the most values, setting the amount of loops to print the rows
	for( ii = 0; ii < NUM_BINS; ii++)
	{	
		if(x < c[ii])
		{
			x = c[ii];
		}
	}
	for( ii = 1; ii < nth_digit; ii++)
	{
		tens_place*=10;
	} 	
	// appearence. Window width is equivalent to about 10 tabs.
	cout << "State after "<< tens_place << "s digit" << endl;
	
	// Loop for row of nth bin:
	for( jj = 0; jj < NUM_BINS; jj++)
	{
		cout << jj << "| ";
		for( kk = 0; kk < x; kk++)
		{
			
			// Check to see if number is remaining in bin:
			if(c[jj] > 0)
			{
				cout << bucket[kk][jj] << " ";
				// This is the key operation to managing number of numbers left in bin to print:
				c[jj]-=1;
			}else{
			cout << " ";
			}
		}
		cout << endl;
	}
	// sets all elements of bin to zero.
	for(ii = 0; ii < length; ii++)
	{
		for(jj = 0; jj < NUM_BINS; jj++)
		{
			bucket[ii][jj]=0;
		}
	}
}

