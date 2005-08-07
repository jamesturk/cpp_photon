//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.15 2005/08/07 07:12:47 cozman Exp $

#include "Application.hpp"

#include "physfs.h"
#include "GL/gl.h"
#include "GL/glfw.h"   //This file depends on glfw

#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"
#include "Log.hpp"
#include "Kernel.hpp"
#include "Application.hpp"
#include "video/VideoCore.hpp"
#include "audio/AudioCore.hpp"
#include "util/filesys/filesys.hpp"


namespace photon
{

std::vector<InputListener*> Application::listeners_;
std::vector<KeyCode> Application::pressedKeys_;

Application::Application(const std::string& arg0) :
    photonVer_(0,0,1),  // this is the current version
    dispWidth_(0), dispHeight_(0),
    updateTask_(new UpdateTask()),
    stateUpdate_(new StateUpdate()),
    stateRender_(new StateRender())
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0
    util::ensureVersion("PhysFS", initPhysFS(arg0), physfsReq);
    
    util::VersionInfo glfwReq(2,4,2);   // requires GLFW 2.4.2
    util::ensureVersion("GLFW", initGLFW(), glfwReq);

    new Kernel; // create Kernel before it is used
    
    Kernel::getInstance().addTask(updateTask_);   // add updater task
    Kernel::getInstance().addTask(stateUpdate_);   // add state updater task
    Kernel::getInstance().addTask(stateRender_);   // add state renderer task
}

Application::~Application()
{
    if(dispWidth_ && dispHeight_)
    {
        glfwCloseWindow();  //close GLFW window
    }
    
    glfwTerminate();    //shutdown GLFW
    
    PHYSFS_deinit();    // shutdown PhysFS
    
    Kernel::destroy();
}

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
    
    // register the callbacks (after a window is open)
    glfwSetKeyCallback(Application::keyCallback);
    //glfwSetCharCallback(Application::charCallback);
    glfwSetMouseButtonCallback(Application::mouseButtonCallback);
    glfwSetMousePosCallback(Application::mouseMoveCallback);
    //glfwSetMouseWheelCallback(Application::mouseWheelCallback);

    Application::initVideoCore(width, height);
    dispWidth_ = width;
    dispHeight_ = height;

    glfwSetWindowTitle(title.c_str());  // title is set separately
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
    return updateTask_->mouseX_;
}

int Application::getMouseY()
{
    return updateTask_->mouseY_;
}

int Application::getMouseWheelPos()
{
    return glfwGetMouseWheel();
}

void Application::addInputListener(InputListener *listener)
{
    // should never happen since listeners add themselves with a this pointer
    if(!listener)
    {
        throw ArgumentException("Null pointer in "
                                "Application::addInputListener");
    }

    // add the listener
    listeners_.push_back(listener);
}

void Application::removeInputListener(InputListener *listener)
{
    // should never happen since listeners remove themselves with a this pointer
    if(!listener)
    {
        throw ArgumentException("Null pointer in "
                                "Application::removeInputListener");
    }

    // find and erase the listener
    std::vector<InputListener*>::iterator it;
    it = std::find(listeners_.begin(), listeners_.end(), listener);

    if(it != listeners_.end())
    {
        listeners_.erase(it);
    }
}

void GLFWCALL Application::keyCallback(int key, int action)
{
    // notify all listeners
    for(std::vector<InputListener*>::iterator listener = listeners_.begin();
        listener != listeners_.end(); 
        ++listener)
    {
        // only active listeners get messages
        if((*listener)->isActive())
        {
            if(action == GLFW_PRESS)
            {
                (*listener)->onKeyPress(key);
            }
            else
            {
                (*listener)->onKeyRelease(key);
            }
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
    // notify all listeners
    for(std::vector<InputListener*>::iterator listener = listeners_.begin();
        listener != listeners_.end(); 
        ++listener)
    {
        // only active listeners get messages
        if((*listener)->isActive())
        {
            if(action == GLFW_PRESS)
            {
                (*listener)->onMouseButtonPress(button);
            }
            else
            {
                (*listener)->onMouseButtonRelease(button);
            }
        }
    }
}

void GLFWCALL Application::mouseMoveCallback(int x, int y)
{
    // notify all listeners
    for(std::vector<InputListener*>::iterator listener = listeners_.begin();
        listener != listeners_.end(); 
        ++listener)
    {
        // only active listeners get messages
        if((*listener)->isActive())
        {
            (*listener)->onMouseMove(math::Vector2(static_cast<scalar>(x),
                                                    static_cast<scalar>(y)));
        }
    }
}

scalar Application::getTime()
{
    return glfwGetTime() - updateTask_->pausedTime_;
}

void Application::setTitle(const std::string& title)
{
    glfwSetWindowTitle(title.c_str());
}

video::VideoCore& Application::getVideoCore()
{
    // return VideoCore if it has been created
    if(videoCore_.get() == 0)
    {
        throw PreconditionException("call to Application::getVideoCore() before"
                                    " Application::initAudioDevice");
    }
    return *videoCore_;
}

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

void Application::initVideoCore(uint width, uint height)
{
    // create VideoCore, avoid double initializaiton
    if(videoCore_.get() == 0)
    {
        videoCore_.reset(new video::VideoCore(width, height));
    }
    else
    {
        throw PreconditionException("Attempt to double initialize VideoCore");
    }
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

bool Application::isActive()
{
    return updateTask_->active_;
}

bool Application::isRunning()
{
    return !updateTask_->quitRequested_;
}

double Application::getElapsedTime()
{
    return updateTask_->secPerFrame_;
}

double Application::getFramerate()
{
    return 1/updateTask_->secPerFrame_;
}

void Application::unregisterState(const std::string& stateName)
{
    StateMap::iterator it( stateMap_.find(stateName) );
    
    if(it == stateMap_.end())
    {
        throw PreconditionException("Application::unregisterState called with "
                "non-existant state name: \"" + stateName + "\""); 
    }
    
    stateMap_.erase(stateName);
}

void Application::setCurrentState(const std::string& stateName)
{
    StateMap::iterator it( stateMap_.find(stateName) );
    
    if(it == stateMap_.end())
    {
        throw PreconditionException("Application::setCurrentState called with "
                "non-existant state name: \"" + stateName + "\""); 
    }
    
    if(stateUpdate_->state_.get() != 0)
    {
        stateUpdate_->state_->exitState();
    }
    
    stateRender_->state_ = stateUpdate_->state_ = stateMap_[stateName];
    stateUpdate_->state_->enterState();
}

uint Application::getDisplayWidth()
{
    return dispWidth_;
}

uint Application::getDisplayHeight()
{
    return dispHeight_;
}

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

Application::UpdateTask::UpdateTask() :
    Task("Application::UpdateTask", PRI_APP_UPDATE),
    mouseX_(0), mouseY_(0),
    active_(false), timerPaused_(false),
    unpauseOnActive_(false), lastPause_(0), pausedTime_(0),
    secPerFrame_(0), lastUpdate_(0),
    quitRequested_(false)
{
}

void Application::UpdateTask::update()
{
    scalar curTime = glfwGetTime() - pausedTime_;

    // update the display here instead of VideoCore (since it belongs to glfw)
    glfwSwapBuffers();
    
    glfwGetMousePos(&mouseX_, &mouseY_);

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

Application::StateUpdate::StateUpdate() :
    Task("StateUpdate", PRI_NORMAL)
{
}

void Application::StateUpdate::update()
{
    state_->update();
}

Application::StateRender::StateRender() :
    Task("StateRender", PRI_RENDER)
{
}

void Application::StateRender::update()
{
    state_->render();
}

}
