//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ResourceManaged.hpp,v 1.1 2005/03/02 08:37:40 cozman Exp $

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
    //  filename - Name of file to open.
    //  zipname - Name of zip to open file from, empty string for no zip file.
    // 
    // See Also:
    //  <open>
    ResourceManaged(const std::string& path);

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
    //  filename - Name of file to open.
    //  zipname - Name of zip to open file from, empty string for no zip file.            
    virtual void open(const std::string& path);

    // Function: release
    //  Removes a reference to the resource, releasing if needed. 
    //  Generally called by destructor, so should rarely be called.
    virtual void release();
    
public:
    // Function: cleanUp
    //  Static method which cleans up any resources. 
    static void cleanUp(); 


private:
    static ResMgrT resMgr_;
    uint resID_;
};

//and he said "the implementation shall follow, as it is written"

template<class ResMgrT>
void ResourceManaged<ResMgrT>::cleanUp()
{
    resMgr_.cleanUp();
}

template<class ResMgrT>
ResourceManaged<ResMgrT>::ResourceManaged() : 
    resID_(Resource::Invalid)
{
}

template<class ResMgrT>
ResourceManaged<ResMgrT>::ResourceManaged(const std::string& path)
{
    open(path);
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
        if(resID_ != Resource::Invalid)
        {
            release();
        }
        resID_ = rhs.resID_;
    }
    return *this;
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::open(const std::string& path)
{
    release();
    resID_ = resMgr_.getResID(path);
}

template<class ResMgrT>
void ResourceManaged<ResMgrT>::release()
{
    resMgr_.delRef(resID_);
}

}

#endif  //PHOTON_RESOURCEMANAGED_HPP
