//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ResourceManager.hpp,v 1.1 2005/03/02 08:37:40 cozman Exp $

#ifndef PHOTON_RESOURCEMANAGER_HPP
#define PHOTON_RESOURCEMANAGER_HPP

#include <vector>
#include <string>

#include <boost/utility.hpp>

#include "types.hpp"
#include "exceptions.hpp"

namespace photon
{

class Resource
{
public:
    static const uint Invalid=0xffffffff;

    Resource() : 
        refCount(0)
    {
    }

    uint refCount;
    std::string path;
};

// Class: ResourceManager
//  Templated base class for managing resources like textures and music.
// 
//  All ResourceManager work is done behind the scenes, it and all classes 
//  derived from it are therefore left without public documentation.
template<class resT>
class ResourceManager : public boost::noncopyable
{
public:
    ResourceManager();

    virtual ~ResourceManager();

    uint getResID(const std::string& path);
    void delRef(uint id);
    void cleanUp();

private:
    virtual void loadResource(resT &res, const std::string& path)=0;
    virtual void freeResource(resT &res)=0;

    uint newResource(const std::string& path);
    void deleteResource(uint id);

private:
    std::vector<resT> resVec_;
};

// implementation (damn you templor, cruel god of templates!)

template<class resT>
ResourceManager<resT>::ResourceManager()
{
}

template<class resT>
ResourceManager<resT>::~ResourceManager()
{
}

template<class resT>
uint ResourceManager<resT>::getResID(const std::string& path)
{
    uint id(0);

    // loop through resources and find id
    for(typename std::vector<resT>::iterator i=resVec_.begin();
        i != resVec_.end(); 
        ++i)
    {
        ++id;   // increment id
        if(i->path == path)
        {
            return id;
        }
    }
    
    if(id == resVec_.size())
    {
        id = newResource(path);
    }

    return id;   //not already in vector, add resource
}

template<class resT>
void ResourceManager<resT>::delRef(uint id)
{
    // if decremented count is <= 0, delete resource
    if(id < resVec_.size() && --resVec_[id].refcount <= 0)
    {
        deleteResource(id);
    }
}

template<class resT>
void ResourceManager<resT>::cleanUp()
{
    // delete resources, until none are left
    for(typename std::vector<resT>::iterator i=resVec_.begin(); 
        i != resVec_.end(); 
        ++i)
    {
        freeResource(*i);
    }
}

template<class resT>
uint ResourceManager<resT>::newResource(const std::string& path)
{
    resT res;
    res.path = path;

    try
    {
        // attempt to load
        loadResource(res,path);
    }
    catch(ResourceException&)
    {
        // rethrow any exceptions with specific information 
        throw ResourceException("Could not load " + path);
    }

    resVec_.push_back(res);     // add resource to resVec & return 
    return static_cast<uint>(resVec_.size()-1);
}

template<class resT>
void ResourceManager<resT>::deleteResource(uint id)
{
    // check boundaries
    if(id >= resVec_.size())
    {
        throw RangeException("Attempt to delete invalid resource.");
    }

    freeResource(resVec_[id]);  // free the resource and erase it from the vec
    resVec_.erase(resVec_.begin()+id);
}

}

#endif  //PHOTON_RESOURCEMANAGER_HPP
