/**
 * @file testTestPoint.cpp
 *
 * @author Johan Karlsson
 *
 * @brief This file contains test for the Class TestPoint
 *
 */
#include <catch.hpp>
#include <string>

#include "GoL_Rules/RuleOfExistence.h" //Directions
#include "Support/SupportStructures.h" //Point

#include "./TestClasses/TestPoint.hpp"

SCENARIO("Test copy Point constructor")
{
    GIVEN("A point at [1,1]")
    {
        TestPoint test_point(Point{1,1});
        THEN("The created test point should get the same cordinates, [1,1]")
        {
//            REQUIRE(test_point.x == 1);
//            REQUIRE(test_point.y == 1);            REQUIRE(test_point.x == 1);
//            REQUIRE(test_point.y == 1);
        }
    }
}
