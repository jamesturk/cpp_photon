//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: filesys.cpp,v 1.2 2005/02/07 01:48:51 cozman Exp $
//
// Revisions:
//  $Log: filesys.cpp,v $
//  Revision 1.2  2005/02/07 01:48:51  cozman
//  fixed several issues in testing
//
//  Revision 1.1  2005/02/06 21:30:10  cozman
//  PhysFS initial integration
//
//


#include "util/filesys/filesys.h"

namespace photon
{
namespace util
{
namespace filesys
{

std::vector<std::string> getCDDirs()
{
    std::vector<std::string> dirs;
    char** buf( PHYSFS_getCdRomDirs() );

    if(buf == 0)
    {
        throw APIError(std::string("getCDDirs failed (") +
                        PHYSFS_getLastError() + ")");
    }

    //iterate over list, adding dirs
    for(char** i(buf); *i != 0; ++i)
    {
        dirs.push_back(*i);
    }

    PHYSFS_freeList(buf);   //free the memory

    return dirs;
}

std::string getBaseDir()
{
    return PHYSFS_getBaseDir();
}

std::string getUserDir()
{
    return PHYSFS_getUserDir();
}

void addToSearchPath(const std::string& dir, bool append)
{
    int success = PHYSFS_addToSearchPath(dir.c_str(), append);
    if(!success)
    {
        throw APIError(std::string("addToSearchPath failed (") +
                        PHYSFS_getLastError() + ")");
    }
}

void removeFromSearchPath(const std::string& dir)
{
    //ignore return value (useless)
    PHYSFS_removeFromSearchPath(dir.c_str());
}

std::vector<std::string> getSearchPath()
{
    std::vector<std::string> dirs;
    char** buf( PHYSFS_getSearchPath() );

    if(buf == 0)
    {
        throw APIError(std::string("getSearchPath failed (") +
                        PHYSFS_getLastError() + ")");
    }

    //iterate over list, adding dirs
    for(char** i(buf); *i != 0; ++i)
    {
        dirs.push_back(*i);
    }

    PHYSFS_freeList(buf);   //free the memory

    return dirs;
}

void setWriteDir(const std::string& dir)
{
    //set write dir to either NULL (disabled) or the directory passed in
    if(PHYSFS_setWriteDir( dir.empty() ? 0 : dir.c_str() ) == 0)
    {
        throw APIError(std::string("setWriteDir failed (") +
                        PHYSFS_getLastError() + ")");
    }
}

std::string getWriteDir()
{
    const char* dir = PHYSFS_getWriteDir();
    
    //return name of directory or empty string if dir is null
    return dir != 0 ? dir : std::string();
}

bool mkdir(const std::string& dir)
{
    return PHYSFS_mkdir(dir.c_str()) != 0;
}

bool remove(const std::string& item)
{
    return PHYSFS_delete(item.c_str()) != 0;
}

std::vector<std::string> listDir(const std::string& dir)
{
    std::vector<std::string> files;
    char** buf( PHYSFS_enumerateFiles(dir.c_str()) );

    if(buf == 0)
    {
        throw APIError(std::string("listDir failed (") +
                        PHYSFS_getLastError() + ")");
    }

    //iterate over list, adding dirs
    for(char** i(buf); *i != 0; ++i)
    {
        files.push_back(*i);
    }

    PHYSFS_freeList(buf);   //free the memory

    return files;
}

bool exists(const std::string& item)
{
    return PHYSFS_exists(item.c_str()) != 0;
}

bool isDir(const std::string& item)
{
    return PHYSFS_isDirectory(item.c_str()) != 0;
}

bool isSymbolicLink(const std::string& item)
{
    return PHYSFS_isSymbolicLink(item.c_str()) != 0;
}

std::string getDirSeparator()
{
    return PHYSFS_getDirSeparator();
}

void permitSymbolicLinks(bool allow)
{
    PHYSFS_permitSymbolicLinks(allow);
}

PHYSFS_sint64 getModTime(const std::string& item)
{
    return PHYSFS_getLastModTime(item.c_str());
}

}
}
}
