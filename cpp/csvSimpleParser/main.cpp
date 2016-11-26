#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

/// A data point
struct CenterPoint
{
    std::string m_name;
    int m_x;
    int m_y;
};

/// A header data definition
struct HeaderData
{
    std::string m_versionString;
    int m_major;
    int m_minor;
    std::string m_numberOfDataString;
    int m_numberOfDataItems;
};

/// get system date
std::string getDate( )
{
    std::stringstream a_date;
    a_date.str( std::string() );
    a_date.clear();

    time_t a_time;
    struct tm* a_localtime;

    // Get current time
    a_time=time(NULL);
    a_localtime = localtime( &a_time );

    a_date << a_localtime->tm_year + 1900;
    if( 10 > a_localtime->tm_mon + 1 )
    {
        a_date << "0";
    }
    a_date << a_localtime->tm_mon + 1;
    if( 10 > a_localtime->tm_mday )
    {
        a_date << "0";
    }

    a_date << a_localtime->tm_mday;
//    std::cout << "getDate integers: " << a_localtime->tm_year << "-" << a_localtime->tm_mon << "-" << a_localtime->tm_mday << std::endl;   // Debug output
//    std::cout << "getDate string: " << a_date.str() << std::endl;   // Debug output
    return a_date.str();
}

/// get system time
std::string getTime( )
{
    std::stringstream a_time;
    a_time.str( std::string() );
    a_time.clear();

    time_t a_timet;
    struct tm* a_localtime;

    // Get current time
    a_timet=time(NULL);
    a_localtime = localtime( &a_timet );

    if( 10 > a_localtime->tm_hour )
    {
        a_time << "0";
    }
    a_time << a_localtime->tm_hour;
    if( 10 > a_localtime->tm_min )
    {
        a_time << "0";
    }
    a_time << a_localtime->tm_min;
    if( 10 > a_localtime->tm_sec )
    {
        a_time << "0";
    }
    a_time << a_localtime->tm_sec;

    return a_time.str();
}

/// checks if directory is existent
bool isDirExistent( std::string t_folderName )
{
    bool r_state( false );
    DIR* a_pDir = NULL;
    a_pDir = opendir( t_folderName.c_str() );

    if( a_pDir != 0 ) {   // Folder existent
        // std::cout << "Open successfully folder: " << t_folderName.c_str() << std::endl;   // Debug output
        if( 0 == closedir( a_pDir ) ) {   // 0 ... closing successful, -1 ... closing failed
            r_state = true;
        }
    }
    else { // Folder doesn't exist
        r_state = false;
        // std::cout << "Opening folder: " << t_folderName.c_str() << " failed!" << std::endl;   // Debug output
    }

    return( r_state );
}

/// creates directory on file system
bool makeSubDir( std::string t_subFolderName )
{
    bool r_state( false );

    if( 0 == mkdir( t_subFolderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) ) {   // 0 ... make dir successful, -1 ... make dir failed
            r_state = true;
            // std::cout << "Create successfully subfolder: " << t_subFolderName.c_str() << std::endl;   // Debug output
        }
    else {
        r_state = false;
        std::cout << "Creating subfolder '" << t_subFolderName.c_str() << "' failed! (errno=" << errno << " -> " << strerror(errno) << ")" << std::endl;   // Debug output
    }

    return( r_state );
}


bool makeDir( std::string t_pathName )
{
    bool r_state( false );
    size_t a_prePos = 0, a_slashPos = 0;
    std::string a_subFolderName;

    // add trailing slash if missing, so we can use one loop
    if( t_pathName[ t_pathName.size() - 1 ] != '/' ){
        t_pathName += '/';
    }

    while( ( a_slashPos=t_pathName.find_first_of( '/', a_prePos ) ) != std::string::npos ){
        a_subFolderName = t_pathName.substr( 0, a_slashPos++ );   // get substring, increment to parse next time one character after slash position
        a_prePos = a_slashPos;   // store current position for next parse

        // if first character is '/', first time length is 0
        if( a_subFolderName.size() == 0 ) continue;

        // make subfolder
        r_state = makeSubDir( a_subFolderName );
    }

    return( r_state );
}

