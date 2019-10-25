/**
 * @file testTestPoint.cpp
 *
 * @author Johan Karlsson
 *
 * @brief This file contains test for the Class TestPoint
 *
 */
#include <string>
#include <sstream>
#include "catch.hpp"
#include "TestPoint.h"

/**
 * @brief Test that the correct values is set with the available constructors
 */
SCENARIO("Test constructors") {

    // Test the default constructor
    GIVEN("Default constructor") {
        TestPoint test_point;
        THEN("The created test point should get the coordinates [0,0]") {
            REQUIRE(test_point.x == 0);
            REQUIRE(test_point.y == 0);
        }
    }

    // Test the x,t int input constructor
    GIVEN("The x,y coordinates [1,1]") {
        TestPoint test_point(1, 1);
        THEN("The created test point should get the same coordinates, [1,1]") {
            REQUIRE(test_point.x == 1);
            REQUIRE(test_point.y == 1);
        }
    }

    // Test the Point input constructor
    GIVEN("A point at [1,1]") {
        TestPoint test_point(Point{1, 1});
        THEN("The created test point should get the same coordinates, [1,1]") {
            REQUIRE(test_point.x == 1);
            REQUIRE(test_point.y == 1);
        }
    }

    // Test the Directions input constructor
    GIVEN("A direction at [2,4]") {
        TestPoint test_point(Directions{2, 4});
        THEN("The created test point should get the same coordinates, [2,4]") {
            REQUIRE(test_point.x == 2);
            REQUIRE(test_point.y == 4);
        }
    }

    // Test the TestPoint input constructor
    GIVEN("A Test Point at [5,2]") {
        TestPoint test_point(TestPoint{5, 2});
        THEN("The created test point should get the same coordinates, [5,2]") {
            REQUIRE(test_point.x == 5);
            REQUIRE(test_point.y == 2);
        }
    }

    // Test that the created TestPoint is not changed when the orginal
    // TestPoint is created
    GIVEN("A direction at [5,2]") {
        TestPoint tpOrg = TestPoint{5, 2};
        TestPoint tpCp(tpOrg);
        THEN("The created test point should get the same coordinates, [5,2]") {
            REQUIRE(tpCp.x == 5);
            REQUIRE(tpCp.y == 2);
        }WHEN("The first Test point is given new coordinates") {
            tpOrg.x = 0;
            tpOrg.y = 0;
            THEN(
                "The created test point should still have the same "
                "coordinates, [5,"
                "2]") {
                REQUIRE(tpCp.x == 5);
                REQUIRE(tpCp.y == 2);
            }
        }
    }
}

/**
 * @brief Test that correct Point and Directions is created
 */
SCENARIO("Extracting a Point and Directions form a instance from the TestPoint")
{
    GIVEN("A TestPoint with the cordinates [7,2]") {
        TestPoint test_point(7,2);
        WHEN("A Directions is created from the TestPoint") {
            Directions testDir = test_point.toDirections();
            THEN("The direction should return the coordinates [7,2]") {
                REQUIRE(7 == testDir.HORIZONTAL);
                REQUIRE(2 == testDir.VERTICAL);
            }
        }WHEN("A Point is created from the TestPoint") {
            Point testPoint = test_point.toPoint();
            THEN("The direction should return the coordinates [7,2]") {
                REQUIRE(7 == testPoint.x);
                REQUIRE(2 == testPoint.y);
            }
        }
    }
}

/**
 * @brief Test that + and += operations gives correct result
 */
SCENARIO("Adding TestPoints") {

    GIVEN("Two TestPoints tp1[1,3] och tp2[4,7]") {
        TestPoint tp1(1, 3);
        TestPoint tp2(4, 7);
        WHEN("tp1 += tp2 is porformed") {
            tp1 += tp2;
            THEN("tp1 should be [5,10]") {
                REQUIRE(5 == tp1.x);
                REQUIRE(10 == tp1.y);
            }THEN("tp2 should still be [4,7]") {
                REQUIRE(4 == tp2.x);
                REQUIRE(7 == tp2.y);
            }
        }
        WHEN("tp3 + tp1 tp2 is porformed") {
            TestPoint tp3 = tp1 + tp2;
            THEN("tp3 should be [5,10]") {
                REQUIRE(5 == tp3.x);
                REQUIRE(10 == tp3.y);
            }THEN("tp1 should still be [1,3]") {
                REQUIRE(4 == tp2.x);
                REQUIRE(7 == tp2.y);
            }
            THEN("tp2 should still be [4,7]") {
                REQUIRE(4 == tp2.x);
                REQUIRE(7 == tp2.y);
            }
        }
    }

}

/**
 * @brief Test that sending a TestPoint to a stream formats the outputs correct
 */
SCENARIO("Sending a point to a stream")
{
    GIVEN("The TestPoint [4,5]")
    {
        TestPoint tp(4,5);
        WHEN("Printing the point")
        {
            std::stringstream out;
            out << tp;
            THEN("The output should be 4:5")
            {
                REQUIRE("4,5" == out.str());
            }
        }
    }
}