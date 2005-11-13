//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FileBuffer.hpp,v 1.5 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_UTIL_FILEBUFFER_HPP
#define PHOTON_UTIL_FILEBUFFER_HPP

#include "types.hpp"

#include "physfs.h"

#include <string>
#include <vector>

namespace photon
{
namespace util
{

// Class: FileBuffer
//  Class for reading data from a file, uses PhysFS 
//  (<http://physfs.icculus.org>)
//  and is capable of reading from archives on the search path.  
//
//  All paths used are relative to the search path.  
//  By default only files within the directory the application is running or 
//  it's subdirectories are accessible.  Additional directories may be added
//  to the search path via <addToSearchPath>.
class FileBuffer
{

// Group: (Con/De)structors
public:
    // Function: FileBuffer
    //  Initializes empty buffer.
    FileBuffer();

    // Function: FileBuffer
    //  Initializing constructor, calls <open>.
    //
    // Parameters:
    //   filename - Name of file to load.  (See notes on how FileBuffer handles
    //              paths at top of page)
    FileBuffer(const std::string& filename);

    //  Function: ~FileBuffer
    //  Destructor, calls <close>.
    ~FileBuffer();

// Group: General
public:
    // Function: open
    //  Loads a file into the FileBuffer.
    //
    // Parameters:
    //   filename - Name of file to load.  (See notes on how FileBuffer handles
    //              paths at top of page)
    void open(const std::string& filename);

    // Function: close
    //  Closes the file, all future read attempts will fail until <open> is 
    //  called agian.
    void close();

// Group: Accessors
public:

    // Function: getData
    //  Reads data from file into a <ubyte>-vector.
    //  If the requested amount of data wasn't available, returns only
    //  what could be loaded.  If amount is 0 (default), returns entire buffer.
    //
    // Parameters:
    //  amount - maximum amount of data to load [default: 0]
    //
    // Returns:
    //  Vector containing loaded data, empty if nothing loaded.
    std::vector<ubyte> getData(int amount=0);

    // Function: getPosition
    //  Gets position of internal cursor inside data.
    //
    // Returns:
    //   Position of cursor reading in data.
    uint getPosition() const;

    // Function: getSize
    //  Gets size of data.
    //
    // Returns:
    //   Size of currently loaded data.
    uint getSize() const;
    
    // Function: isEOF
    //  Checks if internal cursor has reached end of file.
    //
    // Returns:
    //  True iff eof, false otherwise.
    bool isEOF() const;

    // Function: isOpen
    //  Checks if file is open.
    //
    // Returns:
    //  True iff file is open, false otherwise.
    bool isOpen() const;

private:
    // PHYSFS_file* for the buffer
    PHYSFS_file* file_;
};

}
}

#endif  //PHOTON_UTIL_FILEBUFFER_HPP
