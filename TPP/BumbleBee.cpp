#include <iostream>
#include <string>
#include "BubmbleBee.h"
#include "OptimusePrime.h"

/// <summary>
/// Clears all the stdin buffer.
/// </summary>
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


/// <summary>
/// Fills the given array with user given int values.
/// </summary>
/// <param name="pArr">A pointer to the array to fill.</param>
/// <param name="length">The number of the ints to fill.</param>
void fillIntArrWithUserInput(int** pArr, int length)
{
    if (pArr <= 0)
    {
        throw std::exception("Arr length should be at least 1");
    }
    int length_temp = length;

    std::cout << "Enter " << (length_temp) << " more numbers: ";
    for (int i = 0; i < length;)
    {

        std::cin >> (*pArr)[i];
        if (std::cin)
        {
            i++;
            continue;
        }
        else
        {
            std::cout << "Invalid value" << std::endl;
            std::cin.clear();
            ignoreLine();
        }
        std::cout << "Enter " << (length_temp - i) << " more numbers: ";
    }
}

/// <summary>
/// Test each number in the array if it is a prime number or not.
/// </summary>
/// <param name="arr">The array with the numbers to check.</param>
/// <param name="length">The length of the array.</param>
void testIfPrimeArr(int* arr, int length)
{
    for (size_t i = 0; i < length; i++)
    {
        try
        {
            testIfPrimeNumber(arr[i]);
        }
    
        catch (const std::exception& exception)
        {
            std::cout << exception.what() << std::endl;
        }
    }
}