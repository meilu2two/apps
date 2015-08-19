#include <iostream>
#include "point.h"
#include "circle.h"

using namespace std;

int main()
{
    point p1( 1, 1 );
    circle c1( p1, 2 );
    circle c2( 3, 3, 4 );

    p1.printcoordinates();
    c1.printcoordinates();
    c2.printcoordinates();

    // output circle data by stream operator
    cout << c1 << c2;

    return 0;
}
