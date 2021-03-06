//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: State.hpp,v 1.5 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_STATE_HPP
#define PHOTON_STATE_HPP

#include "types.hpp"
#include "math/Vector2.hpp"

namespace photon
{

// Class: State
//  Pure virtual State class, used as base class for Photon's state system.
//
//  Photon's State system is extremely simple yet also very convenient. Simply 
//  by creating classes that fulfill the <State> interface you can use Photon
//  to manage the state that the game is in. 
//
//  Implement as many or as few of the members of State as needed (the only 
//  necessary member being <render>) and make the state current via 
//  <Application::setState>/<Application::pushState>.  Once a state is made  
//  current it's update and render methods will be called every frame until 
//  either a new state is made current or the application ends.
//
//  The active state is also notified of events as they occur, overloading any
//  of the on* functions will result in the overloaded version being called 
//  when the particular event happens while the state is active.
class State
{
// Group: (Con/De)structors
public:
    // Function: State
    //  A State's constructor is called whenever the state is made active via
    //  <Application::setState>.
    State() { };
    
    // Function: ~State
    //  A State's destructor is called whenever the state is no longer the 
    //  active state (the application ends, or a new state is made active).
    virtual ~State() { };

// Group: State Functions
public:
    // Function: update
    //  All of a state's logic should go in update, it is called every frame
    //  before the rendering process begins.  Nothing should be drawn to the 
    //  screen within update because it will be cleared before it is shown.
    virtual void update(scalar timeDelta) { };
    
    // Function: render
    //  The only required member of State, anything that should be drawn to the
    //  screen while the State is active should be drawn in render.  Game logic
    //  inside of render should be kept to a minimum for optimum performance.
    virtual void render()=0;
    
    // Function: onPause
    //  If a state is executing and a new state is pushed onto the stack via
    //  <Application::pushState> the state will be paused until a time that it
    //  is either unpaused or popped from the stack itself.  When it is paused
    //  the state management system will call onPause which may perform any 
    //  necessary work before the state goes idle.
    virtual void onPause() { };
    
    // Function: onResume
    //  If a state has been paused and is then made current again by the 
    //  state(s) pushed on top of it being popped, the state management system
    //  will call onResume allowing the state to undo any work that had been 
    //  done in <onPause>.  
    virtual void onResume() { };

// Group: Keyboard Actions
public:
    // Function: onKeyPress
    //  Called when a key is pressed.
    // 
    // Parameters:
    //  key - <KeyCode> of key that has been pressed. 
    virtual void onKeyPress(KeyCode key) { };
    
    // Function: onKeyRelease
    //  Called when a key is released.
    // 
    // Parameters:
    //  key - <KeyCode> of key that has been released.
    virtual void onKeyRelease(KeyCode key) { };

// Group: Mouse Actions
public:
    // Function: onMouseButtonPress
    //  Called when a mouse button is pressed.
    //
    // Parameters:
    //  button - <MouseButton> that was pressed.
    virtual void onMouseButtonPress(MouseButton button) { };
    
    // Function: onMouseButtonRelease
    //  Called when a mouse button is released.
    //
    // Parameters:
    //  button - <MouseButton> that was released.
    virtual void onMouseButtonRelease(MouseButton button) { };

    // Function: onMouseMove
    //  Called when the mouse is moved with the amount the mouse was moved by
    //  NOT with the new position.
    //
    //  If the new position is needed it can be obtained via 
    //  <Application::getMouseX> and <Application::getMouseY>.
    //
    // Parameters:
    //  delta - Change in mouse position.
    virtual void onMouseMove(const math::Vector2& delta) { };
    
    // Function: onMouseScroll
    //  Called when mouse wheel is scrolled.
    //
    // Parameters:
    //  dir - <ScrollDir> describing if mouse wheel was scrolled up or down.
    virtual void onMouseScroll(ScrollDir dir) { };
};

typedef shared_ptr<State> StatePtr;

}

#endif  //PHOTON_STATE_HPP
