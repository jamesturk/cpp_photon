//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font.cpp,v 1.4 2005/07/04 03:06:48 cozman Exp $

#include "video/Font.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdarg>
#include <sstream>

namespace photon
{
namespace video
{
    
std::ostream& operator<<(std::ostream& os, const StreamFlusher& rhs)
{
    return os.flush();
}

Font::Font() :
    texID_(0), listBase_(0),    // initalize GL variables to zero
    widths_(FontResourceManager::NUM_CHARS),    // make room for 96 widths
    height_(0), drawX_(0), drawY_(0)
{
}

Font::Font(const Font &rhs) :
    ResourceManaged<FontResourceManager>(rhs),
    drawX_(0), drawY_(0)
{
    resMgr_.getFontData(getName(), texID_, listBase_, widths_, height_);
}

Font::Font(const std::string& name) :
    drawX_(0), drawY_(0)
{
    open(name);
}

void Font::open(const std::string& name)
{
    ResourceManaged<FontResourceManager>::open(name);
    resMgr_.getFontData(getName(), texID_, listBase_, widths_, height_);
}

bool Font::isValid() const
{
    return glIsTexture(texID_) == GL_TRUE;
}

Font& Font::operator=(const Font &rhs)
{
    if(&rhs != this)
    {
        ResourceManaged<FontResourceManager>::operator=(rhs);
        resMgr_.getFontData(getName(), texID_, listBase_, widths_, height_);
    }
    return *this;
}

Font::operator bool() const
{
    return isValid();
}

void Font::drawText(float x, float y, const char *str, ...) const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Font::drawText call.");
    }

    std::va_list args;
    char buf[1024];

    va_start(args,str);
    std::vsnprintf(buf, 1024, str, args);   // avoid buffer overflow
    va_end(args);

    glBindTexture(GL_TEXTURE_2D, texID_);
    glPushMatrix();
    glTranslated(x,y,0);
    for(unsigned int i=0; i < std::strlen(buf); ++i)
    {
        // ch-SPACE = DisplayList offset
        unsigned char ch( buf[i] - FontResourceManager::SPACE );     
        // replace characters outside the valid range with undrawable
        if(ch > FontResourceManager::NUM_CHARS)
        {
            // last character is 'undrawable'
            ch = FontResourceManager::NUM_CHARS-1;   
        }
        glCallList(listBase_+ch);    // calculate list to call
    }

    // Alternative, ignores undrawables (no noticable speed difference)
    //glListBase(listBase_-32);
    //glCallLists(static_cast<int>(std::strlen(buf)), GL_UNSIGNED_BYTE, buf);

    glPopMatrix();
}

void Font::drawText(float x, float y, const std::string& str) const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Font::drawText call.");
    }

    glBindTexture(GL_TEXTURE_2D, texID_);
    glPushMatrix();
    glTranslated(x,y,0);
    for(std::string::const_iterator i = str.begin(); i != str.end(); ++i)
    {
        // ch-SPACE = DisplayList offset
        unsigned char ch( *i - FontResourceManager::SPACE ); 
        // replace characters outside the valid range with undrawable
        if(ch > FontResourceManager::NUM_CHARS)
        {
            // last character is 'undrawable'
            ch = FontResourceManager::NUM_CHARS-1;   
        }
        glCallList(listBase_+ch);    // calculate list to call
    }

    // Alternative, ignores undrawables (no noticable speed difference)
    //glListBase(listBase_-32);
    //glCallLists(static_cast<int>(std::strlen(buf)), GL_UNSIGNED_BYTE, buf);

    glPopMatrix();
}

std::ostream& Font::beginDraw(float x, float y)
{
    // clear the string and store the draw-position
    ss_.str("");
    drawX_ = x;
    drawY_ = y;
    return ss_;
}

StreamFlusher Font::endDraw() 
{
    drawText(drawX_, drawY_, ss_.str());    // draw the string
    ss_.str("");                            // clear the buffer
    return StreamFlusher();
}

unsigned int Font::calcStringWidth(const std::string& str) const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Font::calcStringWidth call.");
    }
    unsigned int width=0;

    // iterate through widths of each char and accumulate width of string
    for(std::string::const_iterator i = str.begin(); i < str.end(); ++i)
    {
        width += widths_[static_cast<unsigned int>(*i) - 
                            FontResourceManager::SPACE];
    }

    return width;
}

unsigned int Font::getHeight() const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Font::getHeight call.");
    }
    return height_;
}

void Font::addResource(const std::string& name, const std::string& path, 
                        uint size)
{
    resMgr_.newResource(name, FontResourceDescriptor(path, size));
}

void Font::addResource(const std::string& path, uint size)
{
    resMgr_.newResource(path, FontResourceDescriptor(path, size));
}

}
}
