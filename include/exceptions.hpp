//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exceptions.hpp,v 1.1 2005/02/13 22:12:03 cozman Exp $
//
// Revisions:
//  $Log: exceptions.hpp,v $
//  Revision 1.1  2005/02/13 22:12:03  cozman
//  .h->.hpp
//
//  Revision 1.5  2005/02/07 01:48:26  cozman
//  string references
//
//  Revision 1.4  2005/02/06 21:28:47  cozman
//  removed require
//
//  Revision 1.3  2005/01/31 15:44:38  cozman
//  simplified exceptions
//
//  Revision 1.2  2005/01/27 05:24:11  cozman
//  minor documentation update
//
//  Revision 1.1  2005/01/27 03:35:23  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#ifndef PHOTON_EXCEPTIONS_HPP
#define PHOTON_EXCEPTIONS_HPP

#include "types.hpp"
#include <string>
#include <sstream>
#include <ostream>

#define __FLOC__ __FILE__,__LINE__

namespace photon 
{ 

// Title: Exception/Error Types

// Class: Throwable
//  Throwable is the base exception class for Photon.
//
//  Throwable is pure virtual, and can not be used directly, Exception and
//  Error are available for non-specific exceptions. All exceptions have the
//  same interface as Throwable.
//
// Children:
//  <Exception> - Base class for all non-fatal exceptions.
//  <Error> - Base class for all potentially fatal exceptions.
class Throwable
{
public:
    // Function: Throwable
    //  Constructor for a Throwable object, can specify as little or as much
    //  information as you'd like when throwing.
    //
    // Parameters:
    //  description - description of why exception was thrown [default: empty]
    //  file - name of file where exception was thrown [default: empty]
    //  line - line in file where exception was thrown [default: 0]
    Throwable(const std::string& description = std::string(),
                const std::string& file = std::string(),
                uint line=0) throw();
    virtual ~Throwable() throw()=0;

    std::string getDesc() const throw();

private:
    std::string description_;
    std::string file_;
    uint line_;
};

// Class: Exception
//  Exception is the base exception class, all exceptions inherit from
//  it, and it inherits from <Throwable>.
//  Exception should be used for hard to classify exceptions.
//
//  Exception's children should be used when a problem occurs which is 
//  recoverable.
//
// Operators:
//  ostream&<<
//
// See Also:
//  <Error>
//
// Parent:
//  <Throwable>
//
// Children:
//  <ArgumentException>
//  <PreconditionException>
//  <RangeException>
//  <ResourceException>
class Exception : public Throwable
{
public:
    Exception(const std::string& description = std::string(),
                const std::string& file = std::string(),
                uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const Exception& rhs);
};

// Class: ArgumentException
//  ArgumentException should be thrown when an argument is passed to a function
//  that is invalid.
//
// Operators:
//  ostream&<<
//
// Parent:
//  <Exception>
class ArgumentException : public Exception
{
public:
    ArgumentException(const std::string& description = std::string(),
                        const std::string& file = std::string(),
                        uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const ArgumentException& rhs);
}; 

// Class: PreconditionException
//  PreconditionException should be thrown when a precondition is not met.
//
// Operators:
//  ostream&<<
//
// Parent:
//  <Exception>
class PreconditionException : public Exception
{
public:
    PreconditionException(const std::string& description = std::string(),
                            const std::string& file = std::string(),
                            uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const PreconditionException& rhs);
}; 

// Class: RangeException
//  RangeException should be thrown if something (such as an array bound) is out
//  of bounds.
//
// Operators:
//  ostream&<<
//
// Parent:
//  <Exception>
class RangeException : public Exception
{
public:
    RangeException() throw();
    RangeException(const std::string& description = std::string(),
                    const std::string& file = std::string(),
                    uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const RangeException& rhs);
}; 

// Class: ResourceException
//  ResourceException should be thrown if there is a problem accessing a
//  resource.
//
// Operators:
//  ostream&<<
//
// Parent:
//  <Exception>
class ResourceException : public Exception
{
public:
    ResourceException() throw();
    ResourceException(const std::string& description = std::string(),
                        const std::string& file = std::string(),
                        uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const ResourceException& rhs);
}; 

// Class: Error
//  GeneralError is the base error class, all errors inherit from it, and it
//  inherits from <Throwable>.
//  Error should be used for hard to classify errors.
//
//  Errors should be used when a problem occurs which is difficult to just
//  ignore, usually more severe than exceptions.
//
// Operators:
//  ostream&<<
//  
// See Also:
//  <Exception>
//
// Parent:
//  <Throwable>
//
// Children:
//  <MemoryError>
//  <APIError>
class Error : public Throwable
{
public:
    Error() throw();
    Error(const std::string&description = std::string(),
            const std::string& file = std::string(),
            uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const Error& rhs);
};

// Class: MemoryError
//  MemoryError should be thrown if there is an error allocating memory.
//
// Operators:
//  ostream&<<
//
// Parent:
//  <Error>
class MemoryError : public Error
{
public:
    MemoryError() throw();
    MemoryError(const std::string& description = std::string(),
                const std::string& file = std::string(),
                uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const MemoryError& rhs);
};

// Class: APIError
//  APIError should be thrown if an error occurs in code which is not part of
//  Photon.
//
// Operators:
//  ostream&<<
//
// Parent:
//  <Error>
class APIError : public Error
{
public:
    APIError() throw();
    APIError(const std::string& description = std::string(),
                const std::string& file = std::string(),
                uint line=0) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const APIError& rhs);
};

}

#endif  //PHOTON_EXCEPTIONS_HPP
