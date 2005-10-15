//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font.hpp,v 1.8 2005/10/15 04:56:37 cozman Exp $

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
class Font : public ResourceManaged<FontResourceManager>
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

    // Function: drawText
    //  Draw text to screen at a specific position, using an printf-style 
    //  format string.
    //
    // Parameters:
    //  x   - X position to start drawing text at
    //  y   - Y position to start drawing text at.
    //  str - printf-style format string
    //  ... - optional variable arguments referenced in str
    void drawText(scalar x, scalar y, const char *str, ...) const;
    
    // Function: drawText
    //  Draw text to screen at a specific position.
    //
    // Parameters:
    //  x   - X position to start drawing text at
    //  y   - Y position to start drawing text at.
    //  str - Text to draw at specified posiiton.
    void drawText(scalar x, scalar y, const std::string& str) const;

    // Function: beginDraw
    //  Begin drawing of text using C++ style output streams.
    //
    // Parameters:
    //  x   - X position to start drawing text at
    //  y   - Y position to start drawing text at.
    //
    // Returns:
    //  std::ostream& to stream, anything written to the stream before
    //  <endDraw> will be drawn starting at the specified position.
    std::ostream& beginDraw(scalar x, scalar y);
    
    // Function: endDraw
    //  End drawing of text started with <beginDraw>. 
    //  Should be passed to the open beginDraw stream, flushing and writing the
    //  stream to the display.
    StreamFlusher endDraw();

// Group: Font Metrics
public:

    // Function: calcStringWidth
    //  Calculate the width of a string when drawn in the current font.
    //
    // Parameters:
    //  str - String to calculate the width of.
    //
    // Returns:
    //  Width of string (in pixels) when drawn in current font.
    uint calcStringWidth(const std::string& str) const;
    
    // Function: getHeight
    //  Get height of the font, which is essentially equal to the height of the
    //  tallest character plus a font-specified spacing. 
    //
    // Returns:
    //  Height of the loaded font.
    uint getHeight() const;
    
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
    scalar drawX_;
    scalar drawY_;
    // color
    Color color_;
};

}
}

#endif  //PHOTON_VIDEO_FONT_HPP
