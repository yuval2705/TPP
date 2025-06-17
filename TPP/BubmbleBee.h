#pragma once

/// <summary>
/// Fills the given array with user given int values.
/// </summary>
/// <param name="pArr">A pointer to the array to fill.</param>
/// <param name="length">The number of the ints to fill.</param>
void fillIntArrWithUserInput(int** pArr, int length);

/// <summary>
/// Test each number in the array if it is a prime number or not.
/// </summary>
/// <param name="arr">The array with the numbers to check.</param>
/// <param name="length">The length of the array.</param>
void testIfPrimeArr(int* arr, int length);

/// <summary>
/// Clears all the stdin buffer.
/// </summary>
void ignoreLine();