/**
 * @file    RuleOfExistence_Erik.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This file contains the class for Eriks rules for the game Game of life
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
#define GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H


#include "RuleOfExistence.h"

/**
 * @brief Erik's RuleOfExistence, based on Conway's rule while also
 * differentiate the appearance of cells based on their age.
 *
 * @details Concrete Rule of existence, implementing Erik's rule.
 * Sentient lifeforms is rarely created, but once in a while a cell has lived
 * enough generations to become as wise as Erik.
 * - Once a cell has survived a minimum amount of generations it will
 * receive a color to distinguish itself from younger ones.
 * - If such a cell would then survive another set amount of generations, it
 * will be marked with a value of **E**.
 * - In the extreme case, where the cell has achieved above requirements and
 * is determined to be the oldest living cell, it will
 * become a **prime elder**, and have its color changed once again. A generation
 * may only have one such elder.
 *
 * @issue The class name "conway" should be declared as a class constant that
 * is accessable from the outside
*/
class RuleOfExistence_Erik : public RuleOfExistence
{
private:
  /**
   * @brief char value to Differentiate very old cells.
   * @issue name does not describe what the value is used for.
   * @issue Since it is not changed should it be defined as a constant?
   */
    char usedCellValue;
    Cell* primeElder; ///< @brief Reference to an current elder cell

    /**
     * @brief Applies the Erik specific rules
     *
     * @details Checks if a living cell has reached the age of an old or Erik
     * cells
     * and sets their next gen colo and next gen value.
     * Checks if the cell is the oldest cell, if so it sets the cell as the
     * elder
     * If a cell is killed the cell value is reset to # and the cell is
     * removed as the elder if it is killed.
     *
     * @test That an cell is marked as old when older than 5 generations,
     * STATE_COLORS.OLD
     * @test That the OLD color is reset when a Living cell, OLD is killed
     * @test That the Elder color is reset when a Elder cell is killed
     * @test That an cell cell that reached the Erik state is marked with an 'E'
     * @test That the oldest cell older than 10 get the status Elder
     * @test That the elder data is reset when an elder cell dies
     * @test That only one elder can exists

     * @test That the correct Elder is set when an current Elder cell dies
     *
     * @issue Im missing how >4 relates to the requirement >5
     * @issue 4 is a magic number. Should be replaced with a class constant
     * @issue Im missing how >9 relates to the requirement >10
     * @issue 9 is a magic number. Should be replaced with a class constant
     *
     * @param cell The current cell to update
     * @param action The cell action
     */
    void erikfyCell(Cell& cell, ACTION action);

    /**
     * @brief Sets the private variable elder to the provided cell
     * @param newElder new elder
     */
    void setPrimeElder(Cell* newElder);

public:
  /** @brief default constructor
   * @test that the correct values are set
   * @param cells game board
   */
    explicit RuleOfExistence_Erik(map<Point, Cell>& cells)
            : RuleOfExistence({2,3,3}, cells, ALL_DIRECTIONS, "erik"), usedCellValue('E') {
        primeElder = nullptr;
    }

    /// @brief Deconstructor
    ~RuleOfExistence_Erik() override = default;

  /**
   * @brief Executes the game rules.
   * @details Cells that are Killed gets the color STATE_COLORS.DEAD
   * Cells that are given life gets the color STATE_COLORS.LIVING
   * Specific Eriks rules are supplied in by function erikfyCell
   *
   * @test that a Cell that is given life gets the color STATE_COLORS.LIVING
   * but the same value
   * @test that a Cell that is killed gets the color STATE_COLORS.DEAD but the
   * same value
   * @test that a Alive cell that stays Alive does not change color or value
   * @test that a Dead cell that stays Dead does not change color or value
   *
   */
    void executeRule() override;
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
