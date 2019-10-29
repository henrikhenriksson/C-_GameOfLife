/**
 * @file TestClassRulesOfExistence.hpp
 * @author Johan Karlsson, joka1806
 *
 * @brief This file contains test functionality for the RuleOfExistence class
 * @details Some common used test cases has been extracted to this file for
 * multiple use. This so the test file can contain only SCENARIOS or TestCases
 */

#ifndef GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_

#include <map>
#include <algorithm>
#include "catch.hpp"
#include "AccessRuleOfExistence.h"
#include "TestUtil.h"
#include "TestPoint.h"
#include "GoL_Rules/RuleOfExistence.h"

/**
 * @brief Namespace is used to separate test areas
 */
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


/**
 * @brief Test the the expected values has been set in the class
 * @details Test on THEN level, Expects GIVEN and WHEN to be set by calling
 * functions
 * @param testClass Instance to test
 * @param expCells Expected cells, only size are tested for now
 * @param expLimits Expected limits
 * @param expDirections Expected directions
 * @param expRuleName Expected rule name
 */
void testValesRulesOfExistence(
    AccessRulesOfExistence &testClass,
    map<Point, Cell> &expCells,
    PopulationLimits expLimits = DEFAULT_LIMITS,
    vector<Directions> expDirections = DEFAULT_DIRECTIONS,
    const std::string &expRuleName = DEFAULT_NAME
);

/**
 * @brief Tests that a alive cell att all positions is counted.
 *
 * @details The directions to test is specified by expDirections. This should
 * be the same as the directions by the tested rule.
 * Test is performed so a cell is set to alive at a direction at a time. All
 * Directions is tested and if the current direction is among the expected
 * direction the cell is supposed to be counted. If the direction is not among
 * the expected directions the cell is not to be counted.
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
 * @brief Returns the expected action for a cell with a given nr of alive
 * neighbours
 *
 * @details This function returns DO_NOTHING if an alive count larger than 9
 * is returned.
 *
 * @param aliveNeighbours Alive cell count
 * @param aliveCell Is the cell current alive or dead
 * @return
 */
ACTION getExpAction(int aliveNeighbours, bool aliveCell);

}
#endif //GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_




