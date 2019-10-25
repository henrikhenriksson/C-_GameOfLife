//
// Created by Johan on 2019-10-24.
//

#ifndef GAMEOFLIFE_TEST_TESTCLASSES_TESTPOINT_H_
#define GAMEOFLIFE_TEST_TESTCLASSES_TESTPOINT_H_

#include "Support/SupportStructures.h"


class TestPoint {
 public:
  int x;
  int y;

  TestPoint(int x, int y) : x(x), y(y) {};
  TestPoint(Directions d) : x(d.HORIZONTAL), y(d.VERTICAL) {};
  TestPoint(Point p) : x(p.x), y(p.y) {};
  TestPoint(TestPoint const &p): x(p.x), y(p.y){};

  Point toPoint();
  Directions toDirections();

  ///@todo Overload positions additions

  TestPoint& operator += (TestPoint const &obj) ;
  friend TestPoint operator + (TestPoint const &lhs, TestPoint const &rhs);

};


Point TestPoint::toPoint() { return Point{x, y}; }

Directions TestPoint::toDirections() { return Directions{x, y}; }

TestPoint&TestPoint::operator+=(TestPoint const &obj) {
    x += obj.x;
    y += obj.y;
    return *this;
}
TestPoint operator + (TestPoint const &lhs, TestPoint const &rhs) {
    TestPoint result(lhs);
    return (result+=rhs);
}

std::ostream& operator<<(std::ostream& out, const TestPoint& f)
{
    out << f.x << ":" << f.y;

    return out;
}

#endif //GAMEOFLIFE_TEST_TESTCLASSES_TESTPOINT_H_
