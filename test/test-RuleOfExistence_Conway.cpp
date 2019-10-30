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

SCENARIO("RuleOfExistence_Conway should set the expected rule name", CONWAY_TEST_TAG) {
    WHEN("An instance is created") {
        //Define empty game board, not used
        map<Point, Cell> cells;
        RuleOfExistence_Conway testClass(cells);
        THEN("The name should be set to conway") {
            //Create test instance
            REQUIRE("conway" == testClass.getRuleName());
        }
    }

}

SCENARIO("Test that a dead cell does not change values", CONWAY_TEST_TAG) {

    TestPoint center(1,1);
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
            STATE_COLORS.DEAD);

        WHEN("An iteration is run") {
            testInstance.executeRule();
            THEN("The cell should still be deat")
            {
                testCellState(
                    cells.at(center.toPoint()),
                    0,
                    false,
                    '#',
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

        //Set age of center cell, Test cell, and 3 sorunding cells to keep
        // test cell alive
        updateCells.push_back(std::make_pair(TestPoint(0,1), 1));
        updateCells.push_back(std::make_pair(TestPoint(1,1), 1));
        updateCells.push_back(std::make_pair(TestPoint(-2,1), 1));
        updateCells.push_back(std::make_pair(TestPoint(0,0), 1));
        TestUtil::updateCellsAge(cells, centerPoint, updateCells);

        //Test that the testCell has the correct start values
        testCellState(
            *centerCell,
            1,
            true,
            '#',
            STATE_COLORS.LIVING);

        WHEN("An iteration is run") {
            testInstance.executeRule();

            centerCell->updateState();

            THEN("The cell should still be dead")
            {
                testCellState(
                    *centerCell,
                    2,
                    true,
                    '#',
                    STATE_COLORS.LIVING);

            }
        }
    }
}