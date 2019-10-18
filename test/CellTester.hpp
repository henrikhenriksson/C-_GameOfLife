/**
 * @file CellTester.hpp
 * @author Johan Karlsson, joka1806
 * @brief This file contains test functions that supports testing of the Cell
 * class.
 * @details This to keep the test cases in the test file as clear as possible.
 * This file also contains abstract test cases that can test functionality with
 * different parameters.
 */

#ifndef GAMEOFLIFE_CELLTESTER_H
#define GAMEOFLIFE_CELLTESTER_H


#include <iostream>
#include <ios>
#include <string>


/**
 * @brief Support function that returns the corresponding string for the given
 * action
 * @param action to convert to string
 * @return std::string corresponding to the input value
 *
 * @throws std::runtime_error if unimplemented actions is used. This to make
 * it clear that the function has been used in not defined way.
 */
std::string actionToString(ACTION action)
{
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

/**
 * @brief Test function that checks that the constructor input value isRimCell
 * is stored and returned by function isRimCell()
 *
 * @details Tests implemented in own GIVEN {}
 * @param expIsRimCell constructor input to test
 */
void testSetConstructorValues(bool expIsRimCell)
{
    std::stringstream header;
    header << "Default constructor, rimCell = "
           << std::boolalpha << expIsRimCell;
    GIVEN(header.str() )
    {
        //Create test cell of wanted rim cell status
        Cell testCell(expIsRimCell);

        //Clear header stream
        header.str(std::string());
        header << "isRimCell() should return "
               << std::boolalpha << expIsRimCell;
        //Check that the rim cell status is stored in the cell
        THEN(header.str())
        {
            REQUIRE(testCell.isRimCell() == expIsRimCell);
        }
    }
}

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
void testCellIsAlive(bool testRimCell)
{

    //Create a cell of wanted rim cell status
    Cell testCell(testRimCell);

    //Check that the cell is dead from start
    THEN("The start value should be dead, isAlive() == false")
    {
        REQUIRE(testCell.isAlive() == false);
    }

    //Give cell life
    testCell.setNextGenerationAction(GIVE_CELL_LIFE);
    testCell.updateState();
    WHEN("The cell is set to GIVE_CELL_LIFE")
    {
        //Create header depending on the rim cell status
        std::string header;
        header = testRimCell ? "The rim cell should still be dead" :
                "The cell should be alive";
        THEN(header)
        {
            //Check that the cell has the expected rim cell status
            //If is used to make test output easier to read
            if(testRimCell)
            {
                REQUIRE(testCell.isAlive() == false);
            }
            else
            {
                REQUIRE(testCell.isAlive() == true);
            }
        }
    }

    //Let the cell age one itteration
    testCell.setNextGenerationAction(IGNORE_CELL);
    testCell.updateState();
    AND_WHEN("Another iteration is passed")
    {
        //Create header from rim cell status
        std::string header;
        header = testRimCell ? "The rim cell should still be dead" :
                 "The cell should be alive";
        THEN(header)
        {
            //Check that the cell has the expected rim cell status
            //If is used to make test output easier to read
            if(testRimCell)
            {
                REQUIRE(testCell.isAlive() == false);
            }
            else
            {
                REQUIRE(testCell.isAlive() == true);
            }
        }
    }

    //Kill cell
    testCell.setNextGenerationAction(KILL_CELL);
    testCell.updateState();
    AND_WHEN("The cell is killed")
    {
        //Check that the cell is not alive when killed
        THEN("The cell should be dead, isAlive() == false")
        {
            REQUIRE(testCell.isAlive() == false);
        }
    }
}

/**
 * @brief Test that the cell has the expected age and alive status
 *
 * @details Test on THEN{} level with separate THEN{} for age and alive
 *
 * @param testCell cell to test
 * @param expAge expected cell age
 * @param expAlive expected cell alive status
 */
void testCellState(Cell &testCell, int expAge, bool expAlive)
{
    //Test that the cell has the expected cell
    THEN("getAge() should return: " + std::to_string(expAge))
    {
        REQUIRE(testCell.getAge() == expAge);
    }

    //Create a header that describes the expected status
    std::stringstream header;
    header << "isAlive() should return " << std::boolalpha << expAlive;

    //Test the cell alive status
    THEN(header.str())
    {
        REQUIRE(testCell.isAlive() == expAlive);
    }

    //Clear header stream
    header.str(std::string());
}

/**
 * @brief Test that the cell has the expected status given by the input values
 *
 * @details Test on THEN level with separate THEN for each input
 *
 * @param testCell Cell to test
 * @param expAge expected age
 * @param expAlive expected alive status
 * @param expValue expected Cell value
 * @param expColor expected Cell COLOUR
 */
void testCellState(
        Cell &testCell,
        int expAge,
        bool expAlive,
        char expValue,
        COLOR expColor)
{
    //Test age and alive status
    testCellState(testCell, expAge, expAlive);

    //Create test header
    std::stringstream header;
    header << "getValue() should return: " << expValue;
    THEN(header.str())
    {
        //Test cell value
        REQUIRE(testCell.getCellValue() == expValue);
    }
    //clear test header
    header.str(std::string());

    //Create test header
    header << "getColor() should return: " << std::to_string((int)expColor);
    THEN(header.str())
    {
        //Test expected colour
        REQUIRE(testCell.getColor() == expColor);
    }
    //Clear test header
    header.str(std::string());
}

#endif //GAMEOFLIFE_CELLTESTER_H
