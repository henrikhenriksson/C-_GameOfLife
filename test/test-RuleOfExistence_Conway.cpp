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

    TestPoint center(1,1);
    GIVEN("A alive cell") {
        //Define game world
        map<Point, Cell> cells;
        TestUtil::createMap(cells, 1, 1, true);

        RuleOfExistence_Conway testInstance(cells);
        Cell *centerPoint;
        centerPoint = &cells.at(center.toPoint());

        //Color must be set before setCellAge which will update the color
        centerPoint->setNextColor(STATE_COLORS.LIVING);
        TestUtilCell::setCellAge(*centerPoint, 1);



        testCellState(
            cells.at(center.toPoint()),
            1,
            true,
            '#',
            STATE_COLORS.LIVING);



        WHEN("An iteration is run") {
            testInstance.executeRule();

            //Update states
            for (auto & cell : cells) {
                cell.second.updateState();
            }

            THEN("The cell should still be deat")
            {
                testCellState(
                    cells.at(center.toPoint()),
                    1,
                    true,
                    '#',
                    STATE_COLORS.LIVING);

            }
        }
    }
}