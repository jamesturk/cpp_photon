//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Image.cpp,v 1.1 2005/06/13 07:04:29 cozman Exp $

#include "video/Image.hpp"

#include "GL/gl.h"

namespace photon
{
namespace video
{

Image::Image() : 
    Texture(),
    alpha_(255),
    texMinX_(0), texMinY_(0), texMaxX_(1), texMaxY_(1)
{
}

Image::Image(const Image &rhs) : 
    Texture(rhs),
    alpha_(rhs.alpha_),
    texMinX_(rhs.texMinX_), texMinY_(rhs.texMinY_), 
    texMaxX_(rhs.texMaxX_), texMaxY_(rhs.texMaxY_)
{

}

Image::Image(const std::string& name) : 
    alpha_(255),
    texMinX_(0), texMinY_(0), texMaxX_(1), texMaxY_(1)
{
    open(name);
}

Image& Image::operator=(const Image &rhs)
{
    if(&rhs != this)
    {
        Texture::operator=(rhs);
        alpha_ = rhs.alpha_;
        texMinX_ = rhs.texMinX_;
        texMinY_ = rhs.texMinY_;
        texMaxX_ = rhs.texMaxX_;
        texMaxY_ = rhs.texMaxY_;
    }
    return *this;
}

void Image::open(const std::string& name)
{
    Texture::open(name);
}

void Image::setAlpha(ubyte alpha)
{
    alpha_ = alpha;
}

void Image::flip(bool horizontal, bool vertical)
{
    //all that a flip does is invert the Min/Max coordinates
    if(horizontal)
    {
        std::swap(texMinX_,texMaxX_);
    }
    if(vertical)
    {
        std::swap(texMinY_,texMaxY_);
    }
}

//stretching and resizing is very inexpensive, done via variables
void Image::stretch(scalar xFactor, scalar yFactor)
{
    width_ = xFactor*width_;
    height_ = yFactor*height_;
}

void Image::resize(scalar width, scalar height)
{
    width_ = width;
    height_ = height;
}

void Image::draw(scalar x, scalar y) const
{
    glColor4ub(255,255,255,alpha_);
    bind();
    glBegin(GL_QUADS);
        glTexCoord2i(texMinX_,texMinY_);    glVertex2d(x,y);
        glTexCoord2i(texMaxX_,texMinY_);    glVertex2d(x+width_,y);
        glTexCoord2i(texMaxX_,texMaxY_);    glVertex2d(x+width_,y+height_);
        glTexCoord2i(texMinX_,texMaxY_);    glVertex2d(x,y+height_);
    glEnd();
    glColor4ub(255,255,255,255);
}

void Image::draw(scalar x, scalar y, ubyte vc[]) const
{
    bind();
    glBegin(GL_QUADS);
        glTexCoord2i(texMinX_,texMinY_); 
        glColor4ub(vc[0],vc[1],vc[2],vc[3]); 
        glVertex2d(x,y);
        
        glTexCoord2i(texMaxX_,texMinY_); 
        glColor4ub(vc[4],vc[5],vc[6],vc[7]); 
        glVertex2d(x+width_,y);
        
        glTexCoord2i(texMaxX_,texMaxY_); 
        glColor4ub(vc[8],vc[9],vc[10],vc[11]); 
        glVertex2d(x+width_,y+height_);
        
        glTexCoord2i(texMinX_,texMaxY_); 
        glColor4ub(vc[12],vc[13],vc[14],vc[15]); 
        glVertex2d(x,y+height_);
    glEnd();
    glColor4ub(255,255,255,255);
}

void Image::drawRotated(scalar x, scalar y, scalar angle) const
{
    //center point
    scalar cX = width_/2., cY = height_/2.;

    glPushMatrix();
    glLoadIdentity();
    glTranslated(x+cX,y+cY,0);  //translate to center
    glRotated(angle,0,0,1.0f);  //rotate on z axis, to keep x&y in 2D plane
    glColor4ub(255,255,255,255);
    bind();
    //draw is modified to be based around center
    glBegin(GL_QUADS);
        glTexCoord2i(texMinX_,texMinY_);    glVertex2d(-cX,-cY);
        glTexCoord2i(texMaxX_,texMinY_);    glVertex2d(-cX+width_,-cY);
        glTexCoord2i(texMaxX_,texMaxY_);    glVertex2d(-cX+width_,-cY+height_);
        glTexCoord2i(texMinX_,texMaxY_);    glVertex2d(-cX,-cY+height_);
    glEnd();
    glPopMatrix();
    glColor4ub(255,255,255,255);
}

void Image::drawRotated(scalar x, scalar y, scalar angle, ubyte vc[]) const
{
    //center point
    scalar cX,cY; 
    cX = width_/2.0f;
    cY = height_/2.0f;

    glPushMatrix();
    glLoadIdentity();
    glTranslated(x+cX,y+cY,0);  //translate to center
    glRotated(angle,0,0,1.0f);  //rotate on z axis, to keep x&y in 2D plane
    bind(); 
    //draw is modified to be based around center
    glBegin(GL_QUADS);
        glTexCoord2i(texMinX_,texMinY_); 
        glColor4ub(vc[0],vc[1],vc[2],vc[3]); 
        glVertex2d(-cX,-cY);
        
        glTexCoord2i(texMaxX_,texMinY_); 
        glColor4ub(vc[4],vc[6],vc[6],vc[7]); 
        glVertex2d(-cX+width_,-cY);
        
        glTexCoord2i(texMaxX_,texMaxY_); 
        glColor4ub(vc[8],vc[9],vc[10],vc[11]); 
        glVertex2d(-cX+width_,-cY+height_);
        
        glTexCoord2i(texMinX_,texMaxY_); 
        glColor4ub(vc[12],vc[13],vc[14],vc[15]); 
        glVertex2d(-cX,-cY+height_);
    glEnd();
    glPopMatrix();
    glColor4ub(255,255,255,255);
}

ubyte Image::getAlpha() const
{
    return alpha_;
}

std::ostream& operator<<(std::ostream &o, const Image &rhs)
{
    return o << "Image: { ResID: " << rhs.resID_ <<
        " Dimensions: " << rhs.width_ << "x" << rhs.height_ 
        << " Alpha: " << rhs.alpha_ << " }";
}

}
}
