/**
 * @file test-ScreenPrinter.cpp
 * @author Henrik Henriksson hehe0601
 * @brief This file contains test cases for the class ScreenPrinter.
 *
 */
#include <iostream>
#include <sstream>
#include <string>
#include "../include/ScreenPrinter.h"
#include "catch.hpp"
//---------------------------------------------------------------------------
/// @brief Tag used with CATCH to run test in this test file
#define SCREENPRINTER_TAG "[ScreenPrinter]"

/**
 * @brief This class tests if a message is printed to screen
 * @details The test will redirect the outstream to a std::string that can be
 * compared with the input parameter.
 */
SCENARIO("Printing a message to the screen using printMessage",
         SCREENPRINTER_TAG) {
  GIVEN("An a message to be printed:") {
    std::string testString = "This is a message.";

    WHEN("The message 'This is a message' is passed as an input parameter") {
      std::stringstream bufferStream;
      std::streambuf* oldBuf = std::cout.rdbuf(bufferStream.rdbuf());

      ScreenPrinter::getInstance().printMessage(testString);

      std::string redirectString =
          bufferStream.str();   // redirectString will now contain anything
                                // couted during the function call.
      std::cout.rdbuf(oldBuf);  // Restore the old streambuffer.

      THEN("The outstream should contain the message and a newline") {
        REQUIRE(redirectString == (testString +"\n"));
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
 * @brief test the printHelpScreen function
 * @details This test will make sure that the outstream is not empty when the
 * function has been called. The test cannot be more specific than this as we do
 * not really care exactly how the helpscreen is formatted. This test will
 * simply fail as long as there is no  implementation.
 */
SCENARIO("Calling the printHelpScreen function", SCREENPRINTER_TAG) {
  GIVEN(
      "The a screenprinter instance and the command to print the helpscreen") {
    WHEN("The outstream is redirected and stored in a string") {
      std::stringstream bufferStream;
      std::streambuf* oldBuf = std::cout.rdbuf(bufferStream.rdbuf());
      ScreenPrinter::getInstance().printHelpScreen();
      std::string redirectString = bufferStream.str();
      std::cout.rdbuf(oldBuf);
      THEN(
          "The function should have printed something and the outstream should "
          "not be empty") {
        REQUIRE_FALSE(redirectString.empty());
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Test the printboard function size.
 * @details This funcrion supresses and redirects the outstream to a std::string
 * that can be compared to the predefined world dimensions. When the function is
 * called it should print chars corresponding to the world size, in this case
 * 5*6 = 30 characters.
 * @issue The function printBoard interferes with the presentation of the
 * testcases as the implementation changes and resets the cursor positions. I
 * have not found any valid solution to this that does not involve changing the
 * present implementation, and as such i will leave the code presentation as it
 * is. Comment this section out for prettier Test Case printout.
 */
SCENARIO("Printing the World with the PrintBoard function", SCREENPRINTER_TAG) {
  GIVEN("A gameworld created by a Population object to print") {
    // Save previously stored values
    Dimensions oldDimensions;

    oldDimensions.HEIGHT = WORLD_DIMENSIONS.HEIGHT;
    oldDimensions.WIDTH = WORLD_DIMENSIONS.WIDTH;

    // Create values for a smaller world as large values cause problems in
    // testing
    WORLD_DIMENSIONS.HEIGHT = 5;
    WORLD_DIMENSIONS.WIDTH = 6;

    Population testPop;
    testPop.initiatePopulation("", "");

    WHEN(
        "The population is printed to an ostringstream object using the "
        "printboard funciton") {
      std::stringstream bufferStream;
      std::streambuf* oldBuf = std::cout.rdbuf(bufferStream.rdbuf());

      ScreenPrinter::getInstance().printBoard(testPop);

      std::string redirectString =
          bufferStream.str();   // redirectString will now contain anything
                                // couted during the function call.
      std::cout.rdbuf(oldBuf);  // Restore the old streambuffer.

      THEN("The ostream should not be empty ") {
        REQUIRE(!redirectString.empty());
      }
      // get totalCellPopulation returns (HEIGHT +2) * (WIDTH +2)
      THEN(
          "The printed World size should be equal to the population size "
          "minus rimcells as no newlines are printed") {
        CHECK(redirectString.size() ==
              (WORLD_DIMENSIONS.HEIGHT * WORLD_DIMENSIONS.WIDTH));
      }
    }
    // restore the old values to isolate the test case changes.
    WORLD_DIMENSIONS.HEIGHT = oldDimensions.HEIGHT;
    WORLD_DIMENSIONS.WIDTH = oldDimensions.WIDTH;
  }
}