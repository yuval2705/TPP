#include <iostream>
#include "BubmbleBee.h"


int main()
{
    int arr_length = 0;

    std::cout << "Enter the number of numbers you want to test: ";
    std::cin >> arr_length;

    int* arr = new int[arr_length]{};
    fillIntArrWithUserInput(&arr, arr_length);
    testIfPrimeArr(arr, arr_length);

    delete[] arr;
}