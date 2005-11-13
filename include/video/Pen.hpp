//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Pen.hpp,v 1.5 2005/11/13 07:59:49 cozman Exp $

#ifndef PHOTON_VIDEO_PEN_HPP
#define PHOTON_VIDEO_PEN_HPP

#include "types.hpp"
#include "video/Color.hpp"
#include "math/Rect.hpp"
#include "math/Vector2.hpp"
#include "math/Circle.hpp"

namespace photon
{
namespace video
{

// Class: Pen
//  Class which is used for drawing primitives.
//
//  Each instance of pen has a color, and the various members simply draw 
//  primitives in that color.  Since it is possible to change the color 
//  associated with a pen, there is often no need for multiple instances of Pen.
class Pen
{

// Group: (Con/De)structors 
public:
    // Function: Pen
    //  Default constructor, sets color to white.
    Pen();
    
    // Function: Pen
    //  Initializing constructor, takes components of color to use for drawing.
    // 
    // Parameters:
    //  r - Value for red component.
    //  g - Value for green component.
    //  b - Value for blue component.
    //  a - Value for alpha component. [default: 255]
    // 
    // See Also:
    //  <setColor>
    Pen(ubyte r, ubyte g, ubyte b, ubyte a=255);
    
    // Function: Pen
    //  Initializing constructor, takes <Color> to use for drawing..
    // 
    // Parameters:
    //  color - <Color> to use for drawing.
    // 
    // See Also:
    //  <setColor>
    Pen(const Color& color);

// Group: Color 
public:
    // Function: setColor
    //  Sets color to use for drawing.
    // 
    // Parameters:
    //  r - Value for red component.
    //  g - Value for green component.
    //  b - Value for blue component.
    //  a - Value for alpha component. [default: 255]
    void setColor(ubyte r, ubyte g, ubyte b, ubyte a=255);

    // Function: setColor
    //  Sets color to use for drawing.
    // 
    // Parameters:
    //  color - <Color> to use for drawing.
    void setColor(const Color& color);

// Group: Drawing 
public:
    // Function: drawPoint
    //  Draws a single point.
    // 
    // Parameters:
    //  point - Point to draw.
    void drawPoint(const math::Point2& point) const;
    
    // Function: drawLine
    //  Draw a line from one point to another.
    // 
    // Parameters:
    //  p1 - First endpoint of line.
    //  p2 - Second endpoint of line.
    void drawLine(const math::Point2& p1, const math::Point2& p2) const;
    
    // Function: drawVector
    //  Draw a vector, including small arrow, with base at a given point.
    // 
    // Parameters:
    //  point - Base point for vector.
    //  vector - Vector to draw.
    void drawVector(const math::Point2& point, 
                    const math::Vector2& vector) const;
    
    // Function: drawRect
    //  Draw an empty rectangle.
    // 
    // Parameters:
    //  rect - <Rect> to draw.
    void drawRect(const math::Rect &rect) const;
    
    // Function: fillRect
    //  Draw a filled rectangle.
    // 
    // Parameters:
    //  rect - <Rect> to draw.
    void fillRect(const math::Rect &rect) const;
    
    // Function: drawCircle
    //  Draw an empty circle.
    // 
    // Parameters:
    //  circle - <Circle> to draw.
    void drawCircle(const math::Circle &circle) const;
    
    // Function: fillCircle
    //  Draw a filled circle.
    // 
    // Parameters:
    //  circle - <Circle> to draw.
    void fillCircle(const math::Circle &circle) const;

// data members
private:
    Color color_;
    
    // 30 seems to be an even tradeoff between speed and roundness
    static const int CIRCLE_RESOLUTION = 30;    
};

}
}

#endif  //PHOTON_VIDEO_PEN_HPP
