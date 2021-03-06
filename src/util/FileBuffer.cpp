//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FileBuffer.cpp,v 1.8 2005/07/18 06:18:50 cozman Exp $

#include "util/FileBuffer.hpp"

#include "exceptions.hpp"

namespace photon
{
namespace util
{

FileBuffer::FileBuffer() :
    file_(0)
{}


FileBuffer::FileBuffer(const std::string& filename)
{
    open(filename);
}

FileBuffer::~FileBuffer()
{
    if(file_ != 0)
    {
        close();
    }
}

void FileBuffer::open(const std::string& filename)
{
    file_ = PHYSFS_openRead(filename.c_str());
    if(file_ == 0)
    {
        throw ResourceException("Could not open file \"" + filename + "\".");
    }
}

void FileBuffer::close()
{
    if(file_ == 0)
    {
        throw PreconditionException("No file open in FileBuffer::close");
    }
    
    PHYSFS_close(file_);
    file_ = 0;
}

std::vector<ubyte> FileBuffer::getData(int amount)
{
    if(file_ == 0)
    {
        throw PreconditionException("No file open in FileBuffer::getData");
    }
    
    // if amount is 0, read entire buffer
    if(amount == 0)
    {
        amount = getSize();
    }
    
    std::vector<ubyte> buffer(amount);   //create buffer

    // try to read 'amount' bytes into buffer
    PHYSFS_sint64 bytesRead = PHYSFS_read(file_, &buffer[0], 1, amount);

    // if -1 is returned (an error) or fewer bytes were read than asked but
    // eof hasn't been reached, PhysFS encountered an error
    if( bytesRead == -1 || (bytesRead < amount && PHYSFS_eof(file_) == 0) )
    {
        throw APIError(std::string("PhysFS failure in FileBuffer::getData (") +
                        PHYSFS_getLastError() + ")");
    }

    buffer.resize(bytesRead);   //shrink to size()==bytesRead

    return buffer;
}

uint FileBuffer::getPosition() const
{
    if(file_ == 0)
    {
        throw PreconditionException("No file open in FileBuffer::getPosition");
    }
    
    PHYSFS_sint64 pos = PHYSFS_tell(file_);
    
    if(pos == -1)
    {
        throw APIError(
                std::string("PhysFS failure in FileBuffer::getPosition (") +
                PHYSFS_getLastError() + ")");
    }
    
    return pos;
}

uint FileBuffer::getSize() const
{
    if(file_ == 0)
    {
        throw PreconditionException("No file open in FileBuffer::getSize");
    }

    PHYSFS_sint64 size = PHYSFS_fileLength(file_);

    if(size == -1)
    {
        throw APIError(std::string("PhysFS failure in FileBuffer::getSize (") +
                        PHYSFS_getLastError() + ")");
    }

    return size;
}

bool FileBuffer::isOpen() const
{
    return file_ != 0;
}

}
}
