//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: filesys.hpp,v 1.5 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_UTIL_FILESYS_FILESYS_HPP
#define PHOTON_UTIL_FILESYS_FILESYS_HPP

#include "exceptions.hpp"

#include "physfs.h"

#include <string>
#include <vector>

// Title: filesys::
//  The util::filesys:: namespace is a group of functions all related to dealing
//  with the filesystem.  Photon uses PhysFS (http://physfs.icculus.org) to
//  provide this functionality.  
//
// The Search Path:
//  The search path is an important concept in Photon, due to the nature of 
//  PhysFS when a file is referenced Photon attempts to resolve it by checking
//  for it within the search path.  By default the search path only includes
//  the directory where the application resides.  Nothing which is not within
//  this directory or a directory within it can be accessed. 
//
//  It is possible to add other directories to the search path using 
//  <addToSearchPath>.  Keep in mind that the search path is a list of 
//  directories which will be searched in order for any requested files.
//  In other words if you wish to store your game media in a format like:
// | game/
// |      bin/
// |      images/
// |      audio/
// |      user-audio/
// |
//
//  You will need to add images/ and audio/ to the search path since they 
//  do not reside within bin (where the game is stored).  Also assuming 
//  users are allowed to place custom audio files within user-audio/ you must
//  also add it to the path.  If you wish for files within it to override 
//  existing audio files, it should preceed audio/ in the search path, otherwise
//  it should come be placed in the search path after audio/.

namespace photon
{
namespace util
{
namespace filesys
{

// Group: System Directories ///////////////////////////////////////////////////

// Function: getCDDirs
//  Gets a listing of the CD directories on a system (not supported on all
//  systems)  On Windows it would return something like D:/ or E:/, whereas on
//  Linux it would return something like /media/cdrom0.
//
// Returns:
//  A vector of strings containing the path to the CD directories.
std::vector<std::string> getCDDirs();

// Function: getBaseDir
//  Get the path of the directory that the application is running in.
//
// Returns:
//  Path to directory that application is running from.
std::string getBaseDir();

// Function: getUserDir
//  Get the path of the directory that the OS specifies for the user's home. 
//  On Windows would resemble C:/Documents and Settings/User, on Linux something
//  like /home/user/
//
// Returns:
//  Path to user's home directory.
std::string getUserDir();

// Group: Search Path //////////////////////////////////////////////////////////

// Function: addToSearchPath
//  Attempts to add a directory to the search path.
//
// Parameters:
//  dir - Directory to add to the search path
//  append - optional: if true, directory will be added to end of path (default)
//           if false, directory will be added to front of path
//
// See Also:
//  <removeFromSearchPath>
//  <getSearchPath>
void addToSearchPath(const std::string& dir, bool append=true);

// Function: removeFromSearchPath
//  Removes a directory from the search path, if it exists on the path.
//
// Parameters:
//  dir - Directory to remove from the search path. Ignored if nonexistant.
//
// See Also:
//  <addToSearchPath>
//  <getSearchPath>
void removeFromSearchPath(const std::string& dir);

// Function: getSearchPath
//  Obtain the currently configured search path.
//
// Returns:
//  List of strings in search path.
//
// See Also:
//  <addToSearchPath>
//  <removeFromSearchPath>
std::vector<std::string> getSearchPath();

// Group: Manipulation /////////////////////////////////////////////////////////

// Function: setWriteDir
//  Sets the writing directory, used by <mkdir> and <remove>.  Unlike search 
//  path only one writable directory can be set at once.
//
// Parameters:
//  dir - Directory to make writeable
//
// See Also:
//  <getWriteDir>
void setWriteDir(const std::string& dir);

// Function: getWriteDir
//  Gets the writing directory.
//
// Returns:
//  Writable directory, if set.
//
// See Also:
//  <setWriteDir>
std::string getWriteDir();

// Function: mkdir
//  Attempts to create a directory.
//
// Parameters:
//  dir - name of directory to create
//
// Returns:
//  true iff directory was created, false if not
bool mkdir(const std::string& dir);

// Function: remove
//  Attempts to remove a file or directory.
//
// Parameters:
//  remove - name of file or directory to remove
//
// Returns:
//  true iff file/directory was removed, false if not
bool remove(const std::string& item);

// Group: Searching ////////////////////////////////////////////////////////////

// Function: listDir
//  Lists the contents of a directory.
//
// Parameters:
//  dir - name of directory to get contents of
//
// Returns:
//  list of strings representing items found in 'dir'
std::vector<std::string> listDir(const std::string& dir);

// Function: exists
//  Checks if a file/directory exists.
//
// Parameters:
//  item - file/directory to check existance of
//
// Returns:
//  true iff file/directory exists, false if not
bool exists(const std::string& item);

// Function: isDir
//  Checks if a name refers to a directory.
//
// Parameters:
//  item - name to check
//
// Returns:
//  true iff item is a directory, false if not
bool isDir(const std::string& item);

// Function: isSymbolicLink
//  Checks if a name refers to a symbolic link.
//
// Parameters:
//  item - name to check
//
// Returns:
//  true iff item is a symbolic link, false if not
bool isSymbolicLink(const std::string& item);

// Group: Other ////////////////////////////////////////////////////////////////

// Function: getDirSeparator
//  Gets the system standard directory separator.
//  (/ on unix, \\ on windows, : on MacOS)
//
// Returns:
//  System directory separator.
std::string getDirSeparator();

// Function: permitSymbolicLinks
//  Enables or disables symbolic linking. (which is off by default)
//
// Parameters:
//  allow - true if you wish to enable linking, false if you wish to disable it
void permitSymbolicLinks(bool allow);

// Function: getModTime
//  Gets last modification time for a file.
//
// Parameters:
//  item - name of item to get last modification time of
//
// Returns:
//  Last modification time of a file in seconds since the epoch.
PHYSFS_sint64 getModTime(const std::string& item);

}
}
}

#endif  //PHOTON_UTIL_FILESYS_FILESYS_HPP
