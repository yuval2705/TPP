#include <iostream>
#include <string>

enum ReturnCodes
{
    SUCCESS = 0
};

const int TABLE_WIDTH = 11;
const int TABLE_HEIGHT = 11;


/*
* Prints a single row of the multipication table.
* 
* @param row_value [IN]: The current row value.
* @param width [IN]: The width of the row to print.
*/
void printTableRow(int row_value, int width) {
    std::string row = "";
    for (int i = 0; i < width; i++) {
        row += "  ";
        if (row_value == 0 && i == 0) {
            row += " ";
        }
        else if (row_value == 0)
        {
            row += std::to_string(i);
        }
        else if (i == 0)
        {
            row += std::to_string(row_value);
        }
        else
        {
            row += std::to_string(i * row_value);
        }
        row += "  |";
    }

    std::string divider = "";
    for (int i = 0; i < row.length(); i++)
    {
        divider += "-";
    }
    std::cout << row << std::endl;
    std::cout << divider << std::endl;
}

/*
 * Prints the multipication table in the given dims.
 * 
 * @param width [IN]: The width of the table to print.
 * @param heigth [IN]: The height of the table to print.
 */
void printMultipicationTable(int width, int height)
{
    for (int i = 0; i <= height; i++) {
        printTableRow(i, width);
    }
}


void main()
{
    printMultipicationTable(TABLE_WIDTH, TABLE_HEIGHT);
}