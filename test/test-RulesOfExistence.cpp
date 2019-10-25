/**
 * @file test-RulesOfExistence.cpp
 *
 * @brief Contains test cases for the class RulesOfExistence
 */
#include "catch.hpp"
#include "TestClasses/TestClassRulesOfExistence.hpp"
#include "TestClasses/AccessRulesOfExistence.hpp"
#include "TestUtil/TestUtil.hpp"
#include "TestClasses/TestPoint.hpp"

#define RULES_OF_EXISTENCE_TAG "[RulesOfExistence]"

SCENARIO("Set constructor values should be stored in class",
         RULES_OF_EXISTENCE_TAG) {
    GIVEN("Default constuctor used") {
        map<Point, Cell> cells;

        AccessRulesOfExistence testClass(cells);

        TestClassRulesOfExistence::sTestValesRulesOfExistence(testClass, cells);
    }
}

SCENARIO("Given a existing board", RULES_OF_EXISTENCE_TAG) {
    //Test for rules using the 3 defined direction types
    //All, Cardinal, Diagonal

    //Create board
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 1, 1, false);

    //Check start conditions
    GIVEN("An new game board") {

        WHEN("Elements are added") {

            THEN("The bord should not be empty") {
                REQUIRE(!cells.empty());
                REQUIRE(9 == cells.size());
            }
        }
    }

    //Create a test instance
    AccessRulesOfExistence testClass(cells, ALL_DIRECTIONS);

    //define center point to set new values
    Point center{1, 1};
    GIVEN("Rules That checks all directions") { ///@toto add direction to header


        int age = 1;

        for (auto alivePos : ALL_DIRECTIONS) {

            TestPoint pointAlive = center + alivePos;

            //Test age to use
            std::stringstream header;
            header << "Current Alive cell is placed at distance from Cell: "
                      "" << alivePos << " abs pos: " << pointAlive;

            WHEN(header.str()) {
                //Update the current direction from the center point [1,1]
                std::vector<pair<TestPoint, int>> newCellAges;
                newCellAges.emplace_back(alivePos, age);


                //Update cell values
                TestUtil::updateCellAge(cells, center, newCellAges);

                bool cellIsAlive;

                std::cout << "Cell" << alivePos << std::endl;

                cellIsAlive = cells.at(
                    pointAlive.toPoint()).isAlive();

                THEN("The point ... should be alive") { //Requiere update header
                    REQUIRE(cellIsAlive);
                }

                THEN("Alive counter for the center point should return 1") {
                    // Why is direction no longer set in testClass
                    TestUtil::printCellAge(cells);
                    REQUIRE(
                        1 == testClass.countAliveNeighbours(center)
                    );
                }
            }
        }
    }

}

