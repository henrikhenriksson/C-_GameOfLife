/**
 * @file		Population.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This class is a representation of the complete society of cell
 existence and interactions.
 *
 * @details The Population constitutes of all current, previous and future
 generations of cells, both living and dead
 * as well as those not yet born. By mapping all cells to their respective
 positions in the simulation world,
 * Population has the complete knowledge of each cell's whereabouts.
 Furthermore, the class is responsible for
 * determining which rules should be required from the RuleFactory, and store
 the pointer to these as members.
 *
 * Population's main responsibility during execution is determining which rule
 to apply for each new generation
 * and updating the cells to their new states.
 *
 * @test The constructor and each public function in this class should be tested
 with a separate test function

*/

#ifndef POPULATION_H
#define POPULATION_H

#include <map>
#include <string>
#include "Cell.h"
#include "GoL_Rules/RuleFactory.h"
#include "GoL_Rules/RuleOfExistence.h"
#include "Support/Globals.h"

using namespace std;

class Population {
 private:
  int generation;
  map<Point, Cell> cells;
  RuleOfExistence* evenRuleOfExistence;
  RuleOfExistence* oddRuleOfExistence;

  void randomizeCellCulture();
  void buildCellCultureFromFile();

 public:
  /**
   * @brief Constructor for class population
   * @details always resets generation to 0, sets class object values to nullPtr
   *
   * Test Recommendation:
   * @test no recommended tests at this point.
   */
  Population()
      : generation(0),
        evenRuleOfExistence(nullptr),
        oddRuleOfExistence(nullptr) {}

  ~Population();

  /**
   * @brief test support function
   * @details returns current value of member variable "generation"
   * @return INT generation
   */
  int getGeneration() { return generation; }

  /**
   * @brief test support function
   * @details returns current value of member variable "evenRuleOfExistence"
   * @return INT generation
   */
  RuleOfExistence* getEvenRule() { return evenRuleOfExistence; }
  /**
   * @brief test support function
   * @details returns current value of member variable "oddRuleOfExistence"
   * @return INT generation
   */
  RuleOfExistence* getOddRule() { return oddRuleOfExistence; }

  /**
   * @brief initializes the cell culture and the concrete rules to be used in
   * the sim.
   * @details determines wheter the cell culture should be randomized or built
   * from file, creates the rules to be used, based on a specified rule name. If
   * no odd rule is specified odd rule is set to even rule.
   * @param evenRuleName specifies rule name for evenRuleOfExistence
   * @param oddRuleName specifies rule name for oddRuleOfExistence
   * @test If oddRuleName is set to evenRuleName if no odd rule name is
   * specified.
   * @test If null/undefined/non-existent variable names are used for rulenames.
   * Should throw an exception
   * @bug no exception is thrown when a non-existent value is passed as input.
   */
  void initiatePopulation(const string& evenRuleName, string oddRuleName = "");

  /**
   * @brief update the cell population and next generational changes based on
   * the rules
   * @details first the function calls each cell in turn and updates their state
   * until the entire cell population has been updated. Secondly it alternates
   * between odd and even rulesets, based on the current generation.
   *
   * Test Recommendations
   * @test if generation has been updated after function has been called.
   * @test if generation is even or odd, the correct ruleofexistence should be
   * executed.
   *
   * @bug wrong function name as the function updates and calculates.
   * @return INT generation prefix-incremented
   */
  int calculateNewGeneration();

  /**
   * @brief Returns cell by specified key value.
   * @details Uses Point object position to return the cell at that current
   * position
   * @test check that the function returns the correct value
   * @param position holding the current position of a specified point.
   * @return CELL map object.
   */
  Cell& getCellAtPosition(Point position) { return cells.at(position); }

  /**
   * @brief get the size of a cell object
   * @details Get the total ammount of cells in the population, regardless of
   * state. Function is not used elsewhere in the code.
   * @test if the correct size is returned for a cells object.
   * @return INT size of population object.
   * @bug The function does not return the correct value. Bug probably
   * originates in private functions "randomizeCellCulture" and "buildCellCultureFromFile"
   */
  int getTotalCellPopulation() { return cells.size(); }
};

#endif