//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Pen.cpp,v 1.1 2005/03/02 10:55:29 cozman Exp $

#include "video/Pen.hpp"

#include "gl/gl.h"

#include "math/math.hpp"

namespace photon
{
namespace video
{

Pen::Pen() : 
    color_(255,255,255,255)
{
}

Pen::Pen(ubyte r, ubyte g, ubyte b, ubyte a) :
    color_(r,g,b,a)
{
}

Pen::Pen(Color color) :
    color_(color)
{
}

void Pen::setColor(ubyte r, ubyte g, ubyte b, ubyte a)
{
    color_.setColor(r,g,b,a);
}

void Pen::setColor(Color color)
{
    color_ = color;
}

void Pen::drawPoint(math::Point2 point) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_POINTS);
    glVertex2d(point.x,point.y);
    glEnd();
    glColor4ub(255,255,255,255);
}

void Pen::drawLine(math::Point2 p1, math::Point2 p2) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_LINES);
    glVertex2d(p1.x,p1.y);
    glVertex2d(p2.x,p2.y);
    glEnd();
    glColor4ub(255,255,255,255);
}

void Pen::drawVector(math::Point2 point, math::Vector2 vector) const
{
    double x2,y2,x3,y3,x4,y4;
    math::Vector2 v;
    x2 = point.x+vector.x;
    y2 = point.y+vector.y; 
    //calculate an arrow (5pi/6)
    v.resolveRad(vector.getMagnitude()/5,vector.getAngleRad()+(5./6)*math::Pi);
    x3 = x2+v.x;
    y3 = y2-v.y;
    v.resolveRad(vector.getMagnitude()/5,vector.getAngleRad()-(5./6)*math::Pi);
    x4 = x2+v.x;
    y4 = y2-v.y;

    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_LINE_STRIP);
    glVertex2d(point.x,point.y);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glVertex2d(x4,y4);
    glVertex2d(x2,y2);
    glEnd();
    glColor4ub(255,255,255,255);
}

void Pen::drawRectangle(const math::Rect &rect) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_LINE_STRIP);
    glVertex2d(rect.getLeft(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getBottom());
    glVertex2d(rect.getLeft(),rect.getBottom());
    glVertex2d(rect.getLeft(),rect.getTop());
    glEnd();
    glColor4ub(255,255,255,255);
}

void Pen::fillRectangle(const math::Rect &rect) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_QUADS);
    glVertex2d(rect.getLeft(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getBottom());
    glVertex2d(rect.getLeft(),rect.getBottom());
    glEnd();
    glColor4ub(255,255,255,255);
}

void Pen::drawCircle(const math::Circle &circle) const
{
    //written from Bresenham's algorithm
    double cx(circle.getCenter().x);
    double cy(circle.getCenter().y);
    double d(3-(2*circle.getRadius()));
    double x(0);
    double y(circle.getRadius());

    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_POINTS);
    while(y > x)
    {
        glVertex2d(cx+x,cy+y);
        glVertex2d(cx+x,cy-y);
        glVertex2d(cx-x,cy+y);
        glVertex2d(cx-x,cy-y);
        glVertex2d(cx+y,cy+x);
        glVertex2d(cx+y,cy-x);
        glVertex2d(cx-y,cy+x);
        glVertex2d(cx-y,cy-x);

        if(d < 0)
        {
            d += x*4 + 6;
        }
        else
        {
            d += (x-y)*4 + 10;
            --y;
        }
        ++x;
    }
    glEnd();
    glColor4ub(255,255,255,255);
}

void Pen::fillCircle(const math::Circle &circle) const
{
    //written from Bresenham's algorithm
    double cx(circle.getCenter().x);
    double cy(circle.getCenter().y);
    double d(3-(2*circle.getRadius()));
    double x(0);
    double y(circle.getRadius());

    glBindTexture(GL_TEXTURE_2D,0);
    color_.makeGLColor();
    glBegin(GL_LINES);
    while(y > x)
    {
        glVertex2d(cx+x,cy+y);
        glVertex2d(cx+x,cy-y);
        glVertex2d(cx-x,cy-y);
        glVertex2d(cx-x,cy+y);
        glVertex2d(cx+y,cy+x);
        glVertex2d(cx-y,cy+x);
        glVertex2d(cx-y,cy-x);
        glVertex2d(cx+y,cy-x);

        if(d < 0)
        {
            d += x*4 + 6;
        }
        else
        {
            d += (x-y)*4 + 10;
            --y;
        }
        ++x;
    }
    glEnd();
    glColor4ub(255,255,255,255);
}

}
} 
