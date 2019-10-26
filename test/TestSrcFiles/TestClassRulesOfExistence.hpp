/**
 * @file TestClassRulesOfExistence.hpp
 * @author Johan Karlsson, joka1806
 *
 * @brief This class contains test functionality for the RuleOfExistence class
 *
 * @details This class
 */

#ifndef GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_

#import <algorithm>
#import "GoL_Rules/RuleOfExistence.h"
#import "AccessRulesOfExistence.hpp"
#import "../TestUtil/TestUtil.hpp"

class TestClassRulesOfExistence : public RuleOfExistence {
 private:
 public:
  AccessRulesOfExistence *testClass;

  void testValesRulesOfExistence(
      map<Point, Cell> &expCells,
      PopulationLimits expLimits = DEFAULT_LIMITS,
      vector<Directions> expDirections = DEFAULT_DIRECTIONS,
      std::string expRuleName = DEFAULT_NAME
  );

  /**
   * @brief Test that the real directions matches the expected directions
   * @details Test that the both directions is of the same length and that
   * all elements match. For the catch test everyting is tested under THEN level
   * @param realDir Real values that is to be checked
   * @param expDir Expected values
   */
  static void testCompareDirections(const vector<Directions> &realDir,
                                    const vector<Directions> &expDir);

  static void sTestValesRulesOfExistence(
      AccessRulesOfExistence &testClass,
      map<Point, Cell> &expCells,
      PopulationLimits &expLimits = DEFAULT_LIMITS,
      vector<Directions> expDirections = DEFAULT_DIRECTIONS,
      std::string &expRuleName = DEFAULT_NAME
  );

  /**
   * @brief Tests that a alive cell att all positions is counted, if the
   * position is among the positions set for the rule
   *
   * @details Tests the standard rule directions ALL_DIRECTIONS, CARDINAL and
   * DIAGONAL
   *
   * @param testClass Instance to test
   * @param center Position of the cell to test
   * @param expDirections Directions where an alive cell is to be counted
   */
  static void testAliveCellInAllDirections(
      AccessRulesOfExistence &testClass,
      TestPoint &center,
      const vector<Directions> expDirections);

};

#endif //GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_

void TestClassRulesOfExistence::testValesRulesOfExistence(
    map<Point, Cell> &expCells,
    PopulationLimits expLimits,
    vector<Directions> expDirections,
    std::string expRuleName) {
    sTestValesRulesOfExistence(
        *testClass,
        expCells,
        expLimits,
        expDirections,
        expRuleName);
}

void TestClassRulesOfExistence::testCompareDirections(
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

void TestClassRulesOfExistence::sTestValesRulesOfExistence(
    AccessRulesOfExistence &testClass,
    map<Point, Cell> &expCells,
    PopulationLimits &expLimits,
    vector<Directions> expDirections,
    string &expRuleName) {
    std::stringstream header;

    //Check that the rule name is set
    header << "The correct name should be used: " << expRuleName;
    THEN(header.str()) {
        REQUIRE(testClass.ruleName == expRuleName);
    }

        //Check that getRuleName() returns the expected value
    THEN("getRuleName() should return the correct name") {
        REQUIRE(testClass.getRuleName() == expRuleName);
    }

    //Check that the Population limits is set
    header.str(std::string());
    header << "The Population limits should be set to: " << "";
    THEN(header.str()) {
        CHECK(testClass.POPULATION_LIMITS.OVERPOPULATION
                  == expLimits.OVERPOPULATION);

        CHECK(testClass.POPULATION_LIMITS.UNDERPOPULATION
                  == expLimits.UNDERPOPULATION);

        CHECK(testClass.POPULATION_LIMITS.RESURRECTION
                  == expLimits.RESURRECTION);
    }

    //Check that the directions is set
    testCompareDirections(testClass.DIRECTIONS, expDirections);

}

void TestClassRulesOfExistence::testAliveCellInAllDirections(
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
            TestUtil::updateCellAge(testClass.cells,
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


