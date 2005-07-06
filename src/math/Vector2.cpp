//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Vector2.cpp,v 1.2 2005/07/06 04:27:23 cozman Exp $

#include "math/Vector2.hpp"

#include <cmath>

#include "math/math.hpp"

namespace photon
{
namespace math
{

Vector2::Vector2() :
    x(0), y(0)
{
}

Vector2::Vector2(scalar nx, scalar ny) :
    x(nx), y(ny)
{
}

void Vector2::set(scalar nx, scalar ny)
{
    x = nx;
    y = ny;
}

void Vector2::resolveDeg(scalar magnitude, scalar angle)
{
    angle = degToRad(clamp(angle,0,360));
    x = magnitude*std::cos(angle);
    y = magnitude*-std::sin(angle);
}

void Vector2::resolveRad(scalar magnitude, scalar angle)
{
    x = magnitude*std::cos(angle);
    y = magnitude*-std::sin(angle);
}

void Vector2::normalize()
{
    scalar mag = std::sqrt(x*x+y*y);
    if(mag != 0)
    {
        x /= mag;
        y /= mag;
    }
}

scalar Vector2::dot(const Vector2 &rhs) const
{
    return x*rhs.x + y*rhs.y;
}

bool Vector2::operator==(const Vector2 &rhs) const
{
    return scalarCompare(rhs.x,x) && scalarCompare(rhs.y,y);
}

bool Vector2::operator!=(const Vector2 &rhs) const
{
    return !scalarCompare(rhs.x,x) || !scalarCompare(rhs.y,y);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x,-y);
}

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
    return Vector2(x+rhs.x,y+rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &rhs) const
{
    return Vector2(x-rhs.x,y-rhs.y);
}

Vector2 Vector2::operator*(scalar rhs) const
{
    return Vector2(x*rhs,y*rhs);
}

Vector2 Vector2::operator/(scalar rhs) const
{
    return Vector2(x/rhs,y/rhs);
}

Vector2& Vector2::operator+=(const Vector2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

scalar Vector2::getMagnitude() const
{
    return std::sqrt(x*x+y*y);
}

scalar Vector2::getAngleDeg() const
{
    return radToDeg(std::atan2(y,x));
}

scalar Vector2::getAngleRad() const
{
    return std::atan2(y,x);
}

Vector2 Vector2::calcNormal() const
{
    scalar mag = std::sqrt(x*x+y*y);
    return Vector2(x/mag,y/mag);
}

scalar Vector2::calcInnerAngleRad(const Vector2 &rhs) const
{
    //                 Ux*Vx+Uy*Vy
    // theta =  arccos(-----------)
    //                   |U|*|V|  
    return std::acos((rhs.x*x+rhs.y*y)/(rhs.getMagnitude()*getMagnitude()));
}

scalar Vector2::calcInnerAngleDeg(const Vector2 &rhs) const
{
    return radToDeg(calcInnerAngleRad(rhs));
}

//non-members

std::ostream& operator<<(std::ostream &o, const Vector2 &v)
{
    return o << "(" << v.x << "," << v.y << ")";
}

Vector2 operator*(scalar lhs, const Vector2 &rhs)
{
    return Vector2(rhs.x*lhs,rhs.y*lhs);
}

scalar magnitude(const Vector2 &v)
{
    return v.getMagnitude();
}

scalar distance(const Vector2& v1, const Vector2& v2)
{
    return magnitude(v1-v2);
}

}
}
