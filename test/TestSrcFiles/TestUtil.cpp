//
// Created by Johan on 2019-10-28.
//

#include "TestUtil.h"

//-------------------------------------------------------------------------------------
void TestUtil::createMap(std::map<Point, Cell> &cells,
               int height,
               int width,
               bool defineRimCells) {

    //Update world dimensions
    WORLD_DIMENSIONS.HEIGHT = height;
    WORLD_DIMENSIONS.WIDTH = width;


    //Iterate through the world and create a new cell for each position
    for (int row = 0; row <= height + 1; row++) {
        for (int col = 0; col <= width + 1; col++) {
            cells.insert(
                pair<Point, Cell>
                    (
                        Point{row, col},
                        Cell(defineRimCells && isPosRimCell(row, col))
                    )
            );

        }
    }
}

void TestUtil::printIsRimCell(std::map<Point, Cell> &cells) {
    //Iterate through all the cells and print their rim cell status
    for (auto mapIt : cells) {
        std::cout << mapIt.first.x << "," << mapIt.first.y
                  << ":" << mapIt.second.isRimCell() << std::endl;
    }
}

bool TestUtil::isPosRimCell(int row, int col) {
    //Check if position is around the boarders of the game board
    return ((row == 0) || (row == WORLD_DIMENSIONS.HEIGHT + 1)
        || (col == 0) || col == WORLD_DIMENSIONS.WIDTH + 1);
}

void TestUtil::printCellAge(std::map<Point, Cell> &cells) {
    //Iterate through all the cells and print position and age
    for (auto mapIt : cells) {
        std::cout << " " << mapIt.first.x << "," << mapIt.first.y
                  << ":" << mapIt.second.getAge() << std::endl;
    }
}

void TestUtil::updateCellAge(std::map<Point, Cell> &cells,
                   std::vector<pair<TestPoint, int>>& newCellAges)
{
    updateCellAge(cells, TestPoint(0,0), newCellAges);
}

void TestUtil::updateCellAge(std::map<Point, Cell> &cells,
                   TestPoint center,
                   std::vector<pair<TestPoint, int>> &newCellAges) {

    int newX, newY; //Variables used to temp store the new positions
    for (auto update : newCellAges) {

        //set the age of the cell
        TestUtilCell::setCellAge(
            cells[(center + update.first).toPoint()],
            update.second);
        //TestUtilCell::setCellAge(cells[newPoint], update.second);
    }
}

void TestUtil::updateCellAge(std::map<Point, Cell> &cells, TestPoint pos, int
age)
{
    TestUtilCell::setCellAge(
        cells[pos.toPoint()],age);
}


