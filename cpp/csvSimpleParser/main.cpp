#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

// A Point
struct Point
{
    std::string m_name;
    int m_x;
    int m_y;
};

// A Version Definition
struct Version
{
    std::string m_version;
    int m_major;
    int m_minor;
};

/// This function reads a point from std::istream
std::istream& readData( std::istream& t_in, Point& t_p )
{
    getline( t_in, t_p.m_name, ';');

    std::string a_x;
    getline( t_in, a_x, ';');
    t_p.m_x = atoi( a_x.c_str() );

    std::string a_y;
    getline( t_in, a_y, '\n');
    t_p.m_y = atoi( a_y.c_str() );

    return t_in;
}

/// This function reads the Header from std::istream
std::istream& readHeader( std::istream& t_in, Version& t_v )
{
    getline( t_in, t_v.m_version, '=');

    std::string a_major;
    getline( t_in, a_major, '.');
    t_v.m_major = atoi( a_major.c_str() );

    std::string a_minor;
    getline( t_in, a_minor, '\n');
    t_v.m_minor = atoi( a_minor.c_str() );

    return t_in;
}

int main()
{
    std::string a_filename( "points.csv" );
    std::ifstream a_csvread( a_filename.c_str() );
    if(!a_csvread.is_open())
        std::cout << "Error at opening file: " << a_filename << std::endl;
    else {
        // file is available

        // read file header
        Version a_v;
        readHeader( a_csvread, a_v );
        std::cout <<  a_v.m_version << ": " << a_v.m_major << "." << a_v.m_minor << std::endl;

        // read file data
        for( Point a_p; readData( a_csvread, a_p ); ) { // Nice for-loop
            std::cout <<  a_p.m_name << ", x=" << a_p.m_x << ", y=" << a_p.m_y << std::endl;
        }

        a_csvread.close();
    }
    return 0;
}
