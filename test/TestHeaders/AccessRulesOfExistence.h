//
// Created by Johan on 2019-10-23.
//

#ifndef GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_

#include <sstream>
#include <utility>
#include "GoL_Rules/RuleOfExistence.h"
#include "catch.hpp"

/**
*UNDERPOPULATION	< 2*	**Cell dies of loneliness**
*OVERPOPULATION		> 3*	**Cell dies of overcrowding**
*RESURRECTION		= 3*	**Cell is infused with life**
 */

const std::string DEFAULT_NAME = "TestClassRulesOfExistence";
const PopulationLimits DEFAULT_LIMITS = {2, 3, 3};
const vector<Directions> DEFAULT_DIRECTIONS = ALL_DIRECTIONS;

class AccessRulesOfExistence : public RuleOfExistence {

 private:
 protected:
 public:
  /**
   * Constructor that sets default values used by program rules
   * @param cells
   */
  explicit AccessRulesOfExistence(
      map<Point, Cell> &cells,
      const vector<Directions> &directions = DEFAULT_DIRECTIONS,
      PopulationLimits limits = DEFAULT_LIMITS,
      std::string ruleName = DEFAULT_NAME)
      : RuleOfExistence(limits, cells, directions, std::move(ruleName)
  ) {};

  int countAliveNeighbours(Point center) ;

  ACTION getAction(int aliveNeighbours,
                   bool isAlive);

  PopulationLimits getPopulationLimits();

  map<Point, Cell> &getCells();

  vector<Directions> getDirections();

  virtual void executeRule(){};
};

#endif //GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_
