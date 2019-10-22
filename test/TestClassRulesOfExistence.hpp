//
// Created by Johan on 2019-10-22.
//

#ifndef GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_

#include <sstream>
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

class TestClassRulesOfExistence : public RuleOfExistence {
 private:
 protected:
 public:
  explicit TestClassRulesOfExistence(map<Point, Cell> &cells)
      : RuleOfExistence(
      {2, 3, 3},
      cells,
      ALL_DIRECTIONS,
      DEFAULT_NAME
  ) {}
//  TestClassRulesOfExistence(PopulationLimits limits):RuleOfExistence(
//      limits,
//      cells,
//      AllDirection,
//      "TestClassRulesOfExistence"
//  )
//  {}

  void executeRule() override;

 friend void testDefaultConstructor(TestClassRulesOfExistence testClass);

};

void TestClassRulesOfExistence::executeRule() {
    ///@todo implement
}

void testDefaultConstructor(TestClassRulesOfExistence testClass)
{
    std::stringstream header;
    header << "The correct name should be used: " << DEFAULT_NAME;
    THEN(header.str())
    {
        //REQUIRE(testClass.ruleName == DEFAULT_NAME);
    }
    //THEN("")
}


#endif //GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_
