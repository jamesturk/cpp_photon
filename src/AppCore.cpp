//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AppCore.cpp,v 1.8 2005/06/13 05:38:06 cozman Exp $

#include "AppCore.hpp"

#include <boost/lexical_cast.hpp>
#include "GL/glfw.h"   //This file depends on glfw

#include "Kernel.hpp"
#include "exceptions.hpp"
#include "video/VideoCore.hpp"

namespace photon
{

AppCore::AppCore() :
    dispWidth_(0), dispHeight_(0),
    task_(new UpdateTask())
{
    util::VersionInfo glfwReq(2,4,2);   // requires GLFW 2.4.2
    util::ensureVersion("GLFW", initGLFW(), glfwReq);

    Kernel::getInstance().addTask(task_);
}

AppCore::~AppCore()
{
    glfwCloseWindow();  //close GLFW window
    glfwTerminate();    //shutdown GLFW
}

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
    new video::VideoCore;
    video::VideoCore::getInstance().setDisplaySize(width,height);

    glfwSetWindowTitle(title.c_str());  // title is set separately
}

void AppCore::createDisplay(uint width, uint height, uint bpp,
                            uint depthBits, uint stencilBits, bool fullscreen,
                            const std::string &title)
{
    // call main version of createDisplay with individual values for rgba bits
    switch(bpp)
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
                                    "8,16,24, or 32, passed " +
                                    boost::lexical_cast<std::string>(bpp) );
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
    return task_->mouseX_;
}

int AppCore::getMouseY()
{
    return task_->mouseY_;
}

int AppCore::getMouseWheelPos()
{
    return glfwGetMouseWheel();
}

scalar AppCore::getTime()
{
    return glfwGetTime() - task_->pausedTime_;
}

void AppCore::setTitle(const std::string& title)
{
    glfwSetWindowTitle(title.c_str());
}

bool AppCore::isActive()
{
    return task_->active_;
}

double AppCore::getElapsedTime()
{
    return task_->secPerFrame_;
}

double AppCore::getFramerate()
{
    return 1/task_->secPerFrame_;
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

AppCore::UpdateTask::UpdateTask() :
    Task("AppCore::UpdateTask", PRI_CORE),
    mouseX_(0), mouseY_(0),
    active_(false), timerPaused_(false),
    unpauseOnActive_(false), lastPause_(0), pausedTime_(0),
    secPerFrame_(0), lastUpdate_(0)
{
}

void AppCore::UpdateTask::update()
{
    scalar curTime = glfwGetTime() - pausedTime_;

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
        Kernel::getInstance().killAllTasks();
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

}
