//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: math.cpp,v 1.1 2005/02/27 09:00:13 cozman Exp $

#include "math/math.hpp"

#include "math/Vector2.hpp"

namespace photon
{
namespace math
{
    
bool scalarCompare(scalar val1, scalar val2, scalar epsilon)
{
    return std::fabs(val1-val2) < epsilon;
}

scalar distance(Vector2 v1, Vector2 v2)
{
    return magnitude(v1-v2);
}

scalar degToRad(scalar degrees)
{
    const scalar convFactor(0.0174532925);  //pi/180
    return degrees * convFactor;
}

scalar radToDeg(scalar radians)
{
    const scalar convFactor(57.2957795);    //180/pi
    return radians * convFactor;
}

}
}
