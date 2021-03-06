//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Timer.cpp,v 1.5 2005/08/07 07:12:48 cozman Exp $

#include "util/Timer.hpp"
#include "Application.hpp"

namespace photon
{
namespace util
{

Timer::Timer(bool appTimeLinked) :
    appTimeLinked_(appTimeLinked)
{
    reset();	//initializes other members
}

Timer::~Timer()
{
}

void Timer::reset()
{
    lastPause_ = pausedTime_ = getTimeInternal();
    paused_ = false;
}

void Timer::pause()
{
    if(!paused_)
    {
        lastPause_ = getTimeInternal();
        paused_ = true;
    }
}

void Timer::unpause()
{
    if(paused_)
    {
        //when unpausing update the total paused time by that pause
        pausedTime_ += (getTimeInternal()-lastPause_);
        paused_ = false;
    }
}

double Timer::getTime() const
{
    if(paused_) 
    {
        //when paused timer adjusted to subtract currently paused time
        return lastPause_ - pausedTime_;
    }
    else
    {
        //paused time is the total time the program has been paused
        return getTimeInternal() - pausedTime_;   
    }
}

bool Timer::isPaused() const
{
    return paused_;
}

double Timer::getTimeInternal() const
{
    if(appTimeLinked_)
    {
        // get from Application timer if linked
        return Application::getInstance().getTime();  
    }
    else
    {
        return glfwGetTime();       // raw timer if not linked
    }
}

}
}
