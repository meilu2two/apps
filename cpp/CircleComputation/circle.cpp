#include <iostream>
#include "circle.h"

circle::circle( point t_point, int t_radius ): m_center( t_point ), m_radius ( t_radius )
{
}
circle::circle( int t_x, int t_y, int t_radius ): m_center( t_x, t_y ), m_radius ( t_radius )
{
}

void circle::printcoordinates() const {
    std::cout << "coordinates: M(" << m_center.getX() << "/" << m_center.getY() << "), radius = " << m_radius << std::endl;
}

point circle::getCenter() const { return m_center; }
int circle::getRadius() const { return m_radius; }

// better version of method circle::printcoordinates()
std::ostream& operator<<( std::ostream& lvalue, circle const& rvalue)
{
    return ( lvalue << "coordinates: M(" << rvalue.getCenter().getX()
                    << "/" << rvalue.getCenter().getY()
                    << "), radius = " << rvalue.getRadius()
                    << std::endl );
}
