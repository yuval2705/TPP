#include <iostream>
#include "BubmbleBee.h"

/// <summary>
/// Prints the contents of an array.
/// </summary>
/// <param name="arr">The array to print its values.</param>
/// <param name="length">The length of the array.</param>
void printArr(int* arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}


int main()
{
    int arr_length = 0;

    std::cout << "Enter the number of primes you want to get: ";
    std::cin >> arr_length;

    if (arr_length <= 0)
    {
        throw std::exception("Arr length should be at least 1");
    }
    int* arr = new int[arr_length]{};
    fillWithPrimes(arr, arr_length);
    printArr(arr, arr_length);

    delete[] arr;
}