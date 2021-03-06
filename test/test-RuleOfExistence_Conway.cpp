/**
 * @file test-RuleOfExistence_Conway.cpp
 * @author Johan Karlsson, joka1806
 *
 * @brief Constains test senarios for testing the class
 * RuleOfExistence_Conway
 */

#include <map>
#include "catch.hpp"
#include "TestUtil.h"
#include "TestUtilCell.h"
#include "TestFuncitonsCell.h"
#include "Cell_Culture/Cell.h"
#include "GoL_Rules/RuleOfExistence_Conway.h"

/// @brief Tag used with CATCH to run test in this test file
#define CONWAY_TEST_TAG "[RuleOfExistence_Conway]"

/**
 * @brief Test that the constructor sets the expected start values
 */
SCENARIO("Conway: should set the expected start values",
         CONWAY_TEST_TAG) {
    WHEN("An instance is created") {
        //Define empty game board, not used
        map<Point, Cell> cells;

        //Create test instance
        RuleOfExistence_Conway testClass(cells);
        THEN("The name should be set to conway") {
            //Create test instance
            REQUIRE("conway" == testClass.getRuleName());
        }
///@todo create a RuleOfExistence test class to be able to gain access to
// protected members. Then test population limits and directions can be read
// and tested
//        THEN("Limits shoule be set to "
//             "underpopulation: (<=) 2, "
//             "overpopulation: (>)3, "
//             "resurection (==) 3")
//        {
//
//        }
    }
}

/**
 * @brief Test that the exeuteRule sets the correct next generation values
 * when a cell stays alive
 *
 * @details A game board of [1,1], raw[3,3] is used since no extra cells in
 * needed to keep the main cell alive
 */
SCENARIO("Conway: Test that a dead cell does not change values",
    CONWAY_TEST_TAG) {

    TestPoint center(1, 1);
    GIVEN("A dead cell") {
        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 1, 1, true);

        //Create test instance
        RuleOfExistence_Conway testInstance(cells);

        //Get a reference/pointer to the test cell
        Cell *testCell;
        testCell = &cells.at(center.toPoint());

        testCellState(
            cells.at(center.toPoint()),
            0,
            false,
            '#',
            "Dead",
            STATE_COLORS.DEAD);

        WHEN("An iteration is run") {

            //Execute test function
            testInstance.executeRule();

            //Update test cell to set new values
            testCell->updateState();

            //Check that the correct values are set after update
            THEN("The cell should still be dead") {
                testCellState(
                    cells.at(center.toPoint()),
                    0,
                    false,
                    '#',
                    "Dead",
                    STATE_COLORS.DEAD);

            }
        }
    }
}

/**
 * @brief Test that executeRule sets the correct next action values for a
 * cell that stays alive
 *
 * @details Uting a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("Conway: Test that a alive cell does not change "
         "values",
    CONWAY_TEST_TAG) {

    TestPoint centerPoint(2, 2);
    GIVEN("A alive cell") {

        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Conway testInstance(cells);

        //Create a reference to the tested center cell, easier to write and
        // read test
        Cell *testCell;
        testCell = &cells.at(centerPoint.toPoint());

        //Set the test cell as alive
        TestUtilCell::setCellAlive(*testCell);

        //Set 3 neighbor cell as alive to keep the test cell alive
        TestUtil::setCellAliveNeighbours(cells,
                                         centerPoint,
                                         ALL_DIRECTIONS,
                                         3);

        //Test that the testCell has the correct start values
        testCellState(
            *testCell,
            1,
            true,
            '#',
            "Living",
            STATE_COLORS.LIVING);

        //Check that the correct values is set when an iteration is run
        WHEN("An iteration is run") {
            testInstance.executeRule();

            //executeRule should only affect next generation values. This is
            // tested in other test case
            testCell->updateState();

            //Check that the values is unchanged, except for age
            THEN("The cell should still be dead") {
                testCellState(
                    *testCell,
                    2,
                    true,
                    '#',
                    "Living",
                    STATE_COLORS.LIVING);

            }
        }
    }
}

/**
 * @brief Test that the correct values are set for a cell that is given life
 *
 * @details Uting a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("Conway: Test that a cell that is given life get the "
         "correct values",
         CONWAY_TEST_TAG) {
    GIVEN("A dead cell") {
        TestPoint centerPoint(2, 2);
        map<Point, Cell> cells;

        //Create a map with rim cells, test function will not work without rim
        // cells set.
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Conway testInstance(cells);

        //Set 3 alive neighbours to keep the cell alive
        TestUtil::setCellAliveNeighbours(cells,
                                         centerPoint,
                                         ALL_DIRECTIONS,
                                         3);

        //Store a reference to the test cell to make test easier to write and
        // read
        Cell *testCell;
        testCell = &cells.at(centerPoint.toPoint());

        //Test that the test cell has the correct start values
        testCellState(
            *testCell,
            0,
            false,
            '#',
            "Dead",
            STATE_COLORS.DEAD
        );

        //Test that the correct actions it taken after 1 iteration,
        // executeRule() is called
        WHEN("the cell has 3 alive neighbours the cell shoule be given life") {

            //Call test function
            testInstance.executeRule();

            //Test that executeRule does only update next generation values
            THEN("The cell should be unaffected BEFORE updateState is called") {
                testCellState(
                    *testCell,
                    0,
                    false,
                    '#',
                    "Dead",
                    STATE_COLORS.DEAD
                );
            }
            //Tested function only sets next gen state, not update it
            testCell->updateState();

            //Test the cell values after the cell has been updated from next
            // generation values
            THEN("The cell values should be updated AFTER updateState is "
                 "called") {
                testCellState(
                    *testCell,
                    1,
                    true,
                    '#',
                    "Living",
                    STATE_COLORS.LIVING
                );
            }
        }

    }
}

/**
 * @brief Test that the correct values are set for a cell that is killed
 *
 * @details Uting a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("Conway:Test that a living cell that is Killed gets the correct "
         "values", CONWAY_TEST_TAG)
{
    GIVEN("A alive cell") {
        TestPoint centerPoint(2, 2);
        map<Point, Cell> cells;

        //Create a map with rim cells, test function will not work without rim
        // cells set.
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Conway testInstance(cells);

        //Store a pointer to the test cell, easier to write and read test
        Cell *testCell;
        testCell = &cells.at(centerPoint.toPoint());

        //Set start conditions, a living test cell
        TestUtilCell::setCellAlive(*testCell);

        //Test that the correct start conditions is set
        testCellState(
            *testCell,
            1,
            true,
            '#',
            "Living",
            STATE_COLORS.LIVING
        );

        //Test that the correct actions is taken during one simulated itteration
        WHEN("The cell has no alive neighbours, and should be killed") {

            //Call test function
            testInstance.executeRule();

            //Test that executeRule does only update next generation values
            THEN("The cell should be unaffected BEFORE updateState is called") {
                testCellState(
                    *testCell,
                    1,
                    true,
                    '#',
                    "Living",
                    STATE_COLORS.LIVING
                );
            }
            //Tested function only sets next gen state, not update it
            testCell->updateState();

            //Test that the expected values is set after cell is updated from
            // next generation values
            THEN("The cell values should be updated AFTER updateState is "
                 "called") {
                testCellState(
                    *testCell,
                    0,
                    false,
                    '#',
                    "Dead",
                    STATE_COLORS.DEAD
                );
            }
        }
    }
}
