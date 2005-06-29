//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font.hpp,v 1.1 2005/06/29 04:30:40 cozman Exp $

#ifndef PHOTON_VIDEO_FONT_HPP
#define PHOTON_VIDEO_FONT_HPP

#include "video/FontResourceManager.hpp"
#include "ResourceManaged.hpp"

namespace photon
{
namespace video
{

// Class: Font
//  Simple OO wrapper around a TrueType font that can be drawn to textures and
//  rendered via OpenGL.
// 
//  Since Font is a child of <ResourceManaged>, all memory management is 
//  taken care of.
// 
// Operators:
//  - Font = Font
//  - bool : True if font is loaded, false if not.
//  - ostream& << Font
class Font: public ResourceManaged<FontResourceManager>
{

// Group: (Con/De)structors 
public:


    // Function: Font
    //  Default constructor, initalizes internal state of Font.
    Font();

    // Function: Font
    //  Copy constructor, copies another Font.
    // 
    // Parameters:
    //  rhs - Font to construct copy of.
    Font(const Font &rhs);

    // Function: Font
    // Initializing constructor, loads Font via call to <open>.
    // 
    // Parameters:
    //  name - Name of the Font <Resource> to open.
    // 
    // See Also: 
    //  <open>
    Font(const std::string& name);

// Group: General
public:

    // Function: open
    //  Opens an TrueType font.
    // 
    //  Loading is done via FTGL.
    // 
    // Parameters:
    //  name - Name of the Font <Resource> to open.
    void open(const std::string& name);

    Font& operator=(const Font &rhs);
    operator bool() const;
    
// Group: Writing
public:
    void write(const std::string& str);
    
private:
    FTFont* font_;
};

}
}

#endif  //PHOTON_VIDEO_FONT_HPP
