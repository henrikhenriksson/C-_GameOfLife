/**
 * @file test-RuleOfExistence_Erik.cpp
 * @author Johan Karlsson, joka1806
 *
 * @brief Contains test scenarios for testing the class
 * RuleOfExistence_Erik
 *
 * @details Most testcases ignores the rules of the game when setting up test
 * data and in some cases how test data is changed for the cells that is not
 * current tested. This is something that I have deemed ok since figuring out
 * an cell strucuture that would retult in testable conditions would be to
 * complex and not implrove the tests.
 */

#include <map>
#include "catch.hpp"
#include "TestUtil.h"
#include "TestUtilCell.h"
#include "TestFuncitonsCell.h"
#include "Cell_Culture/Cell.h"
#include "GoL_Rules/RuleOfExistence_Erik.h"
#include "Cell_Culture/Cell.h"

/**
 * @brief Test tag that should be used for all test in this file
 * @details Used to be able to filter out test for the clas
 * RuleOfExistence_Erik when running the test executable
 */


#define ERIK_TEST_TAG "[RuleOfExistence_Erik]"

/**
 * @brief Test that the constructor sets the expected start values
 */
SCENARIO("RuleOfExistence_Erik should set the expected start values",
         ERIK_TEST_TAG) {
    WHEN("An instance is created") {
        //Define empty game board, not used
        map<Point, Cell> cells;

        //Create test instance
        RuleOfExistence_Erik testClass(cells);
        THEN("The name should be set to erik") {
            //Create test instance
            REQUIRE("erik" == testClass.getRuleName());
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
SCENARIO("RuleOfExistence_Erik. Test that a dead cell does not change values",
         ERIK_TEST_TAG) {

    TestPoint center(1, 1);
    GIVEN("A dead cell") {
        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 1, 1, true);

        //Create test instance
        RuleOfExistence_Erik testInstance(cells);

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
 * @details Using a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("RuleOfExistence_Erik. Test that a alive cell does not change "
         "values", ERIK_TEST_TAG) {

    TestPoint centerPoint(2, 2);
    GIVEN("A alive cell") {

        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Erik testInstance(cells);

        //Create a reference to the tested center cell, easier to write and
        // read test
        Cell *testCell;
        testCell = &cells.at(centerPoint.toPoint());

        //Set the test cell as alive
        TestUtilCell::setCellAlive(*testCell);

        //Set 2 neighbor cell as alive to keep the test cell alive, first 2
        // elements in ALL_DIRECTION is CARDINAL and could be used but using
        // CARDINAL to make the test clearer
        TestUtil::setCellAliveNeighbours(cells,
                                         centerPoint,
                                         CARDINAL,
                                         2);

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
SCENARIO("RuleOfExistence_Erik. Test that a cell that is given life get the "
         "correct values",
         ERIK_TEST_TAG) {
    GIVEN("A dead cell") {
        TestPoint centerPoint(2, 2);
        map<Point, Cell> cells;

        //Create a map with rim cells, test function will not work without rim
        // cells set.
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Erik testInstance(cells);

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
SCENARIO("RuleOfExistence_Erik. Test that a living cell that is Killed gets "
         "the correct values",
         ERIK_TEST_TAG) {
    GIVEN("A alive cell") {
        TestPoint centerPoint(2, 2);
        map<Point, Cell> cells;

        //Create a map with rim cells, test function will not work without rim
        // cells set.
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Erik testInstance(cells);

        //Store a pointer to the test cell, easier to write and read test
        Cell *testCell;
        testCell = &cells.at(centerPoint.toPoint());

        //Set start conditions, a living test cell
        TestUtilCell::setCellAlive(*testCell);
        TestUtil::setCellAliveNeighbours(cells, centerPoint, CARDINAL, 1);

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


/**
 * @brief Test that cells that has passed a certain age is marked as old
 * @details Test that cells are not marked as old before they has reached the
 * limit age.
 * Using a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("Test that cells older than 5 itterations are marked as old",
         ERIK_TEST_TAG) {
    //Create game board
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 3, 3, true);

    //Create instance of tested class
    RuleOfExistence_Erik testInstance(cells);

    //Create possition that point to the tested cell
    TestPoint testPoint(2, 2);

    //Create a pointer to the tested cell
    Cell *testCell;
    testCell = &cells.at(testPoint.toPoint());

    //Set test preconditions
    GIVEN("A cell of age 3 that has 3 alive neighbours") {
        //Set age to 2 below limit(>5), test 1 iteration below and 1 above
        TestUtilCell::setCellAge(*testCell, 4);
        TestUtil::setCellAliveNeighbours(cells, testPoint, ALL_DIRECTIONS, 3);

        //Run outside when to store values for next WHEN iteration
        testInstance.executeRule();
        testCell->updateState();
        WHEN("An itteration has passed") {
            testCellState(*testCell,
                          5,
                          true,
                          '#',
                          "Living",
                          STATE_COLORS.LIVING);
        }

        //When the age has passed (>)4 the color should be set to old
        testInstance.executeRule();
        testCell->updateState();

        WHEN("The age has passed (>)4 the cell should be marked as old") {
            testCellState(*testCell,
                          6,
                          true,
                          '#',
                          "Old",
                          STATE_COLORS.OLD);
        }
    }
}

/**
 * @brief Test that cells that killing an old cell resets the old values
 * @details Using a game board of [1,1] raw [3,3] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("All values is reset when a old cell dies",
         ERIK_TEST_TAG) {
    GIVEN("A game board with a Old cell, age > 5") {

        //Create game board
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 1, 1, true);

        //Define a point for the test cell location
        TestPoint testPoint(1, 1);

        //Create a pointer to the test cell
        Cell *testCell;
        testCell = &cells.at(testPoint.toPoint());

        //Set the cell age to 5 and the ange to 6 to be able to set a custom
        // color, this since the set age only sets the color LIVING
        TestUtilCell::setCellAge(*testCell, 5);
        testCell->setNextColor(STATE_COLORS.OLD);
        testCell->setNextGenerationAction(IGNORE_CELL);
        testCell->updateState();

        //Test the start conditions
        testCellState(
            *testCell,
            6,
            true,
            '#',
            "Old",
            STATE_COLORS.OLD);

        WHEN("The cell dies") {
            //Create a test instance
            RuleOfExistence_Erik testInstance(cells);

            //Execute rule to set next generation values, should kill cell
            // since no alive neighbors exists
            testInstance.executeRule();

            //Update cell to apply next generation values set by test function
            testCell->updateState();

            //Test that the correct values are set
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

/**
 * @brief Test that cells that has passed a certain age is marked as Erik
 * @details Test that cells are not marked as Erik before they has reached the
 * limit age.
 * Using a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("Test that cells older than 10 itterations are marked as E",
         ERIK_TEST_TAG) {
    //Create game board
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 3, 3, true);

    //Create instance of tested class
    RuleOfExistence_Erik testInstance(cells);

    //Create possition that point to the tested cell
    TestPoint testPoint(2, 2);

    //Create a pointer to the tested cell
    Cell *testCell;
    testCell = &cells.at(testPoint.toPoint());

    //Set test preconditions
    GIVEN("A cell of age 3 that has 3 alive neighbours") {
        //Set age to 2 below limit(>10). Afterwards test values for 1 iteration
        // below and 1 above
        TestUtilCell::setCellAge(*testCell, 8);
        testCell->setNextGenerationAction(IGNORE_CELL);
        testCell->setNextColor(STATE_COLORS.OLD);
        testCell->updateState();
        TestUtil::setCellAliveNeighbours(cells, testPoint, ALL_DIRECTIONS, 3);

        //Run outside when to store values for next WHEN iteration
        testInstance.executeRule();
        testCell->updateState();
        WHEN("An itteration has passed") {
            testCellState(*testCell,
                          10,
                          true,
                          '#',
                          "Old",
                          STATE_COLORS.OLD);
        }

        //When the age has passed (>)4 the color should be set to old
        testInstance.executeRule();
        testCell->updateState();

        //Second time a cell is the elder it is set to elder as well
        WHEN("The age has passed (>)10 the cell should be marked as Erik") {
            testCellState(*testCell,
                          11,
                          true,
                          'E',
                          "Old",
                          STATE_COLORS.ELDER);
        }
    }
}

/**
 * @brief Test that the oldest cell is set as the elder
 * @details Due to a issue the elder is not set after the second iteration.
 * To make it easier to see the issue the test iterates over 2 iterations to
 * set the elder.
 * Using a game board of [3,3] raw [5,5] to have surrounding cells
 * that is modifiable beyond the rim cells. Rim cells must be defined for
 * execteRules not to throw an error. The cells that is closest surrounding the
 * testCell(center) is modified each itteration to update the main cell
 */
SCENARIO("Test that the oldest cell is set as the elder",
         ERIK_TEST_TAG) {
    GIVEN("A game board with a test cell and 3 alive neigbors") {
        //Create a game board
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 3, 3, true);

        //Create a point for the test cell position
        TestPoint testPoint(2, 2);

        //Create 3 alive neigbors to keep the test cell alive
        TestUtil::setCellAliveNeighbours(
            cells,
            testPoint,
            ALL_DIRECTIONS,
            2);

        //Create a pointer to the test cell
        Cell *testCell;
        testCell = &cells.at(testPoint.toPoint());

        //Set age to 1 below limit of elder cells
        TestUtilCell::setCellAge(*testCell, 9);

        //Create a test instance
        RuleOfExistence_Erik testInstance(cells);

        //Run test funciton, outside WHEN to store result to next WHEN
        testInstance.executeRule();
        testCell->updateState();

        //Check that the elder status is not set before age > 10
        WHEN("An iteration, and cell updated is run when the cell is the "
             "oldes, but not old enough for elder status (>10)") {

            testCellState(
                *testCell,
                10,
                true,
                '#',
                "OLD",
                STATE_COLORS.OLD
            );

        }

        //Run test funciton, outside WHEN to store result to next WHEN
        testInstance.executeRule();
        testCell->updateState();

        //Check that the elder status is not set before age > 10
        WHEN("Another iteration, and cell updated is run when the cell is the "
             "oldes AND old enough for elder status (>10)") {

            testCellState(
                *testCell,
                11,
                true,
                'E',
                "ELDER",
                STATE_COLORS.ELDER
            );

        }

        WHEN("The cell is killed") {
            //Kill neighbor cells
            for (auto &cellIt : cells) {
                if (TestPoint(cellIt.first) == testPoint) {

                } else {
                    TestUtilCell::setCellAge(
                        cellIt.second, 0);
                }
            }

            //When no alive neighbous exist the cell should die
            testInstance.executeRule();
            testCell->updateState();

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

/**
 * @brief Test that only one cell can be the elder cell, and that that cell
 * is the oldest
 * @details Using 3 cells placed so that they keep each other alive with
 * increasing ages. When the oldest dies the second oldes should take place
 * as the new older
 */
SCENARIO("Test that only 1 oldest cell can be an elder",
         ERIK_TEST_TAG) {
    GIVEN("A map of 3 elders") {
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 3, 3, true);

        //Create point to the 3 test cells
        TestPoint testPoint0(2, 2);
        TestPoint testPoint1(1, 2);
        TestPoint testPoint2(1, 1);

        //Create pointers to the 3 test cells
        Cell *testCell0, *testCell1, *testCell2;

        testCell0 = &cells.at(testPoint0.toPoint());
        testCell1 = &cells.at(testPoint1.toPoint());
        testCell2 = &cells.at(testPoint2.toPoint());

        //Set age, each should be old enough to be a elder cell
        TestUtilCell::setCellAge(*testCell0, 13);
        TestUtilCell::setCellAge(*testCell1, 12);
        TestUtilCell::setCellAge(*testCell2, 11);

        //Create a test instance
        RuleOfExistence_Erik testInstance(cells);

        //Execute rules and update cells
        testInstance.executeRule();
        testCell0->updateState();
        testCell1->updateState();
        testCell2->updateState();

        //Test that an elder has been set
        THEN("Only the oldest should be marked Elder") {
            testCellState(*testCell0,
                          14,
                          true,
                          'E',
                          "Elder",
                          STATE_COLORS.ELDER);
        }THEN("The second oldest should only be marked old") {
            testCellState(*testCell1,
                          13,
                          true,
                          'E',
                          "Old",
                          STATE_COLORS.OLD);
        }THEN("The third oldest should only be marked old") {
            testCellState(*testCell2,
                          12,
                          true,
                          'E',
                          "Old",
                          STATE_COLORS.OLD);
        }

        //Simulated by setting age to lower a lower value, Killing the
        // cell would kill the other 2 since they does not have enough
        // neighbors to stay alive. This to keep a simple test case since
        TestUtilCell::setCellAge(*testCell0, 1);

        //Execute rule and update cells, outside WHEN to make it possible to
        // prolong test on the same test data
        testInstance.executeRule();
        testCell0->updateState();
        testCell1->updateState();
        testCell2->updateState();

        //Test that the second oldest becomes the elder when the oldest dies
        WHEN("The oldest Dies") {
            THEN("The second oldest should be marked the Elder") {
                testCellState(*testCell1,
                              14,
                              true,
                              'E',
                              "Elder",
                              STATE_COLORS.ELDER);
            }THEN("The third oldest should be marked Old") {
                testCellState(*testCell2,
                              13,
                              true,
                              'E',
                              "Old",
                              STATE_COLORS.OLD);
            }
        }
    }
}