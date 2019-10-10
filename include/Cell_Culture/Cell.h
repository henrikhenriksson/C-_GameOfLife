/**
 * @file        Cell.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This class handles a single cell in the game "Game of Life"
 *
 * @details A cell is square in the board of the Game of Life that can be
 * either dead or alive. In this version long living cells can be defined as
 * OLD or ELDER. Each state having its own color representation. The fait of
 * each cell is decided in the game logic
*/

#ifndef cellH
#define cellH

#include "../../terminal/terminal.h"

/// @brief Data structure holding colors to visualize the state of cells.
struct StateColors {
    COLOR LIVING, ///< Representing living cell
            DEAD, ///< Representing dead cell
            OLD,  ///< Representing old cell
            ELDER;///< Representing very old cell
}
/// @brief Default state color values color values
/* Initiate default state color values. */
const STATE_COLORS = { COLOR::WHITE, COLOR::BLACK, COLOR::CYAN, COLOR::MAGENTA };

/// @brief Available Cell actions
enum ACTION { KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING };


/**
@brief Cells represents a certain combination of row and column of the
 simulated world.

 @details Cells may be of two types; rim cells, those representing the outer
 limits of the world, or non-rim cells. The first cell type are immutable,
 exempt from the game's rules, and thus their values may not be changed. The
 latter type, however, may be changed and edited in ways specified by the rules.
 Each cell stores its current state and the state for the next iteration
*/
class Cell {

private:
    /**
     * Stores the internal cell data for the current iteration. Is
     * used when deciding the next state for this ans the surrounding cells
     */
    struct CellDetails {	// encapsulate cell details
        int age;
        COLOR color;
        bool rimCell;
        char value;
    } details;

    /**
     * Used to store the calculated cell data for the next iteration
     */
    struct NextUpdate {		// encapsulate changes to next state
        ACTION nextGenerationAction;
        COLOR nextColor;
        char nextValue;
        bool willBeAlive;	// some rules may need to know beforehand whether the cell will be alive
    } nextUpdate;

    /**
     * increments the current age of the cell
     */
    void incrementAge() { details.age++; }

    /**
     * Resets the age for the cell to 0
     */
    void killCell() { details.age = 0; }

    // Sets the character value of the cell, which will be printed to screen.
    void setCellValue(char value) { details.value = value; }

    void setColor(COLOR color) { this->details.color = color; }

public:

    /**
     * @brief Constructor for class Cell.
     * @param isRimCell Sets if the current cell is a rim cell or not
     * @param action What is the initial state of the cell
     */
    explicit Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    /**
     * @brief returns if the cell is alive or not
     *
     * @details A cell is vied as alive if the cell is not a rim cell or if
     * the cell has a age => 0
     *
     * Test Recommendations
     * @test rim cells cant be alive
     * @test cells with details.age >= 0 should be marked as alive
     *
     *
     * @return bool is alive
     * @retval TRUE cell is alive
     * @retval FALSE cell is dead
     */
    bool isAlive();

    /**
     * @brief Updates the cell action for the next generation
     *
     * @details The action for a rim cell cant be updated
     * If the cell currently is alive it cant be updated to GIVE_CELL_LIFE
     *
     * Test Recommendations
     * @test trie to update the state of a rim cell
     * @test GIVE_CELL_LIFE is not set when the cell is alive
     *
     * @param action for next iteration
     */
    void setNextGenerationAction(ACTION action);

    /**
     * @brief Update the cell state from data set in the cells next iteration
     * data
     *
     * @details
     * If the cell is killed the age is set to 0<br>
     * If the cell is born or if the cell stays alive the age is incremented
     * The cell value, character shown, and color is updated if their
     * next generation data does not match their current status
     * The current set action
     *
     * Test Recommendations
     * @test An alive rim cell should not age
     * @test An dead cell should stay dead if neutral actions is used such as
     * IGNORE_CELL or DO_NOTHING
     * @test nextUpdate.nextGenerationAction should be reset after
     */
    void updateState();

    /**
     * @brief Get function for the current cell age (nr iterations)
     *
     * Test Recommendations
     * @test set age and check that the function returns the correct value
     *
     * @return int cell age, nr iterations
     * @retval 0 for dead cells
     * @retval 1.. nr of iterations the cell has been alive
     */
    int getAge() { return details.age; }

    /**
    * @brief Get function for the current cell color
    *
    * Test Recommendations
    * @test set color and check that the function returns the correct value
    *
    * @return COLOR current cell color
    */
    COLOR getColor() { return details.color; }

     /**
     * @brief Get function for the current cell color
     *
     * @details Determines whether the cell is a rim cell, and thus should be
     * immutable
     *
     * Test Recommendations
     * @test set Rim cell and check that the function returns the correct value
     *
     * @return bool if the cell is a rim cell
     * @retval TRUE the cell is a rim cell
     * @retval FALSE the cell is not a rim cell
     */
    bool isRimCell() { return details.rimCell; }

    /**
     * @brief set function for the next iteration color
     *
     * Test recommendations
     * @test set next iteration color and read that the color has been set
     * @test set an color index outside of COLOR class values?
     *
     * @param nextColor color to be used the next iteration
     */
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }

    /**
     * @brief get function for the character that should represent the cell
     *
     * @details the current character used to represent the cell can be
     * changed to
     * distinguish the cell when shown
     *
     * Test recommendations
     * @test set a cell value and check that the function returns the correct
     * value
     *
     * @return char cell representation char
     */
    char getCellValue() { return details.value; }

    /**
     * @brief set function for the cell next iteration value
     *
     * Test recommendation
     * @test set value with function. Call update and check current value
     *
     * @bug should next iteration value change when DO_NOTING is set as action
     *
     * @param value value to be used for next iteration value
     */
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    /**
     * @brief Set the is alive flag for the next iteration.
     *
     * @details Not used internally by this class and
     *
     * Test Recommendations
     * @test since this flag is not used internally when deciding the the
     * next iteration values set and get test should be enough
     *
     * @param isAliveNext bool, set if cell should be alive or not
     */
    void setIsAliveNext(bool isAliveNext) { nextUpdate.willBeAlive = isAliveNext; }

    /**
     * @brief Get function that returns if the cell should be alive next
     * iteration
     *
     * @details This flag is not used internally by class. Only by external
     * usage
     *
     * Test Recommendations
     * @test since this flag is not used internally when deciding the the
     * next iteration values set and get test should be enough
     *
     * @return bool is cell alive next iteration
     * @retval TRUE the cell should be alive next iteration
     * @retval FALSE the cell should not be alive next iteration
     */
    bool isAliveNext() { return nextUpdate.willBeAlive; }

    /**
     * @brief Get the action that should determinate the cell destiny for the
     * next iteration
     *
     * @details returns the action that is used internally to update the cell
     * when the updateState function is called
     *
     * @return @ref ACTION value
     */
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }

};

#endif
