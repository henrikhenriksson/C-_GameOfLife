//
// Author Johan Karlsson, joka1806
// Doxygen comments not adde to .cpp files
//

#include "TestUtilCell.h"

//--------------------------------------------------------------------------------
bool TestUtilCell::setCellAlive(Cell &cell)
{
    bool dummy;
    return setCellAlive(cell, dummy);
}

bool TestUtilCell::setCellAlive(Cell &cell, bool &updated) {

    //If cell is rim cell it cant be given life
    if(cell.isRimCell())
    {
        updated = false;
        return false;
    }

    //Ignore alive cells
    if (!cell.isAlive()) {
        cell.setNextGenerationAction(GIVE_CELL_LIFE);
        cell.setNextColor(STATE_COLORS.LIVING);
        cell.updateState();
        updated = true;
    }
    return true;
}

bool TestUtilCell::setCellAge(Cell &cell, int newAge) {

    //Check if the cell can be updated. If the cell is a rim cell
    // technically the age 0 could be set
    if(cell.isRimCell() && newAge != 0)
    {
        //Failed to update cell due to rim cell
        return false;
    }

    //Check if the cell already is older than the wanted age
    if (cell.getAge() > newAge) {
        //Kill cell to reset age
        cell.setNextGenerationAction(KILL_CELL);
        cell.setNextColor(STATE_COLORS.DEAD);
        cell.updateState();
    }

    //Give cell life again
    if(newAge > 0) {
        setCellAlive(cell);
    }

    //Age the cell the remaining wanted iterations
    for (int currAge = cell.getAge(); currAge < newAge; currAge++) {
        cell.setNextGenerationAction(IGNORE_CELL);
        cell.updateState();
    }

    //return if the cell has reached the wanted state
    return (cell.getAge() == newAge);

}

bool TestUtilCell::ageCell(Cell &cell, int ageIterations)
{
    //Check if the cell can age, is non rim cell
    if(cell.isRimCell() && (ageIterations != 0) )
    {
        return false;
    }

    //Define variable to keep track of nr of iterations the cell has aged
    int i = 0;

    //If cell is dead from start it ages 1 iteration when given life
    if(cell.getAge() == 0) {
        setCellAlive(cell);
        i++;
    }

    //Age remaining iteration
    for (/*i start value already set*/; i < ageIterations; i++) {
        cell.setNextGenerationAction(IGNORE_CELL);
        cell.updateState();
    }
    return true;
}
