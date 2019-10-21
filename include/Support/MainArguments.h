/**
 * @file        MainArguments.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This class handles the main arguments to be passed by the user.
 *
 * @details
 */

#ifndef GAMEOFLIFE_MAINARGUMENTS_H
#define GAMEOFLIFE_MAINARGUMENTS_H

#include <sstream>
#include <string>
#include <utility>
#include "Globals.h"
#include "ScreenPrinter.h"

using namespace std;
/// @brief Data structure holding base app values that modifies how the program
/// runs.
struct ApplicationValues {
  bool runSimulation =
      true;  ///< Bool controlling if the program should be run or not.
  string evenRuleName,       ///< Strings holding even rule name
      oddRuleName;           ///< Strings holding odd rule name
  int maxGenerations = 100;  ///> Int holding the number of max generations to
                             /// be run, default= 100
};

/**
 * @brief abstract base parent class
 * @details abstract base class holding pure virtual function used by derived
 * classes. Derived classes handles every valid type of argument.
 * @test As this is an abstract class - test the class by creating an object of
 * a derived class.
 */
class BaseArgument {
 protected:
  const string argValue;

  /**
   @brief Inform the user that no value was provided for the argument
  */
  void printNoValue();

 public:
  /**
   * @brief initialized constructor for abstract class MainArguments
   * @details
   * @param argValue holding entered argument to be parsed.
   * @test create a derived class object and test that argValue was set
   * correctly.
   */
  explicit BaseArgument(string argValue) : argValue(std::move(argValue)) {}

  /**
   * @brief default virtual constructor.
   * @details For the derived classes to work, a default destructor is required
   * in the abstract class.
   * @test no tests recommended.
   */
  virtual ~BaseArgument() = default;
  /**
   * @brief pure virtual function
   * @details pure virtual function will be overridden in derived classes.
   * @param appValues holding datamembers that can be modified by input
   * arguments.
   * @param value pointer holding argument value.
   * @test will be tested in derived classes to make sure override works.
   */
  virtual void execute(ApplicationValues& appValues, char* value = nullptr) = 0;

  /**
   * @brief Get function for the argValue.
   * @details returns a specific argument to be parsed into either of the
   * derived classes
   * recommended tests
   * @test Test that the function returns the correct value in a derived class
   * object.
   *
   */
  const string& getValue() { return argValue; }
};

/**
 * @brief This class handles the argument -h if passed by the user.
 * @detail derived class of BaseArgument. Presents a help screen if the -h
 * argument is given. The main program "gameOfLife" is not executed if this
 * class is called.
 * @test Test the constructor when given the -h argument. If a helpArgument
 * object is created, the function getValue() should return "-h".
 * @test Test that bool RunSimulation is set to false when -h arg is called.
 */
class HelpArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived HelpArguments Class.
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() returns "-h"
   */
  HelpArgument() : BaseArgument("-h") {}

  /**
   * @brief Overriden destructor
   * @details Overriden default destcutor for a derived class.
   * @test no recommended tests at this time.
   */
  ~HelpArgument() override = default;

  /**
   * @brief changes appValues based on entered parameters.
   * @details called from the MainArgumentsParser, changes the default appValues
   * and if valid argument value is given.
   * @test Pass defalt ApplicationValues object and value, Test that the
   * function sets runSimulation to false.
   */
  void execute(ApplicationValues& appValues, char* value) override;
};

// Amount of generations to simulate
class GenerationsArgument : public BaseArgument {
 public:
  GenerationsArgument() : BaseArgument("-g") {}
  ~GenerationsArgument() override = default;

  void execute(ApplicationValues& appValues, char* generations) override;
};

// Custom population size
class WorldsizeArgument : public BaseArgument {
 public:
  WorldsizeArgument() : BaseArgument("-s") {}
  ~WorldsizeArgument() override = default;

  void execute(ApplicationValues& appValues, char* dimensions) override;
};

// Initiate population from file
class FileArgument : public BaseArgument {
 public:
  FileArgument() : BaseArgument("-f") {}
  ~FileArgument() override = default;

  void execute(ApplicationValues& appValues, char* fileNameArg) override;
};

// Rule used for even generations
class EvenRuleArgument : public BaseArgument {
 public:
  EvenRuleArgument() : BaseArgument("-er") {}
  ~EvenRuleArgument() override = default;

  void execute(ApplicationValues& appValues, char* evenRule) override;
};

// Rule used for odd generations
class OddRuleArgument : public BaseArgument {
 public:
  OddRuleArgument() : BaseArgument("-or") {}
  ~OddRuleArgument() override = default;

  void execute(ApplicationValues& appValues, char* oddRule) override;
};

#endif  // GAMEOFLIFE_MAINARGUMENTS_H
