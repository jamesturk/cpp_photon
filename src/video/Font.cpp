//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font.cpp,v 1.1 2005/06/29 04:30:40 cozman Exp $

#include "video/Font.hpp"


namespace photon
{
namespace video
{

Font::Font()
{ }

Font::Font(const Font &rhs) :
    ResourceManaged<FontResourceManager>(rhs)
{
    resMgr_.getFontData(getName(), font_);
}

Font::Font(const std::string& name)
{
    open(name);
}

void Font::open(const std::string& name)
{
    ResourceManaged<FontResourceManager>::open(name);
    resMgr_.getFontData(getName(), font_);
}

Font& Font::operator=(const Font &rhs)
{
    if(&rhs != this)
    {
        ResourceManaged<FontResourceManager>::operator=(rhs);
        resMgr_.getFontData(getName(), font_);
    }
    return *this;
}

Font::operator bool() const
{
    return font_ != 0;
}

void Font::write(const std::string& str)
{
    font_->Render(str.c_str());
}

}
}
