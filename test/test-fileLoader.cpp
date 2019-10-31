/**
 * @file		test-fileLoader.cpp
 * @author	Henrik Henriksson (hehe0601)
 * @brief  This file contains test cases to test the class fileLoader
 *
 * @details The test cases in this file will strive to ensure that the
 * functionality related to reading information from file actually works.
 *
 */

#include <fstream>
#include <string>
#include "../include/Support/FileLoader.h"
#include "TestHeaders/TestFunctionFileLoader.hpp"
#include "catch.hpp"
//---------------------------------------------------------------------------
#define FILELOADER_TAG "[FileLoader]"
/**
 * @brief Test the Test support function
 * @details Make sure the function creates a file with the given name, and that
 * information can be read from that file.
 */
SCENARIO("Test support function to create a new file for reading is called:",
         FILELOADER_TAG) {
  GIVEN(
      "A std::string with the name of the file to create "
      "'testTestFunction.txt'") {
    std::string testName = "testTestFunction.txt";
    WHEN("The test support function is called with name input") {
      CreateFileToRead(testName);
      THEN("It should be possible to read from the file") {
        std::string readFromFile;
        std::ifstream inFile(testName);
        inFile >> readFromFile;
        AND_THEN("The readString should not be empty.") {
          REQUIRE_FALSE(readFromFile.empty());
        }
      }
    }
  }
}

//---------------------------------------------------------------------------
/**
 * @brief Test invalid fileName
 * @details In this scenarion the test is given an invalid filename. the
 * function should then correctly throw an exception and return an error message
 * to the user.
 * @bug As the variable "fileName" is a global variable. This test creates
 * issues in later tests as they will all print the error message "file not
 * found, closing application".
 */
SCENARIO("Loading a population from an invalid file", FILELOADER_TAG) {
  std::string oldFile = fileName;
  GIVEN("a Map holding cells") {
    map<Point, Cell> cells;
    WHEN("an invalid filename is entered:") {
      fileName = "invalid.txt";
      FileLoader fileloader;
      THEN("an exception should be thrown, with error message:") {
        CHECK_THROWS_WITH(fileloader.loadPopulationFromFile(cells),
                          "Could not find file. Closing application");
      }
    }
  }
  fileName = oldFile;
}

/**
 * @brief Test the loadPopulationFromFile
 * @details In this scenario the test is given a valid filename. The test then
 * makes sure the file is loaded and that a world is created based on the
 * dimensions specified in the file. (Height+2) * (Width+2).
 * this test currently assumes the valid file is places in the same folder as
 * the .exe.
 */
SCENARIO(
    "Loading and building a population from a valid file created for the "
    "test.",
    FILELOADER_TAG) {
  std::string oldFile = fileName;
  GIVEN("a Map holding cells and a file to read from (testFile.txt)") {
    CreateFileToRead("testFile.txt");

    map<Point, Cell> cells;
    WHEN("a valid filename is entered") {
      fileName = "testFile.txt";
      FileLoader fileLoader;
      fileLoader.loadPopulationFromFile(cells);
      THEN("A world with (height+2) * (width+2) dimensions is created") {
        REQUIRE(cells.size() == 264);
      }
    }
  }
  fileName = oldFile;
}
//---------------------------------------------------------------------------
