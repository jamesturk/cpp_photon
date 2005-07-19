//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: InputListener.cpp,v 1.1 2005/07/19 05:45:24 cozman Exp $

#include "InputListener.hpp"

#include "AppCore.hpp" 

namespace photon
{

InputListener::InputListener() :
    active_(true)
{
    AppCore::addInputListener(this);
}

InputListener::~InputListener()
{
    AppCore::removeInputListener(this);
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
void InputListener::onKeyPress(int key) { }
void InputListener::onKeyRelease(int key) { }
void InputListener::onMouseButtonPress(int button)  { }
void InputListener::onMouseButtonRelease(int button) { }
void InputListener::onMouseMove(const math::Vector2& pos) { }


}
