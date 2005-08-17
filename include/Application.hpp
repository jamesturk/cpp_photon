//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.hpp,v 1.21 2005/08/17 03:15:24 cozman Exp $

#ifndef PHOTON_APPLICATION_HPP
#define PHOTON_APPLICATION_HPP

#include <vector>
#include <stack>
#include <valarray>
#include <string>

#include <boost/utility.hpp>

#include "types.hpp"
#include "util/VersionInfo.hpp"
#include "State.hpp"
#include "Kernel.hpp"
#include "audio/AudioCore.hpp"
#include "util/Singleton.hpp"

namespace photon
{

// Class: Application
//  Photon main class, contains functions that control creation of the display,
//  setting the OpenGL view, input handling, timing, and <State> management.
//
//  Application is a <Singleton> and therefore should be accessed through 
//  Application::getInstance().  (Application Singleton is created/destroyed 
//  automatically)
class Application : public util::Singleton<Application>
{

// Group: (Con/De)structors
public:
    // Function: Application
    //  Default constructor, initializes the internal state & dependencies.
    Application(const std::string& arg0);

    // Function: ~Application
    //  Default destructor, shuts down dependencies.
    virtual ~Application();
    
// Group: General
public:
    // Function: run
    //  Runs application until a quit is requested either via the operating 
    //  system (ex. Alt-F4) or through a call to <quit>.
    //
    //  Should not be called before a <State> has been set and a display has
    //  been created via <createDisplay>.
    void run();
    
    // called by run while !quit()
    void update();
    
    // Function: quit
    //  Sets Quit flag, terminating application.
    void quit();
    
    // Function: getUpdateKernel
    //  Access the application's update <Kernel>, <Tasks> registered with this
    //  kernel are executed after the current <State's> <State::update>.
    //
    // Returns:
    //  Reference to "Update Kernel"
    Kernel& getUpdateKernel();
    
    // Function: getRenderKernel
    //  Access the application's render <Kernel>, <Tasks> registered with this
    //  kernel are executed after the current <State's> <State::render>.
    //
    // Returns:
    //  Reference to "Render Kernel"
    Kernel& getRenderKernel();
    
    // Function: isActive
    //  Checks if application is active, which on most systems simply means it
    //  has focus.
    //
    // Returns:
    //  True if application is active, false otherwise.
    bool isActive();

// Group: Window
public:
    // Function: createDisplay
    //  This function attempts to create a display with the given parameters.
    //
    // Parameters:
    //  width       - desired width of display
    //  height      - desired height of display
    //  redBits     - desired bits per pixel for red value
    //  greenBits   - desired bits per pixel for green value
    //  blueBits    - desired bits per pixel for blue value
    //  alphaBits   - desired bits per pixel for alpha value
    //  depthBits   - desired bitdepth of depth buffer
    //  stencilBits - desired bitdepth of stencil buffer
    //  fullscreen  - true: fullscreen, false: windowed
    //  [title       - title of application, optional]
    void createDisplay(uint width, uint height,
                        uint redBits, uint greenBits, uint blueBits,
                        uint alphaBits, uint depthBits, uint stencilBits,
                        bool fullscreen, const std::string& title="Photon App");

    // Function: createDisplay
    //  This function attempts to create a display with the given parameters.
    //
    // Parameters:
    //  width       - desired width of display
    //  height      - desired height of display
    //  bpp         - desired bits per pixel (aka bitdepth) of display
    //  depthBits   - desired bitdepth of depth buffer
    //  stencilBits - desired bitdepth of stencil buffer
    //  fullscreen  - true: fullscreen, false: windowed
    //  [title       - title of application, optional]
    void createDisplay(uint width, uint height, uint bpp,
                        uint depthBits, uint stencilBits, bool fullscreen,
                        const std::string& title="Photon App");
                        
    // Function: setTitle
    //  Sets title of application that shows up in title bar.
    //
    // Parameters:
    //  title - New title of application.
    void setTitle(const std::string& title);
                        
    // Function: getDisplayWidth
    //  Get the width of the display.
    //
    // Returns:
    //  Width of display in pixels.
    uint getDisplayWidth();

    // Function: getDisplayHeight
    //  Get the height of the display.
    //
    // Returns:
    //  Height of display in pixels.
    uint getDisplayHeight();
    
// Group: Ortho 
public:
    // Function: setOrthoView
    //  Sets new ortho viewport within a rectangular portion of the screen.
    //  All drawing is relative to the rectangle, x,y becomes 0,0 and anything  
    //  drawn outside rect is clipped.
    // 
    // Parameters:
    //  x - X coord for top left corner of new viewport.
    //  y - Y coord for top left corner of new viewport.
    //  viewWidth - Width of new viewport.
    //  viewHeight - Height of new viewport.
    //  orthoWidth - Width of ortho perspective.
    //  orthoHeight - Height of ortho perspective.
    void setOrthoView(int x, int y, int viewWidth, int viewHeight, 
                            scalar orthoWidth, scalar orthoHeight);

