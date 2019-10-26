/**
 * @file test-RulesOfExistence.cpp
 *
 * @brief Contains test cases for the class RulesOfExistence
 */
#include "catch.hpp"
#include "TestPoint.h"
#include "TestSrcFiles/TestClassRulesOfExistence.hpp"
#include "TestSrcFiles/AccessRulesOfExistence.hpp"
#include "TestUtil/TestUtil.hpp"

#define RULES_OF_EXISTENCE_TAG "[RulesOfExistence]"

/**
 * @brief Test that the Constructor sets and stores the expected values
 */
SCENARIO("Set constructor values should be stored in class",
         RULES_OF_EXISTENCE_TAG) {
    GIVEN("Default constuctor used") {
        map<Point, Cell> cells;

        TestUtil::createMap(cells, 10, 10, false);

        std::cout << "Map size2: " << cells.size() << std::endl;

        AccessRulesOfExistence testClass(cells);

        TestClassRulesOfExistence::sTestValesRulesOfExistence(testClass, cells);
    }GIVEN("Custom values sent to the Constuctor") {
        map<Point, Cell> cells;

        TestUtil::createMap(cells, 10, 10, false);

        std::cout << "Map size2: " << cells.size() << std::endl;

        PopulationLimits expLim{1, 2, 3};

        std::string expName = "Kalle";

        AccessRulesOfExistence testClass(cells, DIAGONAL, expLim, expName);

        TestClassRulesOfExistence::sTestValesRulesOfExistence(testClass,
                                                              cells,
                                                              expLim,
                                                              DIAGONAL,
                                                              expName);
    }
}

/**
 * @brief Test that all an alive cell is detected at all available positions
 * when ALL_DIRECTIONS is used
 *
 * @details Uses a minimized game board of size [1,1] which will create a
 * board of absolute size [3,3] since this contains the tested cell and
 * sorrounding cells.
 * Also tests that cells older than 1 iteratin only is tested once
 */
SCENARIO("Alive cells should be detected in all directions",
         RULES_OF_EXISTENCE_TAG) {

    //Create minimal board that defines sorounding cells for the tested cell,
    // center
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 1, 1, false);

    //define center point to set new values
    TestPoint center{1, 1};

    GIVEN("Rules That checks ALL_DIRECTIONS") {
        //Create a test instance
        AccessRulesOfExistence testClass(cells, ALL_DIRECTIONS);

        TestClassRulesOfExistence::testAliveCellInAllDirections(
            testClass,
            center,
            ALL_DIRECTIONS);
    }

    GIVEN("Rules That checks CARDINAL directions") {
        // header
        //Create a test instance
        AccessRulesOfExistence testClass(cells, CARDINAL);

        TestClassRulesOfExistence::testAliveCellInAllDirections(
            testClass,
            center,
            CARDINAL);
    }

    GIVEN("Rules That checks DIAGONAL directions") {
        // header
        //Create a test instance
        AccessRulesOfExistence testClass(cells, DIAGONAL);

        TestClassRulesOfExistence::testAliveCellInAllDirections(
            testClass,
            center,
            DIAGONAL);
    }
}

/**
 * @brief Test that countAliveNeighbours returns the correct nr of alive
 * neighbours.
 *
 * @details Test for 0-9 alive cells.
 */
SCENARIO("Should be able to count all alive cells", RULES_OF_EXISTENCE_TAG) {
    //Create minimal board that defines sorounding cells for the tested cell,
    // center
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 1, 1, false);

    //define center point to set new values
    TestPoint center{1, 1};

    GIVEN("Rules that checks all directions") {
        AccessRulesOfExistence testClass(cells);

        for (int nrAliveCells = 0; nrAliveCells <= ALL_DIRECTIONS.size();
             nrAliveCells++) {
            std::stringstream header;
            header << nrAliveCells << " nr of neighbors is set to alive";
            WHEN(header.str()) {

                //Set alive cells
                auto it = ALL_DIRECTIONS.begin();
                for (int i = 0; i < nrAliveCells; i++, it++) {
                    TestUtil::updateCellAge(cells, TestPoint(*it) + center, 1);
                }

                //Check that the correct nr of alive cells is returned
                header.str(std::string(""));
                header << "countAliveNeighbours should return: " <<
                       nrAliveCells;
                THEN(header.str()) {
                    REQUIRE(nrAliveCells
                                == testClass.countAliveNeighbours(center.toPoint()));
                }
            }
        }
    }
}

SCENARIO("Should handle if Points outside the board passed") {
    //Create minimal board that defines sorounding cells for the tested cell,
    // center
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 1, 1, false);

    //define center point to set new values
    GIVEN("A game board of size [3,3]") {
        AccessRulesOfExistence testClass(cells);

        WHEN("A valid point is given[3,2]") {
            TestPoint invalidPoint(1, 1);
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

        WHEN("A rim cell is given [0,1]") {
            TestPoint invalidPoint(0, 1);
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

        WHEN("A rim cell is given [2,1]") {
            TestPoint invalidPoint{2, 1};
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

        WHEN("A rim cell is given [1,0]") {
            TestPoint invalidPoint(1, 0);
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

        WHEN("A rim cell is given [1,2]") {
            TestPoint invalidPoint(1, 2);
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

        WHEN("A negative value cells is given [-1,2]") {
            TestPoint invalidPoint(-1, 2);
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

        WHEN("A negative value cells is given [1,-2]") {
            TestPoint invalidPoint(1, -2);
            THEN("No error should be thrown") {
                REQUIRE_NOTHROW(
                    testClass.countAliveNeighbours(invalidPoint.toPoint())
                );
            }
        }

    }
}