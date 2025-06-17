#include <iostream>
#include <string>

enum ReturnCodes
{
    SUCCESS = 0
};

const int TABLE_WIDTH = 11;
const int TABLE_HEIGHT = 11;
const int CELL_WIDTH = 7;
const char ROW_DIVIDER = '-';
const char CELL_DIVIDER = '|';
const char CELL_SPACE_FILLER = ' ';


void printDividerRow(std::string row)
{
    std::string divider = "";
    for (int i = 0; i < row.length(); i++)
    {
        divider += ROW_DIVIDER;
    }
    std::cout << divider << std::endl;
}


/*
* Prints a single row of the multipication table.
* 
* @param row_value [IN]: The current row value.
* @param width [IN]: The width of the row to print.
* @param cell_width [IN]: The width of each cell.
*/
void printTableRow(int row_value, int width, int cell_width) {
    std::string row = "|";
    
    for (int i = 1; i <= width; i++) {
        std::string curr_cell = "";

        curr_cell += std::to_string(i * row_value);

        for (int i = curr_cell.length(); i < CELL_WIDTH; i++)
        {
            curr_cell += CELL_SPACE_FILLER;
        }
        
        row += curr_cell;
        row += CELL_DIVIDER;
    }

    std::cout << row << std::endl;
    printDividerRow(row);
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
    for (int i = 1; i <= height; i++) {
        printTableRow(i, width, cell_width);
    }
}

void main()
{
    printMultipicationTable(TABLE_WIDTH, TABLE_HEIGHT, CELL_WIDTH);
}