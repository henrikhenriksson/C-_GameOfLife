//
// Created by Johan on 2019-10-29.
//

#include <map>
#include "catch.hpp"
#include "TestUtil.h"
#include "TestUtilCell.h"
#include "TestFuncitonsCell.h"
#include "Cell_Culture/Cell.h"
#include "GoL_Rules/RuleOfExistence_Conway.h"

#define CONWAY_TEST_TAG "[RuleOfExistence_Conway]"

/**
 * @brief Test that the constructor sets the expected start values
 */
SCENARIO("RuleOfExistence_Conway should set the expected start values",
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

SCENARIO("Test that a dead cell does not change values", CONWAY_TEST_TAG) {

    TestPoint center(1, 1);
    GIVEN("A dead cell") {
        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 1, 1, true);

        RuleOfExistence_Conway testInstance(cells);

        testCellState(
            cells.at(center.toPoint()),
            0,
            false,
            '#',
            "Dead",
            STATE_COLORS.DEAD);

        WHEN("An iteration is run") {
            testInstance.executeRule();
            THEN("The cell should still be deat") {
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

SCENARIO("Test that a alive cell does not change values", CONWAY_TEST_TAG) {

    TestPoint centerPoint(2, 2);
    GIVEN("A alive cell") {

        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 3, 3, true);

        //Create test instance
        RuleOfExistence_Conway testInstance(cells);

        //Create a refference to the tested center cell, easier to write and
        // read test
        Cell *centerCell;
        centerCell = &cells.at(centerPoint.toPoint());

        //Create vector of cells to uppdate
        std::vector<pair<TestPoint, int>> updateCells;

        //Set age of center cell, Test cell, and 2 surrounding cells to keep
        // test cell alive
        updateCells.push_back(std::make_pair(TestPoint(0, 1), 1));
        updateCells.push_back(std::make_pair(TestPoint(1, 1), 1));
        updateCells.push_back(std::make_pair(TestPoint(0, 0), 1));
        TestUtil::updateCellsAge(cells, centerPoint, updateCells);

        //Test that the testCell has the correct start values
        testCellState(
            *centerCell,
            1,
            true,
            '#',
            "Living",
            STATE_COLORS.LIVING);

        WHEN("An iteration is run") {
            testInstance.executeRule();

            centerCell->updateState();

            THEN("The cell should still be dead") {
                testCellState(
                    *centerCell,
                    2,
                    true,
                    '#',
                    "Living",
                    STATE_COLORS.LIVING);

            }
        }
    }
}

SCENARIO("Test that a cell that is given life get the correct values",
         CONWAY_TEST_TAG) {
    GIVEN("A dead cell") {
        TestPoint centerPoint(2, 2);
        map<Point, Cell> cells;

        //Create a map with rim cells, test function will not work without rim
        // cells set.
        TestUtil::createMap(cells, 3, 3, true);


        //Create vector of cells to uppdate
        std::vector<pair<TestPoint, int>> updateCells;
        //Set age of center cell, Test cell, and 2 surrounding cells to keep
        // test cell alive
        updateCells.push_back(std::make_pair(TestPoint(0, 1), 1));
        updateCells.push_back(std::make_pair(TestPoint(1, 1), 1));
        updateCells.push_back(std::make_pair(TestPoint(0, 0), 1));
        TestUtil::updateCellsAge(cells, centerPoint, updateCells);

    }
}