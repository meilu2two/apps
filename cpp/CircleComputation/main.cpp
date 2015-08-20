#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include "point.h"
#include "circle.h"

using namespace std;

int main()
{
    point a_p1( 1, 1 );
    circle a_c1( a_p1, 2 );
    circle a_c2( 3, 3, 4 );

    a_p1.printcoordinates();
    a_c1.printcoordinates();
    a_c2.printcoordinates();

    // output circle data by stream operator
    cout << a_c1 << a_c2;

    // stream circle data to a file
    int a_fileIndex( 0 );
    while( 3 > a_fileIndex ) {
        stringstream a_filename;
        a_filename << "logfile" << setw(5) << setfill('0') << a_fileIndex++ << ".txt";
        // ofstream a_outputFile;
        // a_outputFile.open( a_filename.str().c_str() );
        // if ( a_outputFile ) {
        //     a_outputFile << a_c1 << a_c2;
        //     a_outputFile.close();
        // }
        cout << a_filename.str() << endl;
    }

    return 0;
}
