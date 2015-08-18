#include <iostream>
#include "point.h"

point::point( int t_x, int t_y ): m_x( t_x ), m_y( t_y ) {}

void point::printcoordinates() {
    std::cout << "coordinates: x = " << m_x << ", y = " << m_y << std::endl;
}

int point::getX() { return m_x; };
int point::getY() { return m_y; };
