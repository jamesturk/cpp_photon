//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Rect.hpp,v 1.2 2005/03/03 09:25:19 cozman Exp $

#ifndef PHOTON_MATH_RECT_HPP
#define PHOTON_MATH_RECT_HPP

#include "math/Vector2.hpp"

namespace photon
{
namespace math
{
    
class Circle;

// Class: Rect
//  Defines geometric entity known as a rectangle.
// 
//  A four-sided plane figure with four right angles. <http://dictionary.com>
// 
// Operators:
//  - Rect == Rect
//  - ostream& << Rect
class Rect
{
// Group: (Con/De)structors
public:

    // Function: Rect
    //  Initializes rectangle at (0,0) with size of 0.
    Rect();
    
    // Function: Rect
    //  Initializing constructor, creates rectangle from top left point, 
    //  width and height.
    //  
    // Parameters:
    //  topleft - Point describing top left corner.
    //  width - Width of new rectangle.
    //  height - Height of new rectangle.
    Rect(const Point2 &topleft, scalar width, scalar height);
    
    // Function: Rect
    //  Initializing constructor, creates from top left and bottom right points.
    //  
    // Parameters:
    //  topleft - Point describing top left corner.
    //  bottomright - Point describing bottom right corner.
    Rect(const Point2 &topleft, const Point2 &bottomright);
    
    // Function: ~Rect
    //  Default destructor, exists to make Rect inheritance safe.
    virtual ~Rect();

bool operator==(const Rect &rhs) const;

// Group: Movement/Scaling 
public:

    // Function: moveTo
    //  move rectangle to new location.
    //  
    // Parameters:
    //  topleft - Point describing new top left corner.
    void moveTo(const Point2 &topleft);
    
    // Function: moveRel
    //  move rectangle relative to current position.
    //  
    // Parameters:
    //  xMove - Distance to move horizontally.
    //  yMove - Distance to move vertically.
    void moveRel(scalar xMove, scalar yMove);
    
    // Function: resize
    //  set new size for rectangle.
    //  
    // Parameters:
    //  width - New width for rectangle.
    //  height - New height for rectangle.
    void resize(scalar width, scalar height);
    
    // Function: resizeRel
    //  set new size for rectangle, relative to current size.
    //  
    // Parameters:
    //  widthDelta - Change to be applied to width of rectangle.
    //  heightDelta - Change to be applied to height of rectangle.
    void resizeRel(scalar widthDelta, scalar heightDelta);

// Group: Geometry
public:

    // Function: intersects
    //  Check for intersection between two <Rects>.
    // 
    // Parameters:
    //  rect - <Rect> with which to check for intersection.
    // 
    // Returns:
    //  True if Rect intersects rect, false otherwise.
    bool intersects(const Rect &rect) const;
    
    // Function: intersects
    //  Check for intersection between the <Rect> and <Circle>.
    // 
    // Parameters:
    //  circle - <Circle> with which to check for intersection.
    // 
    // Returns:
    //  True if Rect intersects circle, false otherwise.
    bool intersects(const Circle &circle) const;
    
    // Function: contains
    //  Check if a point is contained within the Rect.
    // 
    // Parameters:
    //  point - Point to check containment of.
    // 
    // Returns:
    //  True if Rect contains point, false if not.
    bool contains(const Point2 &point) const;
    
    // Function: contains
    //  Check if another rectangle is entirely contained within the Rect.
    // 
    // Parameters:
    //  rect - <Rect> to check if the Rect contains.
    // 
    // Returns:
    //  True if rect is entirely contained within, false if all or part is 
    //  outside.
    bool contains(const Rect &rect) const;
    
    // Function: calcIntersection
    //  calculates & returns the intersection of two rectangles.
    // 
    // Parameters:
    //  rect - Rectangle to find & calculate area of intersection with.
    // 
    // Returns:
    //  Rectangle defining area of intersection between the two rectangles.  
    // 
    //  If <intersects> is false, the rectangle will have a width & height of 
    //  zero.
    Rect calcIntersection(const Rect &rect) const;

// Group: Accessors
public:

    // Function: getX
    //  Get x coord of rectangle. (top left corner)
    // 
    // Returns:
    //  Returns x coord of top left corner of rectangle.
    scalar getX() const;
    
    // Function: getY
    //  Get y coord of rectangle. (top left corner)
    // 
    // Returns:
    //  Returns y coord of top left corner of rectangle.
    scalar getY() const;
    
    // Function: getTop
    //  Get y coord of top side of rectangle.
    // 
    // Returns:
    //  Returns y coord of top side of rectangle.
    scalar getTop() const;
    
    // Function: getLeft
    //  Get x coord of left side of rectangle.
    // 
    // Returns:
    //  Returns x coord of left side rectangle.  
    scalar getLeft() const;
    
    // Function: getBottom
    //  Get y coord of bottom side of rectangle.
    // 
    // Returns:
    //  Returns y coord of bottom side of rectangle.
    scalar getBottom() const;
    
    // Function: getRight
    //  Get x coord of right side of rectangle.
    // 
    // Returns:
    //  Returns x coord of right side rectangle.
    scalar getRight() const;
    
    // Function: getWidth
    //  Get width of rectangle.
    // 
    // Returns:
    //  Returns width of rectangle.
    scalar getWidth() const;
    
    // Function: getHeight
    //  Get height of rectangle.
    // 
    // Returns:
    //  Height of rectangle.
    scalar getHeight() const;
    
    // Function: getTopLeft
    //  Get top left corner of rectangle.
    // 
    // Returns: 
    //  Top left corner of rectangle.
    Point2 getTopLeft() const;
    
    // Function: getTopRight
    //  Get top right corner of rectangle.
    // 
    // Returns: 
    //  Top right corner of rectangle.
    Point2 getTopRight() const;
    
    // Function: getBottomLeft
    //  Get bottom left corner of rectangle.
    // 
    // Returns: 
    //  Bottom left corner of rectangle.
    Point2 getBottomLeft() const;
    
    // Function: getBottomRight
    //  Get bottom right corner of rectangle.
    // 
    // Returns: 
    //  Bottom right corner of rectangle.
    Point2 getBottomRight() const;

    friend std::ostream& operator<<(std::ostream &o, const Rect &rect);

private:
    Point2 topLeft_;
    Point2 bottomRight_;
};

}
}

#endif  //PHOTON_MATH_RECT_HPP
