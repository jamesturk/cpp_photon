//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AppCore.hpp,v 1.1 2005/02/27 07:43:37 cozman Exp $

#ifndef PHOTON_APPCORE_HPP
#define PHOTON_APPCORE_HPP

#include "types.hpp"
#include "glfw/types_glfw.hpp"
#include "util/VersionInfo.hpp"
#include "util/Singleton.hpp"

namespace photon
{

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

    // Function: 
    //  Get time, in seconds, that application has been running.
    //
    // Returns:
    //  Time, represented as a floating-point number in seconds, application has
    //  been running.
    scalar getTime();
   
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
