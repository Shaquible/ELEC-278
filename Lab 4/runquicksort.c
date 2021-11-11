// TESTSORT.C [161111]
// This code used to test sort routines.
//
// Author: David Athersych.  This code is intended to be used for educational
// purposes only.
//
//
// Code useful for all sort routines.

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

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Array containing initial data
#define MAXINDEX 19 // how much actual data
int data[100] = {
    44, 22, 3, 71, 16, 82, 1, 9, 99, 10,
    32, 18, 77, 28, 9, 17, 52, 61, 38, 12};

// "Global" variables
int verbose = 0;
long unsigned int swaps = 0; // may be lots of swaps

//#include "L4_UTILITYCODE.c"
#include "L4_QUICKSORT.c"

int main(void)
{
    int rslt, max;
    clock_t start, end;
    int *pa; // pointer to array;
    int size;

    // Fetch data
    size = read_int_file("RANDOM.TXT", &pa);
    //size = read_int_file ("ASCENDING.TXT", &pa);
    //size = read_int_file ("DESCENDING.TXT", &pa);
    //return 0;
    swaps = 0;
    start = clock();
    //printf ("Bubble Sort\n");		rslt = bubblesort (pa, 0, size-1);           //OK
    //printf("Insertion Sort\n");
    //rslt = insertionsort(pa, 0, size - 1); //OK
    //printf("Heap Sort\n");
    //rslt = heapsort(pa, size); //2B tested
    //printf ("Merge Sort\n");		rslt = mergesort (pa, 0, size-1);            //OK
    printf("Quicksort\n");
    rslt = quicksort(pa, 0, size - 1); //OK
    // Note: Radix sort does not need to be included in the comparisons
    //printf ("Radix sort\n");		rslt = radixsort (pa, size);			 	 //OK
    //printf ("Selection Sort (Iterative)\n");	rslt = selsortI (pa, 0, size-1); //OK
    //printf ("Selection Sort (Recursive)\n");  rslt = selsortR (pa, 0, size-1); //OK
    //printf ("Shell Sort\n");		rslt = ShellSort (pa, 0, size-1);            //OK
    end = clock();

    printf("End time: %ld  Start time:  %ld  Diff: %ld\n",
           end, start, (end - start));
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
