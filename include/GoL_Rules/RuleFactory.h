/**
 * @file    RuleFactory.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This file contains the RuleFactory
*/

#ifndef RULEFACTORY_H
#define RULEFACTORY_H

#include "GoL_Rules/RuleOfExistence.h"

/**
 * @brief Singleton class to handle creation of RulesOfExistence objects.
 * @details Create an instance of a game RuleOfExistence. Available rules are
 * - Conway
 * - VonNeumann
 * - Erik
 */
class RuleFactory {
 private:
  /// @brief private constructor
  RuleFactory() = default;

 public:
  /// @brief Get the instance of the singelton class
  static RuleFactory &getInstance();

  /**
   * @brief Create an instance of the wanted RuleOfExistence
   * @details Supported rules Conway, VonNeumann and Eric. If no rule name or
   * if an invalid name is supplied Conway is used.
   * Identification strings
   *  - von_neumann
   *  - eric
   *
   * Test Recommendation
   * - Create a VonNeumann rule
   * - Create a Eric rule
   * - A invalid name should return a Conway rule
   * - A empty input should return a Conway rule
   * - What happends if a nullptr is supplied?
   *
   * @test That the expected class is created
   * @test That invalid rule names creates a Conway rule
   * @test That if no rule is given, default, a Conway rule is created
   *
   * @issue It would be good to define constants tha can be used by callers
   * for class identification string. Such ass RuleOfExistence_Erik.CLASS_NAME
   *
   * @param cells Game board
   * @param ruleName string of the rule name to use
   * @return RuleOfInstance* reference to the instance of the created rule
   */
  RuleOfExistence *createAndReturnRule(map<Point, Cell> &cells,
                                       const string &ruleName = "conway");
};

#endif