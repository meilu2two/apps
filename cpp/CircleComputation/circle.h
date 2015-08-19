#pragma once
#include "point.h"

class circle
{
    public:
        circle( point t_point, int t_radius );
        circle( int t_x, int t_y, int t_radius );
        void printcoordinates() const;

        point getCenter() const;
        int getRadius() const;


    private:
        point m_center;
        int m_radius;
};

// Definition of stream operator for class circle
std::ostream& operator<<( std::ostream& lvalue, circle const& rvalue);
