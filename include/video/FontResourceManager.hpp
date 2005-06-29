//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FontResourceManager.hpp,v 1.1 2005/06/29 04:30:40 cozman Exp $

#ifndef PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP
#define PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP

#include "ResourceManager.hpp"

#include "FTGL/FTGL.h"
#include "FTGL/FTFont.h"

namespace photon
{
namespace video
{

class FontResource : public Resource
{
public:
    FTFont* font;
};

class FontResourceManager : public ResourceManager<FontResource>
{
public:
    void getFontData(const std::string& name, FTFont*& font);

private:
    virtual void loadResource(FontResource &res,  const std::string& name);
    virtual void freeResource(FontResource &res);
};

}
}

#endif  //PHOTON_VIDEO_FONTRESOURCEMANAGER_HPP
