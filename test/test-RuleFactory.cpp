/**
 * @file test-RuleFactory.cpp
 * @author Johan Karlsson, joka1806
 *
 * @brief This file contains test for the class RuleFactory
 */

#include "catch.hpp"
#include "GoL_Rules/RuleFactory.h"

#define RULE_FACTORY_TAG "[RuleFactory]"

SCENARIO("Tet")
{
    RuleFactory *ruleFactory1, *ruleFactory2;
    *ruleFactory1 = RuleFactory::getInstance();
    *ruleFactory2 = RuleFactory::getInstance();

    REQUIRE(ruleFactory1 == ruleFactory2);
}

//SCENARIO("Test that each rule can be created from the factory", RULE_FACTORY_TAG)
//{
//    RuleFactory *ruleFactory;
//    *ruleFactory = RuleFactory::getInstance();
//
//
//}