/*
 * @file	    ScreenPrinter.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 *
 * @brief This header contains the singleton class ScreenPrinter.
 *
 * @details The ScreenPrinter class contains private members for Terminal and a
 * private constructor, a public static method for returning the current running
 * instance and support functions for printing and clearing data to/from the
 * console screen.
 * @test As this class contains a private constructor, only testing of the
 * public functions is relevant
 */

#ifndef screenPrinterH
#define screenPrinterH

#include "../terminal/terminal.h"
#include "Cell_Culture/Population.h"

/**
 * @brief ScreenPrinter presents the world to the user.
 *
 * @details ScreenPrinter is the Class that is responsible for visually
 * representing the simulation of the world on the screen terminal.
 * @test the
 * public functions printBoard, printHelpscreen, printMessage, clearScreen and
 * getInstance.
 */
class ScreenPrinter {
 private:
  Terminal terminal;

  // @brief Private constructor.
  ScreenPrinter() = default;

 public:
  /**
   * @brief Returns current singleton object instance.
   * @details This functions provides access to a static single running instance
   * of the class at a time.
   * @return instance, the Current running instance of ScreenPrinter
   * Test Recomendations:
   * @test Static function is not accesible outside. The
   * function will be tested using other public functions.
   */
  static ScreenPrinter& getInstance() {
    static ScreenPrinter instance;
    return instance;
  }

  /**
   * @brief Print the population to screen
   * @details The function takes an input parameter Population object, compares
   * the worldsize, and prints cell values to the screen for each generation it
   * passes.
   * @param population holding a reference to a Population object to print.
   * @test Test that when the function has been called, something has been
   * entered into the outstream.
   * @test That After a printout, the size of the outstream
   * should be the same as WORLD_DIMENSIONS.HEIGHT * WORLD_DIMENSIONS.WIDTH.
   *
   * @issue current impementation is unclear. variable WindowHeight is set to
   * world_dimensions.height + 1. The for loop counter starts at 0 and runs
   * until <= windowHeight. If the HEIGHT variable is 10, the loop will loop 12
   * times. A better implementation would be windowHeight =
   * world_dimensions.height, and the for loop running <= windowHeight+2
   */
  void printBoard(Population& population);

  /**
   * @brief print a predefined message to user.
   * @details If the user enters the Help Arugment when running, the
   * screenPrinter prints the helpScreen to console.
   * @test That when the function has been called, the outstream is not empty.
   */
  void printHelpScreen();

  /**
   * @brief Print a message to the user
   * @details If the printMessage function is called with a std::string
   * parameter, the message will be printed to the screen in a defined format.
   * @param const message, std::string containing the message to be printed.
   * @test Send a teststring message and test that the function prints the
   * message to the outstream.
   */
  void printMessage(const string& message);

  /**
   * @brief clear the Terminal
   * @details Sends the clear command to the current Terminal object to clear
   * the screen from any present data.
   * @test Testing this class will interfere with the code printout for any
   * other test cases. As such i will not write any test case.
   */
  void clearScreen();
};

#endif
