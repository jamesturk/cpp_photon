//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ResourceManager.hpp,v 1.7 2005/06/27 04:24:16 cozman Exp $

#ifndef PHOTON_RESOURCEMANAGER_HPP
#define PHOTON_RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include <boost/utility.hpp>

#include "types.hpp"
#include "exceptions.hpp"

namespace photon
{

class Resource
{
public:
    uint refCount;
    std::string name;
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

    void delRef(const std::string& name);
    void cleanUp();

    void newResource(const std::string& name, const std::string& path);
    
    resT& getResource(const std::string& name);
    
private:
    virtual void loadResource(resT &res, const std::string& path)=0;
    virtual void freeResource(resT &res)=0;

    void deleteResource(const std::string& name);
    
public:
    void printReport(std::ostream& os);

private:
    typedef std::map<std::string,resT> MapT;
    typedef typename MapT::iterator MapIterator;
    MapT resourceMap_;
};

// implementation (damn you templor, cruel god of templates!)

template<class resT>
ResourceManager<resT>::ResourceManager()
{ }

template<class resT>
ResourceManager<resT>::~ResourceManager()
{ }

template<class resT>
void ResourceManager<resT>::delRef(const std::string& name)
{
    MapIterator resource( resourceMap_.find(name) );
    
    // if the resource was found
    if(resource != resourceMap_.end())
    {
        if(--resource->second.refCount <= 0)
        {
            deleteResource(name);
        }
    }
}

template<class resT>
void ResourceManager<resT>::cleanUp()
{
    // delete resources, until none are left
    while(!resourceMap_.empty())
    {
        freeResource(resourceMap_.begin()->second);
    }
}

template<class resT>
void ResourceManager<resT>::newResource(const std::string& name, 
                                        const std::string& path)
{
    resT resource;
    resource.name = name;
    resource.path = path;

    try
    {
        // attempt to load
        loadResource(resource, path);
    }
    catch(ResourceException& e)
    {
        // rethrow any exceptions with specific information 
        throw ResourceException("Could not load " + path + " as " + name + 
            ": " + e.getDesc());
    }

    resourceMap_[name] = resource;     // add the resource to resourceMap
}

template<class resT>
resT& ResourceManager<resT>::getResource(const std::string& name)
{
    MapIterator resource( resourceMap_.find(name) );
    
    if(resource != resourceMap_.end())
    {
        // increment the refCount and return the resource for use
        ++resource->second.refCount;
        return resource->second;
    }
    else
    {
        throw ResourceException("No resource named \"" + name + "\" exists.");
    }
}

template<class resT>
void ResourceManager<resT>::deleteResource(const std::string& name)
{
    MapIterator resource( resourceMap_.find(name) );
    
    // if the resource was found
    if(resource != resourceMap_.end())
    {
        freeResource(resource->second);     // free resource and remove it from the map
        resourceMap_.erase(name);
    }
}

template<class resT>
void ResourceManager<resT>::printReport(std::ostream& os)
{
    MapIterator resource( resourceMap_.begin() );
    
    for(MapIterator i = resourceMap_.begin(); i != resourceMap_.end(); ++i)
    {
        os << i->second.name << "\t" << i->second.path << "\t" 
            << i->second.refCount << "\n";
    }
}


}

#endif  //PHOTON_RESOURCEMANAGER_HPP
