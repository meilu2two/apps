#include <string>

/// checks if directory is existent
bool isDirExistent( std::string t_folderName );

/// creates subdirectory on file system
bool makeSubDir( std::string t_subFolderName );

/// creates directory tree on file system
bool makeDir( std::string t_pathName );
