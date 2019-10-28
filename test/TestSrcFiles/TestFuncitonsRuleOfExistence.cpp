//
// Created by Johan on 2019-10-28.
//



#include "TestFunctionsRulesOfExistence.h"



void TestFunctionsRuleOfExistence::testCompareDirections(
    const vector<Directions> &readDir,
    const vector<Directions> &expDir) {

    THEN("Vector sizes should match") {
        //Check that both vectors has the same length. Not placed in a THEN
        // block since it does not make since to continue if the sizes differ
        REQUIRE(readDir.size() == expDir.size());
        WHEN("Comparing elements") {

            //Iterate the vectors and compare each element.
            //It would be better to use
            // std::equal(expDir.begin(), expDir.en(), vecOfNums2.begin());
            // but it is not possible since DIRECTIONS has implemented the
            // needed operators (==)
            THEN("All elements should match") {
                auto expIt = expDir.begin();
                auto readIt = readDir.begin();
                for (; expIt != expDir.end(); readIt++, expIt++) {
                    //Compare DIRECTIONS elements
                    CHECK(readIt->HORIZONTAL == expIt->HORIZONTAL);
                    CHECK(readIt->VERTICAL == expIt->VERTICAL);
                }
            }
        }
    }
}

void TestFunctionsRuleOfExistence::testValesRulesOfExistence(
    AccessRulesOfExistence &testClass,
    map<Point, Cell> &expCells,
    PopulationLimits expLimits,
    vector<Directions> expDirections,
    const std::string &expRuleName) {
    std::stringstream header;

    //Check that the rule name is set
    header << "The correct name should be used: " << expRuleName;
    THEN(header.str()) {
        REQUIRE(testClass.getRuleName() == expRuleName);
    }

    //Check that getRuleName() returns the expected value
    THEN("getRuleName() should return the correct name") {
        REQUIRE(testClass.getRuleName() == expRuleName);
    }

    //Check that the Population limits is set
    header.str(std::string());
    header << "The Population limits should be set to: " << "";
    THEN(header.str()) {
        CHECK(testClass.getPopulationLimits().OVERPOPULATION
                  == expLimits.OVERPOPULATION);

        CHECK(testClass.getPopulationLimits().UNDERPOPULATION
                  == expLimits.UNDERPOPULATION);

        CHECK(testClass.getPopulationLimits().RESURRECTION
                  == expLimits.RESURRECTION);
    }

    //Check that the directions is set
    TestFunctionsRuleOfExistence::testCompareDirections(testClass
    .getDirections(), expDirections);

}

void TestFunctionsRuleOfExistence::testAliveCellInAllDirections(
    AccessRulesOfExistence &testClass,
    TestPoint &center,
    const vector<Directions> expDirections) {

    //Use age of two to test that older cells is only counted once
    int aliveCellAge = 2;

    //Check that a alive cell is detected when placed in all directions
    for (auto aliveDirection : ALL_DIRECTIONS) {

        //Calculate the position of the alive cell
        TestPoint aliveAbsPos = center + TestPoint(aliveDirection);

        int expAliveCount = -1;

        //Check if current direction is expected to be checked
        auto cell_found =
            std::find_if(expDirections.begin(), expDirections.end(),
                         [&aliveDirection](const Directions &d1) {
                           return (
                               (aliveDirection.VERTICAL == d1.VERTICAL)
                                   && (aliveDirection.HORIZONTAL
                                       == d1.HORIZONTAL)
                           );
                         });

        //set expAlive to 1 counter if the current direction is checked
        if (cell_found != expDirections.end()) {
            //Cell should be counted
            expAliveCount = 1;
        } else {
            //Cell should not be counted
            expAliveCount = 0;
        }

        //Create test header
        std::stringstream header;
        header << "Am alive cell at direction: "
               << TestPoint(aliveDirection)
               << ", abs pos: " << aliveAbsPos;

        WHEN(header.str()) {

            //Update the "alive" cell
            TestUtil::updateCellAge(testClass.getCells(),
                                    aliveAbsPos,
                                    aliveCellAge);

            header.str(std::string(""));
            header << "countAliveNeighbours() should return: " <<
                   expAliveCount;

            THEN(header.str()) {

                REQUIRE(
                    expAliveCount ==
                        testClass.countAliveNeighbours(center.toPoint())
                );
            }

        }
    }
}

ACTION TestFunctionsRuleOfExistence::getExpAction(int aliveNeighbours, bool
aliveCell){
    ACTION action;
    if (aliveCell) {
        switch (aliveNeighbours) {
            case 0:
            case 1:action = KILL_CELL;
                break;
            case 2:
            case 3:action = IGNORE_CELL;
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:action = KILL_CELL;
                break;
            default:action = DO_NOTHING;
                break;
        }
    } else {
        switch (aliveNeighbours) {
            case 3:action = GIVE_CELL_LIFE;
                break;
            case 0:
            case 1:
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:action = DO_NOTHING;
                break;
            default:action = DO_NOTHING;
                break;

        }
    }
    return action;

};