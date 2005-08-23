//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Pen.cpp,v 1.6 2005/08/23 21:55:03 cozman Exp $

#include "video/Pen.hpp"

#include "GL/gl.h"

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

Pen::Pen(const Color& color) :
    color_(color)
{
}

void Pen::setColor(ubyte r, ubyte g, ubyte b, ubyte a)
{
    color_.setColor(r,g,b,a);
}

void Pen::setColor(const Color& color)
{
    color_ = color;
}

void Pen::drawPoint(const math::Point2& point) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    glBegin(GL_POINTS); // draw single point
    glVertex2d(point.x,point.y);
    glEnd();
    glPopAttrib();
}

void Pen::drawLine(const math::Point2& p1, const math::Point2& p2) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    glBegin(GL_LINES);  // draw single line
    glVertex2d(p1.x,p1.y);
    glVertex2d(p2.x,p2.y);
    glEnd();
    glPopAttrib();
}

void Pen::drawVector(const math::Point2& point, 
                        const math::Vector2& vector) const
{
    double x2,y2,x3,y3,x4,y4;
    math::Vector2 v;
    x2 = point.x+vector.x;
    y2 = point.y+vector.y; 
    //calculate an arrow head (5pi/6 radian angle offset)
    v.resolveRad(vector.getMagnitude()/5,vector.getAngleRad()+(5./6)*math::PI);
    x3 = x2+v.x;
    y3 = y2-v.y;
    v.resolveRad(vector.getMagnitude()/5,vector.getAngleRad()-(5./6)*math::PI);
    x4 = x2+v.x;
    y4 = y2-v.y;

    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    glBegin(GL_LINE_STRIP); // use line strip to draw arrow
    glVertex2d(point.x,point.y);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glVertex2d(x4,y4);
    glVertex2d(x2,y2);
    glEnd();
    glPopAttrib();
}

void Pen::drawRect(const math::Rect &rect) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    glBegin(GL_LINE_STRIP); // use line strips to draw outline of rectangle
    glVertex2d(rect.getLeft(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getBottom());
    glVertex2d(rect.getLeft(),rect.getBottom());
    glVertex2d(rect.getLeft(),rect.getTop());
    glEnd();
    glPopAttrib();
}

void Pen::fillRect(const math::Rect &rect) const
{
    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    glBegin(GL_QUADS);  // draw one colored quad 
    glVertex2d(rect.getLeft(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getTop());
    glVertex2d(rect.getRight(),rect.getBottom());
    glVertex2d(rect.getLeft(),rect.getBottom());
    glEnd();
    glPopAttrib();
}

void Pen::drawCircle(const math::Circle &circle) const
{
    scalar radius(circle.getRadius());
    scalar cx(circle.getCenter().x);
    scalar cy(circle.getCenter().y);
    scalar angle(0);
    const scalar angleStep(2*math::PI/CIRCLE_RESOLUTION);
    
    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<CIRCLE_RESOLUTION; ++i)
    {
        glVertex2f(cx+radius*std::cos(angle), cy+radius*std::sin(angle));
        angle += angleStep;
    }
    glEnd();
    glPopAttrib();
}

void Pen::fillCircle(const math::Circle &circle) const
{
    scalar radius(circle.getRadius());
    scalar cx(circle.getCenter().x);
    scalar cy(circle.getCenter().y);
    scalar angle(0);
    const scalar angleStep(2*math::PI/CIRCLE_RESOLUTION);

    glBindTexture(GL_TEXTURE_2D,0);
    glPushAttrib(GL_CURRENT_BIT);
    color_.makeGLColor();
    
    glBegin(GL_POLYGON);
    for(int i=0; i<CIRCLE_RESOLUTION; ++i)
    {
        glVertex2f(cx+radius*std::cos(angle), cy+radius*std::sin(angle));
        angle += angleStep;
    }
    glEnd();
    glPopAttrib();
}

}
} 
