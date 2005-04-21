//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Color.cpp,v 1.2 2005/04/21 19:30:19 cozman Exp $

#include "video/Color.hpp"
#include "GL/gl.h"

namespace photon
{
namespace video
{

Color::Color() :
    red(255), green(255), blue(255), alpha(255)
{
}

Color::Color(ubyte r, ubyte g, ubyte b, ubyte a) :
    red(r), green(g), blue(b), alpha(a)
{
}

void Color::setColor(ubyte r, ubyte g, ubyte b, ubyte a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

void Color::makeGLColor() const
{
    glColor4ub(red,green,blue,alpha);
}

std::ostream& operator<<(std::ostream &o, const Color &rhs)
{
    // cast all colors to integers (internal representation is char)
    return o << "Color {" 
        << " Red: " << static_cast<int>(rhs.red)
        << " Green: " << static_cast<int>(rhs.green)
        << " Blue: " << static_cast<int>(rhs.blue)
        << " Alpha: " << static_cast<int>(rhs.alpha)
        << " }";
}

}
}

