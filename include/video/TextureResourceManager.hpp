//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: TextureResourceManager.hpp,v 1.4 2005/07/18 07:19:48 cozman Exp $

#ifndef PHOTON_VIDEO_TEXTURERESOURCEMANAGER_HPP
#define PHOTON_VIDEO_TEXTURERESOURCEMANAGER_HPP

#include "ResourceManager.hpp"
#include "video/Color.hpp"

namespace photon
{
namespace video
{

class TextureResource : public Resource
{
public:
    uint texID;
    uint width;
    uint height;
    ubyte *pixels;  // keep pixels around for future use (post-load colorkeying)
};

class TextureResourceManager : public ResourceManager<TextureResource>
{
public:
    void setGlobalColorKey(bool enabled, ubyte red, ubyte green, ubyte blue);
    void getGlobalColorKey(bool &enabled, 
                            ubyte &red, ubyte &green, ubyte &blue);

    void getTextureData(const std::string& name, scalar &width, scalar &height, 
                        uint &texID);

private:
    virtual void loadResourceData(TextureResource &res,  
                                    const ResourceDescriptor& path);
    virtual void freeResourceData(TextureResource &res);

    Color colorKey_;
};

}
}

#endif //PHOTON_VIDEO_TEXTURERESOURCEMANAGER_HPP
