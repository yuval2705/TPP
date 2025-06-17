#include <iostream>
#include <string>

enum ReturnCodes
{
    SUCCESS = 0
};

const int TABLE_WIDTH = 11;
const int TABLE_HEIGHT = 11;
const int CELL_WIDTH = 7;

/*
* Prints a single row of the multipication table.
* 
* @param row_value [IN]: The current row value.
* @param width [IN]: The width of the row to print.
* @param cell_width [IN]: The width of each cell.
*/
void printTableRow(int row_value, int width, int cell_width) {
    std::string row = "";
    for (int i = 0; i <= width; i++) {
        std::string curr_cell = "";

        if (row_value == 0 && i == 0) {
            curr_cell += " ";
        }
        else if (row_value == 0)
        {
            curr_cell += std::to_string(i);
        }
        else if (i == 0)
        {
            curr_cell += std::to_string(row_value);
        }
        else
        {
            curr_cell += std::to_string(i * row_value);
        }

        for (int i = curr_cell.length(); i < CELL_WIDTH; i++)
        {
            curr_cell += " ";
        }
        
        row += curr_cell;
        row += "|";
    }

    std::string divider = "";
    for (int i = 0; i <= row.length(); i++)
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
 * @param cell_width [IN]: The width of each cell.
 */
void printMultipicationTable(int width, int height, int cell_width)
{
    for (int i = 0; i <= height; i++) {
        printTableRow(i, width, cell_width);
    }
}

void main()
{
    printMultipicationTable(TABLE_WIDTH, TABLE_HEIGHT, CELL_WIDTH);
}