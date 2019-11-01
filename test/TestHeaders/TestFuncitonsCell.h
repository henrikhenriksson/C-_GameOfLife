/**
 * @file TestFuncitonsCell.h
 * @author Johan Karlsson, joka1806
 * @brief This file contains test functions that supports testing of the Cell
 * class.
 * @details This to keep the test cases in the test file as clear as possible.
 * This file also contains abstract test cases that can test functionality with
 * different parameters.
 * @todo When time is available this file should be splitted into a .h and
 * .cpp files
 */

#ifndef GAMEOFLIFE_CELLTESTER_H
#define GAMEOFLIFE_CELLTESTER_H


#include <sstream>
#include <ios>
#include <string>

#include "catch.hpp"

#include "Cell_Culture/Cell.h"

/**
 * @brief Test function that checks that the constructor input value isRimCell
 * is stored and returned by function isRimCell()
 *
 * @details Tests implemented in own GIVEN {}
 * @param expIsRimCell constructor input to test
 */
void testSetConstructorValues(bool expIsRimCell);

/**
 * @brief Test that isAlive returns correct values.
 *
 * @details Test that cells reports the correct isAlive status before and
 * after GIVE_CELL_LIFE is used as action. The alive status is also checked
 * when an expected alive cell is killed.
 * The test can be performed on bout a non rim cell and a rim cell
 *
 * @param testRimCell should the cell be created and tested as a rim cell.
 */
void testCellIsAlive(bool testRimCell);

/**
 * @brief Test that the cell has the expected age and alive status
 *
 * @details Test on THEN{} level with separate THEN{} for age and alive
 *
 * @param testCell cell to test
 * @param expAge expected cell age
 * @param expAlive expected cell alive status
 */
void testCellState(Cell &testCell, int expAge, bool expAlive);

/**
 * @brief Test that the cell has the expected status given by the input values
 *
 * @details Test on THEN level with separate THEN for each input
 *
 * @param testCell Cell to test
 * @param expAge expected age
 * @param expAlive expected alive status
 * @param expValue expected Cell value
 * @param expColorName name of expected color, Dead, Living..., This to make
 * a easier to read test result
 * @param expColor expected Cell COLOUR
 */
void testCellState(
        Cell &testCell,
        int expAge,
        bool expAlive,
        char expValue,
        std::string expColorName,
        COLOR expColor);

#endif //GAMEOFLIFE_CELLTESTER_H
