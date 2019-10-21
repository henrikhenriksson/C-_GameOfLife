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
   */
  const string& getValue() { return argValue; }
};

/**
 * @brief This class handles the help argument if passed by the user.
 * @detail derived class of BaseArgument. Presents a help screen if the -h
 * argument is given. The main program "gameOfLife" is not executed if this
 * class is called.
 * @test Test the constructor when given the -h argument. If a helpArgument
 * object is created, the function getValue() should return "-h".
 * @test Test the execute function.
 */
class HelpArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived HelpArguments Class.
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() returns the
   * correct argValue.
   */
  HelpArgument() : BaseArgument("-h") {}

  /**
   * @brief Overriden destructor for helpArgument class.
   * @details Overriden default destructor for a derived class.
   * @test no recommended tests at this time.
   */
  ~HelpArgument() override = default;

  /**
   * @brief changes appValues based on entered parameters.
   * @details changes the default appValue for bool runSimulation to false.
   * Calls the function printHelpScreen() for the current running instance.
   * @param appValues struct holding application Values
   * @param value holding the entered parameter.
   * @test Pass defalt ApplicationValues object and value, test that the
   * function sets runSimulation to false.
   */
  void execute(ApplicationValues& appValues, char* value) override;
};

/**
 * @brief This class handles the generations argument if passed by the user.
 * @details Derived class from BaseArgument. Is responsible for the amount of
 * generations to simulate.
 * @test Test the constructor when given the -g argument.
 * @test Test the Execute function.
 */
class GenerationsArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived GenerationsArgument class
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() function
   * returns the correct argValue.
   */
  GenerationsArgument() : BaseArgument("-g") {}
  /**
   * @brief Overriden destructor for the GenerationsArgument class.
   * @details Overriden default destructor for a derived class.
   * @test no recommended tests at this time.
   */
  ~GenerationsArgument() override = default;

  /**
   * @brief changes appValues based on entered parameters.
   * @details changes the default appValue for int maxGenerations to input
   * value. Sets how many generations the simulation should run.
   * @param appValues struct holding application Values
   * @param generations holding the entered parameter.
   * @test Pass default ApplicationValues object and a given value, test that
   * the function sets maxGeneration to the correct value.
   * @test Test that error message is printed if the argument is passed with no
   * value.
   */
  void execute(ApplicationValues& appValues, char* generations) override;
};

/**
 * @brief This class handles the worldsize argument if passed by the user.
 * @details Derived class from BaseArgument. Is responsible for
 * the custom size of the world.
 * @test Test the constructor when given the -s argument.
 * @test Test the Execute function.
 */
class WorldsizeArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived GenerationsArgument class
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() function
   * returns the correct argValue.
   */
  WorldsizeArgument() : BaseArgument("-s") {}
  /**
   * @brief Overriden destructor for WorlsizeArgument class.
   * @details Overriden default destructor for a derived class.
   * @test no recommended tests at this time.
   */
  ~WorldsizeArgument() override = default;
  /**
   * @brief changes appValues based on entered parameters.
   * @details changes the default appValue for world WIDTH and HEIGHT to input
   * value. Sets the size of the world by width and height.
   * @param appValues struct holding application Values
   * @param dimension holding the entered parameter.
   * @test Pass default ApplicationValues object and a given value, test that
   * the function sets WORLD_DIMENSTIONS.WIDTH and .HEIGHT to the correct value.
   * @test Test that error message is printed if the argument is passed with no
   * value.
   */
  void execute(ApplicationValues& appValues, char* dimensions) override;
};

/**
 * @brief This class handles the file argument if passed by the user.
 * @details Derived class from BaseArgument. Is responsible for
 * initiating a population from a file.
 * @test Test the constructor when given the -s argument.
 * @test Test the Execute function.
 */
class FileArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived FileArgument class
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() function
   * returns the correct argValue.
   */
  FileArgument() : BaseArgument("-f") {}
  /**
   * @brief Overriden destructor for WorlsizeArgument class.
   * @details Overriden default destructor for a derived class.
   * @test no recommended tests at this time.
   */
  ~FileArgument() override = default;

  /**
   * @brief changes appValues based on entered parameters.
   * @details changes the default appValue for fileName to input
   * value. Sets the filename to read a worldSize and population from.
   * @param appValues struct holding application Values
   * @param fileNameArg holding the entered parameter.
   * @test Pass default ApplicationValues object and a given value, test that
   * the function sets filename to the correct value.
   * @test Test that error message is printed if the argument is passed with no
   * value.
   */
  void execute(ApplicationValues& appValues, char* fileNameArg) override;
};

/**
 * @brief This class handles the even rule argument if passed by the user.
 * @details Derived class from BaseArgument. Is responsible for
 * setting the rule used for even generations.
 * @test Test the constructor when given the -er argument.
 * @test Test the Execute function.
 */
class EvenRuleArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived EvenRuleArgument class
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() function
   * returns the correct argValue.
   */
  EvenRuleArgument() : BaseArgument("-er") {}
  /**
   * @brief Overriden destructor for EvenRuleArgument class.
   * @details Overriden default destructor for a derived class.
   * @test no recommended tests at this time.
   */
  ~EvenRuleArgument() override = default;

  /**
   * @brief changes appValues based on entered parameters.
   * @details changes the default appValue for evenRuleName to input
   * value. Sets a rule used for even generations.
   * @param appValues struct holding application Values
   * @param evenRule holding the entered parameter.
   * @test Pass default ApplicationValues object and a given value, test that
   * the function sets evenRuleName to the correct value.
   * @test Test that error message is printed if the argument is passed with no
   * value.
   */
  void execute(ApplicationValues& appValues, char* evenRule) override;
};

/**
 * @brief This class handles the odd rule argument if passed by the user.
 * @details Derived class from BaseArgument. Is responsible for
 * setting the rule used for odd generations.
 * @test Test the constructor when given the -or argument.
 * @test Test the Execute function.
 */
class OddRuleArgument : public BaseArgument {
 public:
  /**
   * @brief Default constructor for the derived FileArgument class
   * @details BaseArgument constructor is used to set inherited argValue.
   * @test That an object can be created and that the getValue() function
   * returns the correct argValue.
   */
  OddRuleArgument() : BaseArgument("-or") {}
  /**
   * @brief Overriden destructor for WorlsizeArgument class.
   * @details Overriden default destructor for a derived class.
   * @test no recommended tests at this time.
   */
  ~OddRuleArgument() override = default;
  /**
   * @brief changes appValues based on entered parameters.
   * @details changes the default appValue for oddRuleName to input
   * value. Sets a rule used for odd generations.
   * @param appValues struct holding application Values
   * @param oddRule holding the entered parameter.
   * @test Pass default ApplicationValues object and a given value, test that
   * the function sets oddRuleName to the correct value.
   * @test Test that error message is printed if the argument is passed with no
   * value.
   */
  void execute(ApplicationValues& appValues, char* oddRule) override;
};

#endif  // GAMEOFLIFE_MAINARGUMENTS_H
