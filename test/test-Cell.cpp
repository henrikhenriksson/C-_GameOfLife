/**
 * @file test-Cell.cpp
 *
 * @author Johan Karlsson, joka1806
 *
 * @breif This file contains test cases to test the class Cell
 *
 * @details Some Cell funcitons is tested in multiple tests. This since
 * complex test uses the functionality that is already tested in simpler test.
 * But also that simple/function specific test is wanted to make location of
 * bugs easier.
 */

#include <Cell_Culture/Cell.h>
#include <string>
#include "catch.hpp"
#include "CellTester.hpp"

/**
 * @brief tests set and get for isAliveNextGen
 *
 * @details since isAliveNextGen is separated from other functions in class
 * these two functions can be tested separate
 */
SCENARIO("set and get isAliveNextGen")
{
    Cell testCell;
    GIVEN("A Cell from default constructor")
    {
        //Test default value
        THEN("isAliveNextGen should return false as default")
        {
            REQUIRE(testCell.isAliveNext() == false);
        }
        //Set value to true and check result
        WHEN("setIsAliveNextGen(true) is called")
        {
            testCell.setIsAliveNext(true);
            THEN("isAliveNext should return true")
            {
                REQUIRE(testCell.isAliveNext() == true);
            }
        }
        //Set value back to false and check resutl
        AND_WHEN("setIsAliveNextGen(false) is called")
        {
            testCell.setIsAliveNext(false);
            THEN("isAliveNext should return false")
            {
                REQUIRE(testCell.isAliveNext() == false);
            }
        }
    }
}

/**
 * @brief test that isRimCell can be set with the constructor
 *
 * @details These test focus on the values that can be set from the
 * constructor.
 * Only test isRimCell from constructor values since action is set
 * to DO_NOTHING and then cant be tested.
 *
 */
SCENARIO("Check that constructor can set rimCell and ACTION")
{
    //Test constructor values for a rim cell
    testSetConstructorValues(true);

    //Test constructor values for a non rim cell
    testSetConstructorValues(false);
}

/**
 * @brief Test the values returned from getAge()
 *
 * @details Test that getAge returns an increasing age for a cell when
 * GIVE_CELL_LIFE is set from constructor and IGNORE_CELL is set for the
 * first iteration
 *
 * @Toto check that IGNORE_CELL is the value that should be set when a cell
 * survives an iteration
 */
SCENARIO("Create a cell and validate that the cell ages")
{
    GIVEN("A new born cell that is not a rim cell")
    {
        //Create a non rim cell for test that is living from start
        Cell testCell(false, GIVE_CELL_LIFE);
        THEN("Start age should be 1")
        {
            //Make sure that the cell is not a rim cell
            CHECK(testCell.isRimCell() == false);

            //Check that the cell has the age 1 from start
            REQUIRE(testCell.getAge() == 1);
        }
        WHEN("an iteration is executed, updateState is called")
        {
            //set IGNORE_CELL to increment age
            testCell.setNextGenerationAction(IGNORE_CELL);

            //call updateState to simulate a itteration
            testCell.updateState();

            //Test that the age has increased
            THEN("The cell should have aged, getAge should return 2")
            {
                REQUIRE(testCell.getAge() == 2);
            }
        }
        //Test that the age is reset when the cell is killed
        AND_WHEN("The cell is killed")
        {
            testCell.setNextGenerationAction(KILL_CELL);
            testCell.updateState();
            THEN("Age should be back to 0")
            {
                REQUIRE(testCell.getAge() == 0);
            }
        }
    }
    //Test that an rim cell does not age
    AND_GIVEN("A new born RIM cell that is not a rim cell")
    {
        //Create a rim cell that should be alive
        Cell testCell(true, GIVE_CELL_LIFE);
        THEN("Start age should be 0")
        {
            //Validate that the cell is a rimCell
            CHECK(testCell.isRimCell() == true);

            //Validate that the cell has not aged
            REQUIRE(testCell.getAge() == 0);
        }
        //simulate one itteration and make sure the cell has nog aged
        WHEN("an iteration is executed, updateState is called")
        {
            //set IGNORE_CELL to increment age, state that keeps alive cells
            // alive
            testCell.setNextGenerationAction(IGNORE_CELL);

            //simulate iteration
            testCell.updateState();

            //Validate that the cell still has not aged
            THEN("The cell should have aged, getAge should return 2")
            {
                REQUIRE(testCell.getAge() == 0);
            }
        }
        //Validate that the age is not affected by being killed
        AND_WHEN("The cell is killed")
        {
            testCell.setNextGenerationAction(KILL_CELL);
            testCell.updateState();
            THEN("Age should still be 0")
            {
                REQUIRE(testCell.getAge() == 0);
            }
        }
    }
}

