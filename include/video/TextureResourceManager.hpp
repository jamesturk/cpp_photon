//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: TextureResourceManager.hpp,v 1.1 2005/06/13 05:38:06 cozman Exp $

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
    ubyte *pixels;
};

class TextureResourceManager : public ResourceManager<TextureResource>
{
public:
    void setGlobalColorKey(bool enabled, ubyte red, ubyte green, ubyte blue);
    void getGlobalColorKey(bool &enabled, 
                            ubyte &red, ubyte &green, ubyte &blue);

    void getTextureData(uint id, scalar &width, scalar &height, uint &texID);

private:
    virtual void loadResource(TextureResource &res,  const std::string& name);
    virtual void freeResource(TextureResource &res);

    Color colorKey_;
};

}
}

#endif //PHOTON_VIDEO_TEXTURERESOURCEMANAGER_HPP
