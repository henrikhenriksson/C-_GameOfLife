/**
 * @file test-RulesOfExistence.cpp
 *
 * @brief Contains test cases for the class RulesOfExistence
 */
#include "catch.hpp"
#include "TestClasses/TestClassRulesOfExistence.hpp"
#include "TestClasses/AccessRulesOfExistence.hpp"
#include "TestUtil/TestUtil.hpp"


#define RULES_OF_EXISTENCE_TAG "[RulesOfExistence]"

SCENARIO("Set constructor values should be stored in class",
         RULES_OF_EXISTENCE_TAG) {
    GIVEN("Default constuctor used") {
        map<Point, Cell> cells;

        AccessRulesOfExistence testClass(cells);

        TestClassRulesOfExistence::sTestValesRulesOfExistence(testClass, cells);
    }
}

SCENARIO("Given a specific nr of alive neighbours", "[Test]")
{
    //Test for rules using the 3 defined direction types
    //All, Cardinal, Diagonal
    map<Point, Cell> cells;
    TestUtil::createMap(cells, 1,1, false);

    vector<Directions> dir = ALL_DIRECTIONS;
    AccessRulesOfExistence testClass(cells, dir);
    vector<Directions> testDir = testClass.getDirections();
    std::cout << "TEste" << std::endl;

    GIVEN("Rules with direction: ") { ///@toto add direction to header

        //Create map with updated cells
        Point d1 {1,1};

        std::vector<pair<Point, int>> newCellAges;
        newCellAges.push_back(std::make_pair(d1, 1));

        Point center{1,1};
        //Make util function
        TestUtil::updateCellAge(cells, center, newCellAges);
//
//
//        REQUIRE(cells[Point{2,2}].isAlive());
//
//
//        TestUtil::printAliveCell(cells );
//        THEN("Alive counter should return 1")
//        {
//            // Why is direction no longer set in testClass
//            TestUtil::printAliveCell(cells );
//            REQUIRE(1 == testClass.countAliveNeighbours(Point{1,1}));
//        }
    }
}

