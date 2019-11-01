/**
 * @file test-RuleFactory.cpp
 * @author Johan Karlsson, joka1806
 *
 * @brief This file contains test for the class RuleFactory
 */

#include "catch.hpp"

#include "GoL_Rules/RuleOfExistence_Conway.h"
#include "GoL_Rules/RuleOfExistence_VonNeumann.h"
#include "GoL_Rules/RuleOfExistence_Erik.h"

#include "GoL_Rules/RuleFactory.h"

/// @brief Tag used with CATCH to run test in this test file
#define RULE_FACTORY_TAG "[RuleFactory]"

/**
 * @brief Thest that getInstance always returns the same instance
 */
SCENARIO("Test that the getInstance() returns the same instance",
    RULE_FACTORY_TAG)
{
    WHEN("2 different instances is requested, 2 calls") {
        //Store 2 separate references to requested instances
        RuleFactory &ruleFactory1 = RuleFactory::getInstance();
        RuleFactory &ruleFactory2 = RuleFactory::getInstance();

        //Debug print
//    std::cout << "1: " << &ruleFactory1 << ", 2: " << &ruleFactory2 <<
//    std::endl;

        THEN("They should point to the same location") {
            REQUIRE(&ruleFactory1 == &ruleFactory2);
        }
    }
}

/**
 * @brief Test that the correct rule is created for varyin inputs
 *
 * @details Test rule input
 *  - Default (Conway)
 *  - Invalid (Conway)
 *  - VonNeumann
 *  - Erik
 */
SCENARIO("Test that each rule can be created from the factory",
    RULE_FACTORY_TAG)
{
    GIVEN("A valid factory") {
        //Create game board
        map<Point, Cell> cells;

        //Get instance of the factory
        RuleFactory *ruleFactory;
        *ruleFactory = RuleFactory::getInstance();

        //Test no rule name input
        WHEN("No rule is given") {
            RuleOfExistence
                *conwayRule = ruleFactory->createAndReturnRule(cells);
            THEN("The created rule should be \"conway\"")
            {
                REQUIRE("conway" == conwayRule->getRuleName());
            }
        }

        //Test non existent rule input
        WHEN("Non existent rule (\"kalle\") is given") {
            RuleOfExistence
                *conwayRule = ruleFactory->createAndReturnRule(cells, "kalle");
            THEN("The created rule should be \"conway\"")
            {
                REQUIRE("conway" == conwayRule->getRuleName());
            }
        }

        //Test Erik rule
        WHEN("Erik rule is given") {
            RuleOfExistence
                *conwayRule = ruleFactory->createAndReturnRule(cells, "erik");
            THEN("The created rule should be \"erik\"")
            {
                REQUIRE("erik" == conwayRule->getRuleName());
            }
        }

        //Test VonNeumann rule
        WHEN("VonNeumann rule is given") {
            RuleOfExistence
                *conwayRule = ruleFactory->createAndReturnRule(cells, "von_neumann");
            THEN("The created rule should be \"von_neumann\"")
            {
                REQUIRE("von_neumann" == conwayRule->getRuleName());
            }
        }
    }
}