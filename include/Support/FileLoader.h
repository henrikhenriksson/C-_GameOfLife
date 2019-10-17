/**
 * @file		FileLoader.h
 * @author      Erik Ström
 * @date        July 2019
 * @version     0.2
 *
 *
 *
 * @brief this class handles the starting values for the simulation. Based on
 * the contents of specified file.
 *
 * @details Reads startup values from specified file, containing values for
 * WORLD_DIMENSIONS and cell population. Will then create the corresponding
 * cells.
 */

#ifndef FileLoaderH
#define FileLoaderH

#include <map>
#include "Cell_Culture/Cell.h"
#include "Globals.h"

using namespace std;

/*
Determines starting values for simulation, based on contents of specified file.

Reads startup values from specified file, containing values for WORLD_DIMENSIONS
and cell Population. Will create the corresponding cells.
*/
class FileLoader {
 public:
  /**
   * @brief default constructor
   * @details default class constructor, taking no arguments or parameters.
   * @test No tests recommended.
   */
  FileLoader() = default;

  /***
   * @brief load given cell map from file..
   * @details Loads the given map with cells that is read from the file, pointed
   * to by the global variable "fileName", opens the file for reading, reads and
   * loads the read dimension from file and creates the world
   * @param map cells containing Point and Cell objects.
   * @test to make sure the function throws an ios_base::failure exception
   * @test that the file reads the correct dimensions from the file.
   * @test to make sure the function calculates the correct amount of rows and
   * colums compared to world size.
   */
  void loadPopulationFromFile(map<Point, Cell>& cells);
};

#endif
