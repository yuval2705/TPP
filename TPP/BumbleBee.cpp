#include <iostream>
#include <string>
#include "BubmbleBee.h"
#include "OptimusePrime.h"


/// <summary>
/// Fills the given array with user given int values.
/// </summary>
/// <param name="arr">An array to fill with prime</param>
/// <param name="length">The number of the ints to fill.</param>
void fillWithPrimes(int* arr, int length)
{
    if (length <= 0)
    {
        throw std::exception("Arr length should be at least 1");
    }

    int currValue = 2;
    for (int i = 0; i < length; currValue++)
    {
        if (isPrime(currValue))
        {
            arr[i] = currValue;
            i++;
        }
    }
}
