//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exceptions.cpp,v 1.1 2005/01/27 03:35:24 cozman Exp $
//
// Revisions:
//  $Log: exceptions.cpp,v $
//  Revision 1.1  2005/01/27 03:35:24  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//


#include "exceptions.h"


namespace photon 
{

Throwable::Throwable() throw() {}
Throwable::Throwable(std::string description) throw() :
    description_(description) {}
Throwable::~Throwable() throw() {}
std::string Throwable::getDesc() const throw()
{
    return description_;
}

//exceptions//

Exception::Exception() throw() {}
Exception::Exception(std::string description) throw() :
    Throwable(description) {}
std::ostream& operator<<(std::ostream& os, const Exception& rhs)
{
    return os << "General exception occured. " << rhs.getDesc();
}

ArgumentException::ArgumentException() throw() {}
ArgumentException::ArgumentException(std::string description) throw() :
    Exception(description) {}
std::ostream& operator<<(std::ostream& os, const ArgumentException& rhs)
{
    return os << "Invalid argument exception occured. " << rhs.getDesc();
}

PreconditionException::PreconditionException() throw() {}
PreconditionException::PreconditionException(std::string description) throw() :
    Exception(description) {}
std::ostream& operator<<(std::ostream& os, const PreconditionException& rhs)
{
    return os << "Precondition exception occured. " << rhs.getDesc();
}

RangeException::RangeException() throw() {}
RangeException::RangeException(std::string description) throw() :
    Exception(description) {}
std::ostream& operator<<(std::ostream& os, const RangeException& rhs)
{
    return os << "Out-of-range exception. " << rhs.getDesc();
}

ResourceException::ResourceException() throw() {}
ResourceException::ResourceException(std::string description) throw() :
    Exception(description) {}
std::ostream& operator<<(std::ostream& os, const ResourceException& rhs)
{
    return os << "Resource exception. " << rhs.getDesc();
}

//errors//

Error::Error() throw() {}
Error::Error(std::string description) throw() :
    Throwable(description) {}
std::ostream& operator<<(std::ostream& os, const Error& rhs)
{
    return os << "General error occured. " << rhs.getDesc();
}

MemoryError::MemoryError() throw() {}
MemoryError::MemoryError(std::string description) throw() :
    Error(description) {}
std::ostream& operator<<(std::ostream& os, const MemoryError& rhs)
{
    return os << "Memory error occured. " << rhs.getDesc();
}

APIError::APIError() throw() {}
APIError::APIError(std::string description) throw() :
    Error(description) {}
std::ostream& operator<<(std::ostream& os, const APIError& rhs)
{
    return os << "Error occured within another library. " << rhs.getDesc();
}

}
