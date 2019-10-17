/**
 * @file test-Population.cpp
 * @author Henrik Henriksson, hehe0601
 * @brief This file contains test cases to test the class Population
 * @details to come
 *
 */

#include <catch.hpp>
#include <string>
#include "GameOfLife.h"

//---------------------------------------------------------------------------
/**
 * @brief Tests initiatePopulation
 * @details Test the function initiatePopulation when input parameters are
 * given, when only one is given, which should set the oddRule to evenRule, and
 * that an exception is thrown if an incorrect rule name is given, as it would
 * not be desirable for the program to run default rulesets if the user intended
 * to use another ruleset.
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
 * @details test that the support function returns the correct value of the
 * variable generation after the function has been called during "runtime".
 * @todo test if evenRule or oddRule is executed depending on the value of
 * generation.
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
/**
 * @brief Tests getCellatPosition
 * @details test to make sure that if a cell is position at a point that is a
 * border cell, it should get the value isRimCell, otherwise, it should not.
 */
SCENARIO("Get the value of a specific cell in the population") {
  GIVEN("a Population object is created by default constructor and initiated") {
    Population pop;
    pop.initiatePopulation("");
    WHEN("you get the value of the first cell") {
      Cell cell = pop.getCellAtPosition(Point{0, 0});
      THEN("That cell should have the isRimCell value = true") {
        REQUIRE(cell.isRimCell() == true);
      }
    }
    WHEN("you get the value of the nth-1 cell (non border cell)") {
      Cell cell = pop.getCellAtPosition(Point{10, 14});
      THEN("That cell should have the isRimCell value = false") {
        REQUIRE(cell.isRimCell() == false);
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Tests getTotalCellPopulation
 * @details Test to make sure that the funciton returns the correct value. The
 * standard WORLD_DIMENSIONS should return the value 80+2x24+2 == 1920.
 */
SCENARIO("Check the total cell population") {
  GIVEN("a Population object is created by default constructor and initiated") {
    Population pop;
    pop.initiatePopulation("");
    THEN("The entire population should be WIDTH * HEIGHT") {
      REQUIRE(pop.getTotalCellPopulation() ==
              ((WORLD_DIMENSIONS.HEIGHT+2) * (WORLD_DIMENSIONS.WIDTH+2)));
    }
  }
}
//---------------------------------------------------------------------------
