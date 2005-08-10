//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.21 2005/08/10 05:36:58 cozman Exp $

#include "Application.hpp"

#include "physfs.h"     // This file depends on physfs
#include "GL/glfw.h"    // This file depends on glfw
#include "GL/gl.h"      // This file depends on OpenGL
#include "GL/glu.h"

#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"
#include "Log.hpp"
#include "Kernel.hpp"
#include "Application.hpp"
#include "audio/AudioCore.hpp"
#include "util/filesys/filesys.hpp"

namespace photon
{

// static class members
std::vector<InputListener*> Application::listeners_;
std::vector<KeyCode> Application::pressedKeys_;

// (Con/De)structors ///////////////////////////////////////////////////////////

Application::Application(const std::string& arg0) :
    photonVer_(0,0,1),  // this is the current version
    displayWidth_(0), displayHeight_(0),
    viewportWidth_(0), viewportHeight_(0),
    updateTask_(new UpdateTask()),
    stateUpdate_(new StateUpdate()),
    stateRender_(new StateRender())
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0
    util::ensureVersion("PhysFS", initPhysFS(arg0), physfsReq);
    
    util::VersionInfo glfwReq(2,4,2);   // requires GLFW 2.4.2
    util::ensureVersion("GLFW", initGLFW(), glfwReq);

    new Kernel;     // create Kernel before it is used
    
    Kernel::getInstance().addTask(updateTask_);     // add updater task
    Kernel::getInstance().addTask(stateUpdate_);    // add state updater task
    Kernel::getInstance().addTask(stateRender_);    // add state renderer task
}

Application::~Application()
{
    if(displayWidth_ && displayHeight_)
    {
        glfwCloseWindow();  //close GLFW window
    }
    
    glfwTerminate();        // shutdown GLFW
    
    PHYSFS_deinit();        // shutdown PhysFS
    
    Kernel::destroy();      // destroy Kernel on way out
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
    
    Kernel::getInstance().addTask(TaskPtr(new VideoTask()));

    // register the callbacks (after a window is open)
    glfwSetKeyCallback(Application::keyCallback);
    //glfwSetCharCallback(Application::charCallback);
    glfwSetMouseButtonCallback(Application::mouseButtonCallback);
    glfwSetMousePosCallback(Application::mouseMoveCallback);
    //glfwSetMouseWheelCallback(Application::mouseWheelCallback);
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

bool Application::isActive()
{
    return updateTask_->active_;
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

void Application::setPerspectiveProjection(scalar fovy, scalar zNear, scalar zFar)
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

// Input Listeners /////////////////////////////////////////////////////////////

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
                (*listener)->onKeyPress(KeyCode(key));
            }
            else
            {
                (*listener)->onKeyRelease(KeyCode(key));
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
                (*listener)->onMouseButtonPress(MouseButton(button));
            }
            else
            {
                (*listener)->onMouseButtonRelease(MouseButton(button));
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

// Timing //////////////////////////////////////////////////////////////////////

scalar Application::getTime()
{
    return glfwGetTime() - updateTask_->pausedTime_;
}

double Application::getElapsedTime()
{
    return updateTask_->secPerFrame_;
}

double Application::getFramerate()
{
    return 1/updateTask_->secPerFrame_;
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

    // Setup depth checking.
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);

    //setup hints
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    
    glEnable(GL_POLYGON_SMOOTH);

    //enable texturing
    glEnable(GL_TEXTURE_2D);

    //setup alpha blending of 2D textures with the scene
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

// Tasks ///////////////////////////////////////////////////////////////////////

Application::UpdateTask::UpdateTask() :
    Task("Application::UpdateTask", PRI_APP_UPDATE),
    mouseX_(0), mouseY_(0),
    active_(false), timerPaused_(false),
    unpauseOnActive_(false), lastPause_(0), pausedTime_(0),
    secPerFrame_(0), lastUpdate_(0)
{
}

void Application::UpdateTask::update()
{
    scalar curTime = glfwGetTime() - pausedTime_;

    // update the display here instead of Application (since it belongs to glfw)
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

Application::VideoTask::VideoTask() :
    Task("Application::VideoTask", PRI_VIDEO_UPDATE)
{
}

void Application::VideoTask::update()
{
    // TODO: clear depth/stencil if requested
    glClear(GL_COLOR_BUFFER_BIT);
}

Application::StateUpdate::StateUpdate() :
    Task("Application::StateUpdate", PRI_NORMAL)
{
}

void Application::StateUpdate::update()
{
    state_->update();
}

Application::StateRender::StateRender() :
    Task("Application::StateRender", PRI_RENDER)
{
}

void Application::StateRender::update()
{
    state_->render();
}

}
