//
// Created by Johan on 2019-10-22.
//

#ifndef GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_
#define GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_

#import "GoL_Rules/RuleOfExistence.h"
#import "AccessRulesOfExistence.hpp"



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

  static void testCompareDirections(const vector<Directions> &realDir,
                             const vector<Directions> &expDir);

  static void sTestValesRulesOfExistence(
      AccessRulesOfExistence &testClass,
      map<Point, Cell> &expCells,
      PopulationLimits &expLimits = DEFAULT_LIMITS,
      vector<Directions> expDirections = DEFAULT_DIRECTIONS,
      std::string &expRuleName = DEFAULT_NAME
  );

};

#endif //GAMEOFLIFE_TEST_TESTCLASSRULESOFEXISTENCE_HPP_


void TestClassRulesOfExistence::testValesRulesOfExistence(
    map<Point, Cell> &expCells,
    PopulationLimits expLimits,
    vector<Directions> expDirections,
    std::string expRuleName )
{
    sTestValesRulesOfExistence(
        *testClass,
        expCells,
        expLimits,
        expDirections,
        expRuleName);
}
void TestClassRulesOfExistence::testCompareDirections(const vector<Directions> &realDir,
                                                      const vector<Directions> &expDir) {
    THEN("Vector sizes should match") {
        REQUIRE(realDir.size() == expDir.size());
        WHEN("Comparing elements") {
            auto realIt = realDir.begin();
            auto expIt = expDir.begin();
            int i = 0;
            while (realIt != realDir.end()) {
                stringstream header;
                header << "Value at pos: " << i << "should match";
                THEN(header.str()) {
                    REQUIRE(realIt->HORIZONTAL == expIt->HORIZONTAL);
                    REQUIRE(realIt->VERTICAL == expIt->VERTICAL);
                }
                realIt++;
                expIt++;
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
    header << "The correct name should be used: " << DEFAULT_NAME;
    THEN(header.str()) {
        REQUIRE(testClass.ruleName == expRuleName);
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



