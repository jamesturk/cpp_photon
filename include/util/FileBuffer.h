//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FileBuffer.h,v 1.2 2005/02/07 01:48:26 cozman Exp $
//
// Revisions:
//  $Log: FileBuffer.h,v $
//  Revision 1.2  2005/02/07 01:48:26  cozman
//  string references
//
//  Revision 1.1  2005/02/06 21:30:10  cozman
//  PhysFS initial integration
//
//

#ifndef PHOTON_UTIL_FILEBUFFER_H
#define PHOTON_UTIL_FILEBUFFER_H

#include "types.h"

#include "physfs.h"

#include <string>
#include <vector>

namespace photon
{
namespace util
{

// Class: FileBuffer
// Class for reading data from a file, uses PhysFS <http://physfs.icculus.org>
// and is capable of reading from archives on the search path.
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
    //   filename - Name of file to load.
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
    //   filename - Name of file to load.
    void open(const std::string& filename);

    // Function: close
    //  Frees memory occupied by loaded data.
    void close();

// Group: Accessors
public:

    // Function: getData
    //  Loads an amount of data, returns a pointer to the loaded data.
    //  If the requested amount of data wasn't available, returns only
    //  what could be loaded.
    //
    // Parameters:
    //  amount - maximum amount of data to load
    //
    // Returns:
    //  Vector containing loaded data, empty if nothing loaded.
    std::vector<ubyte> getData(int amount);

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
    //  Checks if internal cursor is at end of file.
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

#endif  //PHOTON_UTIL_FILEBUFFER_H
