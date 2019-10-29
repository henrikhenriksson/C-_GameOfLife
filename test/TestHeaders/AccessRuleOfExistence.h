/**
 * @file AccessRuleOfExistence.h
 *
 * @author Johan Karlsson, joka1806
 *
 * @brief This file is used to be able to make instances of the abstract class
 * RuleOfExistence
 *
 * @details This file makes it possible to isolate the RuleOfExistence class
 * for testing and to get access to its protected functions.
 * This file should only contain functionality that makes it easier to get
 * access to data for test and should not contain any test functions.
 * Using this class also makes it possible to test the class RuleOfExistence
 * without modify the original class
 */

#ifndef GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_

#include <sstream>
#include <utility>
#include "GoL_Rules/RuleOfExistence.h"
#include "catch.hpp"

/// @brief Default test class name used
/// @details Define to be able to access the value from test funcitons
const std::string DEFAULT_NAME = "TestClassRulesOfExistence";

/// @brief Default limits used for class
/// @details Split over multiple lines cince CLion also shows the parameter
// name
const PopulationLimits DEFAULT_LIMITS = {2,
                                         3,
                                         3};

/// @brief Default directions used
const vector<Directions> DEFAULT_DIRECTIONS = ALL_DIRECTIONS;

/**
 * @brief Makes it possible to isolate test of the abstract class
 * RuleOfExistence
 *
 * @details This class makes it possible to reach protected functions of RuleOfExistence
 * It is bad practice to make protected members available like this but this
 * class should only be included in test builds
 */
class AccessRulesOfExistence : public RuleOfExistence {

 private:
 protected:
 public:
  /**
   * @brief Constructor that sets default values used by program rules
   * @param cells Gameborad to use
   */
  explicit AccessRulesOfExistence(
      map<Point, Cell> &cells,
      const vector<Directions> &directions = DEFAULT_DIRECTIONS,
      PopulationLimits limits = DEFAULT_LIMITS,
      std::string ruleName = DEFAULT_NAME)
      : RuleOfExistence(limits, cells, directions, std::move(ruleName)
  ) {};

  /**
   * @brief Access function to give test access of protected parent function
   * @param center Point to use as center when counting alive cells
   * @return nr of alive neighbours
   */
  int countAliveNeighbours(Point center) ;

  /**
   * @brief Access function to give test access of protected parent function
   * @param aliveNeighbours Counted nr of alive neighboars
   * @param isAlive If the center cell is currently alive or not
   * @return Action to take on the cell for next iteration
   */
  ACTION getAction(int aliveNeighbours,
                   bool isAlive);

  /**
   * @brief Access function to give test access of protected parent variable
   * @return PopulationLimis for parrent
   */
  PopulationLimits getPopulationLimits();

  /**
   * @brief Access function to give test access of protected parent variable
   * @return Gameborad cells
   */
  map<Point, Cell> &getCells();

  /**
   * @brief Access function to give test access of protected parent variable
   * @return Directions used by parrent function
   */
  vector<Directions> getDirections();

  /**
   * @brief Stubbed function to make this class non abstract.
   * @details Since the parent class does not define any functionality for
   * this function it is enough to leave it as stubbed
   */
  virtual void executeRule(){};
};

#endif //GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_
