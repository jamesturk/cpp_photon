//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ResourceManaged.hpp,v 1.3 2005/06/10 07:06:06 cozman Exp $

#ifndef PHOTON_RESOURCEMANAGED_HPP
#define PHOTON_RESOURCEMANAGED_HPP

#include <string>

#include "ResourceManager.hpp"

namespace photon
{

// Class: ResourceManaged
//  Base template class, to be used as a base from which classes which have
//  resources that can be controlled, such as textures and music, can be
//  derived.  Resource managed classes rely on a <ResourceManager>.
// 
// Children:
//  <Texture>, <Image>
// 
//  <Audio>, <Music>, <Sound>
template<class ResMgrT>
class ResourceManaged
{
// Group: (Con/De)structors 
public:
    // Function: ResourceManaged
    //  Default constructor.
    ResourceManaged();

    // Function: ResourceManaged
    //  Initializing constructor, calls <open> with a filename/zipname.
    // 
    // Parameters: 
    //  name - name of resource
    // 
    // See Also:
    //  <open>
    ResourceManaged(const std::string& name);

    // Function: ~ResourceManaged
    //  Destructor, calls <release>.
    virtual ~ResourceManaged();

    ResourceManaged& operator=(const ResourceManaged &rhs);

// Group: General
public:
    // Function: open
    //  Opens new resource via the associated <ResourceManager>.
    // 
    // Parameters: 
    //  name - name of resource
    virtual void open(const std::string& name);

    // Function: release
    //  Removes a reference to the resource, releasing if needed. 
    //  Generally called by destructor, so should rarely be called.
    virtual void release();
    
// Group: Resource Manager Access

    // Function: cleanUp
    //  Cleans up any unused resources of the type.
    //  (Ex. Image::cleanUp() will unload all images.)
    virtual void cleanUp();
    
    // Function: addResource
    //  Define a new named resource.
    //  (Ex. Image::addResource("monkey","images/monkey.png") would 
    //   make it so that any attempts to load "monkey" would load the image 
    //   images/monkey.png)
    //
    // Parameters:
    //  name - Name to give to resource.
    //  path - Path of resource data file.
    static void addResource(const std::string& name, const std::string& path);
    
    // Function: addResource
    //  Define a new unaliased resource. (name == path).
    //  (Ex. Image::addResource("images/monkey.png") is essentially the same as
    //   Image::addResource("images/monkey.png","images/monkey.png")
    //
    // Parameters:.
    //  path - Path of resource data file.
    static void addResource(const std::string& path);

protected:
    static ResMgrT resMgr_;
    uint resID_;
};

//and he said "the implementation shall follow, as it is written"

template<class ResMgrT>
ResourceManaged<ResMgrT>::ResourceManaged() : 
    resID_(Resource::InvalidID)
{
}

template<class ResMgrT>
ResourceManaged<ResMgrT>::ResourceManaged(const std::string& name)
{
}

template<class ResMgrT>
ResourceManaged<ResMgrT>::~ResourceManaged()
{
    release();
}

template<class ResMgrT>
ResourceManaged<ResMgrT>& 
ResourceManaged<ResMgrT>::operator=(const ResourceManaged<ResMgrT> &rhs)
{
    if(this != &rhs)
    {
        if(resID_ != Resource::InvalidID)
        {
            release();
        }
        resID_ = rhs.resID_;
    }
    return *this;
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::open(const std::string& name)
{
    release();
    resID_ = resMgr_.getResID(name);
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::release()
{
    resMgr_.delRef(resID_);
    resID_ = Resource::InvalidID;
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::cleanUp()
{
    resMgr_.cleanUp();
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::addResource(const std::string& name, 
                                            const std::string& path)
{
    resMgr_.newResource(name,path);
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::addResource(const std::string& path)
{
    resMgr_.newResource(path,path);
}

}

#endif  //PHOTON_RESOURCEMANAGED_HPP
