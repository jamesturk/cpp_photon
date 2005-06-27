//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Texture.cpp,v 1.3 2005/06/27 04:24:16 cozman Exp $

#include "video/Texture.hpp"

#include "GL/gl.h"

namespace photon
{
namespace video
{

Texture::Texture()
{ }

Texture::Texture(const Texture &rhs) :
    ResourceManaged<TextureResourceManager>(rhs)
{
    resMgr_.getTextureData(getName(), width_, height_, texID_);
}

Texture::Texture(const std::string& name)
{
    open(name);
}

void Texture::open(const std::string& name)
{
    ResourceManaged<TextureResourceManager>::open(name);
    resMgr_.getTextureData(getName(), width_, height_, texID_);
}

void Texture::bind() const
{
    if(glIsTexture(texID_) == GL_FALSE)
    {
        throw PreconditionException("Texture::bind call without valid image.");
    }
    glBindTexture(GL_TEXTURE_2D, texID_);
}

Texture& Texture::operator=(const Texture &rhs)
{
    if(&rhs != this)
    {
        ResourceManaged<TextureResourceManager>::operator=(rhs);
        resMgr_.getTextureData(getName(), width_, height_, texID_);

        //w&h after getTextureData
        width_ = rhs.width_;
        height_ = rhs.height_;
    }
    return *this;
}

Texture::operator bool() const
{
    return glIsTexture(texID_) == GL_TRUE;
}

scalar Texture::getWidth() const
{
    return width_;
}

scalar Texture::getHeight() const
{
    return height_;
}

std::ostream& operator<<(std::ostream &o, const Texture &rhs)
{
    return o << "Texture: { Name: " << rhs.getName() << " TexID: " << rhs.texID_
        << " Dimensions: " << rhs.width_ << "x" << rhs.height_ << " }";
}

}
}
