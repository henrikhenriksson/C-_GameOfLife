/**
 * @file TestUtilCell.hpp
 * @author Johan Karlsson joka1806
 *
 * @brief This file contains suport functions to modify or interact with the
 * Cell class
 *
 * @details This file contains commonly used funcitons that modifies data or
 * instances of the Cell class. This file should not contain any test
 * functions, only supporting functions. Test functions should be places in
 * the TestCell file
 */

#ifndef TESTUTILCELL_HPP
#define TESTUTILCELL_HPP


/**
 * @brief Support functions that modifies or interacts with Cells or Cell data
 *
 * @details The TestUtilCell should contain functions that modifies or interacts
 * with test data or objects that are note tied to the Cell class.
 */
namespace TestUtilCell {

/**
 * @brief sets the specific age to a cell.
 *
 * @details used next generation action and update cells which limits
 * function to affect non rim cells. If the age 0 is set the cell is killed
 * and setting a age > 0 will give life to the cell
 *
 * @param cell to update
 * @param newAge to set
 *
 * @return operation success
 * @retval true
 * @retval false - Failed to set wanted age
 */
bool setCellAge(Cell &cell, int newAge);

/**
 * @brief ages non rim cells ageIterations
 *
 * @details If the cell is a non rim cell the cell is aged the given nr of
 * iterations. Dead cells is given life.
 *
 * @param cell to age
 * @param ageIterations nr iterations to age
 * @return operation sucess
 * @retval true
 * @retval false
 */
bool ageCell(Cell &cell, int ageIterations);

/**
 * @brief gives life to dead non rim cells
 *
 * @details Cells that already are alive is ignored and ded cells are given
 * life. If the cell is a rim cell the action is ignored.
 * This function does not kill a alive cell
 *
 * @param cell to give life
 * @param [out] updated sets if the cell has been updated, was dead from start
 * @return operation success
 * @retval true - if the cell was a non rim cell
 */
bool setCellAlive(Cell &cell, bool &updated);

/**
 * @overload bool setCellAlive(Cell &cell, bool &updated)
 * Overloaded function where the caller does not care if the cell was updated
 * or not
 * @param cell to give life
 * @return operation success
 * @retval true if the cell is alive
 * @retval false if the cell could not be given life
 */
bool setCellAlive(Cell &cell);

//--------------------------------------------------------------------------------
bool setCellAlive(Cell &cell)
{
    bool dummy;
    return setCellAge(cell, dummy);
}

bool setCellAlive(Cell &cell, bool &updated) {

    //If cell is rim cell it cant be given life
    if(cell.isRimCell())
    {
        updated = false;
        return false;
    }

    //Ignore alive cells
    if (!cell.isAlive()) {
        cell.setNextGenerationAction(GIVE_CELL_LIFE);
        cell.updateState();
        updated = true;
    }
    return true;
}

bool setCellAge(Cell &cell, int newAge) {

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
        cell.updateState();

        //Give cell life again
        if(newAge > 0) {
            setCellAlive(cell);
        }
    }

    //Age the cell the remaining wanted iterations
    for (int currAge = cell.getAge(); currAge < newAge; currAge++) {
        cell.setNextGenerationAction(IGNORE_CELL);
        cell.updateState();
    }

    //return if the cell has reached the wanted state
    return (cell.getAge() == newAge);

}

bool ageCell(Cell &cell, int ageIterations)
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

bool isRimCellPos(int row, int col) {
    //Check if the given position is a rim cell position
    return ((row == 0) || (row == WORLD_DIMENSIONS.HEIGHT + 1)
        || (col == 0) || col == WORLD_DIMENSIONS.WIDTH + 1);
}

}

#endif