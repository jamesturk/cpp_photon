//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VideoCore.cpp,v 1.2 2005/03/15 18:53:27 cozman Exp $

#include "video/VideoCore.hpp"

#include "exceptions.hpp"

#include "gl/gl.h"
#include "gl/glu.h"

namespace photon
{
namespace video
{
    
VideoCore::VideoCore() : 
    displayWidth_(0), displayHeight_(0), 
    viewportWidth_(0), viewportHeight_(0) 
{
    initOpenGL();
}

VideoCore::~VideoCore()
{
}

void VideoCore::clear()
{
    // TODO: clear depth/stencil if requested
    glClear(GL_COLOR_BUFFER_BIT);
}

void VideoCore::setOrthoView(int x, int y, int viewWidth, int viewHeight, 
                                scalar orthoWidth, scalar orthoHeight)
{
    // set viewport & ortho projection
    setViewport(x,y,viewWidth,viewHeight);
    setOrthoProjection(orthoWidth,orthoHeight);
}

void VideoCore::setOrthoView(scalar width, scalar height)
{
    // set viewport to fullscreen, then set ortho (alternative ratio)
    setViewport(0, 0, displayWidth_, displayHeight_);
    setOrthoProjection(width,height);
}

void VideoCore::setOrthoView()
{
    // set viewport to fullscreen, then set ortho (1:1 ratio)
    setViewport(0, 0, displayWidth_, displayHeight_);
    setOrthoProjection(displayWidth_, displayHeight_);
}

void VideoCore::setPerspectiveView(int x, int y, int width, int height, 
                                scalar fovy, scalar zNear, scalar zFar)
{
    // set viewport & perspective projection
    setViewport(x, y, width, height);
    setPerspectiveProjection(fovy, zNear, zFar);
}

void VideoCore::setPerspectiveView(scalar fovy, scalar zNear, scalar zFar)
{
    // set viewport fullscreen, then set perspective
    setViewport(0, 0, displayWidth_, displayHeight_);
    setPerspectiveProjection(fovy, zNear, zFar);
}

void VideoCore::setViewport(int x, int y, int width, int height)
{
    // viewport described from bottom corner, so flip y
    glViewport(x, displayHeight_-(y+height), width, height);
    viewportWidth_ = width;
    viewportHeight_ = height;
}

void VideoCore::setOrthoProjection(scalar width, scalar height)
{
    // setup default Ortho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, static_cast<GLdouble>(width), static_cast<GLdouble>(height),
            0, -1.0, 1.0);

    //back to modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void VideoCore::setPerspectiveProjection(scalar fovy, scalar zNear, scalar zFar)
{
    GLdouble ratio = static_cast<GLdouble>(viewportWidth_) / 
                        static_cast<GLdouble>(viewportHeight_);

    //set new projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, ratio, zNear, zFar);
    
    //back to modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void VideoCore::initOpenGL()
{
    // Set smooth shading.
    glShadeModel(GL_SMOOTH);

    // Setup depth checking.
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);

    //setup hints
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    //enable texturing
    glEnable(GL_TEXTURE_2D);

    //setup alpha blending of 2D textures with the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void VideoCore::setDisplaySize(uint width, uint height)
{
    displayWidth_ = width;
    displayHeight_ = height;
}

uint VideoCore::getDisplayWidth()
{
    return displayWidth_;
}

uint VideoCore::getDisplayHeight()
{
    return displayHeight_;
}

}
}
