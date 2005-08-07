//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Kernel.hpp,v 1.3 2005/08/07 07:12:46 cozman Exp $

#ifndef PHOTON_KERNEL_HPP
#define PHOTON_KERNEL_HPP

#include <list>
#include <algorithm>

#include "util/Singleton.hpp"
#include "Task.hpp"

namespace photon
{

// Class: Kernel
//  Kernel class, maintains a list of <Tasks> and manages their status,
//  handles adding, deleting, pausing, and unpausing tasks.
//
//  To use Kernel:
//      - (1) Add any tasks (should be derived from <Task>)
//      - (2) call <Kernel::run>
//      - (3) in order to avoid running forever, all tasks should eventually die
class Kernel : public util::Singleton<Kernel>
{

// Group: (Con/De)structors
public:
    // Function: Kernel
    //  Kernel constructor, initializes kernel singleton.
    Kernel();
    
    // Function: ~Kernel
    //  Kernel destructor, destroys kernel singleton.
    ~Kernel();

// Group: Running
public:
    // Function: step
    //  Steps the kernel, calling each active task once.
    //
    //  Each 'step' all tasks are run in order of their priorities, if two 
    //  tasks have the same priority, they are run in the order they were added.
    void step();

    // Function: run
    //  Runs tasks until all tasks are asleep or dead.
    //
    // See Also:
    //  <step>
    void run();

// Group: Task Management
public:
    // Function: addTask
    //  Add a new <Task> to the Kernel's list.  All tasks MUST have unique 
    //  names.
    //
    // Parameters:
    //  task - <TaskPtr> representing instance of <Task> subclass to add. 
    void addTask(TaskPtr task);
    
    // Function: killTask
    //  Kill a task in the Kernel task list.
    //  Dead tasks are removed in next loop through tasks. 
    //
    // Parameters:
    //  taskName - Name of task to kill.
    void killTask(const std::string& taskName);
    
    // Function: pauseTask
    //  Pause a task in the Kernel task list.
    //
    // Parameters:
    //  taskName - Name of task to pause.
    void pauseTask(const std::string& taskName);
    
    // Function: unpauseTask
    //  Unpause a task in the Kernel task list.
    //
    // Parameters:
    //  taskName - Name of task to unpause.
    void unpauseTask(const std::string& taskName);

    // Function: killAllTasks
    //  Kills all tasks.
    //  Dead tasks are removed in next loop through tasks.
    void killAllTasks();

// data members
private:

    //stored list of tasks (stored in order of priority highest to lowest)
    std::list<TaskPtr> tasks_; 
    
    //predicate for search
    class TaskNameEq : public std::binary_function<TaskPtr, std::string, bool>
    {
    public:
        bool operator()(const TaskPtr& lhs, const std::string& rhs) const;
    };
};

}

#endif  //PHOTON_KERNEL_HPP
