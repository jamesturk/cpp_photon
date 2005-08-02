//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AppCore.hpp,v 1.9 2005/08/02 23:07:51 cozman Exp $

#ifndef PHOTON_APPCORE_HPP
#define PHOTON_APPCORE_HPP

#include "types.hpp"
#include "util/VersionInfo.hpp"
#include "Task.hpp"
#include "InputListener.hpp"

#include <vector>

namespace photon
{

// Class: AppCore
//  Photon's core for application behavior.  Defines the interface through which
//  all "application" related functions are performed.  This means input, 
//  display creation, etc.
//
//  AppCore is the Core that essentially represents the window management,
//  input, and timing systems.
class AppCore
{

public:
    AppCore();
    ~AppCore();
    
    void init();
    void shutdown();

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
    
// Group: Input Listeners
public:

    // Function: addInputListener
    //  Registers an <InputListener> to listen for any input events so that it
    //  is notified when they occur.
    //
    // Parameters:
    //  listener - Pointer to <InputListener> to add.
    static void addInputListener(InputListener *listener);
    
    // Function: removeInputListener
    //  Removes an <InputListener> from the list of active listeners.
    //
    // Parameters:
    //  listener - Pointer to <InputListener> to remove.
    static void removeInputListener(InputListener *listener);
    
    static void GLFWCALL keyCallback(int key, int action);
    //static void GLFWCALL charCallback(int character, int action);
    static void GLFWCALL mouseButtonCallback(int button, int action);
    static void GLFWCALL mouseMoveCallback(int x, int y);
    //static void GLFWCALL mouseWheelCallback(int pos);

// Group: Timing
public:

    // Function: getTime
    //  Get time, in seconds, that application has been running.
    //
    // Returns:
    //  Time, represented as a floating-point number in seconds, application has
    //  been running.
    scalar getTime();

// Group: General
public:

    // Function: setTitle
    //  Sets title of application that shows up in title bar.
    //
    // Parameters:
    //  title - New title of application.
    void setTitle(const std::string& title);

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
    //  Gets number of frames per second the application is currently processing
    //
    // Returns:
    //  Current frames per second.
    double getFramerate();

// Group: Accessors
public:
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
    

    // UpdateTask, does the updating work of AppCore, registered as a Task
    //  so that user need not call something akin to AppCore::update() every 
    //  frame
    class UpdateTask : public Task
    {

    friend class AppCore;

    public:
        UpdateTask();

        void update();

    private:
        int mouseX_;
        int mouseY_;
        bool active_;
        bool timerPaused_;
        bool unpauseOnActive_;
        scalar lastPause_;
        scalar pausedTime_;
        scalar secPerFrame_;
        scalar lastUpdate_;
    };

// data members
private:
    uint dispWidth_;
    uint dispHeight_;
    shared_ptr<UpdateTask> task_;
    
    // input monitoring variables
    static std::vector<InputListener*> listeners_;
    static std::vector<KeyCode> pressedKeys_;

// API initialization
private:
    util::VersionInfo initGLFW();
};

}

#endif  //PHOTON_APPCORE_HPP
