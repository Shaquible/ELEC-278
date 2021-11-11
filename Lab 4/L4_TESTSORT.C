// TESTSORT.C [161111]
// This code used to test sort routines.
//
// Author: David Athersych.  This code is intended to be used for educational
// purposes only.
//
//
// Code useful for all sort routines.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXINDEX 19 // how much actual data
int data[100] = {
	44, 22, 3, 71, 16, 82, 1, 9, 99, 10,
	32, 18, 77, 28, 9, 17, 52, 61, 38, 12};

// "Global" variables
int verbose = 0;
long unsigned int swaps = 0; // may be lots of swaps
/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2021.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */
// UTILITYCODE.C [161031]
//
// Author: David Athersych.  This code is intended to be used for educational
// purposes only.
//
//
// Code useful for all sort routines.
//
// READ THIS WARNING BEFORE USING!
//
// Warning! This module is expected to be included in your code, not separately
//          linked. This is not good programming, IMHO, but is done this way to
//          make it a little easier for students in ELEC278.
//
//			This code uses stdio. It is expected that the #include of stdio.h
//			has been done before this code is included.
//
//			This code uses stderr for warnings and errors, and it uses stdout
//			for expected output.
//
//          This code expects two GLOBAL variables to be declared BEFORE the
//          include directive that includes this code:
//          verbose - set to a non-zero value if messages showing action are
//                    required
//          swaps - keeps track of how many swaps done. Calling code must
//                  set swaps to 0 before starting.
//
// Limitation: This code expects that the array values will be integers. (It
//			would be an exercise to see how easy it might be to change this
//			code to deal with floats, doubles, long ints, unsigned ints, chars
//			or unsigned chars. It would be slightly harder to change this code
//			to work with arbitrary structures of data.
//
//  List of functions:

/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2021.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */

//int		array_sorted (char *msg, int *a, int min, int max, int ascending);
//void	error (char *msg);
//void	printarray (char *msg, int *a, int min, int max, int numperline);
//void	swapcontents (int *pa, int *pb);
//void	swap (int *a, int g, int h);

int array_sorted(char *msg, int *a, int min, int max, int ascending)
// Check if portion of array (parameter a) from index min to index max
// inclusive is sorted. Parameter ascending determines whether check is for
// ascending order, meaning lower value is in lower index, or descending
// order, meaning lower value is in higher index.
// If msg is not NULL, prints string pointed to by msg on stdout.
{
	int correct = 0; // either error or unsorted to begin

	// Check first for dumbness
	if (a != NULL)
	{
		int i;
		if (msg != NULL)
			printf("%s\n", msg);
		for (i = min; i < max; i++)
		{
			// data in higher index position should be equal or higher value
			// when array is sorted in ascending order, and should be equal
			// or lower value when array is sorted in descending order.
			// (Note use of C's conditional evaluation.) Variable correct
			// will be true if order OK, and false if order wrong.
			if ((ascending && (a[i] > a[i + 1])) ||
				(!ascending && (a[i] < a[i + 1])))
			{
				// found two out of order - therefore it is unsorted
				if (verbose)
				{
					printf("Sort check failed at position %d\n", i);
					printf("a[%d] = %d, a[%d] = %d\n", i, a[i], i + 1, a[i + 1]);
				}
				return 0;
			}
		} //endfor
		// Get to this point only because we did not detect an out of order
		correct = 1;
	}
	else
	{
		fprintf(stderr, "Call to array_sorted() with no array to check\n");
	} //endif a valid
	return correct;
} //array_sorted()

void error(char *msg)
// Errors are reported to both stderr and stdout.
{
	if (msg == NULL)
		msg = "Default error message";
	fprintf(stderr, "ERROR: %s\n", msg);
	fprintf(stdout, "ERROR: %s\n", msg);
} //error()

void printarray(char *msg, int *a, int min, int max, int numperline)
// Print contents of array a from position min to position max. If msg is not
// NULL, prints msg on stdout before printing array. Parameter numperline -
// if not 0 - indicates how many numbers to print per line.
{
	// Check first for dumbness
	if ((a != NULL) && (numperline > 0))
	{
		int i, num2print;
		if (msg != NULL)
			printf("%s\n", msg);
		// Compute total number of data items to print
		num2print = 1 + max - min;
		for (i = 0; i < num2print; i++)
		{
			// See if we have to finish current line and start next line.
			if (i && ((i % numperline) == 0))
				putchar('\n');
			// Print number - remember counter goes from 0 but items to
			// print start at min.
			printf(" %4d", a[i + min]);
		}
		// Close off last line
		putchar('\n');
	}
	else
	{
		fprintf(stderr, "Error in printarray() parameters\n");
	}
} //printarray()