    // Function: setOrthoView
    //  Sets entire screen as current viewport with a given ortho perspective.
    // 
    // Parameters:
    //  width - Width of view.
    //  height - Height of view.
    void setOrthoView(scalar width, scalar height);

    // Function: setOrthoView
    //  Sets entire screen as current viewport with a 1:1 perspective.
    void setOrthoView();

// Group: Perspective
public:
    // Function: setPerspectiveView
    //  Creates a viewport with a given 3D perspective inside of a rectangular
    //  portion of the screen.
    //
    //  Note that <setDepthTestMode>(true) will be called as a side effect.
    // 
    // Parameters:
    //  x - X coord for top left corner of new viewport.
    //  y - Y coord for top left corner of new viewport.
    //  width - Width of new viewport.
    //  height - Height of new viewport.
    //  fovy - The y axis field of view angle, in degrees.
    //  zNear - Distance from viewer to near clipping plane.
    //  zFar - Distance from viewer to far clipping plane.
    void setPerspectiveView(int x, int y, int width, int height, 
                                scalar fovy, scalar zNear, scalar zFar);
    
    // Function: setPerspectiveView
    //  Sets entire screen as current viewport with a given 3D perspective.
    //
    //  Note that <setDepthTestMode>(true) will be called as a side effect.
    // 
    // Parameters:
    //  fovy - The y axis field of view angle, in degrees.
    //  zNear - Distance from viewer to near clipping plane.
    //  zFar - Distance from viewer to far clipping plane.
    void setPerspectiveView(scalar fovy, scalar zNear, scalar zFar);
    
// Group: Viewport/Projection 
//  These functions are called by the above Ortho/Perspective functions, very 
//  rarely do they need to be called directly.
public:
    // Function: setViewport
    //  Set the current viewport rectangle within the screen.
    void setViewport(int x, int y, int width, int height);
    
    // Function: setOrthoProjection
    //  Sets an orthographic projection matrix.
    // 
    // Parameters:
    //  width - Width of view.
    //  height - Height of view.
    void setOrthoProjection(scalar width, scalar height);
    
    // Function: setPerspectiveProjection
    //  Sets a perspective projection matrix.  
    //
    //  Note that <setDepthTestMode>(true) will be called as a side effect.
    // 
    // Parameters:
    //  fovy - The y axis field of view angle, in degrees.
    //  zNear - Distance from viewer to near clipping plane.
    //  zFar - Distance from viewer to far clipping plane.
    void setPerspectiveProjection(scalar fovy, scalar zNear, scalar zFar);
    
    // Function: setDepthBufferParams
    //  Toggle depth testing and clearing of depth buffer.
    //
    // Parameters:
    //  enable - if true, testing/clearing depth buffer is enabled, if false
    //              testing and clearing of depth buffer will be disabled.
    //  depth  - optional clear depth amount, clamped [0..1], default is 1
    void setDepthBufferParams(bool enable, scalar depth=1);

// Group: Input
public:
    // Function: keyPressed
    //  Check if a given key is currently pressed.
    //
    // Parameters:
    //  key - <KeyCode> of key to determine status of.
    //
    // Returns:
    //  true: key is pressed, false: key isn't pressed
    bool keyPressed(KeyCode key);
    
    // Function: getPressedKeys
    //  Obtain a list of all keys which are currently pressed.
    //
    // Returns:
    //  std::vector of <KeyCodes> of any pressed keys.
    std::vector<KeyCode> getPressedKeys();

    // Function: mouseButtonPressed
    //  Check if a given mouse button is currently pressed.
    //
    // Parameters:
    //  button - <MouseButton> to determine status of.
    //
    // Returns:
    //  true: button is pressed, false: button isn't pressed
    bool mouseButtonPressed(MouseButton button);

    // Function: getMouseX
    //  Gets current x location of mouse with respect to screen coordinates.
    //
    // Returns:
    //  Mouse x-coordinate, with respect to screen coordinates.
    int getMouseX();

    // Function: getMouseY
    //  Gets current y location of mouse with respect to screen coordinates.
    //
    // Returns:
    //  Mouse y-coordinate, with respect to screen coordinates.
    int getMouseY();

    // Function: getMouseWheelPos
    //  Gets current location of mouse wheel, treated as if wheel describes a
    //  third axis of movement for the mouse.
    //
    // Returns:
    //  Mouse wheel position, zero assumed to be starting position.
    int getMouseWheelPos();
    
// Group: Timing
public:

    // Function: getTime
    //  Get time, in seconds, that application has been running.
    //
    // Returns:
    //  Time, represented as a floating-point number in seconds, application has
    //  been running.
    scalar getTime();
    
