/**
 * @file		GameOfLife.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1

 @brief This Header contains the GameOfLife Class.

 @details The GameOfLife class is the main function called by the main
 application for running the simulated game world.
 */

#ifndef GameOfLifeH
#define GameOfLifeH

#include <string>
#include "Cell_Culture/Population.h"
#include "ScreenPrinter.h"

/**
* @brief The heart of the simulation, interconnects the main execution with the
graphical
* presentation.

* @brief Creates and manages Population and the ScreenPrinter instances. Will
instruct
* the Population of cells to keep updating as long as the specified number of
* generations is not reached, and for each iteration instruct ScreenPrinter to
* write the information on screen.
* @test Test cases will validate the constructor and runsimulation function.
*/
class GameOfLife {
 private:
  Population
      population;  ///< population, Population object used in the simulation.
  ScreenPrinter& screenPrinter;  ///< screenPrinter Referenced Screenprinter
                                 ///< singleton object
  int nrOfGenerations;  ///< int nrOfGeneraltions used as a counter for how many
                        ///< generations to run.

 public:
  /**
   * @brief initialization class constructor
   * @details The constructor accepts parameters which is used to set amount of
   * generations and rules to use in the simulation. The population object owned
   * by the class is initialized with the given rules. A singleton screenprinter
   * instance is initialized
   * @param nrOfGenerations int setting the total generation iterations to run.
   * @param evenRuleName std::string holding the ruleset used for even
   * generations
   * @param oddRuleName  std::string holding the ruleset used for odd
   * generations.
   * @test if the constructor sets private nrOfGenerations correctly.
   * @test that even and odd rulenames has been initialized correctly.
   *
   */
  GameOfLife(int nrOfGenerations, string evenRuleName, string oddRuleName);

  //---------------------------------------------------------------------------
  /**
   * @brief Support function to enable testing of the class.
   * @details this function is needed to make sure the member variables included
   * in the class are set correctly
   * @return nrOfGenerations the value set by the constructor.
   * @test Test that the correct value is returned. Will be tested in the test
   * case they are used to validate
   */
  int getNrOfGenerations() { return nrOfGenerations; }

  /**
   * @brief Support function to enable testing of the class.
   * @details this will allow validating of the constructor to make sure it sets
   * rulenames based on input parameter values correctly.
   * @return reference to the member object population.
   * @test Will be tested in the test case they are used to validate
   */
  Population& getPopulation() { return population; }

  //---------------------------------------------------------------------------

  /**
   * @brief Run the Game of Life simulation
   * @details This function is called once and runs the simulation for as many
   * generations as has been set by the used, or the default. For each
   * iteration, the function calculates population changes and print the
   * information to the screen.
   * @test Make sure no exception is thrown when running the simulation.
   * @test Make sure the appValue generation the same as nrOfGenerations after
   * running the function.
   */
  void runSimulation();
};

#endif
