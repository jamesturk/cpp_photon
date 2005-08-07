//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Task.hpp,v 1.4 2005/08/07 07:12:46 cozman Exp $

#ifndef PHOTON_TASK_HPP
#define PHOTON_TASK_HPP

#include <string>

#include "types.hpp"

namespace photon
{

// Type: TaskPriority
enum PriorityLevel
{
    PRI_APP_UPDATE,     // special priority for Application updating (first)
    
    // user-level priorities all lie in logic area
    PRI_HIGHEST,        
    PRI_HIGH, 
    PRI_NORMAL, 
    PRI_LOW,
    PRI_LOWEST,
    
    PRI_VIDEO_UPDATE,   // special priority for clearing screen/video buffers
    PRI_RENDER          // special priority for rendering (right after clear)
    
    // It is also important that no priorities fall between render/app update
    // so that flow of applications is:
    //  1) Update & SwapBuffers
    //  2) Logic & User Level tasks
    //  3) Clear screen/buffers
    //  4) Render
    //  5) SwapBuffers again (see step 1)
};

// Class: Task
//  Abstract class for tasks, which are runnable classes for use with <Kernel>.
//
//  When writing a task, only update() needs to be overloaded.
class Task
{
// Group: (Con/De)structors
public:
    // Function: Task
    //  Constructor, every task needs a name and priority.
    //
    // Parameters:
    //  name - Name for task, must be unique!
    //  priority - Optional argument for desired priority for the Task, 
    //              controls order in which tasks are run by the <Kernel>.
    //              Default Priority is PRI_NORMAL
    Task(const std::string& name, PriorityLevel priority=PRI_NORMAL);
    
    // Function: ~Task
    //  Virtual destructor, exists simply to make inheritance safe.
    virtual ~Task();
    
// Group: Control
public:
    // Function: update
    //  Pure virtual, every child task must overload it's own update(), when a 
    //  task is active this is called every 'frame.'
    virtual void update()=0;
    
    // Function: onStart
    //  Virtual function, overload to define behavior when the task is started.
    virtual void onStart();
    
    // Function: onKill
    //  Virtual function, overload to define behavior when the task is killed.
    virtual void onKill();
    
    // Function: onPause
    //  Virtual function, overload to define behavior every time that the 
    //  task is paused.
    //
    // Note:
    //  Children of onPause should call Task::onPause to let the task know it's
    //  been paused.
    virtual void onPause();
    
    // Function: onUnpause
    //  Virtual function, overload to define behavior every time that the 
    //  task is unpaused.
    //
    // Note:
    //  Children of onUnpause should call Task::onUnpause to let the task know 
    //  it's been paused.
    virtual void onUnpause();
    
    // Function: kill
    //  Sets state of application to dead, dead tasks remove themselves from 
    //  the Kernel's task pool.
    void kill();
    
// Group: Accessors
public:
    // Function: getName
    //  Get the name of the task.
    //
    // Return:
    //  Name of task.
    std::string getName() const;

    // Function: getPriority
    //  Get the priority of the task.
    //
    // Return:
    //  priority of task.
    uint getPriority() const;

    // Function: isAlive
    //  Check if task is alive or not. 
    //
    // Return:
    //  true if task is alive, false if task has been killed
    bool isAlive() const;

    // Function: isPaused
    //  Check if task is paused or not. 
    //
    // Return:
    //  true iff task is paused
    bool isPaused() const;

// data members
private:
    std::string name_;          // all tasks need a unique name
    PriorityLevel priority_;    // priority determines ordering of tasks
    bool alive_;                // if false, task will be pruned
    bool paused_;               // if false task won't be executed
};

// Type: TaskPtr
//  Pointer to a task, used since Task is abstract and will always be accessed 
//  via a pointer.
typedef shared_ptr<Task> TaskPtr;

}

#endif  //PHOTON_TASK_HPP
