/**
 * @file		SupportStructures.h
 * @author		Erik Ström
 * @date        October 2017
 * @version     0.1
 *
 * @brief Various supportive structures to be used throughout the application!
 *
 * @details This header holds support structures used in various functions and
 * classes within the application. As these support structures lack their own
 * behaviour, no tests will be performed on them in isolation, but in how they
 * are used in other objects.
 */

#ifndef GAMEOFLIFE_SUPPORTSTRUCTURES_H
#define GAMEOFLIFE_SUPPORTSTRUCTURES_H

/**
 * @brief Constitues a single Point in the simulated world.
 *
 * @details The Point structure handles x and y (column/row) coordinates in the
 * world of Game of life, and is used to map Cell objects to their positions.
 */
struct Point {
  int x, y;

  /// @brief Overloading operator < for comparing Point objects
  bool operator<(const Point& other) const {
    if (x == other.x) return y < other.y;
    return x < other.x;
  }
};

/*
 * @brief Data structure holding information about world dimensions in pixels.
 * @details Can be used to generate a Dimensions object holding width and height
 * to be used for the game world size
 */
struct Dimensions {
  int WIDTH, HEIGHT;
};

#endif  // GAMEOFLIFE_SUPPORTSTRUCTURES_H
