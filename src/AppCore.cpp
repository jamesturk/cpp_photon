//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AppCore.cpp,v 1.3 2005/03/02 08:43:33 cozman Exp $

#include "AppCore.hpp"

#include "glfw.h"   //This file depends on glfw

#include "exceptions.hpp"

namespace photon
{

void AppCore::createDisplay(uint width, uint height, 
                            uint redBits, uint greenBits, uint blueBits, 
                            uint alphaBits, uint depthBits, uint stencilBits,
                            bool fullscreen, const std::string &title)
{
    GLboolean status;
    status = glfwOpenWindow(width, height, redBits, greenBits, 
                            blueBits, alphaBits, depthBits, stencilBits, 
                            fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW);              
    if(status == GL_FALSE) 
    {
        throw APIError("Failed to create display.");
    }
    
    dispWidth_ = width;
    dispHeight_ = height;
    
    glfwSetWindowTitle(title.c_str());  // title is set separately
}

void AppCore::createDisplay(uint width, uint height, uint bpp, 
                            uint depthBits, uint stencilBits, bool fullscreen,
                            const std::string &title)
{
    // call main version of createDisplay with individual values for rgba bits
    switch(depthBits)
    {
        case 8:
            createDisplay(width, height, 3, 3, 2, 0, depthBits, stencilBits, 
                            fullscreen, title);
            break;
        case 16:
            createDisplay(width, height, 5, 6, 5, 0, depthBits, stencilBits, 
                            fullscreen, title);
            break;
        case 24:
            createDisplay(width, height, 8, 8, 8, 0, depthBits, stencilBits, 
                            fullscreen, title);
            break;
        case 32:
            createDisplay(width, height, 8, 8, 8, 8, depthBits, stencilBits, 
                            fullscreen, title);
            break;
        default:
            throw ArgumentException("bpp argument of createDisplay must be " 
                                    "8,16,24, or 32.");
    }
}

bool AppCore::keyPressed(KeyCode key)
{
    return glfwGetKey(key) == GLFW_PRESS;
}

bool AppCore::mouseButtonPressed(MouseButton button)
{
    return glfwGetMouseButton(button) == GLFW_PRESS;
}

int AppCore::getMouseX()
{
    int x;
    glfwGetMousePos(&x,0);  //only get x
    return x;
}

int AppCore::getMouseY()
{
    int y;
    glfwGetMousePos(0,&y);  //only get y
    return y;
}

int AppCore::getMouseWheelPos()
{
    return glfwGetMouseWheel();
}

scalar AppCore::getTime()
{
    return glfwGetTime() - pausedTime_;
}

void AppCore::update()
{
    scalar curTime = getTime();
    
    // update the display here instead of VideoCore (since it belongs to glfw)
    glfwSwapBuffers();  
    
    // keep track of time between frames
    secPerFrame_ = curTime-lastUpdate_;
    lastUpdate_ = curTime;
    
    // quit on window closing or Alt-F4/Alt-X
    if(!glfwGetWindowParam(GLFW_OPENED) || 
        ( (glfwGetKey(GLFW_KEY_LALT) || glfwGetKey(GLFW_KEY_RALT)) && 
          (glfwGetKey(GLFW_KEY_F4) || glfwGetKey('X')) ) )
    {
        quitRequested_ = true;
    }

    // hold active-state
    active_ = (glfwGetWindowParam(GLFW_ACTIVE) == GL_TRUE);

    // automatically pause/unpause app timer on focus
    if(!active_ && !timerPaused_)
    {
        timerPaused_ = true;
        lastPause_ = curTime;
        unpauseOnActive_ = true;
    }
    else if(active_ && unpauseOnActive_)
    {
        timerPaused_ = true;
        pausedTime_ += curTime - lastPause_;
        unpauseOnActive_ = false;
    }
}

void AppCore::setTitle(const std::string& title)
{
    glfwSetWindowTitle(title.c_str());
}

void AppCore::requestQuit()
{
    quitRequested_ = true;
}

bool AppCore::quitRequested()
{
    return quitRequested_;
}

bool AppCore::isActive()
{
    return active_;
}

double AppCore::getElapsedTime()
{
    return secPerFrame_;
}

double AppCore::getFramerate()
{
    return 1/secPerFrame_;
}

uint AppCore::getDisplayWidth()
{
    return dispWidth_;
}

uint AppCore::getDisplayHeight()
{
    return dispHeight_;
}

util::VersionInfo AppCore::initGLFW()
{
    int maj,min,patch;
    if(glfwInit() == GL_FALSE) 
    {
        throw APIError("Initialization of GLFW failed!");
    }
    glfwGetVersion(&maj,&min,&patch);
    return util::VersionInfo(maj,min,patch);
}

AppCore::AppCore() :
    dispWidth_(0), dispHeight_(0),
    quitRequested_(true), active_(false), timerPaused_(false), 
    unpauseOnActive_(false), lastPause_(0), pausedTime_(0),
    secPerFrame_(0), lastUpdate_(0)
{
    util::VersionInfo glfwReq(2,4,2);   // requires GLFW 2.4.2

    util::ensureVersion("GLFW", initGLFW(), glfwReq);
}

AppCore::~AppCore() 
{
    glfwCloseWindow();  //close GLFW window
    glfwTerminate();    //shutdown GLFW
}

}
