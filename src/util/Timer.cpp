//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Timer.cpp,v 1.2 2005/03/15 18:52:07 cozman Exp $

#include "util/Timer.hpp"

namespace photon
{
namespace util
{

Timer::Timer(bool appTimeLinked) :
    appCore_(AppCore::getInstance()),
    appTimeLinked_(appTimeLinked)
{
    reset();	//initializes other members
}

Timer::~Timer()
{
}

void Timer::reset()
{
    lastPause_ = pausedTime_ = appCore_.getTime();
    paused_ = false;
}

void Timer::pause()
{
    if(!paused_)
    {
        lastPause_ = appCore_.getTime();
        paused_ = true;
    }
}

void Timer::unpause()
{
    if(paused_)
    {
        //when unpausing update the total paused time by that pause
        pausedTime_ += (appCore_.getTime()-lastPause_);
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
        return appCore_.getTime() - pausedTime_;   
    }
}

bool Timer::isPaused() const
{
    return paused_;
}

}
}
