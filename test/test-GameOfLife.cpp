/**
 * @file	test-GameOfLife.cpp
 * @author	Henrik Henriksson (hehe0601)
 * @brief	This file contains test cases to test the class GameOfLife
 *
 * @details The test cases in this file will strive to validate that the
 * functions included in the class behaves as intended, that no exception is
 * thrown when running the program because of this class.
 *
 */

#include <iostream>
#include "../include/GameOfLife.h"
#include "catch.hpp"

//---------------------------------------------------------------------------
/// @brief Tag used with CATCH to run test in this test file
#define GAMEOFLIFE_TAG "[GameOfLife]" 

/**
 * @brief Test the constructor
 * @details The constructor takes parameters for rulenames. This test will make
 * sure that the constructor correctly sets these rulenames.
 */
SCENARIO("Initializing a GameOfLife object with parameter values.",
         GAMEOFLIFE_TAG) {
  GIVEN(
      "Parameter values for generations (5), even (erik) and odd rulenames "
      "(Conway)") {
    int generations = 5;
    std::string evenRuleName = "erik";
    std::string oddRuleName = "conway";

    WHEN("The gameOfLife object is Initialized") {
      GameOfLife testGame(generations, evenRuleName, oddRuleName);
      THEN(
          "The value for nrOfGenerations, even and odd rulenames should be set "
          "to given values (5, erik, conway)") {
        CHECK(testGame.getNrOfGenerations() == 5);
        CHECK(testGame.getPopulation().getEvenRule()->getRuleName() == "erik");
        CHECK(testGame.getPopulation().getOddRule()->getRuleName() == "conway");
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Test the public function RunSimulation()
 * @details The runSimulation function should run as many times as there are
 * generations. The function should validate against the member variable
 * "nrOfGenerations" if a new generation should be calculated.
 */
SCENARIO("Running the simulation with valid input values.", GAMEOFLIFE_TAG) {
  GIVEN(
      "A GameOfLife object initialized with valid input of one nrOfGenerations "
      "(1)") {
    GameOfLife testGame(10, "erik", "conway");
    WHEN(
        "The function runSimulation is called, it should not throw an "
        "exception") {
      // redirect std::cout to a stringstream buffer to mute std::cout during
      // testing. Otherwise a a generation will be printedduring test
      // presentation
      std::stringstream buffer;
      std::streambuf* old =
          std::cout.rdbuf(buffer.rdbuf());  // save the old streambuffer.
      CHECK_NOTHROW(testGame.runSimulation());
      std::string redirectString =
          buffer.str();      // redirectString will now contain anything couted
                             // during the function call.
      std::cout.rdbuf(old);  // Restore the old streambuffer.
      THEN(
          "The number of appValue generations should have been updated from 0 "
          "to 1") {
        REQUIRE(testGame.getPopulation().getGeneration() == 10);
      }
    }
  }
}
