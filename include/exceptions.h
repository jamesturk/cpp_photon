//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exceptions.h,v 1.1 2005/01/27 03:35:23 cozman Exp $
//
// Revisions:
//  $Log: exceptions.h,v $
//  Revision 1.1  2005/01/27 03:35:23  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#ifndef PHOTON_EXCEPTIONS_H
#define PHOTON_EXCEPTIONS_H

#include <string>
#include <ostream>

namespace photon 
{ 

// Class: Throwable
//  Throwable is the base exception class for Photon.
//
//  Throwable is pure virtual, and can not be used directly, Exception and
//  Error are available for non-specific exceptions.
//
// Children:
//  <Exception> - Base class for all non-fatal exceptions.
//  <Error> - Base class for all potentially fatal exceptions.
class Throwable
{
public:
    Throwable() throw();
    Throwable(std::string description) throw();
    virtual ~Throwable() throw()=0;

    std::string getDesc() const throw();

private:
    std::string description_;
};

// Class: Exception
//  Exception is the base exception class, all exceptions inherit from
//  it, and it inherits from <Throwable>.
//  Exception should be used for hard to classify exceptions.
//
//  Exception's children should be used when a problem occurs which is 
//  recoverable.
//
// See Also:
//      <Error>
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
    Exception() throw();
    Exception(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const Exception& rhs);
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
    ArgumentException() throw();
    ArgumentException(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const ArgumentException& rhs);
}; 

// Class: PreconditionException
//  PreconditionException should be thrown when a precondition is not met.
//
// Parent:
//  <Exception>
class PreconditionException : public Exception
{
public:
    PreconditionException() throw();
    PreconditionException(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const PreconditionException& rhs);
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
    RangeException() throw();
    RangeException(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const RangeException& rhs);
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
    ResourceException() throw();
    ResourceException(std::string description) throw();
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
    Error(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const Error& rhs);
};

// Class: MemoryError
//  MemoryError should be thrown if there is an error allocating memory.
//
// Parent:
//  <Error>
class MemoryError : public Error
{
public:
    MemoryError() throw();
    MemoryError(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const MemoryError& rhs);
};

// Class: APIError
//  APIError should be thrown if an error occurs in code which is not part of
//  Photon.
//
// Parent:
//  <Error>
class APIError : public Error
{
public:
    APIError() throw();
    APIError(std::string description) throw();
    friend std::ostream& operator<<(std::ostream& os,
                                    const APIError& rhs);
};


// Function: require
//  Similar to an assert, given a condition checks if it is true, and if it is
//  not, throws an exception.
//
//  An example of when to use require would be in a function that does an
//  operation to a certain pointer:
//  void func()
//  {
//      require<PreconditionException>(pointer != NULL,"pointer must be valid");
//
//      pointer->doSomething();
//  }
//
// Template Parameters:
//  ExceptionT - type of exception to throw
//
// Parameters:
//  condition - boolean expression to be satisfied
//  description - description of this condition (optional parameter)
template<class ExceptionT>
void require(bool condition, std::string description="");

//definition of require template
template<class ExceptionT>
void require(bool condition, std::string description)
{
    if(!condition)
    {
        throw ExceptionT(description);
    }
}

}

#endif  //PHOTON_EXCEPTIONS_H
