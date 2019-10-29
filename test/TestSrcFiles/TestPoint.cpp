//
// Author Johan Karlsson, joka1806
// Implementations of class functions for TestPoint
// Doxygen comments not added for .cpp files
//

#include "TestPoint.h"

TestPoint &TestPoint::operator+=(TestPoint const &obj) {
    x += obj.x;
    y += obj.y;
    return *this;
}

TestPoint operator+(TestPoint lhs, TestPoint const &rhs) {
    lhs += rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &out, const TestPoint &f) {
    out << f.x << "," << f.y;

    return out;
}

bool operator==(const TestPoint& lhs, const TestPoint& rhs)
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}