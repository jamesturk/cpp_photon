//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Singleton.hpp,v 1.8 2005/07/18 06:18:51 cozman Exp $

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
    // Function: initialize
    //  Initialize the instance of the singleton, can be done explicitly if
    //  order of construction matters.  Will be done on first call to
    //  getInstance otherwise.
    static void initialize();
    
    // Function: destroy
    //  Destroy the instance of the singleton, can be done explicitly if order
    //  of destruction matters.  Will be done automatically if not done.
    static void destroy();

    // Function: getInstance
    //  Get a reference to the instance of the derived class.
    static T& getInstance();

protected:
    Singleton();
    virtual ~Singleton();   // allow inheritance

private:
    static T* instance_;
};


// template implementation

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
T* Singleton<T>::instance_(0);

}
}

#endif  //PHOTON_UTIL_SINGLETON_HPP
