//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.27 2005/08/17 06:35:56 cozman Exp $

#include "Application.hpp"

#include "physfs.h"     // This file depends on physfs
#include "GL/glfw.h"    // This file depends on glfw
#include "GL/gl.h"      // This file depends on OpenGL
#include "GL/glu.h"

#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"
#include "Application.hpp"
#include "util/filesys/filesys.hpp"

#include <iostream>

namespace photon
{

// static class members
std::vector<KeyCode> Application::pressedKeys_;
std::stack<StatePtr> Application::stateStack_;

// (Con/De)structors ///////////////////////////////////////////////////////////

Application::Application(const std::string& arg0) :
    photonVer_(0,0,1),  // this is the current version
    displayWidth_(0), displayHeight_(0), viewportWidth_(0), viewportHeight_(0),
    clearFlags_(GL_COLOR_BUFFER_BIT),
    mouseX_(0), mouseY_(0),
    active_(false), timerPaused_(false), unpauseOnActive_(false),
    lastPause_(0), pausedTime_(0), elapsedTime_(0), lastUpdate_(0),
    fixedTimeStep_(0), maxTimeStep_(0), timeAccumulator_(0), frameTimes_(0),
    quit_(true)
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0
    util::ensureVersion("PhysFS", initPhysFS(arg0), physfsReq);
    
    util::VersionInfo glfwReq(2,4,2);   // requires GLFW 2.4.2
    util::ensureVersion("GLFW", initGLFW(), glfwReq);
}

Application::~Application()
{
    glfwTerminate();        // shutdown GLFW
    
    PHYSFS_deinit();        // shutdown PhysFS
}

void Application::run()
{
    while(!quit_)
    {
        update();
    }
}

void Application::update()
{
    // update glfw state 
    glfwGetMousePos(&mouseX_, &mouseY_);

    // quit on window closing or Alt-F4/Alt-X
    if(!glfwGetWindowParam(GLFW_OPENED) ||
        ( (glfwGetKey(GLFW_KEY_LALT) || glfwGetKey(GLFW_KEY_RALT)) &&
          (glfwGetKey(GLFW_KEY_F4) || glfwGetKey('X')) ) )
    {
        quit();
    }

    // hold active-state
    active_ = (glfwGetWindowParam(GLFW_ACTIVE) == GL_TRUE);
    
    //automatically pause/unpause app timer on focus
    scalar curTime( getTime() );
    if(!active_ && !timerPaused_)
    {
        timerPaused_ = true;
        lastPause_ = curTime;
        unpauseOnActive_ = true;
    }
    else if(active_ && unpauseOnActive_)
    {
        timerPaused_ = false;
        //pausedTime_ += curTime - lastPause_;
        unpauseOnActive_ = false;
    }

    // keep track of time between frames
    static uint frameIndex(0);

    if(++frameIndex >= frameTimes_.size())
    {
        frameIndex = 0;
    }
    elapsedTime_ = frameTimes_[frameIndex] = curTime-lastUpdate_;
    
    lastUpdate_ = curTime;
    
    if(!stateStack_.empty() && !quit_)
    {
        if(fixedTimeStep_ > 0)
        {
            if(elapsedTime_ > maxTimeStep_)
            {
                elapsedTime_ = maxTimeStep_;
            }
            
            timeAccumulator_ += elapsedTime_;
            
            while(timeAccumulator_ >= fixedTimeStep_)
            {
                stateStack_.top()->update(fixedTimeStep_);
                updateTaskManager_.step(fixedTimeStep_);
                timeAccumulator_ -= fixedTimeStep_;
            }
        }
        else
        {
            stateStack_.top()->update(elapsedTime_);
            updateTaskManager_.step(elapsedTime_);
        }
    }

    // render step
    if(!stateStack_.empty() && !quit_)
    {
        // clear everything before rendering
        glClear(clearFlags_);
        stateStack_.top()->render();
        renderTaskManager_.step(fixedTimeStep_);
        glfwSwapBuffers();  // swap buffers after rendering
    }
}

void Application::quit()
{
    glfwCloseWindow();  //close GLFW window
    
    quit_ = true;
}

util::TaskManager& Application::getUpdateTaskManager()
{
    return updateTaskManager_;
}

util::TaskManager& Application::getRenderTaskManager()
{
    return renderTaskManager_;
}

bool Application::isActive()
{
    return active_;
}

// Window //////////////////////////////////////////////////////////////////////

