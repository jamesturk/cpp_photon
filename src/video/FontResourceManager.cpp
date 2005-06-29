//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FontResourceManager.cpp,v 1.1 2005/06/29 04:30:40 cozman Exp $

#include "video/FontResourceManager.hpp"

#include "util/FileBuffer.hpp"

#include "FTGL/FTGLTextureFont.h"


namespace photon
{
namespace video
{
    
void FontResourceManager::getFontData(const std::string& name, FTFont*& font)
{
    FontResource resource( getResource(name) );
    font = resource.font;
}

void FontResourceManager::loadResource(FontResource &res, 
                                            const std::string& path)
{
    util::FileBuffer buf(path);
    
    std::vector<ubyte> data = buf.getData();

    //res.font = new FTGLTextureFont((ubyte*)&data[0],data.size());
    res.font = new FTGLTextureFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf");

    if(!res.font || res.font->Error() != 0)
    {
        throw APIError("Failed to create FTGLTextureFont");
    }
    
    assert( res.font->FaceSize(6) );
}

void FontResourceManager::freeResource(FontResource &res)
{
    delete res.font;
}

}
}