/**
 * @brief Tests that the correct color is returned by getColor()
 *
 * @details Uses setNextGenColor() and updateState() to validate that the
 * correct color is stored.
 */
SCENARIO("Create a cell and validate that the color can be changed")
{
    GIVEN("Any cell")
    {
        //Defin colors to test
        const COLOR TEST_COLORS[] = {STATE_COLORS.DEAD, STATE_COLORS.ELDER,
                             STATE_COLORS.LIVING, STATE_COLORS.OLD};

        Cell testCell;

        //Test all colors
        for (auto expColor : TEST_COLORS)
        {
            //@todo use color name instead of index
            WHEN("Color is set to: " + std::to_string((int)expColor)
            + " and updateState is called")
            {
                //Set next color
                testCell.setNextColor(expColor);

                //Color is updated for all actions, dont update to make sure
                // nothing changes
                testCell.setNextGenerationAction(DO_NOTHING);

                //Call updateState to set the nextColor to color
                testCell.updateState();

                //Check result
                THEN("getColor should return " + std::to_string((int)expColor) )
                {
                    REQUIRE(testCell.getColor() == expColor);
                }
            }
        }
    }
}

/**
 * @brief Test that an incorect color cant be set
 *
 * @details Tries to set an COLOR index out of bound, undefined.
 * This should be detected and ignored
 *
 * @todo test with program what happends in terminal when an undefined color
 * is used and update test cases with lession learned
 */
SCENARIO("Trie to set an non defined color for a cell")
{
    GIVEN("A default cell")
    {
        Cell testCell;
        COLOR expColor;
        expColor = COLOR(8);
        testCell.setNextColor(expColor);
        WHEN("An undefined color is set and an simulated iteration has passed")
        {
            testCell.updateState();
            THEN("The set color should be ignored")
            {
                REQUIRE(testCell.getColor() != expColor);
            }
        }
    }
}

/**
 * @brief tests that a correct value is returned by getValue()
 *
 * @details tests that valid characters can be set and is returned by getValue()
 * setNextCellValue() and updateState() is used to set values
 */
SCENARIO("getValue should return the value set by setNextCellValue after "
         "updateState is called")
{
    GIVEN("A valid cell")
    {
        //Create a default test cell
        Cell testCell;

        //Test with all english lowercase letters
        for(char expChar = 'a'; expChar <= 'z'; ++expChar)
        {
            //Define when header for WHEN label
            std::stringstream header;
            header << "setNexCellValue is set to: " << expChar;

            WHEN(header.str())
            {
                //Update value
                testCell.setNextCellValue(expChar);
                testCell.updateState();

                //Create THEN header
                header.clear();
                header << "getValue should return: " << expChar;

                //Check that the cell value has been updated
                THEN(header.str())
                {
                    REQUIRE(testCell.getCellValue() == expChar);
                }
            }
        }
    }
}

/**
 * @brief Test that some invalid character cant be set.
 *
 * @details characters such as new line or tab is not suited and should be
 * limited
 *
 * @todo Add system test that test if such invalid values as new line could
 * destory intended layout of game board. Also check if this should be tested
 * elsvere
 */
SCENARIO("Test that invalid escape character can't be used as cell value")
{
    GIVEN("A valid cell")
    {
        Cell testCell;
        WHEN("A newline is set as setNexCellValue")
        {
            //Trie to set invalid value
            testCell.setNextCellValue('\n');
            testCell.updateState();

            //Check that the value is not used
            THEN("The getValue should not return new line char(\\n)")
            {
                REQUIRE(testCell.getCellValue() != '\n');
            }
        }
    }
}

/**
 * @brief Test that isAlive() returns correct values
 *
 * @details Test that isAlive returns true for alive cells, age > 0.
 * Rim cells are not allowed to be alive and is also tested
 * updateState() and setNextStateAction() is used to manipulate age.
 */
SCENARIO("Check the alive status of a cell")
{
    //Test that a non rim cell is aging
    GIVEN("A non rim cell")
    {
        testCellIsAlive(false);
    }
    //Test that a rim cell is not aging
    AND_GIVEN("A rim cell")
    {
        testCellIsAlive(true);
    }
}

