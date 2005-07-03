//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ResourceManager.hpp,v 1.8 2005/07/03 06:33:19 cozman Exp $

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
};

class ResourceDescriptor
{
public:
    ResourceDescriptor() { }
    ResourceDescriptor(const std::string& p) :
        path(p)
    { }
    std::string path;
};

// Class: ResourceManager
//  Templated base class for managing resources like textures and music.
// 
//  All ResourceManager work is done behind the scenes, it and all classes 
//  derived from it are therefore left without public documentation.
template<class resT, class ResDescT_=ResourceDescriptor>
class ResourceManager : public boost::noncopyable
{
public:
    typedef ResDescT_ ResDescT;
    
public:
    ResourceManager();

    virtual ~ResourceManager();

    void delRef(const std::string& name);
    void cleanUp();

    void newResource(const std::string& name, const ResDescT& path);
    
    resT& getResource(const std::string& name);
    
private:
    virtual void loadResourceData(resT &res, const ResDescT& path)=0;
    virtual void freeResourceData(resT &res)=0;

    void deleteResource(const std::string& name);
    
public:
    void printReport(std::ostream& os);

private:
    typedef std::map<std::string,resT> MapT;
    typedef typename MapT::iterator MapIterator;
    MapT resourceMap_;
};

// implementation (damn you templor, cruel god of templates!)

template<class resT, class ResDescT>
ResourceManager<resT, ResDescT>::ResourceManager()
{ }

template<class resT, class ResDescT>
ResourceManager<resT, ResDescT>::~ResourceManager()
{ }

template<class resT, class ResDescT>
void ResourceManager<resT, ResDescT>::delRef(const std::string& name)
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

template<class resT, class ResDescT>
void ResourceManager<resT, ResDescT>::cleanUp()
{
    // delete resources, until none are left
    while(!resourceMap_.empty())
    {
        freeResourceData(resourceMap_.begin()->second);
    }
}

template<class resT, class ResDescT>
void ResourceManager<resT, ResDescT>::newResource(const std::string& name, 
                                                    const ResDescT& desc)
{
    resT resource;

    try
    {
        // attempt to load
        loadResourceData(resource, desc);
    }
    catch(ResourceException& e)
    {
        // rethrow any exceptions with specific information 
        throw ResourceException("Could not load " + desc.path + " as " + name + 
            ": " + e.getDesc());
    }

    resourceMap_[name] = resource;     // add the resource to resourceMap
}

template<class resT, class ResDescT>
resT& ResourceManager<resT, ResDescT>::getResource(const std::string& name)
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

template<class resT, class ResDescT>
void ResourceManager<resT, ResDescT>::deleteResource(const std::string& name)
{
    MapIterator resource( resourceMap_.find(name) );
    
    // if the resource was found
    if(resource != resourceMap_.end())
    {
        // free resource and remove it from the map
        freeResourceData(resource->second);
        resourceMap_.erase(name);
    }
}

template<class resT, class ResDescT>
void ResourceManager<resT, ResDescT>::printReport(std::ostream& os)
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
