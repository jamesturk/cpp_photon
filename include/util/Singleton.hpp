//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Singleton.hpp,v 1.4 2005/03/01 07:51:23 cozman Exp $

#ifndef PHOTON_UTIL_SINGLETON_HPP
#define PHOTON_UTIL_SINGLETON_HPP

#include <memory>
#include <boost/utility.hpp>

namespace photon
{
namespace util
{

// Class: Singleton
//  Template class for singleton pattern.  Is non-copyable to enforce
//  correct behavior.
//
// Defining a Singleton:
//  (code)
//  YourClass : public Singleton<Class>
//  {
//      // class specific data
//  
//      // Singleton-required code
//      private:
//          // Singleton-required code  
//          YourClass();
//          ~YourClass();
//  
//          friend class util::Singleton<YourClass>;
//          friend class std::auto_ptr<YourClass>;
//  };
//  (end)
//
// Using The Singleton:
//  (code)
//  YourClass::initialize();
//  YourClass& yc(YourClass::getInstance());
//
//  // use yc
//
//  YourClass::destroy();   //optional
//  (end)
template<class T>
class Singleton : public boost::noncopyable
{
public:
    
    // Function: initialize
    //  Initialize the instance of the singleton, must be done explicitly.
    static void initialize();
    
    // Function: destroy
    //  Destroy the instance of the singleton, can be done explicitly if order
    //  of destruction matters.  Will be done automatically if not done.
    static void destroy();

    // Function: getInstance
    //  Get a reference to the instance of the derived class.
    static T& getInstance();

protected:
    virtual ~Singleton()=0;

private:
    static std::auto_ptr<T> instance_;
};


// template implementation

template<class T>
Singleton<T>::~Singleton() 
{
}

template<class T>
void Singleton<T>::initialize()
{
    assert(instance_.get() == 0);

    instance_ = std::auto_ptr<T>(new T);
}

template<class T>
void Singleton<T>::destroy()
{
    assert(instance_.get() != 0);

    instance_.reset();
}

template<class T>
T& Singleton<T>::getInstance()
{
    assert(instance_.get() != 0);

    return *instance_;
}

template<class T> 
std::auto_ptr<T> Singleton<T>::instance_(0);

}
}

#endif  //PHOTON_UTIL_SINGLETON_HPP
