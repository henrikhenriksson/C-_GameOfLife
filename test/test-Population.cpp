/**
 * @file test-Population.cpp
 * @author Henrik Henriksson, hehe0601
 * @brief This file contains test cases to test the class Population
 * @details to come
 *
 */

#include <catch.hpp>
#include <string>
#include "../include/Cell_Culture/Population.h"

//---------------------------------------------------------------------------
/**
 * @brief Tests initiatePopulation
 * @details to come
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
 * @details to come
 * @todo test if evenRule or odd rule is executed depending on the value of
 * generation
 */
SCENARIO("The function is called as the programme is running") {
  GIVEN("a Population obejct created by default constructor and initiated") {
    Population pop;
    pop.initiatePopulation("");
    THEN("Generation should be 0") { REQUIRE(pop.getGeneration() == 0); }

    WHEN("The function is called during runtime") {
      pop.calculateNewGeneration();
      THEN("The value of generation should increase by 1") {
        REQUIRE(pop.getGeneration() == 1);
      }
      AND_WHEN("The Function has been called 5 times") {
        for (size_t i = 1; i < 5; i++) {
          pop.calculateNewGeneration();
        }
        THEN("The value of generation should be 5") {
          REQUIRE(pop.getGeneration() == 5);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
