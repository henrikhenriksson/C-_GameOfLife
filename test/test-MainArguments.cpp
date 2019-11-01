/**
 * @file test-MainArguments.cpp
 * @author Henrik Henriksson, hehe0601
 * @brief This file contains test cases to test the classes within the header
 * MainArguments.h
 * @details the header file "MainArguments.h" contains an abstract base class
 * and several derived classes. This file will contain tests for these classes
 * in turn. Test that the abstract class constructor works by creating an object
 * of every derived class. The getValue function should return the correct
 * argValue for each.
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include "Support/MainArguments.h"
#include "catch.hpp"
//---------------------------------------------------------------------------
#define MAINARGUMENTS_TAG "[MainArguments]"

/**
 * @brief Test HelpArgument constructor and public function
 * @details This scenario will test the abstract constructor, getvalue and
 * execute functions for the derived class HelpArgument
 *
 * std::cout is redirected during the function call of ::execute()
 * as this function calls in turn another function which prints to screen during
 * the test.
 */
SCENARIO("Test the HelpArgument Constructor and public funtions",
         MAINARGUMENTS_TAG) {
  GIVEN("An object of a derived class HelpArgument") {
    HelpArgument helpArgTest;
    THEN("The function getValue should return the correct argValue '-h'") {
      REQUIRE(helpArgTest.getValue() == "-h");
    }
    // redirect std::cout to a stringstream buffer to mute std::cout during
    // testing. Otherwise a helpscreen will be printed during test
    // presentation
    std::stringstream buffer;
    std::streambuf* old =
        std::cout.rdbuf(buffer.rdbuf());  // save the old streambuffer.

    WHEN("The function Execute() is called and given nullptr argument value") {
      ApplicationValues appValues;
      char* value = nullptr;  // set to nullptr as no value for -h can be set.

      helpArgTest.execute(appValues, value);

      std::string redirectString =
          buffer.str();  // redirectString will now contain anything couted
                         // during the function call.

      THEN("The bool runSimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }

    std::cout.rdbuf(old);  // Restore the old streambuffer.
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Test GenerationsArgument constructor and public function
 * @details This scenario will test the abstract constructor, getvalue and
 * execute functions for the derived class GenerationsArgument
 *
 */
SCENARIO("Test the GenerationsArgument Constructor and Public funtion",
         MAINARGUMENTS_TAG) {
  GIVEN("An object of a derived class GenerationsArgument") {
    GenerationsArgument genArgTest;
    THEN("The function getValue should return the correct argValue '-g'") {
      REQUIRE(genArgTest.getValue() == "-g");
    }
    WHEN("The function execute() is called and given an argument value") {
      ApplicationValues appValues;
      char* generations = "300";
      genArgTest.execute(appValues, generations);
      THEN(
          "the appValue 'maxGenerations' should be set to the given value "
          "300") {
        REQUIRE(appValues.maxGenerations == 300);
      }
    }
    WHEN("The function execute is called and not given any argument value") {
      ApplicationValues appValues;
      char* generations = nullptr;

      THEN(
          "The appValue 'runsimulation' should be false and function should "
          "throw an exception") {
        REQUIRE_THROWS(genArgTest.execute(appValues, generations));
      }
      THEN("The bool runSimulation should be set to false") {
        genArgTest.execute(appValues, generations);
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
    WHEN("THe function execute() is given an invalid input for Value") {
      ApplicationValues appValues;
      char* generations = "notaNumber";
      THEN("An exception should throw as the function should expect digits") {
        REQUIRE_THROWS(genArgTest.execute(appValues, generations));
      }
      THEN("runsimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Test WorldsizeArgument constructor and public functions
 * @details This scenario will test the abstract constructor, getvalue and
 * execute functions for the derived class WorldsizeArgument
 */
SCENARIO("Test the WorldsizeArgument Constructor and Public funtions",
         MAINARGUMENTS_TAG) {
  GIVEN("An object of a derived class WorldsizeArgument") {
    WorldsizeArgument WorldsizeTest;
    THEN("The function getValue should return the correct argValue '-s'") {
      REQUIRE(WorldsizeTest.getValue() == "-s");
    }
    // Save the previously stored values.
    Dimensions oldDimensions;
    oldDimensions.HEIGHT = WORLD_DIMENSIONS.HEIGHT;
    oldDimensions.WIDTH = WORLD_DIMENSIONS.WIDTH;

    WHEN("The function execute() is called and given an argument value") {
      ApplicationValues appValues;
      char* dimensions = "20x24";
      WorldsizeTest.execute(appValues, dimensions);
      THEN(
          "The global variable WORLD_DIMENSIONS.WIDTH should be set to the "
          "given value "
          "20") {
        REQUIRE(WORLD_DIMENSIONS.WIDTH == 20);
        THEN(
            "The global variable WORLD_DIMENSIONS.HEIGHT should be set to "
            "the "
            "given value 24") {
          REQUIRE(WORLD_DIMENSIONS.HEIGHT == 24);
        }
      }
    }
    WHEN("The function execute() is called and given no values.") {
      ApplicationValues appValues;
      char* dimensions = nullptr;
      THEN("An exception should be thrown") {
        CHECK_THROWS(WorldsizeTest.execute(appValues, dimensions));
      }
      THEN("runsimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
    WHEN("The function execute() is given an invalid format for given Value") {
      ApplicationValues appValues;
      char* dimensions = "20xtest";
      THEN("An exception should throw as the function should expect digits") {
        CHECK_THROWS(WorldsizeTest.execute(appValues, dimensions));
      }
      THEN("runsimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
    // restore the old values to isolate the test case changes.
    WORLD_DIMENSIONS.HEIGHT = oldDimensions.HEIGHT;
    WORLD_DIMENSIONS.WIDTH = oldDimensions.WIDTH;
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Test FileArgument constructor and public functions
 * @details This scenario will test the abstract constructor, getvalue and
 * execute functions for the derived class FileArgument
 */
SCENARIO("Test the FileArgument Constructor and public functions",
         MAINARGUMENTS_TAG) {
  // save the old value
  std::string oldFile = fileName;
  GIVEN("An object of the derived class FileArgument") {
    FileArgument FileArgTest;
    THEN("The function getValue() should return the correct argValue '-f'") {
      REQUIRE(FileArgTest.getValue() == "-f");
    }
    WHEN("The function execute() is called and given an argument value") {
      ApplicationValues appValues;
      char* fileNameArg = "Population_Seed.txt";
      FileArgTest.execute(appValues, fileNameArg);
      THEN("The global variable fileName should be set to fileNameArg")
      CHECK(fileName == "Population_Seed.txt");
    }
    WHEN("The function Execute() is called and given an no value") {
      ApplicationValues appValues;
      char* fileNameArg = nullptr;
      THEN("The function should throw an exception") {
        CHECK_THROWS(FileArgTest.execute(appValues, fileNameArg));
      }
      THEN("runsimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
  }
  // restore the old value after test changes.
  fileName = oldFile;
}
//---------------------------------------------------------------------------
/**
 * @brief Test EvenRuleArgument constructor and public functions
 * @details This scenario will test the abstract constructor, getvalue and
 * execute functions for the derived class FileArgument
 */
SCENARIO("Test the EvenRuleArgument Constructor and public functions",
         MAINARGUMENTS_TAG) {
  GIVEN("An object of the derived class EvenRuleArgument") {
    EvenRuleArgument EvenRuleTest;
    THEN("The function getValue() should return the correct argValue '-er'") {
      REQUIRE(EvenRuleTest.getValue() == "-er");
    }
    WHEN("The function execute() is called and given an argument value") {
      ApplicationValues appValues;
      char* evenRule = "von_neumann";
      EvenRuleTest.execute(appValues, evenRule);
      THEN("The evenRule variable  should be set to evenRule")
      REQUIRE(appValues.evenRuleName == evenRule);
    }
    WHEN("The function execute() is called and given an no value") {
      ApplicationValues appValues;
      char* evenRule = nullptr;
      THEN("The function should throw an exception") {
        REQUIRE_THROWS(EvenRuleTest.execute(appValues, evenRule));
      }
      THEN("runsimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
  }
}
//---------------------------------------------------------------------------
/**
 * @brief Test OddRuleArgument constructor and public functions
 * @details This scenario will test the abstract constructor, getvalue and
 * execute functions for the derived class FileArgument
 */
SCENARIO("Test the OddRuleArgument Constructor and public functions",
         MAINARGUMENTS_TAG) {
  OddRuleArgument OddRuleTest;
  GIVEN("An object of the derived class OddRuleArgument") {
    THEN("The function getValue() should return the correct argValue '-or'") {
      REQUIRE(OddRuleTest.getValue() == "-or");
    }
    WHEN("The function execute() is called and given an argument value") {
      ApplicationValues appValues;
      char* oddRule = "erik";
      OddRuleTest.execute(appValues, oddRule);
      THEN("The evenRule variable  should be set to evenRule") {
        REQUIRE(appValues.oddRuleName == oddRule);
      }
    }
    WHEN("The function execute() is called and given an no value") {
      ApplicationValues appValues;
      char* evenRule = nullptr;
      THEN("The function should throw an exception") {
        REQUIRE_THROWS(OddRuleTest.execute(appValues, evenRule));
      }
      THEN("runsimulation should be set to false") {
        REQUIRE_FALSE(appValues.runSimulation);
      }
    }
  }
}
//---------------------------------------------------------------------------
