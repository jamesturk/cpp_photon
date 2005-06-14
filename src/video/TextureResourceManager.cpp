//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: TextureResourceManager.cpp,v 1.2 2005/06/14 00:28:36 cozman Exp $

#include "video/TextureResourceManager.hpp"

#include "util/FileBuffer.hpp"

#include "GL/gl.h"
#include "corona.h"

namespace photon
{
namespace video
{
    
void TextureResourceManager::setGlobalColorKey(bool enabled, ubyte red, 
                                                ubyte green, ubyte blue)
{
    colorKey_.setColor(red,green,blue,enabled?0:255);
}

void TextureResourceManager::getGlobalColorKey(bool &enabled, ubyte &red, 
                                                ubyte &green, ubyte &blue)
{
    enabled = (colorKey_.alpha == 0);
    red = colorKey_.red;
    green = colorKey_.green;
    blue = colorKey_.blue;
}

void TextureResourceManager::getTextureData(const std::string& name, 
                                            scalar &width, scalar &height, 
                                            uint &texID)
{
    TextureResource resource( getResource(name) );
    width = resource.width;
    height = resource.height;
    texID = resource.texID;
}

void TextureResourceManager::loadResource(TextureResource &res, 
                                            const std::string& path)
{
    corona::Image *image(0);
    util::FileBuffer buf(path);
    corona::File *file;
    
    std::vector<ubyte> data = buf.getData();

    file = corona::CreateMemoryFile((ubyte*)&data[0],data.size());

    if(!file)
    {
        throw ResourceException("corona::CreateMemoryFile failed");
    }
    
    image = corona::OpenImage(file,corona::PF_R8G8B8A8);

    delete file;

    if(!image)
    {
        throw ResourceException("corona::OpenImage failed");
    }

    res.width = image->getWidth();
    res.height = image->getHeight();

    //size to allocate = w*h*4 = size of bitmap * bytes per pixel
    res.pixels = new ubyte[res.width*res.height*4]; 
    std::memcpy(res.pixels,image->getPixels(),res.width*res.height*4);
    delete image;   //no longer need image

    if(colorKey_.alpha == 0)    //ck alpha == 0, means colorkey on
    {
        ubyte r,g,b;
        ubyte *pxl=res.pixels;
        for(uint i=0; i < res.width*res.height; ++i) 
        {
            r = *pxl++;
            g = *pxl++;
            b = *pxl++;
            //set current pixel alpha = 0
            if(r == colorKey_.red && 
                g == colorKey_.green && 
                b == colorKey_.blue)
            {
                *pxl = 0;
            }
            *pxl++;
        }
    }

    glGenTextures(1,&res.texID);
    glBindTexture(GL_TEXTURE_2D,res.texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                        GL_NEAREST_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, res.width, res.height, GL_RGBA, 
                        GL_UNSIGNED_BYTE, res.pixels);
}

void TextureResourceManager::freeResource(TextureResource &res)
{
    if(res.pixels)
    {
        delete []res.pixels;
        res.pixels = 0;
    }
    glDeleteTextures(1, &res.texID);
}



}
}
