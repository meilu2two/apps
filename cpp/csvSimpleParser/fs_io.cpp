#include "fs_io.h"
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

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