void swapcontents(int *pa, int *pb)
// Swap values at locations pa and pb - two pointers to integers
{
	int t = *pa;
	*pa = *pb;
	*pb = t;
} //swapcontents()

void swap(int *a, int g, int h)
// Swap values at locations g and h in array a.
// If global verbose is set, reports that swap takes place.
// Global counter swaps is incremented by 1.  User needs to remember to
// reset swaps before starting code that swap count is required.
{
	int t = a[g]; // temporary to hold one value being swapped
	a[g] = a[h];
	a[h] = t;
	swaps++;
} //swap()

int read_int_file(char *fname, int **parray)
// Function reads file containing positive integer values and stores data in
// order in an array.  The data is terminated by a negative value.
// Function uses malloc() to get enough memory for the array, and returns
// the size of the array in integers (not bytes). The pointer to the array
// is returned in the place pointed to by parray.
// If parray is NULL, function reads file and determines how many integers are
// in the file, but does not create an array and store the values.
{
	FILE *fp;
	int *pa; // pointer to array
	int count;
	int rslt;
	int data;

	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "ERROR: Cannot open %s\n", fname);
		return -1;
	}

	// Step 1. Read through array just counting how many numbers there are
	count = 0;
	while (fscanf(fp, "%d", &data) == 1)
	{
		if (data == -1)
			break;
		count++;
	}
	// report if asked
	if (verbose)
	{
		printf("File %-15s contains %d data items\n", fname, count);
	}

	// Step 2. If caller provided a parray pointer then we reread the file
	// storing data as we go.
	if (parray != NULL)
	{
		int k;
		rewind(fp); // back to beginning of file
		// gat an array big enough to store all the data
		pa = (int *)malloc(count * sizeof(int));
		if (pa == NULL)
		{
			fprintf(stderr, "ERROR: Cannot allocate space for array\n");
			fclose(fp);
			return -1;
		}
		// Got an array - fill it
		for (k = 0; k < count; k++)
		{
			if (fscanf(fp, "%d", pa + k) != 1)
			{
				fprintf(stderr, "ERROR: Problem reading item %d from file\n",
						k);
				fclose(fp);
				return -1;
			}
		} //endfor
	}	  //endif parray non-NULL

	// All data read. Close file and provide pointer
	fclose(fp);
	*parray = pa;
	return count;
} //read_int_file()
//-----------------------------------------------------------------

// Array containing initial data

#include "L4_BUBBLESORT.c"
#include "L4_HEAPSORT.C"
#include "L4_INSTSORT.C"
#include "L4_MERGESORT.C"
#include "L4_QUICKSORT.C"
#include "L4_RADXSORT.C"
#include "L4_SELSORT.C"
#include "L4_SHELLSORT.C"

int main(void)
{
	int rslt, max;
	clock_t start, end;
	int *pa; // pointer to array;
	int *pa2;
	int *pa3;
	int size;

	size = read_int_file("RANDOM.TXT", &pa);
	size = read_int_file("ASCENDING.TXT", &pa2);
	size = read_int_file("DESCENDING.TXT", &pa3);
	//return 0;

	printf("==Check array before sort\n");
	if (array_sorted(NULL, pa, 0, size - 1, 1))
	{
		printf("Warning: Array is initially sorted\n");
	}
	else
	{
		printf("    Array is unsorted\n");
	}
	swaps = 0;
	int diff;
	start = clock();
	printf("Bubble Sort\n");
	rslt = bubblesort(pa, 0, size - 1); //OK
	printf("Insertion Sort\n");
	//rslt = insertionsort(pa, 0, size - 1); //OK
	//printf("Heap Sort\n");
	//rslt = heapsort(pa, size); //2B tested
	//printf("Merge Sort\n");
	//rslt = mergesort(pa, 0, size - 1); //OK
	//printf("Quicksort\n");
	//rslt = quicksort(pa, 0, size - 1); //OK
	//Note: Radix sort does not need to be included in the comparisons
	//printf ("Radix sort\n");		rslt = radixsort (pa, size);			 	 //OK
	//printf("Selection Sort (Iterative)\n");
	//rslt = selsortI(pa, 0, size - 1); //OK
	//printf("Selection Sort (Recursive)\n");
	//rslt = selsortR(pa, 0, size - 1); //OK
	//printf("Shell Sort\n");
	//rslt = ShellSort(pa, 0, size - 1); //OK
	end = clock();

	printf("End time: %ld  Start time:  %ld  Diff: %ld\n",
		   end, start, end - start);

	if (array_sorted(NULL, pa, 0, size - 1, 1))
		printf("==After sort, array is sorted\n");
	else
	{
		printf("Sort failed - array is not sorted\n");
		//printarray ("Sort error: ", pa, 0, size-1, 8);
	}
	printf("Swaps:  %ld  CPU time:  %ld\n", rslt, end - start);

	return 0;
} //main()