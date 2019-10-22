/**
 * @file		test-fileLoader.cpp
 * @author	Henrik Henriksson (hehe0601)
 * @brief  This file contains test cases to test the class fileLoader
 *
 * @details
 *
 */

#include <string>
#include "../include/Support/FileLoader.h"
#include "catch.hpp"
//---------------------------------------------------------------------------
/**
 * @brief test the loadPopulationFromFile
 * @details In this scenario the test is given a valid filename. The test then
 * makes sure the file is loaded and that a world is created based on the
 * dimensions specified in the file. (Height+2) * (Width+2).
 * this test currently assumes the valid file is places in the same folder as the .exe.
 */
SCENARIO("Loading and building a population from a valid file") {
  GIVEN("a Map holding cells") {
    map<Point, Cell> cells;
    WHEN("a valid filename is entered") {
      fileName = "Population_Seed.txt";
      FileLoader fileLoader;
      fileLoader.loadPopulationFromFile(cells);
      THEN("A world with (height+2) * (width+2) dimensions is created") {
        REQUIRE(cells.size() == 264);
      }
    }
  }
}
//---------------------------------------------------------------------------

SCENARIO("Loading a population from an invalid file") {
  GIVEN("a Map holding cells") {
    map<Point, Cell> cells;
    WHEN("an invalid filename is entered:") {
      fileName = "invalid.txt";
      FileLoader fileloader;
      THEN("an exception should be thrown, with error message:") {
        REQUIRE_THROWS_WITH(fileloader.loadPopulationFromFile(cells),
                            "Could not find file. Closing application");
      }
    }
  }
}