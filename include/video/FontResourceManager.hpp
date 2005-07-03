//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FontResourceManager.hpp,v 1.2 2005/07/03 05:20:49 cozman Exp $

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

class FontResourceManager : public ResourceManager<FontResource>
{
public:
    FontResourceManager();
    ~FontResourceManager();

    void getFontData(const std::string& name, uint& texID, uint& listBase,
                        std::vector<ubyte>& widths, ubyte& height);

private:

    // defined but not implemented
    virtual void loadResource(FontResource &res,  const std::string& name);
    
    FontResource newResource(const std::string& name, const std::string& path, 
                                uint size);
    
    virtual void loadResource(FontResource &res,  const std::string& name, 
                                uint size);
    virtual void freeResource(FontResource &res);
    
private:
    FT_Library library_;
public:
    static const unsigned int SPACE = 32;
    static const unsigned int NUM_CHARS = 96;
};

}
}

#endif  //PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP
