//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Rect.cpp,v 1.1 2005/02/27 09:00:13 cozman Exp $

#include "math/Rect.hpp"

#include <algorithm>

namespace photon
{
namespace math
{

Rect::Rect()
{
}

Rect::Rect(const Point2 &topleft, scalar width, scalar height) :
    topLeft_(topleft),
    bottomRight_(topleft.x+std::max(width,0.),topleft.y+std::max(height,0.))
{
}

Rect::Rect(const Point2 &topleft, const Point2 &bottomright) :
    topLeft_(topleft),bottomRight_(bottomright)
{
}

Rect::~Rect()
{
}

bool Rect::operator==(const Rect &rhs) const
{
    return topLeft_ == rhs.topLeft_ && bottomRight_ == rhs.bottomRight_;
}

void Rect::moveTo(const Point2 &topleft)
{
    bottomRight_ += (topleft-topLeft_);
    topLeft_ = topleft;

}

void Rect::moveRel(scalar xMove, scalar yMove)
{
    topLeft_.x += xMove;
    topLeft_.y += yMove;
    bottomRight_.x += xMove;
    bottomRight_.y += yMove;
}

void Rect::resize(scalar width, scalar height)
{
    bottomRight_.x = topLeft_.x+std::max(width,0.);
    bottomRight_.y = topLeft_.y+std::max(height,0.);
}

void Rect::resizeRel(scalar widthDelta, scalar heightDelta)
{
    bottomRight_.x += widthDelta;
    bottomRight_.y += heightDelta;
}

bool Rect::intersects(const Rect &rect) const
{
    return !(topLeft_.x > rect.bottomRight_.x || 
            rect.topLeft_.x > bottomRight_.x ||
            topLeft_.y > rect.bottomRight_.y || 
            rect.topLeft_.y > bottomRight_.y);
}

bool Rect::contains(const Point2 &point) const
{
    return point.x > topLeft_.x && point.x < bottomRight_.x && 
            point.y > topLeft_.y && point.y < bottomRight_.y;
}

bool Rect::contains(const Rect &rect) const
{
    return rect.topLeft_.x > topLeft_.x && 
            rect.bottomRight_.x < bottomRight_.x && 
            rect.topLeft_.y > topLeft_.y && 
            bottomRight_.y < bottomRight_.y;
}

Rect Rect::calcIntersection(const Rect &rect) const
{
    Rect temp;

    //can only grab the intersection if they intersect
    if(intersects(rect))
    {
        temp.topLeft_.x = std::max(topLeft_.x,rect.topLeft_.x);
        temp.topLeft_.y = std::max(topLeft_.y,rect.topLeft_.y);
        temp.bottomRight_.x = std::min(bottomRight_.x,rect.bottomRight_.x);
        temp.bottomRight_.y = std::min(bottomRight_.y,rect.bottomRight_.y);
    }

    return temp;
}

scalar Rect::getX() const
{
    return topLeft_.x;
}

scalar Rect::getY() const
{
    return topLeft_.y;
}

scalar Rect::getTop() const
{
    return topLeft_.y;
}

scalar Rect::getLeft() const
{
    return topLeft_.x;
}

scalar Rect::getBottom() const
{
    return bottomRight_.y;
}

scalar Rect::getRight() const
{
    return bottomRight_.x;
}

scalar Rect::getWidth() const
{
    return bottomRight_.x-topLeft_.x;
}

scalar Rect::getHeight() const
{
    return bottomRight_.y-topLeft_.y;
}

Point2 Rect::getTopLeft() const
{
    return topLeft_;
}

Point2 Rect::getTopRight() const
{
    return Point2(bottomRight_.x,topLeft_.y);
}

Point2 Rect::getBottomLeft() const
{
    return Point2(topLeft_.x,bottomRight_.y);
}

Point2 Rect::getBottomRight() const
{
    return bottomRight_;
}

std::ostream& operator<<(std::ostream &o, const Rect &rect)
{
    return o << "Rect { Top left: " << rect.topLeft_ 
                    << " Width: " << rect.getWidth() 
                    << " Height: " << rect.getHeight() << " }";
}

}
}
