#pragma once

class point
{
    public:
        point( int t_x, int t_y );
        void printcoordinates() const;

        int getX() const;
        int getY() const;

    private:
        int m_x;
        int m_y;
};