    // Function: setFrameTimeSmoothing
    //  Sets number of frames used to smooth the timeDelta so that minor jitters
    //  in frramerate do not cause severe stuttering.
    //
    // Parameters:
    //  numFrames - Number of frames to average, setting to <= 1 turns off 
    //              smoothing of timeDelta.  (Recommend something >= 50, <= 500)
    void setFrameTimeSmoothing(int numFrames);
    
    // Function: getElapsedTime
    //  Finds the amount of time passed between frames, or average of a number
    //  of frames if <setFrameTimeSmoothing> has been called.
    //
    // Returns:
    //  Time (or average time) between frames.
    double getElapsedTime();

    // Function: getFramerate
    //  Gets number of frames per second the application is currently processing
    //  subject to smoothing by <setFrameTimeSmoothing>.
    //
    // Returns:
    //  Calculated number of frames per second.
    double getFramerate();
    
    // Function: setFixedUpdateStep
    //  Sets a fixed timestep to be used in calls to the current <State's> 
    //  update method.  This allows stability in physics systems.
    //
    // Parameters:
    //  enable - if true, will enable fixed timestepping (if false will disable)
    //  fixedStep - the timestep to use for the fixed step, ignored if disabling
    //  maxStep - if somehow the update portion get signifigantly behind the
    //            render portion, to avoid executing a large number of steps
    //            (hanging the program) an optional maxStep can be specified. 
    //            [default = 5*fixedStep]
    void setFixedUpdateStep(bool enable, scalar fixedStep, scalar maxStep=0);

// Group: State Management 
public:
    // Function: setState
    //  Set the current Application <State>, removing all other <States>.
    //
    // Template Parameters:
    //  StateT - Class derived from <State> to set as current.
    template<class StateT>
    void setState();

    // Function: pushState
    //  Push a new <State>, does not remove old <State>.
    //
    // Template Parameters:
    //  StateT - Class derived from <State> to push.
    template<class StateT>
    void pushState();

    // Function: popState
    //  Pop the current <State>, returning to the prior <State> on the stack.
    void popState();

#ifdef PHOTON_USE_OPENAL
// Group: AudioCore
public:
    // Function: getAudioCore
    //  Get the Application's <AudioCore>, should only be called after 
    //  <initAudioCore>.
    //
    // Return:
    //  Reference to the <AudioCore>.
   audio::AudioCore& getAudioCore();
   
   // Function: initAudioCore
   //  Initialize the <AudioCore>, should be done before attempting to access
   //  it via <getAudioCore>.
   //
   // Arguments:
   //  deviceName - Optional name for desired Audio device, will use default 
   //               device if none specified.
   void initAudioCore(const std::string& deviceName="");
#endif //PHOTON_USE_OPENAL

// Callbacks
public:
    static void GLFWCALL keyCallback(int key, int action);
    //static void GLFWCALL charCallback(int character, int action);
    static void GLFWCALL mouseButtonCallback(int button, int action);
    static void GLFWCALL mouseMoveCallback(int x, int y);
    static void GLFWCALL mouseWheelCallback(int pos);

// API Initialization
private:
    util::VersionInfo initPhysFS(const std::string& arg0);
    util::VersionInfo initGLFW();
    void initOpenGL();

// Data members
private:
    // version number for photon
    util::VersionInfo photonVer_;

    // display variables
    uint displayWidth_;
    uint displayHeight_;
    uint viewportWidth_;
    uint viewportHeight_;
    GLbitfield clearFlags_;
    
    // input system variables
    static std::vector<KeyCode> pressedKeys_;
    int mouseX_;
    int mouseY_;
    
    // timing variables
    bool active_;
    bool timerPaused_;
    bool unpauseOnActive_;
    scalar lastPause_;
    scalar pausedTime_;
    scalar elapsedTime_;
    scalar lastUpdate_;
    scalar fixedTimeStep_;
    scalar maxTimeStep_;
    scalar timeAccumulator_;
    std::valarray<scalar> frameTimes_;
    
    // other
    bool quit_;
    Kernel updateKernel_;
    Kernel renderKernel_;
    
    // state system
    static std::stack<StatePtr> stateStack_;

    // Cores
    #ifdef PHOTON_USE_OPENAL
    std::auto_ptr<audio::AudioCore> audioCore_;
    #endif //PHOTON_USE_OPENAL
};

template<class StateT>
void Application::setState()
{
    StatePtr newState(new StateT);

    // clear stack
    while(!stateStack_.empty())
    {
        popState();
    }
    stateStack_.push(newState); // make newState the only state on stack
}

template<class StateT>
void Application::pushState()
{
    StatePtr newState(new StateT);

    // if a state is currently running, pause it 
    if(!stateStack_.empty())
    {
        stateStack_.top()->onPause();
    }
    stateStack_.push(newState); // push newState on top of stack
}


}

#endif  //PHOTON_APPLICATION_HPP
