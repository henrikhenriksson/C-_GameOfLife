/**
 * @file RuleOfExistence.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This file contains the abstract class RulesOfExistence and supporting
 * structures.
 *
 * @details These rules lies at the heart of the simulation, and determines
 * the fate of each cell in the world population. This file also contains
 * support structures for defining which cells is to be considered as
 * neighbours.
*/
#ifndef RULEOFEXISTENCE_H
#define RULEOFEXISTENCE_H

#include<string>
#include<map>
#include <utility>
#include<vector>
#include "Cell_Culture/Cell.h"
#include "Support/Globals.h"

using namespace std;

/**
 * @brief Data structure for storing population survival
 * limits.
 * Used by game rules to determine what ACTION to make.
 */
struct PopulationLimits {
  int UNDERPOPULATION, ///< cell with this many neighbours dies
      OVERPOPULATION, ///< cell with this many neighbours dies
      RESURRECTION; ///< cell with this many neighbours is given life
};

/**
 * @brief Data structure for storing directional values.
 * @details Used by direction vectors to set which cell use as neighbours. To
 * calculate a neighbourg position the cell position + Direction is calculated
 */
struct Directions {
  int HORIZONTAL; ///< horizontal offset fom cell
  int VERTICAL; ///< vertical offset form cell
};

/// @brief vector defining all the directions (N, E, S, W, NE, SE, SW, NW)
const vector<Directions> ALL_DIRECTIONS
    {{0, -1}, {1, 0}, {0, 1}, {-1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

/// @brief vector defining the Cardinal directions (N, E, S, W)
const vector<Directions> CARDINAL{{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

/// @brief vector defining the Diagonal directions (NE, SE, SW, NW)
const vector<Directions> DIAGONAL{{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

/**
 * @brief Abstract base class, upon which concrete rules will derive.
 *
 * @details The derivations of RuleOfExistence is what determines the culture
 * of Cell Population. Each rule implements specific behaviours and so may
 * execute some parts in different orders. In order to accommodate this
 * requirement RuleOfExistence will utilize a **Template Method** desing
 * pattern, where all derived rulesimplements their logic based on the virtual
 * method executeRule().
*/
class RuleOfExistence {
 protected:
   /// @brief Rule ui identification string
  string ruleName;

  /// @brief Reference to the population of cells
  map<Point, Cell> &cells;

  /// @brief Amounts of alive neighbouring cells, with specified limits
  const PopulationLimits POPULATION_LIMITS;

  /// @brief The directions, by which neighbouring cells are identified
  const vector<Directions> &DIRECTIONS;

  /**
   * @brief count the nr of alive cell for the cell att the supplied position
   *
   * @details Counts the nr of alive cell in the directions supplied by the
   * defined rules
   *
   * Test recommendation
   * Count only specified (in constructor) directions
   * Count various nr of alice cells
   * Null input to point
   * negative currentPoint
   * Point out of board
   *
   * @param currentPoint Point to a cell at the game board to use as center
   * for calculation
   * @return int alive neighbours count
   */
  int countAliveNeighbours(Point currentPoint);

  /**
   * @brief Returns the ACTION to use for the a Cell to be used for the next
   * iteration
   *
   * @details The action is Calculated dependent on the nr of alive neighbors
   * and if the cell was alive the current itteration
   *
   * Test Recommendation
   * Negative nr of alive Neighbours
   *
   * @param aliveNeighbours
   * @param isAlive
   * @return
   */
  ACTION getAction(int aliveNeighbours, bool isAlive);

 public:
  /**
   * @brief Constructor for the abstract class RuleOfExistence
   *
   * @details
   *
   * Test Recommendations
   * Test that each data field can be set
   *
   * @param limits Defines the limits that defines what ACTION should be used
   * for nr of alive neighbours
   * @param cells Maps of the Cells and position for the cells at the game
   * board
   * @param DIRECTIONS that defines where the neighbours is located
   * @param ruleName A string identification for the rule that could be used
   * in a ui
   */
  RuleOfExistence(PopulationLimits limits,
                  map<Point, Cell> &cells,
                  const vector<Directions> &DIRECTIONS,
                  string ruleName)
      : POPULATION_LIMITS(limits),
        cells(cells),
        DIRECTIONS(DIRECTIONS),
        ruleName(std::move(ruleName)) {}
  virtual ~RuleOfExistence() = default;

  // Execute rule, in order specific to the concrete rule, by utilizing template method DP
  virtual void executeRule() = 0;

  /**
   * @brief Get function for the rule name
   *
   * Test Recommendation
   * Create instance and read value
   *
   * @return string : rule name
   */
  string getRuleName() { return ruleName; }
};

#endif