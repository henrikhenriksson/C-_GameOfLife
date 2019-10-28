//
// Created by Johan on 2019-10-25.
//

#include <iostream>
#include "TestPoint.h"
#include "GoL_Rules/RuleOfExistence.h"

Directions TestPoint::toDirections() { return Directions{x, y}; }

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