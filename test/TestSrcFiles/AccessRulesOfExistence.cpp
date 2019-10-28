//
// Created by Johan on 2019-10-28.
//

#include "AccessRulesOfExistence.h"



int AccessRulesOfExistence::countAliveNeighbours(Point center)
{
return RuleOfExistence::countAliveNeighbours(center);
}

ACTION AccessRulesOfExistence::getAction(int aliveNeighbours,
                 bool isAlive) {
    return RuleOfExistence::getAction(aliveNeighbours,
                                      isAlive);
}

PopulationLimits AccessRulesOfExistence::getPopulationLimits() { return
POPULATION_LIMITS; }


map<Point, Cell> &AccessRulesOfExistence::getCells() { return cells; }

vector<Directions> AccessRulesOfExistence::getDirections() { return
RuleOfExistence::DIRECTIONS; }