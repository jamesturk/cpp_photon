//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FontResourceManager.hpp,v 1.3 2005/07/03 06:33:19 cozman Exp $

#ifndef PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP
#define PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP

#include "ResourceManager.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace photon
{
namespace video
{

class FontResource : public Resource
{
public:
    uint texID;
    uint listBase;
    std::vector<ubyte> widths;
    ubyte height;
};

class FontResourceDescriptor : public ResourceDescriptor
{
public:
    FontResourceDescriptor(const std::string& str, uint sz) : 
        ResourceDescriptor(str), size(sz)
    { }

public:
    uint size;
};

class FontResourceManager : public ResourceManager<FontResource, 
                                                    FontResourceDescriptor>
{
public:
    FontResourceManager();
    ~FontResourceManager();

    void getFontData(const std::string& name, uint& texID, uint& listBase,
                        std::vector<ubyte>& widths, ubyte& height);

private:

    virtual void loadResourceData(FontResource &res,  
                                const FontResourceDescriptor& desc);
    virtual void freeResourceData(FontResource &res);
    
private:
    FT_Library library_;
public:
    static const unsigned int SPACE = 32;
    static const unsigned int NUM_CHARS = 96;
};

}
}

#endif  //PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP
