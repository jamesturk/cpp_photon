//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Timer.hpp,v 1.5 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_UTIL_TIMER_HPP
#define PHOTON_UTIL_TIMER_HPP

namespace photon
{
namespace util
{


// Class: Timer
//  Class capable of keeping track of time.
//  Time is kept in double format, representing seconds.
class Timer
{

// Group: (Con/De)structors
public:
    // Function: Timer
    //  Initializes timer, timer is running starting at it's creation.  
    //  If this is not desired behavior call <reset> when you want it to start.
    //
    // Parameters:
    //  appTimeLinked - Option only available on creation of timer. When true  
    //      timer will pause when the Application timer is paused. 
    //      [default: true]
    Timer(bool appTimeLinked=true);
    
    // Function: ~Timer
    //  Virtual destructor, does nothing, exists only to make Timer inheritance 
    //  safe.
    virtual ~Timer();

// Group: General
public:
    // Function: reset
    //  Reset timer to 0, will unpause timer if paused.
    void reset();
    
    // Function: pause
    //  Pause timer.
    void pause();
    
    // Function: unpause
    //  Unpause timer if paused.
    void unpause();

// Group: Accessors 
public:
    // Function: getTime
    //  Get time in seconds.  (ie. A value of .001 means 1 millisecond.)
    double getTime() const;
    
    // Function: isPaused
    //  Check paused/unpaused status of timer.
    bool isPaused() const;
    
private:
    double getTimeInternal() const;   // get time from source timer
    
// data members
private:
    bool appTimeLinked_;
    bool paused_;
    double pausedTime_;
    double lastPause_;
};

}
}

#endif  //PHOTON_UTIL_TIMER_HPP
