//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FontResourceManager.hpp,v 1.4 2005/07/18 07:19:48 cozman Exp $

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
    FT_Library library_;    // only need one FT_Library, so manager owns it
public:
    static const uint SPACE = 32;
    static const uint NUM_CHARS = 96;
};

}
}

#endif  //PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP
