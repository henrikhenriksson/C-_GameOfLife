/**
 * @file    RuleOfExistence_VonNeumann.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This class contains the definitions of the VonNeumann Game of life
 * rules
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
#define GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H

#include "RuleOfExistence.h"
/**
 * @brief Von Neumann's RuleOfExistence, differs from Conway in that only 4
 * neighbours are accounted for.
 *
 * @details Concrete Rule of existence, implementing Von Neumann's rule.
 * Only difference from Conway is that neighbours are determined using only
 * cardinal directions (N, E, S, W).
*/
class RuleOfExistence_VonNeumann : public RuleOfExistence
{
private:

public:
  /// @brief Default constructor
    explicit RuleOfExistence_VonNeumann(map<Point, Cell>& cells)
            : RuleOfExistence({ 2,3,3 }, cells, CARDINAL, "von_neumann") {}
    /// @brief Default destructor
            ~RuleOfExistence_VonNeumann() override = default;

/**
 * @brief calculates the next generation values for the VonNewmann rules
 *
 * @details Uses Cardinal directions when checking for alive neighbours
 * Sets the color STATE_COLORS.DEAD to cells that are killed
 * Sets the color STATE_COLORS.LIVING to cells that are given life
 * Uses default functions for counting alive neighbours and which action to take
 *
 * Test Recommendations
 * Test that only alice cells at cardinal directions is counted
 * Test that the correct color is set for cells that are killed
 * Test that the correct color is set for cells that are given life
 */
    void executeRule() override;
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