/**
 * @brief Test that updateState() performes the correct actions on a cell for
 * the the deffined actions
 *
 * @details Test the correct actions, for defined actions, is taken on the
 * different cell states. Tested cell states Alive, Dead and for rimCells
 * Tested actions
 */
SCENARIO("Test that the correct actions is taken for defined ACTIONS")
{
    GIVEN("An alive cell")
    {
        //Create an alive non rim cell
        Cell testCell;
        testCell.setNextGenerationAction(GIVE_CELL_LIFE);
        testCell.updateState();

        //Test start conditions
        testCellState(testCell, 1, true, '#', STATE_COLORS.DEAD);

        //Test that the action KILL_CELL
        WHEN("The cell next generation action is set to KILL_CELL")
        {
            char expVal = 'a';  //value to test
            COLOR  expColor = STATE_COLORS.OLD; //color to test

            //Set test values
            testCell.setNextGenerationAction(KILL_CELL);
            testCell.setNextCellValue(expVal);
            testCell.setNextColor(expColor);

            //Simulate iteration
            testCell.updateState();

            //Test that the expected values are updated
            testCellState(testCell, 0, false, expVal, expColor);

        }

        //Test the action IGNORE_CELL
        WHEN("The cell next generation action is set to IGNORE_CELL")
        {
            //Age cell
            testCell.setNextGenerationAction(IGNORE_CELL);
            testCell.updateState();

            //Test that the cell is still alive and has aged by one
            testCellState(testCell, 2, true);
        }

        //Test that the action GIVE_CELL_LIFE sets the new born status
        WHEN("The cell next generation action is set to GIVE_LIFE")
        {
            testCell.setNextGenerationAction(GIVE_CELL_LIFE);
            testCell.updateState();
            THEN("The cell should not change this iteration")
            {
                testCellState(testCell, 1, true);
            }

            //testCellState(testCell, 1, true);
        }
        WHEN("The cell next generation action is set to DO_NOTHING")
        {
            //Test that do nothing does not change values as expected
            //Define test data
            char testVal = 'g';
            char expVal = '#';
            COLOR  expColor = STATE_COLORS.DEAD;
            COLOR testColor = STATE_COLORS.ELDER;

            //Set test data
            testCell.setNextGenerationAction(DO_NOTHING);
            testCell.setNextCellValue(testVal);
            testCell.setNextColor(testColor);
            testCell.updateState();

            //Test cell status
            testCellState(testCell, 1, true, expVal, STATE_COLORS.DEAD);
        }
    }
    GIVEN("An dead cell")
    {
        //Create a dead cell
        Cell testCell;
        testCellState(testCell, 0, false, '#', STATE_COLORS.DEAD);

        WHEN("The cell next generation action is set to KILL_CELL")
        {
            //Define test data
            char expVal = 'a';
            COLOR  expColor = STATE_COLORS.OLD;

            //Set test data
            testCell.setNextGenerationAction(KILL_CELL);
            testCell.setNextCellValue(expVal);
            testCell.setNextColor(expColor);
            testCell.updateState();

            //Test cell values
            testCellState(testCell, 0, false, expVal, expColor);

        }
        WHEN("The cell next generation action is set to IGNORE_CELL")
        {
            //Test that the cell ages

            //Age cell
            testCell.setNextGenerationAction(IGNORE_CELL);
            testCell.updateState();

            //Test cell values
            testCellState(testCell, 0, false);
        }
        WHEN("The cell next generation action is set to GIVE_LIFE")
        {
            //Increment age to 2 to see if the cell is reset when GIVE_CELL_LIFE
            //is tested
            testCell.setNextGenerationAction(IGNORE_CELL);
            testCell.updateState();

            //This should not be able to set for an alive cell
            testCell.setNextGenerationAction(GIVE_CELL_LIFE);
            testCell.updateState();

            //Test if the cell has been reset to a newborn cell
            testCellState(testCell, 1, true);
        }
        WHEN("The cell next generation action is set to DO_NOTHING")
        {
            //Test that do nothing does not change values as expected

            //Define test data
            char testVal = 'g';
            char expVal = '#';
            COLOR  expColor = STATE_COLORS.DEAD;
            COLOR testColor = STATE_COLORS.ELDER;

            //Set test data
            testCell.setNextGenerationAction(DO_NOTHING);
            testCell.setNextCellValue(testVal);
            testCell.setNextColor(testColor);
            testCell.updateState();

            //Test cell values
            testCellState(testCell, 0, false, expVal, STATE_COLORS.DEAD);
        }
    }
    GIVEN("An rim cell")
    {
        //Create a rim test cell
        Cell testCell(true);
        testCellState(testCell, 0, false, '#', STATE_COLORS.DEAD);

        WHEN("The cell next generation action is set to KILL_CELL")
        {
            //Define test data
            char expVal = 'a';
            COLOR  expColor = STATE_COLORS.OLD;

            //Set test data
            testCell.setNextGenerationAction(KILL_CELL);
            testCell.setNextCellValue(expVal);
            testCell.setNextColor(expColor);
            testCell.updateState();

            //test cell values
            testCellState(testCell, 0, false, expVal, expColor);

        }
        WHEN("The cell next generation action is set to IGNORE_CELL")
        {
            //Test that the rim cell does not age
            testCell.setNextGenerationAction(IGNORE_CELL);
            testCell.updateState();

            //Test cell values
            testCellState(testCell, 0, false);
        }
        WHEN("The cell next generation action is set to GIVE_LIFE")
        {
            //Give the cell a chance to increment the age again
            testCell.setNextGenerationAction(IGNORE_CELL);
            testCell.updateState();

            //A rim cell should not be affected by GIVE_CELL_LIFE
            testCell.setNextGenerationAction(GIVE_CELL_LIFE);
            testCell.updateState();

            //test that the cell still is not alive
            testCellState(testCell, 0, false);
        }
        WHEN("The cell next generation action is set to DO_NOTHING")
        {
            //Test that do nothing does not change values as expected

            //Define test data
            char testVal = 'g';
            char expVal = '#';
            COLOR  expColor = STATE_COLORS.DEAD;
            COLOR testColor = STATE_COLORS.ELDER;

            //Set test data
            testCell.setNextGenerationAction(DO_NOTHING);
            testCell.setNextCellValue(testVal);
            testCell.setNextColor(testColor);
            testCell.updateState();

            //Test that the rim cell is not affected
            testCellState(testCell, 0, false, expVal, STATE_COLORS.DEAD);
        }
    }
}

