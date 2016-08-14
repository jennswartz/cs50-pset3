/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int low = 0, high = n - 1, middle = (low + high) / 2;
    
    if (n < 0)
    {
        return false;
    }
    while (low <= high)
    {
        if (values[middle] < value)
            low = middle + 1;
        else if (values[middle] == value)
        {
            return true;
        }
        else 
        high = middle - 1;
        middle = (high + low)/2;
    } 
    if (high > low)
    {
        return false;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
// Implementation of selection sort
void sort(int values[], int n)
{
    // Outer loop determines where the unsorted portion of the list begins.
    // First run-through of the loop looks at the entire list.  Second run through starts at values[1]. 
    // Third starts at values[2], etc.
    for (int counter = 0; counter < (n - 1); counter++)
    {
        int minimum = counter;

        // Inner loop compares successive elements with current minimum of unsorted elements.
        // If it finds a value lower, it resets that lower value to the minimum value.
        for (int position = counter + 1; position < n; position++)
        {
            if (values[position] < values[minimum])
            {   
                minimum = position;  
            }
        }
    
        // Swap values[minimum] with the first unsorted element, i.e. values[counter].
        int swap = values[counter];
        values[counter] = values[minimum];
        values[minimum] = swap;
    }
    return;
}