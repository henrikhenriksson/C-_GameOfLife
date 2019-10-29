/**
 * @file TestPoint.h
 * @author Johan Karlsson
 *
 * @brief This file contains the class TestPoint.
 */

#ifndef GAMEOFLIFE_TEST_TESTCLASSES_TESTPOINT_H_
#define GAMEOFLIFE_TEST_TESTCLASSES_TESTPOINT_H_

#include "Support/SupportStructures.h"
#include "GoL_Rules/RuleOfExistence.h"

/**
 * @brief This is a Extends the structs Point and Directions
 *
 * @details Since the program contains two separate structs Point and
 * Directions that simply fulfills the same functionality. But since there is
 * not short way of printing, adding or transform a struct to the other struct.
 * This class gives the extra functionality and can be extended further if
 * needed.
 * Finally the functionality has been given without modifying the program
 * components
 */
class TestPoint {
 public:
  int x;    ///< Store the col, horizontal direction
  int y;    ///< Store the row, vertical direction

  /**
  * @name FunctionGroup
  *
  * @brief  Constructor available for TestPoint
  *
  * @test That the correct x and y values is set
  */
///@{
/**
 * @details Sets the coodinate to [0,0]
 */
  TestPoint() : x(0), y(0) {};
  TestPoint(int x, int y) : x(x), y(y) {};
  explicit TestPoint(Directions d) : x(d.HORIZONTAL), y(d.VERTICAL) {};
  explicit TestPoint(Point p) : x(p.x), y(p.y) {};
  TestPoint(TestPoint const &p) : x(p.x), y(p.y) {};
///@}

/**
 * @brief Creates a Point instance with the x,y coordinates
 *
 * @test That a Point with the correct coordinates is created
 *
 * @return Point with the coordinates from the TestPoint
 */
  inline Point toPoint() { return Point{x, y}; }

  /**
   * @brief Creates a Direction instance from the data in the TestPoint
   *
   * @test That a Directions is created with the correct values
   *
   * @return Directions
   */
  inline Directions toDirections() { return Directions{x, y}; }

  /**
   * @brief Override the += operator to make it simpler to increase a TestPoint
   *
   * @test That only the lhs instance is added correctly
   *
   * @param obj other TestPoint to add
   * @return The updated objects
   */
  TestPoint &operator+=(TestPoint const &obj);

  /**
   * @brief Overload + operator to make is simpler to add 2 TestPoints
   *
   * @test Tha a new TestPoint is created with the correct data and that the
   * used point is unchanged
   *
   * @param lhs left hand side instance
   *
   * @param rhs right hand side instance
   *
   * @return A resulting instance
   */
  friend TestPoint operator+(TestPoint lhs, TestPoint const &rhs);

  /**
   * @brief Overloads the << operator to make it simpler send a point to a
   * stream
   * @details The TestPoint is represented in the format x,y
   *
   * @test That the output is in the format x,y
   *
   * @param out stream to add the instance to
   * @param f instance to send to the stream
   * @return stream instance
   */
  friend std::ostream &operator<<(std::ostream &out, const TestPoint &f);

  /**
   * @brief Overload == operator to make point and direction comparision easier
   * @details Compares point or direction data
   * @param lhs left hand size instance
   * @param rhs right hand size instance
   * @return bool, does instances point to the same point/directions
   */
  friend bool operator==(const TestPoint& lhs, const TestPoint& rhs);
};

#endif //GAMEOFLIFE_TEST_TESTCLASSES_TESTPOINT_H_
