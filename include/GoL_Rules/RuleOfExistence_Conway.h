/**
 * @file    RuleOfExistence_Conway.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This files contains the class and execution for the Conway rules
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H
#define GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H

#include "RuleOfExistence.h"
/**
 * @brief Conway's RuleOfExistence, applying actions based on
 * PopulationLimits on all 8 surrounding neighbours.
 *
 * @details Concrete RuleOfExistence, implementing Conway's rule of determining
 * alive neighbours surrounding the cell by checking all 8 directions, 4 x
 * Cardinal + 4 x Diagonal. PopulationLimits are set as;
 * UNDERPOPULATION	    < 2*	**Cell dies of loneliness**
 * OVERPOPULATION		> 3*	**Cell dies of overcrowding**
 * RESURRECTION		    = 3*	**Cell is infused with life**
 */
class RuleOfExistence_Conway : public RuleOfExistence {
 private:

 public:
  /**
   * @brief constructor
   * @test Test that the expected rule name is set
   */

  explicit RuleOfExistence_Conway(map<Point, Cell> &cells)
      : RuleOfExistence({2, 3, 3}, cells, ALL_DIRECTIONS, "conway") {}
/// @brief default destructor
  ~RuleOfExistence_Conway() override = default;

/**
 * @brief Calculates and updates the cell population (game board) for the
 * next generation
 *
 * @details Iterates through all the cells, rim cells is ignored, and
 * calculates and sets the next generation action and color. Does only define
 * colors for alive and dead
 *
 * Test Recommendations
 * Test that the correct action is set for an cell
 * Test that a cell that is given life gets the correct color
 * Test that a cell that is killed gets the correct color
 */
  void executeRule() override;
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_CONWAY_H
