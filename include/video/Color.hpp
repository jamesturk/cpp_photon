//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Color.hpp,v 1.1 2005/03/02 08:40:11 cozman Exp $

#ifndef PHOTON_VIDEO_COLOR_HPP
#define PHOTON_VIDEO_COLOR_HPP

#include <ostream>

#include "types.hpp"

namespace photon
{
namespace video
{

// Class: Color
// Class for storing components of a color.
// 
// Operators:
//     - ostream& << Color
class Color
{
//  Group: Variables 
public:
    // Variable: red
    //  Red component of color. (0-255)
    ubyte red;

    // Variable: green
    //  Green component of color. (0-255)
    ubyte green;

    // Variable: blue
    //  Blue component of color. (0-255)
    ubyte blue;

    // Variable: alpha
    //  Alpha component of color. (0-255)
    ubyte alpha;

//  Group: (Con/De)structors
public:
    // Function: Color
    //  Initializes all components to 255. (Solid White)
    Color();

    // Function: Color
    //  Initializes color, component by component.
    // 
    // Parameters:
    //  r - Value for red component.
    //  g - Value for green component.
    //  b - Value for blue component.
    //  a - Value for alpha component. [default: 255]
    // 
    // See Also:
    //  <setColor>
    Color(ubyte r, ubyte g, ubyte b, ubyte a=255);

// Group: Utility
public:
    // Functions: setColor
    //  Creates color, component by component.
    // 
    // Parameters:
    //  r - Value for red component.
    //  g - Value for green component.
    //  b - Value for blue component.
    //  a - Value for alpha component. [default: 255]
    void setColor(ubyte r, ubyte g, ubyte b, ubyte a=255);

    // Functions: makeGLColor
    //  Makes the Color the current openGL color.  (glColor4ub)
    void makeGLColor() const;

    friend std::ostream& operator<<(std::ostream &o, const Color &rhs);
};

}
}

#endif  //PHOTON_VIDEO_COLOR_HPP
