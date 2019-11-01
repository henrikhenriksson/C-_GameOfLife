/**
 * @file test-MainArguments.cpp
 * @author Henrik Henriksson, hehe0601
 * @brief This file contains test cases to test the class MainArgumentsParser.h
 * @details The parser is responsible for setting any given argument values when
 * launching the program. These tests will strive to ensure that the parser
 * performs as we want it to. If an argument is given, the parser should
 * initiate objects of a corresponding MainArguments class and set these values.
 * If no argument is given, the parser should not set any values.
 *
 */

#include <string>
#include "Support/MainArgumentsParser.h"
#include "catch.hpp"
//---------------------------------------------------------------------------
#define PARSER_TAG "[MainArgumentsParser]"
/**
 * @brief The Parser manipulates application values.
 * @details This test scenario will use a MainArgumentsParser object to
 * manipulate application values in an ApplicationValues Struct. As global
 * variables exist, the default values of these are saved to be restored later,
 * as otherwise they can interfere with subsequent testing. The test scenarios
 * should be "isolated".
 */
SCENARIO(
    "A MainArgumentsParser is created and used to set valid application "
    "values",
    PARSER_TAG) {
  // save old global variable values:
  Dimensions oldDimensions = WORLD_DIMENSIONS;
  std::string oldFile = fileName;

  GIVEN("A MainArgumentsParser object") {
    MainArgumentsParser testParser;
    WHEN(
        "An ApplicationValues object is initialized using the Parser and an "
        "array of valid arguments") {
      char* testArgv[] = {
          "./GameOfLife.exe",    "-g",  "20",   "-s",  "20x40",  "-f",
          "Population_Seed.txt", "-er", "eric", "-or", "conway", NULL};
      int testArgc = 11;
      ApplicationValues testValues = testParser.runParser(testArgv, testArgc);
      THEN("runSimulation Should be true") {
        REQUIRE(testValues.runSimulation == true);
      }
      THEN(
          "After parsing '-g' '20' the variable maxGeneration should be "
          "correctly set") {
        REQUIRE(testValues.maxGenerations == 20);
      }
      THEN(
          "After parsing '-s' '20x40' the lobal variable WORLD_DIMENSIONS "
          "should be set "
          "correcly") {
        CHECK(WORLD_DIMENSIONS.WIDTH == 20);

        CHECK(WORLD_DIMENSIONS.HEIGHT == 40);
      }
      THEN(
          "After parsing '-f' 'Population_Seed.txt' theGlobal Variable "
          "fileName should be correcly set") {
        REQUIRE(fileName == "Population_Seed.txt");
      }
      THEN("After parsing '-er' 'eric' evenRuleName should be correctly set") {
        REQUIRE(testValues.evenRuleName == "eric");
      }
      THEN("After parsing '-or' 'conway' should be correctly set") {
        REQUIRE(testValues.oddRuleName == "conway");
      }
    }
  }
  // restore old values to isolate the changes from the test to the test case.
  WORLD_DIMENSIONS = oldDimensions;
  fileName = oldFile;
}

/**
 * @brief the parser recieves no arguments to parse
 * @details The Parsers task is to set arguments and values if contained in the
 * input parameter. If no arguments are given, the parser should not change any
 * default settings, as this is not its purpouse.
 */
SCENARIO("A MainArgumentsParser is created given no extra arguments to parse",
         PARSER_TAG) {
  // save old global variable values:
  Dimensions oldDimensions = WORLD_DIMENSIONS;
  std::string oldFile = fileName;

  GIVEN("A MainArgumentsParser object and Default application Values") {
    ApplicationValues defaultValues;
    MainArgumentsParser testDefaultParser;
    WHEN(
        "An ApplicationValues object is initialized using the Parser and an "
        "array containing no extra arguments") {
      char* testArgv[] = {"./GameOfLife.exe", NULL};
      int testArgc = 1;
      ApplicationValues testValues =
          testDefaultParser.runParser(testArgv, testArgc);
      THEN(
          "Application Values and Global Variables should be default values.") {
        CHECK(testValues.maxGenerations == defaultValues.maxGenerations);

        CHECK(WORLD_DIMENSIONS.HEIGHT == oldDimensions.HEIGHT);
        CHECK(WORLD_DIMENSIONS.WIDTH == oldDimensions.WIDTH);
        CHECK(fileName == oldFile);
        CHECK(testValues.evenRuleName == defaultValues.evenRuleName);

        CHECK(testValues.oddRuleName == defaultValues.oddRuleName);
      }
    }
  }
  WORLD_DIMENSIONS = oldDimensions;
  fileName = oldFile;
}
//---------------------------------------------------------------------------
/**
 * @brief test the -h argument.
 * @details this scenario will check whether the "-h" argument behaves as
 * desired. As no argument value is given after the argument, none should be
 * required when parsing this argument.
 * @TODO make this test work without producing runtime error in VSC.
 */
////SCENARIO("The Parser is given the -h argument to bring up the help screen",
///PARSER_TAG)
//{ /  GIVEN("A mainArgumentsParser object and an argv[] containing '-h'
// argument") { /    MainArgumentsParser testHelpParser; /    char* testArgv[]
// =
//{"./GameOfLife.exe", "-h", NULL}; /    int testArgc = 2; /    THEN("The
// parser should not need a parameter value after the -h argument") { /
// REQUIRE_NOTHROW(ApplicationValues testValues = /
// testHelpParser.runParser(testArgv, testArgc);); /    } /  }
////}
