//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AppCore.hpp,v 1.2 2005/03/01 07:51:04 cozman Exp $

#ifndef PHOTON_APPCORE_HPP
#define PHOTON_APPCORE_HPP

#include "types.hpp"
#include "glfw/types_glfw.hpp"
#include "util/VersionInfo.hpp"
#include "util/Singleton.hpp"

namespace photon
{

// Class: AppCore
//  Photon's <Singleton> core for application behavior.  Defines the interface 
//  through which all "application" related functions are performed.
//
//  AppCore is the Core that essentially represents the window management, 
//  input, and timing systems.
//
// Parent:
//  <Singleton>
class AppCore : public util::Singleton<AppCore>
{
   
// Group: Video
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
    //  title       - title of application   
    void createDisplay(uint width, uint height, 
                        uint redBits, uint greenBits, uint blueBits, 
                        uint alphaBits, uint depthBits, uint stencilBits,
                        bool fullscreen, const std::string &title);

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
    //  title       - title of application   
    void createDisplay(uint width, uint height, uint bpp, 
                        uint depthBits, uint stencilBits, bool fullscreen,
                        const std::string &title);

    // Function: updateDisplay
    //  Updates the display, usually involves flipping the front/back buffers.
    void updateDisplay();

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
    
// Group: Application 
public:
    // Function: update
    //  Updates the  
    void update();

    // Function: setTitle
    //  Sets title of application that shows up in title bar.
    // 
    // Parameters:
    //  title - New title of application.
    void setTitle(const std::string& title);

    // Function: requestQuit
    //  Sets the internal quit flag to true.
    void requestQuit();

    // Function: quitRequested
    //  Checks the internal quit flag, if a quit has been requested, 
    //  the application should comply.
    //
    // Returns: 
    //  State of internal quit flag, if true application should quit ASAP.
    bool quitRequested();

    // Function: isActive
    //  Checks if application is active, which on most systems simply means it 
    //  has focus.
    // 
    // Returns:    
    //  True if application is active, false otherwise.
    bool isActive();

    // Function: getElapsedTime
    //  Finds the amount of time passed between frames, useful for time-based 
    //  movement.
    // 
    // Returns: 
    //  Time between current frame and last frame. (1/<getFramerate>())
    double getElapsedTime();
    
    // Function: getFramerate
    //  Gets number of frames per second the application is currently being run at.
    // 
    // Returns: 
    //  Current frames per second.
    double getFramerate();

// data members
private:
    bool quitRequested_;
    bool active_;
    bool timerPaused_;
    bool unpauseOnActive_;
    scalar lastPause_;
    scalar pausedTime_;
    scalar secPerFrame_;
    scalar lastUpdate_;

// API initialization
private:
    util::VersionInfo initGLFW();

// Singleton-required code
private:  
    AppCore();
    ~AppCore();

    friend class util::Singleton<AppCore>;
    friend class std::auto_ptr<AppCore>;
};

}

#endif  //PHOTON_APPCORE_HPP