/// This function writes data to file
std::string writeFile( std::string t_foldername, std::string t_filename )
{
    std::stringstream r_filepath;
    r_filepath.str( std::string() );
    r_filepath.clear();
    r_filepath << t_foldername << t_filename;
    std::cout << "Path: " << r_filepath.str() << std::endl;

    bool a_dirExists( false );
    if( !isDirExistent( t_foldername ) ){
        a_dirExists = makeDir( t_foldername );
    }
    else {
        a_dirExists = true;
    }

    std::ofstream a_outputFile;
    if( a_dirExists )
    {
        a_outputFile.open( r_filepath.str().c_str(), std::ios_base::trunc );
    }

    if( !a_outputFile.is_open() )
    {
      std::cout << "Error at opening file: " << r_filepath.str() << std::endl;
    }
    else
    {
      int a_numberOfDataItems( 10 );

      // Write Header
      a_outputFile << "FileVersion=23.42" << std::endl;
      a_outputFile << "NumberOfDataItems=" << a_numberOfDataItems << std::endl;


      // Write Data
      std::vector< int > a_pointIndex( a_numberOfDataItems, 0 );
      std::vector< int >::iterator a_pointIndexIt = a_pointIndex.begin();
      for ( int a_i( 0 ); a_numberOfDataItems > a_i ; ++a_i )
      {
          *a_pointIndexIt = a_i;
          ++a_pointIndexIt;
      }

      a_pointIndexIt = a_pointIndex.begin();
      while( a_pointIndex.end() != a_pointIndexIt )
      {
         std::string a_separator( ";" );
         a_outputFile << *a_pointIndexIt << a_separator << 100 + *a_pointIndexIt << a_separator << 200 + *a_pointIndexIt << std::endl;

         ++a_pointIndexIt;
      }

      a_outputFile.close();
    }

    return r_filepath.str();
}

/// This function reads the Header from std::istream
std::istream& readHeader( std::istream& t_in, HeaderData& t_header )
{
    getline( t_in, t_header.m_versionString, '=');

    std::string a_major;
    getline( t_in, a_major, '.');
    t_header.m_major = atoi( a_major.c_str() );

    std::string a_minor;
    getline( t_in, a_minor, '\n');
    t_header.m_minor = atoi( a_minor.c_str() );

    getline( t_in, t_header.m_numberOfDataString, '=');

    std::string a_numberOfDataItems;
    getline( t_in, a_numberOfDataItems, '\n');
    t_header.m_numberOfDataItems = atoi( a_numberOfDataItems.c_str() );

    return t_in;
}

/// This function reads a point from std::istream
std::istream& readData( std::istream& t_in, CenterPoint& t_data )
{
    getline( t_in, t_data.m_name, ';');

    std::string a_x;
    getline( t_in, a_x, ';');
    t_data.m_x = atoi( a_x.c_str() );

    std::string a_y;
    getline( t_in, a_y, '\n');
    t_data.m_y = atoi( a_y.c_str() );

    return t_in;
}

/// This function reads data from file
void readFile( std::string t_filepath )
{
    std::ifstream a_csvread( t_filepath.c_str() );
    if(!a_csvread.is_open())
        std::cout << "Error at opening file: " << t_filepath << std::endl;
    else {
        // file is available

        // read file header
        HeaderData a_header;
        readHeader( a_csvread, a_header );
        std::cout <<  a_header.m_versionString << ": " << a_header.m_major << "." << a_header.m_minor << std::endl;
        std::cout <<  a_header.m_numberOfDataString << ": " << a_header.m_numberOfDataItems << std::endl;

        // read file data
        for( CenterPoint a_data; readData( a_csvread, a_data ); ) { // Nice for-loop
            std::cout <<  a_data.m_name << ", x=" << a_data.m_x << ", y=" << a_data.m_y << std::endl;
        }

        a_csvread.close();
    }
}

int main()
{
    std::stringstream a_foldername;
    a_foldername.str( std::string() );
    a_foldername.clear();
    a_foldername << "calibrationData" << "/" << getDate() << "_" << getTime() << "/";
    std::cout << "Folder: " << a_foldername.str() << std::endl;

    std::stringstream a_filename;
    a_filename.str( std::string() );
    a_filename.clear();
    a_filename << "pointsGen.csv";
    std::cout << "File: " << a_filename.str() << std::endl;

    std::string a_filepath = writeFile( a_foldername.str(), a_filename.str() );

    readFile( a_filepath );

    return 0;
}
