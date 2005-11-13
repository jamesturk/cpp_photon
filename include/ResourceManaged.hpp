//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ResourceManaged.hpp,v 1.9 2005/11/13 07:59:48 cozman Exp $

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
//  Unless extending Photon, generally ResourceManaged does not need to be
//  directly used.  For this reason public documentation is not availble.  See
//  ResourceManaged.hpp for documentation.
//
// Children:
//  <Texture>, <Image>
// 
//  <Source>
template<class ResMgrT>
class ResourceManaged
{
// Nondoc-Group: (Con/De)structors 
public:
    // Nondoc-Function: ResourceManaged
    //  Default constructor.
    ResourceManaged();

    // Nondoc-Function: ResourceManaged
    //  Initializing constructor, calls <open> with a filename/zipname.
    // 
    // Parameters: 
    //  name - name of resource
    // 
    // See Also:
    //  <open>
    ResourceManaged(const std::string& name);

    // Nondoc-Function: ~ResourceManaged
    //  Destructor, calls <release>.
    virtual ~ResourceManaged();

    ResourceManaged& operator=(const ResourceManaged &rhs);

// Nondoc-Group: General
public:
    // Nondoc-Function: open
    //  Opens new resource via the associated <ResourceManager>.
    // 
    // Parameters: 
    //  name - name of resource
    virtual void open(const std::string& name);

    // Nondoc-Function: release
    //  Removes a reference to the resource, releasing if needed. 
    //  Generally called by destructor, so should rarely be called.
    virtual void release();
    
// Nondoc-Group: Accessors
public:
    // Nondoc-Function: getName
    //  Get the name associated with the resource.  
    //
    // Returns:
    //  Name of resource, or empty string if no resource is loaded.
    std::string getName() const;
    
// Nondoc-Group: Resource Manager Access
public:
    static ResMgrT resMgr_;
    
    // Nondoc-Function: cleanUp
    //  Cleans up any unused resources of the type.
    //  (Ex. Image::cleanUp() will unload all images.)
    static void cleanUp();
    
    // Nondoc-Function: addResource
    //  Define a new named resource.
    //  (Ex. Image::addResource("monkey","images/monkey.png") would 
    //   make it so that any attempts to load "monkey" would load the image 
    //   images/monkey.png)
    //
    // Parameters:
    //  name - Name to give to resource.
    //  path - Path of resource data file.
    static void addResource(const std::string& name, 
                            const typename ResMgrT::ResDescT& desc);
    
    // Nondoc-Function: addResource
    //  Define a new unaliased resource. (name == path).
    //  (Ex. Image::addResource("images/monkey.png") is essentially the same as
    //   Image::addResource("images/monkey.png","images/monkey.png")
    //
    // Parameters:.
    //  path - Path of resource data file.
    static void addResource(const typename ResMgrT::ResDescT& desc);

private:
    std::string resName_;
};

//and he said "the implementation shall follow, as it is written"

template<class ResMgrT>
ResourceManaged<ResMgrT>::ResourceManaged()
{ }

template<class ResMgrT>
ResourceManaged<ResMgrT>::ResourceManaged(const std::string& name) :
    resName_(name)
{ }

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
        release();
        resName_ = rhs.resName_;
    }
    return *this;
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::open(const std::string& name)
{
    release();
    resName_ = name;
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::release()
{
    if(!resName_.empty())       // release is a no-op on an invalid resource
    {
        resMgr_.delRef(resName_);   // decrement the refcount 
        resName_.clear();           // empty string = invalid resource
    }
}

template<class ResMgrT>
std::string ResourceManaged<ResMgrT>::getName() const
{
    return resName_;
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::cleanUp()
{
    resMgr_.cleanUp();
}

// define the resource manager static instance
template <class T>
T ResourceManaged<T>::resMgr_;

}

#endif  //PHOTON_RESOURCEMANAGED_HPP
