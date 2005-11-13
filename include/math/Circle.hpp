//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Circle.hpp,v 1.4 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_MATH_CIRCLE_HPP
#define PHOTON_MATH_CIRCLE_HPP

#include "math/Vector2.hpp"

namespace photon
{
namespace math
{

class Rect;

// Class: Circle
//  Defines geometric entity known as a circle.
// 
//  A plane curve everywhere equidistant from a given fixed point, the center. 
//  (<http://dictionary.com>)
//
//  Exists mainly to provide a bounding circle for objects, simplifying 
//  collision detection.
// 
// Operators:
//  - Circle == Circle
//  - ostream& << 
class Circle
{
// Group: (Con/De)structors
public:  
    // Function: Circle
    //  Default constructor for circle, sets position to (0,0) and radius to 0.
    Circle();
       
    // Function: Circle
    // Constructs circle with a given radius and center point.
    // 
    // Parameters:
    //  center - Center point for circle.
    //  radius - Radius of circle.
    Circle(const Point2 &center, scalar radius);
    
    // Function: ~Circle
    //  Destructor, does nothing, exists to make Circle inheritance safe.
    virtual ~Circle();

    bool operator==(const Circle &rhs) const;

// Group: Movement/Scaling
public:
    // Function: moveTo
    //  Move the center of the Circle to a new location.
    // 
    // Parameters: 
    //  center - New center for circle.
    void moveTo(const Point2 &center);
    
    // Function: moveRel
    //  Move the center of the Circle a given x and y distance.
    // 
    // Parameters:
    //  xMove - The amount to move in the x direction.
    //  yMove - The amount to move in the y direction.
    void moveRel(scalar xMove, scalar yMove);
    
    // Function: resize
    //  Change the size of the Circle.
    // 
    // Parameters:
    //  radius - The new radius for the Circle.
    void resize(scalar radius);
    
    // Function: resizeRel
    //  Change the size of the Circle in relation to the current size.
    // 
    // Parameters:
    //  radiusChange - The change to apply to the radius.
    void resizeRel(scalar radiusChange);

// Group: Geometry 
public:
    // Function: intersects
    //  Check if circle intersects another.
    // 
    // Parameters:
    //  circle - Circle to check for intersection with.
    // 
    // Returns:
    //  True if the circles intersect, false otherwise.
    bool intersects(const Circle &circle) const;
    
    // Function: intersects
    //  Check if circle intersects rectangle.
    // 
    // Parameters:
    //  rect - Rectangle to check for intersection with.
    // 
    // Returns:
    //  True if circle/rect intersect, false otherwise. 
    bool intersects(const Rect &rect) const;
    
    // Function: contains
    //  Check if circle contains a given point.
    // 
    // Parameters:
    //  point - Point to check for containment of.
    // 
    // Returns:
    //  True if circle contains point, false otherwise.  
    bool contains(const Point2 &point) const;
     
// Group: Accessors
public:    
    // Function: getCenter
    //  Get center <Vector2::Point2>.
    Point2 getCenter() const;
    
    // Function: getRadius
    //  Get radius of Circle.
    scalar getRadius() const;
    
    friend std::ostream& operator<<(std::ostream &o, const Circle &circle);

// Data members
private:
    Point2 center_;
    scalar radius_;
};

}
}

#endif  //PHOTON_MATH_CIRCLE_HPP
