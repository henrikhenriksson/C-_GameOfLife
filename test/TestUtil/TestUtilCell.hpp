//
// Created by Johan on 2019-10-23.
//

#ifndef TESTUTILCELL_HPP
#define TESTUTILCELL_HPP



namespace TestUtilCell {
//void setCellAge(Cell &cell, int newAge);
//
//void ageCell(Cell &cell, int ageIterations);
//
//void setCellAlive(Cell &cell);
void setCellAlive(Cell &cell) {
    if (!cell.isAlive()) {
        cell.setNextGenerationAction(GIVE_CELL_LIFE);
        cell.updateState();
    }
}

void setCellAge(Cell &cell, int newAge) {

    if (cell.getAge() > newAge) {
        cell.setNextGenerationAction(KILL_CELL);
        cell.updateState();
        setCellAlive(cell);
    }

    for (int currAge = cell.getAge(); currAge < newAge; currAge++) {
        cell.setNextGenerationAction(IGNORE_CELL);
        cell.updateState();
    }

}

void ageCell(Cell &cell, int ageIterations) {
    setCellAlive(cell);
    for (int i = 0; i < ageIterations; i++) {
        cell.setNextGenerationAction(IGNORE_CELL);
        cell.updateState();
    }
}

bool isRimCell(int row, int col) {
    return ((row == 0) || (row == WORLD_DIMENSIONS.HEIGHT + 1)
        || (col == 0) || col == WORLD_DIMENSIONS.WIDTH + 1);
}

}

#endif