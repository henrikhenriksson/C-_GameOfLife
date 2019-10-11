/**
 * @file		Population.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 * @brief This class is a representation of the complete society of cell existence and interactions.
 *
 * @details The Population constitutes of all current, previous and future generations of cells, both living and dead
 * as well as those not yet born. By mapping all cells to their respective positions in the simulation world,
 * Population has the complete knowledge of each cell's whereabouts. Furthermore, the class is responsible for
 * determining which rules should be required from the RuleFactory, and store the pointer to these as members.
 *
 * Population's main responsibility during execution is determining which rule to apply for each new generation
 * and updating the cells to their new states.
 * 
 * @test The constructor and each public function in this class should be tested with a separate test function

*/

#ifndef POPULATION_H
#define POPULATION_H

#include<map>
#include<string>
#include "Cell.h"
#include "Support/Globals.h"
#include "GoL_Rules/RuleOfExistence.h"
#include "GoL_Rules/RuleFactory.h"

using namespace std;


class Population
{
private:
    int generation;
    map<Point, Cell> cells;
    RuleOfExistence* evenRuleOfExistence;
    RuleOfExistence* oddRuleOfExistence;

    void randomizeCellCulture();
	/// @brief Send cells map to FileLoader, which will populate its culture based on file values.
    void buildCellCultureFromFile();

public:
    /**
	* @brief Constructor for class population
	* @details always resets generation to 0, sets class object values to nullPtr
	* 
	* Test Recommendation:
	* @test no recommended tests at this point.
	*/
    Population() : generation(0), evenRuleOfExistence(nullptr), oddRuleOfExistence(nullptr) {}
    ~Population();

	/**
	* @brief initializes the cell culture and the concrete rules to be used in the sim.
	* @details determines wheter the cell culture should be randomized or built from file,
	* creates the rules to be used, based on a specified rule name. If no odd rule is specified
	* odd rule is set to even rule.
	* @param evenRuleName specifies rule name for evenRuleOfExistence
	* @param oddRuleName specifies rule name for oddRuleOfExistence
	* Recommended Tests:
	* @test if filename could be read, the correct function should be called.
	* @test if oddRuleName is set to evenRuleName if no odd rule name is specified,
	*/
    void initiatePopulation(const string& evenRuleName, string oddRuleName = "");
    
	
	int calculateNewGeneration();

    // Returns cell by specified key value.
    Cell& getCellAtPosition(Point position) { return cells.at(position); }

    // Gets the total amount of cells in the population, regardless of state.
    int getTotalCellPopulation() { return cells.size(); }

};

#endif