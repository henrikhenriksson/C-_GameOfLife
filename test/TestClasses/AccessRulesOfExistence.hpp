//
// Created by Johan on 2019-10-23.
//

#ifndef GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_

///@todo implement
#include <sstream>
#include <utility>
#include "GoL_Rules/RuleOfExistence.h"
#include "catch.hpp"

/**
 * @todo add this to RuleOfExistence class
 *
*UNDERPOPULATION	< 2*	**Cell dies of loneliness**
*OVERPOPULATION		> 3*	**Cell dies of overcrowding**
*RESURRECTION		= 3*	**Cell is infused with life**
 */

    std::string DEFAULT_NAME = "TestClassRulesOfExistence";
PopulationLimits DEFAULT_LIMITS = {2, 3, 3};
const vector<Directions> DEFAULT_DIRECTIONS = ALL_DIRECTIONS;

class AccessRulesOfExistence : public RuleOfExistence {

 private:
 protected:
 public:
  /**
   * Constructor that sets default values used by program rules
   * @param cells
   */
  AccessRulesOfExistence(
      map<Point, Cell> &cells,
      const vector<Directions>& directions = DEFAULT_DIRECTIONS,
      PopulationLimits limits = DEFAULT_LIMITS,
      std::string ruleName = DEFAULT_NAME)
      : RuleOfExistence(limits,cells,directions,std::move(ruleName)
  ) {};

  void executeRule() override;

  int countAliveNeighbours(Point center)
  { return RuleOfExistence::countAliveNeighbours(center);    }


vector<Directions> getDirections()
{   return RuleOfExistence::DIRECTIONS; }
  friend class TestClassRulesOfExistence;
};




void AccessRulesOfExistence::executeRule() {
    ///@todo implement
}




#endif //GAMEOFLIFE_TEST_TESTCLASSES_ACCESSRULESOFEXISTENCE_HPP_
