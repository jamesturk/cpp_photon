//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Circle.cpp,v 1.1 2005/02/27 09:00:13 cozman Exp $

#include "math/Circle.hpp"

#include "math/Rect.hpp"
#include "math/math.hpp"

namespace photon
{
namespace math
{

Circle::Circle() :
    radius_(0)
{
}

Circle::Circle(const Point2 &center, scalar radius) :
    center_(center), radius_(std::max(radius,0.))
{
}

Circle::~Circle()
{
}

bool Circle::operator==(const Circle &rhs) const
{
    return center_ == rhs.center_ && scalarCompare(radius_,rhs.radius_);
}

void Circle::moveTo(const Point2 &center)
{
    center_ = center;
}

void Circle::moveRel(scalar xMove, scalar yMove)
{
    center_.x += xMove;
    center_.y += yMove;
}

void Circle::resize(scalar radius)
{
    radius_ = std::max(radius,0.);
}


void Circle::resizeRel(scalar radiusChange)
{
    radius_ += radiusChange;
    radius_ = std::max(radius_,0.);
}

bool Circle::intersects(const Circle &circle) const
{
    return distance(center_,circle.center_) < radius_+circle.radius_;
}

bool Circle::intersects(const Rect &rect) const
{
    scalar newX;
    scalar newY;
    Rect circBound(center_-Vector2(radius_,radius_),2*radius_,2*radius_);

    //reference of rects, 'rect' is shown as rect 5
    //      _____________
    //      |   |   |   |
    //      | 1 | 2 | 3 |
    //      |___|___|___|
    //      |   |   |   |
    //      | 4 | 5 | 6 |
    //      |___|___|___|
    //      |   |   |   |
    //      | 7 | 8 | 9 |
    //      |___|___|___|

    if(rect.intersects(circBound))  //within bounding rect
    {
        if(center_.x < rect.getLeft())   //narrowed down to 1,4,7
            newX = center_.x+radius_;
        else if(center_.x > rect.getRight()) //narrowed down to 3,6,9
            newX = center_.x-radius_;
        else    //narrowed down to 2,5,8
            newX = center_.x;

        if(center_.y < rect.getTop())    //3
            newY = center_.y+radius_;
        else if(center_.y > rect.getBottom())    //9
            newY = center_.y-radius_;
        else
            newY = center_.y;

        if(scalarCompare(newX,center_.x) || 
            scalarCompare(newY,center_.y))  //2,4,5,6,8 
            return true;
        else    //1,3,7,9 
        {
            if(contains(rect.getTopLeft()) || contains(rect.getBottomLeft()) || 
                contains(rect.getTopRight()) || contains(rect.getBottomRight()))
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

bool Circle::contains(const Point2 &point) const
{
    return distance(center_,point) < radius_;
}

Point2 Circle::getCenter() const
{
    return center_;
}

scalar Circle::getRadius() const
{
    return radius_;
}

std::ostream& operator<<(std::ostream &o, const Circle &circle)
{
    return o << "Circle { Center: " << circle.center_ 
                << " Radius: " << circle.radius_ << " }";
}

}
}
