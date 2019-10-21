/*
 * @file        MainArgumentsParser.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1

 * @brief This file contains the mainArgumentsParser class
 * @details The MainArgumentsParser handles the parsiing of input parameter
 arguments.
*/

#ifndef mainArgumentsParserH
#define mainArgumentsParserH

#include <algorithm>
#include <sstream>
#include <string>
#include "MainArguments.h"

using namespace std;

/*
Static functions that parses the starting arguments for the application.
*/

/**
 * @brief This class parses any arguments.
 * @details The user can opt to add arguments when running the program. This
 * class checks if there are arguments when the program starts and will parse
 * these starting arguments to the simulation.
 * @test Test the main function runParser.
 * @bug this class has a datamember but no constructor. Even if none is
 * explicitly needed, a constructor can ensure that the class behaves the way it
 * should when a class object is initialized = no surprises.
 */
class MainArgumentsParser {
 public:
  /**
   * @brief Takes input parmeter arguments and parses them to corresponding
   * derived mainArgument classes.
   * @details Only looks for valid arguments. Invalid arguments are discarded.
   * Sets the evenRUleName to default "conway" if none is entered.
   * @param argv Argument Vector containing strings of arguments and values.
   * @param lenght containing the number of arguments in the argument vector.
   * @test What happens if the function is given argument parameter. Test that
   * the function returns the correct appValues.
   * @test Test that the function actually sets global functions
   * WORLD_DIMENTIONS and FileName
   *
   */
  ApplicationValues& runParser(char* argv[], int length);

 private:
  /// @brief ApplicationValues object holding default values.
  ApplicationValues appValues;

  /// @brief Checks if a given option exists
  bool optionExists(char** begin, char** end, const std::string& option);

  /// @brief gets the given option value
  char* getOption(char** begin, char** end, const std::string& option);
};

#endif
