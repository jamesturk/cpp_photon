//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Singleton.hpp,v 1.1 2005/02/27 05:50:54 cozman Exp $

#ifndef PHOTON_UTIL_SINGLETON_HPP
#define PHOTON_UTIL_SINGLETON_HPP

#include <memory>
#include <boost/utility.hpp>

namespace photon
{
namespace util
{

template<class T>
class Singleton : public boost::noncopyable
{
public:
    static void initSingleton();
    
    static void destroySingleton();

    static T& getSingleton();

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
void Singleton<T>::initSingleton()
{
    assert(instance_.get() == 0);
    
    instance_ = std::auto_ptr<T>(new T);
}

template<class T>
void Singleton<T>::destroySingleton()
{
    assert(instance_.get() != 0);
    
    instance_.reset();
}

template<class T>
T& Singleton<T>::getSingleton()
{
    assert(instance_.get() != 0);
    
    return *instance_;
}

template<class T>
std::auto_ptr<T> Singleton<T>::getSingletonPtr()
{
    assert(instance_.get() != 0);
    
    return instance_;
}

template<class T> 
std::auto_ptr<T> Singleton<T>::instance_(0);

}
}

#endif  //PHOTON_UTIL_SINGLETON_HPP
