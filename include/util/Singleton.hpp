//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Singleton.hpp,v 1.9 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_UTIL_SINGLETON_HPP
#define PHOTON_UTIL_SINGLETON_HPP

#include <boost/utility.hpp>

#include "exceptions.hpp"

namespace photon
{
namespace util
{

// Class: Singleton
//  Template class for singleton pattern.  Is non-copyable to enforce correct
//  behavior.
//
// Defining a Singleton:
//  (code)
//  class YourClass : public Singleton<Class>
//  { 
//      // class definition
//  };
//  (end)
//
// Using The Singleton:
//  (code)
//  new YourClass;
//  YourClass& yc(YourClass::getInstance());
//
//  // use yc
//
//  YourClass::destroy(); 
//  (end)
template<class T>
class Singleton : public boost::noncopyable
{
public:
    // Function: destroy
    //  Destroy the instance of the singleton, must be done for every singleton
    //  created.
    //
    // Throws:
    //  <PreconditionException> if called for uninitialized singleton
    static void destroy();

    // Function: getInstance
    //  Get a reference to the instance of the derived class.
    //
    // Throws:
    //  <PreconditionException> if called for uninitialized singleton
    static T& getInstance();

protected:
    Singleton();
    virtual ~Singleton();   // allow inheritance

private:
    static T* instance_;
};


// template implementation

template<class T>
void Singleton<T>::destroy()
{
    if(instance_ == 0)
    {
        throw PreconditionException("Attempt to destroy null singleton.");
    }

    if(instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

template<class T>
T& Singleton<T>::getInstance()
{
    if(instance_ == 0)
    {
        throw PreconditionException("Attempt to access null singleton.");
    }

    return *instance_;  //return dereferenced instance
}

template<class T>
Singleton<T>::Singleton()
{
    if(instance_ != 0)
    {
        throw PreconditionException("Attempt to double-initialize singleton.");
    }

    instance_ = static_cast<T*>(this);  // cast self to type of T*
}

template<class T>
Singleton<T>::~Singleton() 
{
}

template<class T> 
T* Singleton<T>::instance_(0);

}
}

#endif  //PHOTON_UTIL_SINGLETON_HPP
