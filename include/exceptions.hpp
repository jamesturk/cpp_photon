//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exceptions.hpp,v 1.4 2005/03/01 07:51:04 cozman Exp $

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
// Operators:
//  ostream& << Throwable - All exceptions defined here can be output via '<<'
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

    // Function: what
    //  Similar to the std::exception family, all photon exceptions (the  
    //  Throwable family) define what() that returns a description of the
    //  exception.
    //
    // Returns: std::string describing the error
    std::string virtual what() const throw();
    friend std::ostream& operator<<(std::ostream& os, const Throwable& rhs);

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
//  Exception and children should be used when a problem occurs which is 
//  recoverable.
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
    std::string what() const throw();
};

// Class: ArgumentException
//  ArgumentException should be thrown when an argument is passed to a function
//  that is invalid.
//
// Parent:
//  <Exception>
class ArgumentException : public Exception
{
public:
    ArgumentException(const std::string& description = std::string(),
                        const std::string& file = std::string(),
                        uint line=0) throw();
    std::string what() const throw();
}; 

// Class: PreconditionException
//  PreconditionException should be thrown when a precondition is not met.
//
// Parent:
//  <Exception>
class PreconditionException : public Exception
{
public:
    PreconditionException(const std::string& description = std::string(),
                            const std::string& file = std::string(),
                            uint line=0) throw();
    std::string what() const throw();
}; 

// Class: RangeException
//  RangeException should be thrown if something (such as an array bound) is out
//  of bounds.
//
// Parent:
//  <Exception>
class RangeException : public Exception
{
public:
    RangeException(const std::string& description = std::string(),
                    const std::string& file = std::string(),
                    uint line=0) throw();
    std::string what() const throw();
}; 

// Class: ResourceException
//  ResourceException should be thrown if there is a problem accessing a
//  resource.
//
// Parent:
//  <Exception>
class ResourceException : public Exception
{
public:
    ResourceException(const std::string& description = std::string(),
                        const std::string& file = std::string(),
                        uint line=0) throw();
    std::string what() const throw();
}; 

// Class: Error
//  Error is the base error class, all errors inherit from it, and it inherits 
//  from <Throwable>.
//  Error should be used for hard to classify errors.
//
//  Errors should be used when a problem occurs which is difficult to just
//  ignore, usually more severe than exceptions.
//  
// See Also:
//  <Exception>
//
// Parent:
//  <Throwable>
//
// Children:
//  <APIError>
//  <MemoryError>
class Error : public Throwable
{
public:
    Error(const std::string&description = std::string(),
            const std::string& file = std::string(),
            uint line=0) throw();
    std::string what() const throw();
};

// Class: MemoryError
//  MemoryError should be thrown if an error occurs while allocating memory.
//
// Parent:
//  <Error>
class MemoryError : public Error
{
public:
    MemoryError(const std::string& description = std::string(),
                const std::string& file = std::string(),
                uint line=0) throw();
    std::string what() const throw();
}; 

// Class: APIError
//  APIError should be thrown if an error occurs in code which is not part of
//  Photon.
//
// Parent:
//  <Throwable>
class APIError : public Error
{
public:
    APIError(const std::string& description = std::string(),
                const std::string& file = std::string(),
                uint line=0) throw();
    std::string what() const throw();
}; 

}

#endif  //PHOTON_EXCEPTIONS_HPP
