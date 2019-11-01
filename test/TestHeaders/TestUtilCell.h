/**
 * @file TestUtilCell.h
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

#include "Cell_Culture/Cell.h"

/**
 * @brief Support functions that modifies or interacts with Cells or Cell data
 *
 * @details The TestUtilCell should contain functions that modifies or interacts
 * with test data or objects that are note tied to the Cell class.
 */
namespace TestUtilCell {

/**
 * @brief Sets the specific age to a cell.
 *
 * @details Used next generation action and update cells which limits
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
 * @brief Ages non rim cells ageIterations
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
 * @brief Gives life to dead non rim cells
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
 * @brief See setCellAlive(Cell &cell, bool &updated)
 *
 * @details Overloaded function where the caller does not care if the cell was
 * updated
 * or not
 * @param cell to give life
 * @return operation success
 * @retval true if the cell is alive
 * @retval false if the cell could not be given life
 */
bool setCellAlive(Cell &cell);


}

#endif