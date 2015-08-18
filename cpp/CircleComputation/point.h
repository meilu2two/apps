#pragma once

class point
{
    public:
        point( int t_x, int t_y );
        void printcoordinates();

        int getX();
        int getY();

    private:
        int m_x;
        int m_y;
};
