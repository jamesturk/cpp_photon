//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Image.hpp,v 1.2 2005/07/18 07:19:48 cozman Exp $

#ifndef PHOTON_VIDEO_IMAGE_HPP
#define PHOTON_VIDEO_IMAGE_HPP

#include "video/Texture.hpp"

namespace photon
{
namespace video
{

// Class: Image
//  Image is a class which is used to store a single image, for use in 2D games.
// 
//  Image is derived from <Texture>, which is a resource managed class.  
//  <Texture> is a simple OO wrapper around the concept of a texture in OpenGL. 
//  An Image simply adds the ability to draw to a quad, as well as some rotation
//  per-vertex tinting, and several other bonuses.
// 
//  Since Image is a child of <ResourceManaged>, all memory management is taken 
//  care of.
// 
// Operators:
//  - Texture = Texture
//  - operator bool
//  - ostream& << Texture
class Image : public Texture
{

// Group: (Con/De)structors
public:
    // Function: Image
    //  Default constructor, initalizes internal state of Image.
    Image();


    // Function: Image
    //  Copy constructor, copies another Image.
    // 
    // Parameters:
    //  rhs - Image to construct copy of.
    Image(const Image &rhs);

    // Function: Image
    //  Initializing constructor, loads Image via call to <open>.
    // 
    // Parameters:
    //   name - Name of the Image <Resource> to open.
    // 
    // See Also: 
    //   <open>
    Image(const std::string& name);

    Image& operator=(const Image &rhs);

// Group: General
public:
    // Function: open
    //  Opens an image file, currently supported image types are BMP, GIF, JPEG,
    //  PCX, PNG, and TGA. (Images can be any dimensions)
    // 
    //  Loading is done via <a href="http://corona.sf.net">Corona</a>.
    // 
    // Parameters:
    //   name - Name of the Image <Resource> to open.
    void open(const std::string& name);

    // Function: setAlpha
    //  Sets alpha-component for Image to be used when surface is drawn.
    // 
    // Parameters:
    //  alpha - Desired surface-wide alpha component for Image.
    void setAlpha(ubyte alpha);

    // Function: flip
    //  Flips image, horizontally and/or vertically.
    // 
    // Parameters:
    //  horizontal - True if a flip over horizontal axis is desired.
    //  vertical - True if a flip over vertical axis is desired.
    void flip(bool horizontal, bool vertical);

    // Function: stretch
    //  Stretch image by a given factor.  
    //  For example: 1 = no change, .5 = 50% current size, 10 = 10 times current
    //  size.
    // 
    // Parameters:
    //  xFactor - Factor for horizontal stretch. 
    //  yFactor - Factor for vertical stretch.
    void stretch(scalar xFactor, scalar yFactor);

    // Function: resize
    //  Resize the image to a specific size.
    // 
    // Parameters:
    //  width - New desired with for image.
    //  height - New desired height for image.
    void resize(scalar width, scalar height);

// Group: Drawing
public:

    // Function: draw
    // draws image to the screen at a givem positon.
    // 
    // Parameters:
    //  x - X position to draw image at.
    //  y - Y position to draw image at.
    void draw(scalar x, scalar y) const;

    // Function: draw
    //  Draw image to screen at given position.
    // 
    //  This version has an extra parameter, a color vertex option.  The 3rd 
    //  parameter is an array of 16 <ubytes> defining,
    //  Starting in the top left corner & going counterclockwise, tint colors 
    //  for the image.  It is possible to make very nice effects with little 
    //  effort via this option.  Things like shading and lighting can be bluffed
    //  using this technique.
    //
    //  There are versions of <drawRotated> and <drawClipped> that have the vc 
    //  parameter which works in the same manner.
    // 
    // Parameters:
    //  x - X position to draw image at.
    //  y - Y position to draw image at.
    //  vc - Array of 16 <ubytes> defining the colors of the 4 vertices in 
    //          clockwise order. (Order: R1,G1,B1,A1,...B4,A4)
    void draw(scalar x, scalar y, ubyte vc[]) const;

    // Function: drawRotated
    //  Draw image, rotated about it's own center by a specified angle.
    // 
    // Parameters:
    //  x - X position to draw image at. (before rotation)
    //  y - Y position to draw image at. (before rotation)
    //  angle - Angle (in degrees) to rotate image.
    void drawRotated(scalar x, scalar y, scalar angle) const;

    // Function: drawRotated
    //  Draw image, rotated about it's own center by a specified angle.
    //  Includes color vertex option.
    // 
    // Parameters:
    //  x - X position to draw image at. (before rotation)
    //  y - Y position to draw image at. (before rotation)
    //  angle - Angle (in degrees) to rotate image.
    //  vc - Array of 16 <ubytes> defining the colors of the 4 vertices in 
    //          clockwise order. (Order: R1,G1,B1,A1,...B4,A4)        
    void drawRotated(scalar x, scalar y, scalar angle, ubyte vc[]) const;

// Group: Accessors
public:

    // Function: getAlpha
    //  Get current surface-wide alpha value for image.
    // 
    // Returns: 
    //  Current surface-wide alpha.
    // 
    // See Also:
    //  <setAlpha>
    ubyte getAlpha() const;

    friend std::ostream& operator<<(std::ostream &o, const Image &rhs);
    
private:
    ubyte alpha_;
    int texMinX_;
    int texMinY_;
    int texMaxX_;
    int texMaxY_;
    scalar width_;
    scalar height_;
};

}
}

#endif //PHOTON_VIDEO_IMAGE_HPP 