void Application::createDisplay(uint width, uint height,
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
    
    // fetch window size (fixes X11 fullscreen bug)
    glfwGetWindowSize(reinterpret_cast<int*>(&displayWidth_), 
                        reinterpret_cast<int*>(&displayHeight_));
    
    glfwSetWindowTitle(title.c_str());  // title is set separately
    
    initOpenGL();
    setOrthoView();
    
    // register the callbacks (after a window is open)
    glfwSetKeyCallback(Application::keyCallback);
    //glfwSetCharCallback(Application::charCallback);
    glfwSetMouseButtonCallback(Application::mouseButtonCallback);
    glfwSetMousePosCallback(Application::mouseMoveCallback);
    glfwSetMouseWheelCallback(Application::mouseWheelCallback);
    
    quit_ = false;
}

void Application::createDisplay(uint width, uint height, uint bpp,
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

void Application::setTitle(const std::string& title)
{
    glfwSetWindowTitle(title.c_str());
}

uint Application::getDisplayWidth()
{
    return displayWidth_;
}

uint Application::getDisplayHeight()
{
    return displayHeight_;
}

// Ortho ///////////////////////////////////////////////////////////////////////

void Application::setOrthoView(int x, int y, int viewWidth, int viewHeight, 
                                scalar orthoWidth, scalar orthoHeight)
{
    // set viewport & ortho projection
    setViewport(x,y,viewWidth,viewHeight);
    setOrthoProjection(orthoWidth,orthoHeight);
}

void Application::setOrthoView(scalar width, scalar height)
{
    // set viewport to fullscreen, then set ortho (alternative ratio)
    setViewport(0, 0, displayWidth_, displayHeight_);
    setOrthoProjection(width,height);
}

void Application::setOrthoView()
{
    // set viewport to fullscreen, then set ortho (1:1 ratio)
    setViewport(0, 0, displayWidth_, displayHeight_);
    setOrthoProjection(displayWidth_, displayHeight_);
}

// Perspective /////////////////////////////////////////////////////////////////

void Application::setPerspectiveView(int x, int y, int width, int height, 
                                scalar fovy, scalar zNear, scalar zFar)
{
    // set viewport & perspective projection
    setViewport(x, y, width, height);
    setPerspectiveProjection(fovy, zNear, zFar);
}

void Application::setPerspectiveView(scalar fovy, scalar zNear, scalar zFar)
{
    // set viewport fullscreen, then set perspective
    setViewport(0, 0, displayWidth_, displayHeight_);
    setPerspectiveProjection(fovy, zNear, zFar);
}

// Viewport/Projection /////////////////////////////////////////////////////////

void Application::setViewport(int x, int y, int width, int height)
{
    // viewport described from bottom corner, so flip y
    glViewport(x, displayHeight_-(y+height), width, height);
    viewportWidth_ = width;
    viewportHeight_ = height;
}

void Application::setOrthoProjection(scalar width, scalar height)
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

void Application::setPerspectiveProjection(scalar fovy, scalar zNear, 
                                            scalar zFar)
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
    
    setDepthBufferParams(true);
}

void Application::setDepthBufferParams(bool enable, scalar depth)
{
    if(enable)
    {
        glClearDepth(depth);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        clearFlags_ |= GL_DEPTH_BUFFER_BIT;
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        clearFlags_ &= ~GL_DEPTH_BUFFER_BIT;
    }
}

// Input ///////////////////////////////////////////////////////////////////////
bool Application::keyPressed(KeyCode key)
{
    return glfwGetKey(key) == GLFW_PRESS;
}

std::vector<KeyCode> Application::getPressedKeys()
{
    return pressedKeys_;
}

bool Application::mouseButtonPressed(MouseButton button)
{
    return glfwGetMouseButton(button) == GLFW_PRESS;
}

int Application::getMouseX()
{
    return mouseX_;
}

int Application::getMouseY()
{
    return mouseY_;
}

int Application::getMouseWheelPos()
{
    return glfwGetMouseWheel();
}

// Timing //////////////////////////////////////////////////////////////////////

scalar Application::getTime()
{
    return glfwGetTime() - pausedTime_;
}

void Application::setFrameTimeSmoothing(int numFrames)
{
    if(numFrames <= 1)
        numFrames = 0;
    
    frameTimes_.resize(numFrames);
}

double Application::getElapsedTime()
{
    if(frameTimes_.size() == 0)
    {
        return elapsedTime_;
    }
    else
    {
        return frameTimes_.sum()/frameTimes_.size();
    }
}

double Application::getFramerate()
{
    return 1/getElapsedTime();
}

