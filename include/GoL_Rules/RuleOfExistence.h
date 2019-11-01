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
 *
 * @issue Directions and Point fulfills the same need and could be replaced
 * with one struct instead of two. Since direction has no limitation of the
 * range of the input.
 * @issue Operations such as +, += and == should be overloaded to make it
 * easier to use and read. Instead of as now adding the elements in code
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
 * requirement RuleOfExistence will utilize a **Template Method** design
 * pattern, where all derived rules implemented their logic based on the virtual
 * method executeRule().
 *
*/
class RuleOfExistence {
 /**
  * @issue Should the data have protected scope. It have made testing easier
  * but it would be preferred with a redesign that does not depend on
  * protected variables
  */

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
   * @test That an alive cell is detected at every possible direction when
   * ALL_DIRECTIONS is set
   * @test That cells older than 1 iteration is only counted as 1 alive cell
   * @test That the correct nr of alive cells is counted, from 0 to 9 alive
   * neighbours
   * @test That no error is thrown when an cell outside the board is given
   * @test That no error is thrown when an rim cell is given
   * @test That no error is thrown when an negative coords cell is given
   *
   * @bug Throws an error when an rim cell is given. Trying to acces cells
   * outside the game board, non existent
   * Test recommendation

   * Point out of board
   * Test that nrAlive cells is not affected if the cell age are > 1, counter
   * adds age instead of 1 for alive cells
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
   * @param aliveNeighbours nr of counted alive neighbours given by rule
   * @param isAlive if the current cell is currentlly alive
   * @return Action that defines what to happen with the cell next itteration
   */
  ACTION getAction(int aliveNeighbours, bool isAlive);

 public:
  /**
   * @brief Constructor for the abstract class RuleOfExistence
   *
   * @test test that the correct values is set
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

  /**
   * @brief Execute rule, in order specific to the concrete rule, by utilizing
   * template method DP
   */
  virtual void executeRule() = 0;

  /**
   * @brief Get function for the rule name
   *
   * @test Test that name given for constructor is used
   *
   * @return string Name of rule
   */
  string getRuleName() { return ruleName; }
};

#endif