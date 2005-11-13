//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: TaskManager.hpp,v 1.2 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_UTIL_TASKMANAGER_HPP
#define PHOTON_UTIL_TASKMANAGER_HPP

#include <list>
#include <algorithm>

#include "Task.hpp"

namespace photon
{
namespace util
{

// Class: TaskManager
//  TaskManager class, maintains a list of <Tasks> and manages their status,
//  handles adding, deleting, pausing, and unpausing tasks.
//
//  To use TaskManager:
//      - Add any tasks (should be derived from <Task>)
//      - Call step() every frame when task should update.
class TaskManager
{

// Group: (Con/De)structors
public:
    // Function: TaskManager
    //  TaskManager constructor, initializes task manager
    TaskManager();
    
    // Function: ~TaskManager
    //  TaskManager destructor, destroys task manager
    ~TaskManager();

// Group: Running
public:
    // Function: step
    //  Steps the task manager, calling each active task once.
    //
    //  Each 'step' all tasks are run in order of their priorities, if two 
    //  tasks have the same priority, they are run in the order they were added.
    //
    // Parameters:
    //  timeDelta - The time elapsed between frames.
    void step(scalar timeDelta);

// Group: Task Management
public:
    // Function: addTask
    //  Add a new <Task> to the TaskManager's list.  All tasks MUST have unique 
    //  names.
    //
    // Parameters:
    //  task - <TaskPtr> representing instance of <Task> subclass to add. 
    void addTask(TaskPtr task);
    
    // Function: killTask
    //  Kill a task in the TaskManager task list.
    //  Dead tasks are removed in next loop through tasks. 
    //
    // Parameters:
    //  taskName - Name of task to kill.
    void killTask(const std::string& taskName);
    
    // Function: pauseTask
    //  Pause a task in the TaskManager task list.
    //
    // Parameters:
    //  taskName - Name of task to pause.
    void pauseTask(const std::string& taskName);
    
    // Function: unpauseTask
    //  Unpause a task in the TaskManager task list.
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
}

#endif  //PHOTON_UTIL_TASKMANAGER_HPP
