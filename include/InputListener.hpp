//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: InputListener.hpp,v 1.1 2005/07/19 05:45:23 cozman Exp $

#ifndef PHOTON_INPUTLISTENER_HPP
#define PHOTON_INPUTLISTENER_HPP

#include "math/Vector2.hpp"

namespace photon
{

// Class: InputListener
//  Virtual class to handle user input, classes can derive from this to be 
//  notified of input events.
class InputListener
{
// Group: (Con/De)structors
public:

    // Function: InputListener
    //  Registers the InputListener to listen for input with <AppCore>.
    InputListener();

    // Function: ~InputListener
    //  Deregisters the listener with <AppCore>. so that it is no longer
    //  notified of events.
    virtual ~InputListener();

// Group: General
public:

    // Function: setActive
    //  Enable/Disable the InputListener.
    //
    // Parameters:
    //  active - Active state of the InputListener.
    void setActive(bool active);

    // Function: isActive
    //  Returns true if the InputListener is active.
    //
    // Returns: true if active, false if deactivated
    bool isActive() const;

// Group: Keyboard Actions
public:
    // Function: onKeyPress
    //  Called when a key is pressed.
    // 
    // Parameters:
    //  key - Key that has been pressed. 
    virtual void onKeyPress(int key);
    
    // Function: onKeyRelease
    //  Called when a key is released.
    // 
    // Parameters:
    //  key - Key that has been released.
    virtual void onKeyRelease(int key);

// Group: Mouse Actions
public:
    // Function: onMouseButtonPress
    //  Called when a mouse button is pressed.
    //
    // Parameters:
    //  button - Mouse button that was pressed.
    virtual void onMouseButtonPress(int button);
    
    // Function: onMouseButtonRelease
    //  Called when a mouse button is released.
    //
    // Parameters:
    //  button - Mouse button that was released.
    virtual void onMouseButtonRelease(int button);

    // Function: onMouseMove
    //  Called when the mouse is moved.
    //
    // Parameters:
    //  pos - Position of the mouse.
    virtual void onMouseMove(const math::Vector2& pos);
    
private:
    bool active_;
};

}

#endif  //PHOTON_INPUTLISTENER_HPP
