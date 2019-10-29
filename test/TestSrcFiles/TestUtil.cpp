//
// Created by Johan on 2019-10-28.
// Doxygen comments not used in .cpp files
//

#include "TestUtil.h"

//-------------------------------------------------------------------------------------
/*
 * Creates a game board of wanted dimensions. Caller decides if rim cells is
 * to be set or not
 */
void TestUtil::createMap(std::map<Point, Cell> &cells,
               int height,
               int width,
               bool defineRimCells) {

    //Update world dimensions
    WORLD_DIMENSIONS.HEIGHT = height;
    WORLD_DIMENSIONS.WIDTH = width;


    //Iterate through the world and create a new cell for each position
    for (int row = 0; row <= height + 1; row++) {
        for (int col = 0; col <= width + 1; col++) {
            //Create a Point and cell with the wanted position
            //If the cell is suposed to be a rim cell the rim cell status is set
            cells.insert(
                pair<Point, Cell>
                    (
                        Point{row, col},
                        Cell(defineRimCells && isPosRimCell(row, col))
                    )
            );

        }
    }
}

/*
 * Prints the rimcell and its status to shell to cout
 */
void TestUtil::printIsRimCell(std::map<Point, Cell> &cells) {
    //Iterate through all the cells and print their rim cell status
    for (auto mapIt : cells) {
        std::cout << TestPoint(mapIt.first)
                  << ":" << mapIt.second.isRimCell() << std::endl;
    }
}

/*
 * Check if a cell at the given position should be a rim cell or not
 */
bool TestUtil::isPosRimCell(int row, int col) {
    //Check if position is around the boarders of the game board
    return ((row == 0) || (row == WORLD_DIMENSIONS.HEIGHT + 1)
        || (col == 0) || col == WORLD_DIMENSIONS.WIDTH + 1);
}

/*
 * Prints the cell position and age to cout
 */
void TestUtil::printCellAge(std::map<Point, Cell> &cells) {
    //Iterate through all the cells and print position and age
    for (auto mapIt : cells) {
        std::cout << " " << TestPoint(mapIt.first)
        << ":" << mapIt.second.getAge() << std::endl;
    }
}

/*
 * Updates cell ages for the given cells. Cells is given with a direction
 * from the center point given
 */
void TestUtil::updateCellsAge(std::map<Point, Cell> &cells,
                              TestPoint center,
                              std::vector<pair<TestPoint, int>> &newCellAges) {

    int newX, newY; //Variables used to temp store the new positions
    for (auto update : newCellAges) {

        //set the age of the cell
        TestUtilCell::setCellAge(
            cells[(center + update.first).toPoint()],
            update.second);
    }
}

/*
 * Updates the cell age for a given position
 */
void TestUtil::updateCellAge(std::map<Point, Cell> &cells,
    TestPoint pos,
    int age)
{
    TestUtilCell::setCellAge(cells[pos.toPoint()],age);
}

std::string TestUtil::actionToString(ACTION action)
{
    //Return string representation of each action
    switch (action)
    {
        case KILL_CELL:
            return "KILL_CELL";
        case IGNORE_CELL:
            return "IGNORE_CELL";
        case GIVE_CELL_LIFE:
            return "GIVE_CELL_LIFE";
        case DO_NOTHING:
            return "DO_NOTHING";
        default:
            //Trow error if undefined actions are used
            throw std::runtime_error("Unsupported action, actionToString" +
                std::to_string(action) );

    }
}

