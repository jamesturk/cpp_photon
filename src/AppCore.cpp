//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AppCore.cpp,v 1.1 2005/02/27 07:43:37 cozman Exp $

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
    }
}

void AppCore::updateDisplay()
{
    glfwSwapBuffers();
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
    return glfwGetTime();
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

AppCore::AppCore()
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
