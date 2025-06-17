#include <iostream>
#include <string>

enum ReturnCodes
{
    SUCCESS = 0
};


const int TABLE_WIDTH = 11;
const int TABLE_HEIGHT = 11;


void printTableRow(int width) {
    std::string row = "";
    for (int i = 1; i < width; i++) {
        row += "  ";
        row += i;
        row += "  |";
    }

    std::string divider = "";
    for (int i = 0; i < row.length(); i++)
    {
        divider = "-";
    }

}

/*
 * Prints the multipication table in the given dims.
 */
void printMultipicationTable(int width, int height)
{
    std::cout << "|    |";
    printTableRow(width);
    for (int i = 1; i <= height; i++) {

    }
}