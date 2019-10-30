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

#include <map>
#include <iostream>
#include "Support/SupportStructures.h"
#include "TestUtilCell.h"
#include "TestPoint.h"
#include "Cell_Culture/Cell.h"


/**
 * @brief Support functions that is not specific to any tested type
 *
 * @details The TestUtil should contain functions that modifies or interacts
 * with test data or objects that are note tied to a specific class or type.
 */
namespace TestUtil {

static const char *ACTIONNames[] = {"KILL_CELL", "IGNORE_CELL",
                                    "GIVE_CELL_LIFE", "DO_NOTHING"};

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
void createMap(std::map<Point, Cell> &map,
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
void updateCellPossAge(std::map<Point, Cell> &cells,
                       TestPoint center,
                       std::vector<pair<TestPoint, int>> &newCellAges);

/**
 * @brief Updates the age for the cell at the given pos
 *
 * @details Updates the age for a non rim cells at positions.
 * Rim cells cant be updated with this function due to restrictions in the
 * Cell class
 *
 */
void updateCellPosAge(std::map<Point, Cell> &cells, TestPoint pos, int
age);

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
void printBoardlIsRimCell(map<Point, Cell> &cells);

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
void printBoardCellAge(map<Point, Cell> &cells);

/**
 * @brief Support function that returns the corresponding string for the given
 * action
 * @param action to convert to string
 * @return std::string corresponding to the input value
 *
 * @throws std::runtime_error if unimplemented actions is used. This to make
 * it clear that the function has been used in not defined way. Since tests
 * should be run the same way each time I think that it is better to notice
 * missuse directly instead of notice it in test results
 *
 */
std::string actionToString(ACTION action);


/**
 * @brief Sets the given nr of neighbours to alive from the given Directions.
 * @details Directions is picked from the first direction to the given nr.
 * Directions can preferably be used with pre defined game rules directions.
 * Directions must be larger than setNrAliveCells.
 * If a cell at a given direction already is alive that cell still counts
 *
 * @param cells reference to the game map
 * @param cellPos Center position that directions is given from
 * @param directions Directions from start point to use
 * @param setNrAliveCells nr of alive cells to set
 */
void setCellAliveNeighbours(map<Point,Cell> &cells,
    TestPoint cellPos,
    std::vector<Directions> directions,
    int setNrAliveCells);
}
#endif //GAMEOFLIFE_TEST_TESTUTIL_H_
