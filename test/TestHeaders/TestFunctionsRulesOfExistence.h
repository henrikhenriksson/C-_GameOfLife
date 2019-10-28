/**
 * @file TestClassRulesOfExistence.hpp
 * @author Johan Karlsson, joka1806
 *
 * @brief This file contains test functionality for the RuleOfExistence class
 *
 */

#ifndef GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_

#include <map>
#include <algorithm>
#include "catch.hpp"
#include "GoL_Rules/RuleOfExistence.h"
#include "AccessRulesOfExistence.h"
#include "TestUtil.h"

namespace TestFunctionsRuleOfExistence {

/**
 * @brief Test that the real directions matches the expected directions
 * @details Test that the both directions is of the same length and that
 * all elements match. For the catch test everyting is tested under THEN level
 * @param realDir Real values that is to be checked
 * @param expDir Expected values
 */
static void testCompareDirections(const vector<Directions> &realDir,
                                  const vector<Directions> &expDir);

void testValesRulesOfExistence(
    AccessRulesOfExistence &testClass,
    map<Point, Cell> &expCells,
    PopulationLimits expLimits = DEFAULT_LIMITS,
    vector<Directions> expDirections = DEFAULT_DIRECTIONS,
    const std::string &expRuleName = DEFAULT_NAME
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
void testAliveCellInAllDirections(
    AccessRulesOfExistence &testClass,
    TestPoint &center,
    vector<Directions> expDirections);

/**
 * @brief Returns the action for a cell with the given nr of alive neighbours
 *
 * @param aliveNeighbours
 * @param aliveCell Is the cell current alive or dead
 * @return
 */
ACTION getExpAction(int aliveNeighbours, bool aliveCell);

}
#endif //GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_




