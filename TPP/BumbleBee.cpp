#include <iostream>
#include <string>
#include "BubmbleBee.h"
#include "OptimusePrime.h"


void fillIntArrWithUserInput(int** pArr, int length)
{
    if (pArr <= 0)
    {
        throw std::exception("Arr length should be at least 1");
    }
    int length_temp = length;
    for (int i = 0; i < length; i++)
    {
        if (!std::cin)
        {
            std::cout << "Enter " << length_temp << " more numbers: ";
            std::cin >> (*pArr)[i];
        }
    }
}


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