/**
 * @brief Test that setNextGenerationActions sets the correct value
 *
 * @details Test all start Action and simulates one iteration
 * For all start Actions all Actions is set and tested that the correct
 * action is returned.
 * For alive cells GIVE_CELL_LIFE should be ignored
 */
SCENARIO("Test possible nextGenarationAction changes")
{
    ACTION TEST_ACTIONS[] =
            { GIVE_CELL_LIFE, IGNORE_CELL, KILL_CELL, DO_NOTHING };
    Cell testCell;
    for(auto startAction: TEST_ACTIONS)
    {
        testCell.setNextGenerationAction(startAction);
        GIVEN("A non rim cell of state: " + actionToString(startAction))
        {

            //Check that the start action is set
            THEN("getNextGenAction() should return the start state: "
                 + actionToString(startAction));
            {
                REQUIRE(testCell.getNextGenerationAction() == startAction);
            }

            //Simulate one iteration
            testCell.updateState();
            AND_WHEN("A simulated iteration has passed")
            {
                //Test to set all actions
                for(auto nextAction: TEST_ACTIONS)
                {

                    AND_WHEN("nextGenerationAction is set to: "
                                 + actionToString(nextAction))
                    {
                        //Set tested action
                        testCell.setNextGenerationAction(nextAction);

                        //When an alive cell is set to give live the set
                        // command should be ignored,
                        if((nextAction == GIVE_CELL_LIFE)
                            && (testCell.isAlive()) )
                        {
                            //test for DO_NOTHING, set in updateState
                            nextAction = DO_NOTHING;
                        }

                        THEN("getNextGeneration() should return: "
                             + actionToString(nextAction))
                        {
                            REQUIRE(testCell.getNextGenerationAction()
                                    == nextAction);
                        }
                    }
                }
            }

        }
    }
}

/**
 * @brief Test that setNextGenerationAction does not affect rim cells
 */
 SCENARIO("Test that setNextGenerationAction does not affects rim cells")
{
    ACTION TEST_ACTIONS[] =
            { GIVE_CELL_LIFE, IGNORE_CELL, KILL_CELL, DO_NOTHING };
    GIVEN("A Rim cell")
    {
         //Define a rim cell as test cell
        Cell testCell(true);
        for(auto setAction : TEST_ACTIONS)
        {
            WHEN(actionToString(setAction) + "is set with setNextGenerationAction")
            {
                testCell.setNextGenerationAction(setAction);
                THEN("getNextAction should return DO_NOTHING")
                {
                    REQUIRE(testCell.getNextGenerationAction() == DO_NOTHING);
                }
            }
        }
    }
}
