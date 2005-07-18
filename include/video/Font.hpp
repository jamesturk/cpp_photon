//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font.hpp,v 1.6 2005/07/18 05:14:18 cozman Exp $

#ifndef PHOTON_VIDEO_FONT_HPP
#define PHOTON_VIDEO_FONT_HPP

#include "video/FontResourceManager.hpp"
#include "ResourceManaged.hpp"
#include "video/Color.hpp"

namespace photon
{
namespace video
{

class StreamFlusher { };
std::ostream& operator<<(std::ostream& os, const StreamFlusher& rhs);

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
    //  Loading is done via FreeType.
    // 
    // Parameters:
    //  name - Name of the Font <Resource> to open.
    void open(const std::string& name);
    
    // Function: isValid
    //  Determine status of Font.
    //
    // Returns:
    //  True if font is loaded, false if font is not loaded/initialized.
    bool isValid() const;

    Font& operator=(const Font &rhs);
    operator bool() const;
    
// Group: Coloring
public:
    // Function: setColor
    //  Set draw color of the font.
    //
    // Parameters:
    //  color - <Color> to shade font glyphs when drawn.
    void setColor(const Color& color);
    
    // Function: getColor
    //  Get draw color of the font.
    //
    // Returns:
    //  Currently set <Color> to shade font glyphs when drawn.
    Color getColor() const;
    
// Group: Drawing
public:
    void drawText(float x, float y, const char *str, ...) const;
    void drawText(float x, float y, const std::string& str) const;

    std::ostream& beginDraw(float x, float y);
    StreamFlusher endDraw();

// Group: Font Metrics
public:
    unsigned int calcStringWidth(const std::string& str) const;
    unsigned int getHeight() const;
    
// Group: Resource Creation
public:
    // Function: addResource
    //  Define a new named resource.
    //  (Ex. Image::addResource("monkey","images/monkey.png") would 
    //   make it so that any attempts to load "monkey" would load the image 
    //   images/monkey.png)
    //
    // Parameters:
    //  name - Name to give to resource.
    //  path - Path of resource data file.
    static void addResource(const std::string& name, const std::string& path, 
                            uint size);
    
    // Function: addResource
    //  Define a new unaliased resource. (name == path).
    //  (Ex. Image::addResource("images/monkey.png") is essentially the same as
    //   Image::addResource("images/monkey.png","images/monkey.png")
    //
    // Parameters:.
    //  path - Path of resource data file.
    static void addResource(const std::string& path, uint size);
    
private:
    // font data
    uint texID_;
    uint listBase_;
    std::vector<ubyte> widths_;
    ubyte height_;
    // stream drawing stuff
    std::ostringstream ss_;
    float drawX_;
    float drawY_;
    // color
    Color color_;
};

}
}

#endif  //PHOTON_VIDEO_FONT_HPP
