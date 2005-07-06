//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: filesys_test.cpp,v 1.2 2005/07/06 02:10:07 cozman Exp $

#include "photon.hpp"
#include <iostream>

using namespace std;
using namespace photon;
using namespace photon::util;

class FilesysTest : public Application
{
public:

    int main(const StrVec& args)
    {
        StrVec list;
        
        //System Directories
        
        list = filesys::getCDDirs();
        cout << "CD directories: ";
        for(StrVec::iterator i=list.begin(); i != list.end(); ++i)
        {
            cout << *i << " ";
        }
        cout << endl;
        
        cout << "Base Directory: " << filesys::getBaseDir() << endl;
        cout << "User Directory: " << filesys::getUserDir() << endl;
        
        //Search Path
        
        cout << "adding base directory to search & write path" << endl;
        filesys::addToSearchPath( filesys::getBaseDir(), false );
        filesys::setWriteDir( filesys::getBaseDir() );
        
        list = filesys::getSearchPath();
        cout << "Search path: ";
        for(StrVec::iterator i=list.begin(); i != list.end(); ++i)
        {
            cout << *i << " ";
        }
        cout << endl;
        
        // Searching & Manipulation
        
        list = filesys::listDir("/");
        cout << "base dir contents: ";
        for(StrVec::iterator i=list.begin(); i != list.end(); ++i)
        {
            cout << *i << " ";
        }
        cout << endl;
        
        cout << "filesys_test.cpp" << (filesys::exists("filesys_test.cpp") ? " exists" : " not found") << endl;
        cout << "wokka " << (filesys::exists("wokka") ? " exists" : " not found") << endl;
        
        cout << "making directory 'bam'" << endl;
        filesys::mkdir("bam");
        
        cout << "bam " << (filesys::isDir("bam") ? " is dir" : " not dir") << endl;
        cout << "filesys_test.cpp" << (filesys::isDir("filesys_test.cpp") ? " is dir" : " not dir") << endl;
        
        filesys::remove("bam");
        cout << "removing directory 'bam'" << endl;
        
        //other
        
        cout << "Dir separator: " << filesys::getDirSeparator() << endl;
        cout << "Mod time of filesys_test.cpp" ": " << filesys::getModTime("filesys_test.cpp") << endl;
        
        // search path redux
        
        cout << "removing base directory from search/write path" << endl;
        filesys::removeFromSearchPath( filesys::getBaseDir() );
        filesys::setWriteDir( std::string() );
        
        list = filesys::getSearchPath();
        cout << "Search path: ";
        for(vector<string>::iterator i=list.begin(); i != list.end(); ++i)
        {
            cout << *i << " ";
        }
        cout << endl;
        
        return 0;
    }
};

ENTRYPOINT(FilesysTest)

