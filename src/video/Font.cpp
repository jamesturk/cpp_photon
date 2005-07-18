//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font.cpp,v 1.6 2005/07/18 07:19:48 cozman Exp $

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
    // a font is a texture, 96 lists, 96 widths, and a height
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
    // valid if texture is created
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

void Font::setColor(const Color& color)
{
    color_ = color;
}

Color Font::getColor() const
{
    return color_;
}

void Font::drawText(scalar x, scalar y, const char *str, ...) const
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

    // push attrib before setting color
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    
    glBindTexture(GL_TEXTURE_2D, texID_);
    glPushMatrix();
    glTranslated(x,y,0);
    for(uint i=0; i < std::strlen(buf); ++i)
    {
        // ch-SPACE = DisplayList offset
        ubyte ch( buf[i] - FontResourceManager::SPACE );     
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
    glPopAttrib();
}

void Font::drawText(scalar x, scalar y, const std::string& str) const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Font::drawText call.");
    }

    // push attrib before setting color 
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    
    glBindTexture(GL_TEXTURE_2D, texID_);
    glPushMatrix();
    glTranslated(x,y,0);
    for(std::string::const_iterator i = str.begin(); i != str.end(); ++i)
    {
        // ch-SPACE = DisplayList offset
        ubyte ch( *i - FontResourceManager::SPACE ); 
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
    glPopAttrib();
}

std::ostream& Font::beginDraw(scalar x, scalar y)
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
    return StreamFlusher(); // special null class that simply outputs nothing
}

uint Font::calcStringWidth(const std::string& str) const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Font::calcStringWidth call.");
    }
    uint width(0);  // accumulator for widths

    // iterate through widths of each char and accumulate width of string
    for(std::string::const_iterator i = str.begin(); i < str.end(); ++i)
    {
        width += widths_[static_cast<uint>(*i) - 
                            FontResourceManager::SPACE];
    }

    return width;
}

uint Font::getHeight() const
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
