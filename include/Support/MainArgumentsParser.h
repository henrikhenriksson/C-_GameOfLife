/**
 * @file        MainArgumentsParser.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1

 * @brief This file contains the mainArgumentsParser class
 * @details The MainArgumentsParser handles the parsing of input parameter
 * arguments using static functions.
*/

#ifndef mainArgumentsParserH
#define mainArgumentsParserH

#include <algorithm>
#include <sstream>
#include <string>
#include "MainArguments.h"

using namespace std;


/**
 * @brief This class parses any given arguments.
 * @details The user can opt to add arguments when running the program. This
 * class checks if there are arguments when the program starts and will parse
 * these starting arguments to the simulation.
 * @test Test the main function runParser.
 */
class MainArgumentsParser {
 public:
  /**
   * @brief Takes input parmeter arguments and parses them to corresponding
   * derived mainArgument classes.
   * @details Only looks for valid arguments. Invalid arguments are discarded.
   * Sets the evenRuleName to default "conway" if none is entered.
   * @param argv[] Argument Vector containing strings of arguments and values.
   * @param length containing the number of arguments in the argument vector.
   * @test What happens if the function is given argument parameter. Test that
   * the function returns the correct appValues.
   * @test Test that the function actually sets global functions
   * WORLD_DIMENTIONS and FileName.
   * @test Test that the parser does not change any application values or
   * variables from default when given no arguments.
   * @bug [WHEN An ApplicationValues object is initialized using the Parser and
   * an array containing no extra arguments] the Parser sets the value of even
   * and odd rule even if no value was parsed. This should not be the
   * responsability of the parser function, but rather the
   * even/oddRuleArgument Execute function, or the RuleFactory class.
   * @bug [SCENARIO The Parser is given the -h argument to bring up the help
   * screen] This scenario produces a runtime error when the test is compiled
   * using VC++ compiler as the char * "value" is uninitialized when passed as
   * parameter. This is not desired behaviour as the argument "-h" does not take
   * any value, and thus should be nullptr.
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
