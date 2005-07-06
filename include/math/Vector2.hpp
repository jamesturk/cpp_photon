//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Vector2.hpp,v 1.4 2005/07/06 04:27:23 cozman Exp $

#ifndef PHOTON_MATH_VECTOR2_HPP
#define PHOTON_MATH_VECTOR2_HPP

#include <ostream>

#include "types.hpp"

namespace photon
{
namespace math
{

// Class: Vector2
//  Represents a two-dimensional vector.  A quantity specified by a magnitude 
//  and a direction.
// 
// Operators:
//  - Vector2 == Vector2
//  - Vector2 != Vector2
//  - Vector2 + Vector2
//  - Vector2 - Vector2
//  - Vector2 * scalar or scalar * Vector2
//  - Vector2 / scalar
//  - Vector2 += Vector2
//  - Vector2 -= Vector2
//  - Vector2 *= scalar
//  - Vector2 /= scalar
//  - ostream& << Vector2
class Vector2
{

// Group: Data Members
public:
    // Variable: x
    //  x component of vector
    scalar x;
    
    // Variable: y
    //  y component of vector
    scalar y;
    
// Group: (Con/De)structors
public:
    
    // Function: Vector2
    // Initializes zero length vector.
    Vector2();
    
    
    // Function: Vector2
    //  Initialize vector given an x and y component.
    //
    // Parameters:
    //  nx - X component of vector.
    //  ny - Y component of vector.
    // 
    // See Also:
    //  <set>
    Vector2(scalar nx, scalar ny);
    
// Group: General 
public:

    // Function: set
    //  Initialize vector given an x and y component.
    // 
    // Parameters:
    //  nx - X component of vector.
    //  ny - Y component of vector.
    // 
    // See Also:
    //  <set>
    void set(scalar nx, scalar ny);
   
    // Function: resolveDeg
    //  resolve vector, given a magnitude & angle in degrees.
    // 
    // Parameters:
    //  magnitude - Magnitude of new vector.
    //  angle - Angle of new vector, in degrees.
    // 
    // See Also:
    //  <resolveRad>
    void resolveDeg(scalar magnitude, scalar angle);
    
    
    // Function: resolveRad
    //  resolve vector, given a magnitude & angle in radians.
    // 
    // Parameters:
    //  magnitude - Magnitude of new vector.
    //  angle - Angle of new vector, in radians.
    // 
    // See Also:
    //  <resolveDeg>
    void resolveRad(scalar magnitude, scalar angle);
    
    
    // Function: normalize
    //  Normalizes the vector. (makes it length of 1.0 but leaves ratio of 
    //  components intact)
    void normalize();
    
    // Function: dot
    //  Calculates dot product of two vectors.
    // 
    // Parameters:
    //  rhs - Vector to calculate dot product with.
    // 
    // Returns:
    //  Dot product of two vectors.
    scalar dot(const Vector2 &rhs) const;

    bool operator==(const Vector2 &rhs) const;
    bool operator!=(const Vector2 &rhs) const;

    Vector2 operator-() const;
    Vector2 operator+(const Vector2 &rhs) const;
    Vector2 operator-(const Vector2 &rhs) const;
    Vector2 operator*(scalar rhs) const;
    Vector2 operator/(scalar rhs) const;

    Vector2& operator+=(const Vector2 &rhs);
    Vector2& operator-=(const Vector2 &rhs);

// Group: Special Accessors
public:

    // Function: getMagnitude
    //  Get length of vector.
    // 
    // Returns: 
    //  Length of the vector.
    scalar getMagnitude() const;

    // Function: getAngleDeg
    //  Angle of vector in degrees, angle is calculated with respect to positive
    //  X axis.
    // 
    // |               |90�
    // |               |
    // |               |
    // |180�-----------------------0� or 360�
    // |               |
    // |               |
    // |               |270�
    // 
    // Returns: 
    //  Angle of vector (in degrees).
    scalar getAngleDeg() const;
    
    // Function: getAngleRad
    //  Angle of vector in radians, angle is calculated with respect to positive
    //  X axis.
    // 
    // |               | pi/2
    // |               |
    // |               |
    // | pi-----------------------0 or 2pi
    // |               |
    // |               |
    // |               | 3pi/4
    // 
    // Returns:
    //  Angle of vector (in radians).
    scalar getAngleRad() const;

    // Function: calcNormal
    //  Calculate the normal vector.
    // 
    // Returns: 
    //  Normal vector (vector w/ magnitude of 1) but same angle.
    Vector2 calcNormal() const;

    // Function: calcInnerAngleRad
    //  Calculates angle between two vectors.
    // 
    // Parameters:
    //  vec - Vector to calculate angle between.
    // 
    // Returns: 
    //  Angle between the two vectors in radians.
    scalar calcInnerAngleRad(const Vector2 &vec) const;

    // Function: calcInnerAngleDeg
    //  Calculates angle between two vectors.
    // 
    // Parameters:
    //  vec - Vector to calculate angle between.
    // 
    // Returns: 
    //  Angle between the two vectors in degrees.
    scalar calcInnerAngleDeg(const Vector2 &vec) const;

    friend std::ostream& operator<<(std::ostream &o, const Vector2 &v);
};

Vector2 operator*(scalar lhs, const Vector2 &rhs);

// Group: External Utilities

// Function: magnitude
//  Find length of a vector.  
//  Same as a call to v.getMagnitude() but provided for convinience.
// 
// Parameters:
//  v - Vector to calculate magnitude of
//
// Returns: 
//  Length of the vector.
scalar magnitude(const Vector2 &v);

// Function: distance
//  Determine distance between two points.
// 
// Parameters:
//  v1 - First point.
//  v2 - Second point.
// 
// Returns:
//  Scalar distance between the two points.
scalar distance(const Vector2& v1, const Vector2& v2);

// Group: Aliases

// Typedef: Point2
//  Alias for Vector2 type.
typedef Vector2 Point2;

}
}

#endif  //PHOTON_MATH_VECTOR2_HPP
