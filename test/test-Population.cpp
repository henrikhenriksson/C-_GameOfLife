/**
 * @file test-Population.cpp
 *
 * @author Henrik Henriksson, hehe0601
 *
 * @brief This file contains test cases to test the class Population
 *
 * @details
 *
 */

#include <catch.hpp>
#include <string>
#include "../include/Cell_Culture/Population.h"

//---------------------------------------------------------------------------
/**
 * @brief Tests initiatePopulation
 */
SCENARIO("Input is given to initiatePopulation") {
  GIVEN("a Population object created by default constructor") {
    Population pop;
    WHEN("Valid rule names are given") {
      pop.initiatePopulation("erik", "von_neumann");
      THEN("The correct rulenames should be set:")
      REQUIRE(pop.getEvenRule()->getRuleName() == "erik");
      REQUIRE(pop.getOddRule()->getRuleName() == "von_neumann");
    }
    WHEN("Only even rule name is given:") {
      pop.initiatePopulation("erik");
      THEN("OddRuleName should be set to even rule Name") {
        REQUIRE(pop.getOddRule()->getRuleName() == "erik");
      }
    }
    WHEN("No value is given") {
      pop.initiatePopulation("", "");
      THEN("Default rulenames should be chosen") {
        REQUIRE(pop.getEvenRule()->getRuleName() == "conway");
        REQUIRE(pop.getOddRule()->getRuleName() == "conway");
      }
      WHEN("Non existent rule name is given") {
        THEN("initiatePopulation should throw an exception") {
          REQUIRE_THROWS(pop.initiatePopulation("Henrik"));
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
* @brief Tests calculateNewGeneration
*/
SCENARIO() {


}