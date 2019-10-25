/*
 * @file	    Globals.h
 * @author      Erik Ström
 * @date        October 2017
 * @version     0.1
 *
 * @brief this header file contains global data members used throughout the
 * simulation.
 * @details certain data structures might need to be accessed globally. These
 * should preferably be const declared
 * @issue This file contains global variables that can be accessed and changed
 * by any class in the solution. Global variables should be avoided, and a
 * better solution would be to add these structures as private members of
 * classes that uses them with relevant set and get functions.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include "SupportStructures.h"

using namespace std;

/// @brief The actual width and height of the used world
extern Dimensions WORLD_DIMENSIONS;

// @brief Name of file to read
extern string fileName;

#endif
