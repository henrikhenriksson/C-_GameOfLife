/**
 * @file testUtil.hpp
 * @author Johan Karlsson, joka1806
 *
 * @brief this file contains support functions modify or interacts with test
 * data not specific to any specific object/type
 *
 * @details This cell should define support functions that modify or
 * interact with test data or tested objects. Functions that only interacts
 * with a specific test object should be places in a Utility file for that
 * class. This file should not contain any test functions, only files that
 * modifies data.
 */


#ifndef GAMEOFLIFE_TEST_TESTUTIL_H_
#define GAMEOFLIFE_TEST_TESTUTIL_H_

#include "Support/SupportStructures.h"
#include "TestUtilCell.hpp"
#include "Cell_Culture/Cell.h"


/**
 * @brief Support functions that is not specific to any tested type
 *
 * @details The TestUtil should contain functions that modifies or interacts
 * with test data or objects that are note tied to a specific class or type.
 */
namespace TestUtil {

/**
 * @brief Creates a new empty game map of the defined size
 *
 * @details Sets the global WORLD_DIMENSIONS.HEIGHT and WIDTH to the
 * parameters. The raw size of the world will be width+2 and heigth+2 to
 * account for rim cells. If the rim cells should be defined as rim cells can
 * be defined in the input parameters
 *
 * @param map reference to the game map to place Cells
 * @param height of the new world, excluding rim cells
 * @param width of the new world, excluding rim cells
 * @param defineRimCells should the cells surrounding the game board be set to
 * rimCells
 */
void createMap(map<Point, Cell> &map,
               int height,
               int width,
               bool defineRimCells);

/**
 * @brief Updates the cells around the center to the input age.
 *
 * @details Sets the age of the defined cells surrounding the give center
 * point of the game board. There is no check that the center + point
 * position is inside the game board. Only positions that is defined in the
 * vector are updated.
 *
 * @param cells the game board to affect.
 * @param center Sets the center which the positions of the cells is calculated
 * @param newCellAges defines distances from the center and the ages to set
 */
void updateCellAge(map<Point, Cell> &cells,
                   TestPoint center,
                   std::vector<pair<TestPoint, int>> &newCellAges);

/**
 * @brief Overloaded version of void updateCellAge(map<Point, Cell> &cells,
                   Point center,
                   std::vector<pair<TestPoint, int>> &newCellAges);
   with center set to [0,0]
 * @param cells
 * @param newCellAges
 */
void updateCellAge(map<Point, Cell> &cells,
    std::vector<pair<TestPoint, int>>& newCellAges);

/**
 * @brief Updates the age of a singel cell
 * @param cells Game board
 * @param pos Positon to update
 * @param age New Age to set
 */
void updateCellAge(map<Point, Cell> &cells, TestPoint pos, int age);

/**
 * @brief Print the positions and if the cell is a rim cell or not
 *
 * @details Example 1,2:0 for a non rim cell at position 1,2
 *
 * @todo decide if a prety print should be added to print the game board
 * @todo decide if it is wanted to include a algorytm of what to print such
 * as age or rimCell status
 *
 * @param cells to print
 */
void printIsRimCell(map<Point, Cell> &cells);

/**
 * @brief Checks wheter the cell at the given position is a rim cell or not
 *
 * @details Does not check if the position is outside the game board or not
 *
 * @todo add status[out] and check boarders and overloaded version
 *
 * @todo create overloaded version for Position
 *
 * @param row Cell x pos
 * @param col Cell y pos
 * @return
 */
bool isPosRimCell(int x, int y);

/**
 * @brief Prints the age of all cells in the game board
 *
 * @details Prints all the cells on a own row in the format x,y:age
 *
 * @todo decide if algorithm input and common print function should be developed
 *
 * @param cells defining the game board
 */
void printCellAge(map<Point, Cell> &cells);





//-------------------------------------------------------------------------------------
void createMap(map<Point, Cell> &cells,
               int height,
               int width,
               bool defineRimCells) {
    //Clear existing cells in the game map.
    //cells.clear();
    //Update world dimensions
    WORLD_DIMENSIONS.HEIGHT = height;
    WORLD_DIMENSIONS.WIDTH = width;


    //Iterate through the world and create a new cell for each position
    for (int row = 0; row <= height + 1; row++) {
        for (int col = 0; col <= width + 1; col++) {
            cells.insert(
                pair<Point, Cell>
                    (
                        Point{row, col},
                        Cell(defineRimCells && isPosRimCell(row, col))
                    )
            );
//            cells[Point{row,col}] =
//                Cell( defineRimCells && isPosRimCell(row, col) );
//                cells[Point{row, col}] = Cell(true);
        }
    }
}

void printIsRimCell(map<Point, Cell> &cells) {
    //Iterate through all the cells and print their rim cell status
    for (auto mapIt : cells) {
        std::cout << mapIt.first.x << "," << mapIt.first.y
                  << ":" << mapIt.second.isRimCell() << std::endl;
    }
}

bool isPosRimCell(int row, int col) {
    //Check if position is around the boarders of the game board
    return ((row == 0) || (row == WORLD_DIMENSIONS.HEIGHT + 1)
        || (col == 0) || col == WORLD_DIMENSIONS.WIDTH + 1);
}

void printCellAge(map<Point, Cell> &cells) {
    //Iterate through all the cells and print position and age
    for (auto mapIt : cells) {
        std::cout << " " << mapIt.first.x << "," << mapIt.first.y
                  << ":" << mapIt.second.getAge() << std::endl;
    }
}

void updateCellAge(map<Point, Cell> &cells,
                   std::vector<pair<TestPoint, int>>& newCellAges)
{
    updateCellAge(cells, TestPoint(0,0), newCellAges);
}

void updateCellAge(map<Point, Cell> &cells,
                   TestPoint center,
                   std::vector<pair<TestPoint, int>> &newCellAges) {

    int newX, newY; //Variables used to temp store the new positions
    for (auto update : newCellAges) {

        //set the age of the cell
        TestUtilCell::setCellAge(
            cells[(center + update.first).toPoint()],
            update.second);
        //TestUtilCell::setCellAge(cells[newPoint], update.second);
    }
}

void updateCellAge(map<Point, Cell> &cells, TestPoint pos, int age)
{
    TestUtilCell::setCellAge(
        cells[pos.toPoint()],age);
}


}
#endif //GAMEOFLIFE_TEST_TESTUTIL_H_
