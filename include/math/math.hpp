//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: math.hpp,v 1.2 2005/03/01 07:51:23 cozman Exp $

#ifndef PHOTON_MATH_MATH_HPP
#define PHOTON_MATH_MATH_HPP

#include <cmath>

#include "types.hpp"

namespace photon
{
namespace math
{

class Vector2;

// Title: Math Utilities

// Group: Generic

// Function: clamp
//  Clamp a value between two boundaries.
//
// Parameters:
//  val  - value to clamp
//  low  - lower boundary 
//  high - upper boundary
//
// Returns:
//  low if val < low, high if val > high, val otherwise
template<typename T, typename C>
T clamp(T val, C low, C high);

// Function: scalarCompare
//  Check for equality, using an epsilon.
// 
// Parameters:
//  val1 - First value to compare.
//  val2 - Second value to compare.
//  epsilon - Epsilon value, defaults to 0.0001.
// 
// Returns:
//  true if |val1-val2| < epsilon
bool scalarCompare(scalar val1, scalar val2, scalar epsilon=0.000001);

// Function: distance
//  Determine distance between two points.
// 
// Parameters:
//  v1 - First point.
//  v2 - Second point.
// 
// Returns:
//  Scalar distance between the two points.
scalar distance(Vector2 v1, Vector2 v2);

// Group: Degrees/Radians

// Function: degToRad
//  Convert degrees to radians.
// 
// Parameters:
//  degrees - Degree value to convert to radians.
// 
// Returns: 
//  Radian equivalent of 'degrees'.
scalar degToRad(scalar degrees);

// Function: radToDeg
//  Convert radians to degrees.
// 
// Parameters:
//  radians - Radian value to convert to degrees.
// 
// Returns: 
//  Degree equivalent of 'radians'
scalar radToDeg(scalar radians);

//template implementation

template<typename T, typename C>
T clamp(T val, C low, C high)
{
    if(val < low)
        return low;
    else if(val > high)
        return high;
    else 
        return val;
}

}
}

#endif  //PHOTON_MATH_MATH_HPP
