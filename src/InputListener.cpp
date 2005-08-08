//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: InputListener.cpp,v 1.3 2005/08/08 19:19:22 cozman Exp $

#include "InputListener.hpp"

#include "Application.hpp" 

namespace photon
{

InputListener::InputListener() :
    active_(true)
{
    Application::addInputListener(this);
}

InputListener::~InputListener()
{
    Application::removeInputListener(this);
}

void InputListener::setActive(bool active)
{
    active_ = active;
}

bool InputListener::isActive() const
{
    return active_;
}

// do nothing, overloaded as needed
void InputListener::onKeyPress(KeyCode key) { }
void InputListener::onKeyRelease(KeyCode key) { }
void InputListener::onMouseButtonPress(MouseButton button)  { }
void InputListener::onMouseButtonRelease(MouseButton button) { }
void InputListener::onMouseMove(const math::Vector2& pos) { }


}
