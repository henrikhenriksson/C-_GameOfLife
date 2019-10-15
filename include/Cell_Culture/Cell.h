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

/**
 * @brief Available Cell actions
 * @bug IGNORE_CELL is a missleading name, KEEP_STATE would more correctly
 * describe actions taken by program
 */

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
     *
     * @test Test that rimCell status can be set for a created Cell
     *
     * @param isRimCell Sets if the current cell is a rim cell or not
     * @param action What is the initial state of the cell
     */
    explicit Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    /**
     * @brief Returns if the cell is alive or not
     *
     * @details A cell is vied as alive if the cell is not a rim cell or if
     * the cell has a age => 0
     *
     * Test Recommendations
     * @test Validate that rim cells is not alive after the status
     * GIVE_CELL_LIFE
     * @test Validate that non rim cells get status alive after given life
     * and stays alive when aging. Finaly that isAlive return false when the
     * cell has been killed.
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
     * @test Test that all actions can be set for a non rim cell and that
     * GIVE_CELL_LIFE is ignored for alive cells.
     *
     * @test Test that setNextGenerationAction is ignored by rim cells
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
     * @test Check that an cell is updated according to the action set. All
     * defined Actions is tested for cell states:  Alive, Dead and rim cells.
     *
     * @bug DO_NOTHING updates cell color and value. This is not indicated
     * from the state name.
     */
    void updateState();

    /**
     * @brief Get function for the current cell age (nr iterations)
     *
     * @test Test that getAge() increased when alive and set to 0 when killed
     *
     * @return int cell age, nr iterations
     * @retval 0 for dead cells
     * @retval 1.. nr of iterations the cell has been alive
     */
    int getAge() { return details.age; }

    /**
    * @brief Get function for the current cell color
    *
    * @test Test that getColor() returns the color that has been set with
    * setNextGenerationAction(), after one simulated iteration has passed
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
     * @test Test that the correct status is returned for rim cells and non
      * rim cells. Set value given by constructor.
     *
     * @return bool if the cell is a rim cell
     * @retval TRUE the cell is a rim cell
     * @retval FALSE the cell is not a rim cell
     */
    bool isRimCell() { return details.rimCell; }

    /**
     * @brief Set function for the next iteration color
     *
     * @test Set next iteration color and read that the color has been set
     * @test Set an color index that is not defined in COLOR class values
     *
     * @bug Function are not detecting if an undefined color is set.
     * Investigate expected behavior and update test.
     *
     * @param nextColor color to be used the next iteration
     */
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }

    /**
     * @brief Get function for the character that should represent the cell
     *
     * @details The current character used to represent the cell can be
     * changed to
     * distinguish the cell when shown
     *
     * @test Test that the value set in setNextCellValue is returned by
     * getCellValue() after an simulated iteration has passed.
     *
     * @return char cell representation char
     */
    char getCellValue() { return details.value; }

    /**
     * @brief Set function for the cell next iteration value
     *
     * @test Test that the value set with setNextCellValue is returned with
     * getCellValue() after an simulated iteration has passed
     *
     * @test Test that invalid cell values as escape character such as tab
     * (\\t) or new line(\\n) is ignored.
     *
     * @bug It should not be possible to set format breaking cell values such
     * as tab(\\t) or new line (\\n). Investigate correct behavior and update
     * test cases
     *
     * @param value value to be used for next iteration value
     */
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    /**
     * @brief Set the is alive flag for the next iteration.
     *
     * @details Not used internally by this class and
     *
     * @test Test that the value set by setIsAliveNext is returned by
     * getIsAliveNext()
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
     * @test Test that the value set by setIsAliveNext is returned by
     * getIsAliveNext()
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
     * @details Returns the action that is used internally to update the cell
     * when the updateState function is called
     *
     * @test Test that all actions can be set and for an alive cell
     * GIVE_CELL_LIFE is ignored
     *
     *
     * @return @ref ACTION value
     */
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }

};

#endif
