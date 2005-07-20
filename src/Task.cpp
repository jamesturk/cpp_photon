//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Task.cpp,v 1.3 2005/07/20 06:12:54 cozman Exp $

#include "Task.hpp"

namespace photon
{

Task::Task(const std::string& name, uint priority) :
    name_(name), priority_(priority), alive_(true), paused_(false)
{ 
}

// do nothing.. again (oh how I wish destructors were virtual by default)
Task::~Task() { }

// do nothings (not pure-virtual since some tasks may not need special behavior)
void Task::onStart() { }
void Task::onKill() { }

void Task::onPause() 
{
    paused_ = true; 
}

void Task::onUnpause() 
{ 
    paused_ = false; 
}

void Task::kill()
{
    alive_ = false;
}

std::string Task::getName() const
{
    return name_;
}

uint Task::getPriority() const
{
    return priority_;
}

bool Task::isAlive() const
{
    return alive_;
}

bool Task::isPaused() const
{
    return paused_;
}

}