void Application::setFixedUpdateStep(bool enable, scalar fixedStep, 
                                    scalar maxStep)
{
    if(!enable)
    {
        fixedTimeStep_ = -1;    // set to < 0, disabling fixed timestepping
    }
    else
    {
        fixedTimeStep_ = fixedStep;
        if(maxStep <= 0)
        {
            maxTimeStep_ = 5*fixedTimeStep_;
        }
        else
        {
            maxTimeStep_ = maxStep;
        }
    }
}

// States //////////////////////////////////////////////////////////////////////

void Application::popState()
{
    // check for underflow
    if(stateStack_.empty())
    {
        throw PreconditionException("Attempt to popState without at least one "
                                    "states on stack.");
    }

    // pop current state from stack
    stateStack_.pop();

    // resume new top state & set tasks for next state
    if(!stateStack_.empty())
    {
        stateStack_.top()->onResume();
    }
}

// AudioCore ///////////////////////////////////////////////////////////////////
#ifdef PHOTON_USE_OPENAL

audio::AudioCore& Application::getAudioCore()
{
    // return AudioCore if it has been created
    if(audioCore_.get() == 0)
    {
        throw PreconditionException("call to Application::getAudioCore() before"
                                    " Application::initAudioDevice");
    }
    return *audioCore_;
}

void Application::initAudioCore(const std::string& deviceName)
{
    // create AudioCore, avoid double initializaiton
    if(audioCore_.get() == 0)
    {
        audioCore_.reset(new audio::AudioCore(deviceName));
    }
    else
    {
        throw PreconditionException("Attempt to double initialize AudioCore");
    }
}

#endif //PHOTON_USE_OPENAL

// Callbacks ///////////////////////////////////////////////////////////////////

void GLFWCALL Application::keyCallback(int key, int action)
{
    if(!stateStack_.empty())
    {
        if(action == GLFW_PRESS)
        {
            stateStack_.top()->onKeyPress(KeyCode(key));
        }
        else
        {
            stateStack_.top()->onKeyRelease(KeyCode(key));
        }
    }

    // maintain a list of pressed keys
    if(action == GLFW_PRESS)
    {
        pressedKeys_.push_back(static_cast<KeyCode>(key));
    }
    else
    {
        // delete a key from the vector
        std::vector<KeyCode>::iterator it;
        it = std::find(pressedKeys_.begin(), pressedKeys_.end(), key);
    
        if(it != pressedKeys_.end())
        {
            pressedKeys_.erase(it);
        }
    }
}

void GLFWCALL Application::mouseButtonCallback(int button, int action)
{
    if(!stateStack_.empty())
    {
        if(action == GLFW_PRESS)
        {
            stateStack_.top()->onMouseButtonPress(MouseButton(button));
        }
        else
        {
            stateStack_.top()->onMouseButtonRelease(MouseButton(button));
        }
    }
}

void GLFWCALL Application::mouseMoveCallback(int x, int y)
{
    static math::Point2 lastPos;
    
    if(!stateStack_.empty())
    {
        // calculate change in position and send delta
        math::Point2 pos(static_cast<scalar>(x), static_cast<scalar>(y));
        stateStack_.top()->onMouseMove(pos - lastPos);
        lastPos = pos;
    }
}

void GLFWCALL Application::mouseWheelCallback(int pos)
{
    static int lastPos(0);
    
    if(!stateStack_.empty())
    {
        // if pos < lastPos scrolled up, otherwise scrolled down
        stateStack_.top()->onMouseScroll( pos < lastPos ? 
                                            SCROLL_DOWN : 
                                            SCROLL_UP);
        lastPos = pos;
    }
}

// API initialization //////////////////////////////////////////////////////////

util::VersionInfo Application::initPhysFS(const std::string& arg0)
{
    PHYSFS_Version ver;
    PHYSFS_init(arg0.c_str());
    PHYSFS_addToSearchPath(PHYSFS_getBaseDir(),0);
    PHYSFS_getLinkedVersion(&ver);
    return util::VersionInfo(ver.major, ver.minor, ver.patch);
}

util::VersionInfo Application::initGLFW()
{
    int maj,min,patch;
    if(glfwInit() == GL_FALSE)
    {
        throw APIError("Initialization of GLFW failed!");
    }
    glfwGetVersion(&maj,&min,&patch);
    return util::VersionInfo(maj,min,patch);
}

void Application::initOpenGL()
{
    // Set smooth shading.
    glShadeModel(GL_SMOOTH);

    //setup hints
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    
    glEnable(GL_POLYGON_SMOOTH);

    //enable texturing
    glEnable(GL_TEXTURE_2D);

    //setup alpha blending of 2D textures with the scene
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    // depth testing enabled by default
    setDepthBufferParams(false);
}

}
