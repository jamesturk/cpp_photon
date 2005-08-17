//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: TaskManager.cpp,v 1.1 2005/08/17 06:35:56 cozman Exp $

#include "util/TaskManager.hpp"

#include "exceptions.hpp"

namespace photon
{
namespace util
{

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
    killAllTasks();
}

void TaskManager::step(scalar timeDelta)
{
    std::list<TaskPtr>::iterator it;
    
    // loop through active tasks, updating each one
    for(it = tasks_.begin(); it != tasks_.end(); ++it)
    {
        TaskPtr& task(*it);
        
        // only update alive, non-paused tasks
        if(task->isAlive() && !task->isPaused())
        {
            task->update(timeDelta);
        }
    }

    // loop through tasks, removing any dead tasks
    for(it = tasks_.begin(); it != tasks_.end(); )
    {
        TaskPtr& task(*it);

        // remove dead tasks
        if(!task->isAlive())
        {
            task->onKill();     // symmetry with onStart, clean up act
            it = tasks_.erase(it);
        }
        else
        {
            ++it;   //advance iterator, if not deleting
        }
    }
}

void TaskManager::addTask(TaskPtr task)
{
    std::list<TaskPtr>::iterator it = tasks_.begin();
    // attempt to find task
    std::list<TaskPtr>::iterator found = std::find_if(tasks_.begin(), 
                                tasks_.end(),
                                std::bind2nd(TaskNameEq(), task->getName()) );
                                
    // if found task (meaning task w/ same name exists) throw exception
    if(found != tasks_.end())
    {
        throw PreconditionException("Attempted to add duplicate task \"" +  
                                    task->getName() + "\".");
    }
    
    task->onStart();    // called whenever a task is being started
    
    // find the first task in the list with a lower priority
    while(it != tasks_.end() && (*it)->getPriority() <= task->getPriority())
    {
        ++it;
    }
    tasks_.insert(it, task);    // insert task after iterator
}

void TaskManager::killTask(const std::string& taskName)
{
    // attempt to find the task
    std::list<TaskPtr>::iterator task = std::find_if(tasks_.begin(), 
                                tasks_.end(),
                                std::bind2nd(TaskNameEq(), taskName) );
    
    if(task != tasks_.end())    // kill task if found
    {
        (*task)->kill();
    }
    else
    {
        throw PreconditionException("Attempted to kill nonexistant task \"" +  
                                    taskName + "\".");
    }
}

void TaskManager::pauseTask(const std::string& taskName)
{
    // attempt to find the task
    std::list<TaskPtr>::iterator task = std::find_if(tasks_.begin(), 
                                tasks_.end(),
                                std::bind2nd(TaskNameEq(), taskName) );

    if(task != tasks_.end())    // pause task if found
    {
        (*task)->onPause();
    }
    else
    {
        throw PreconditionException("Attempted to pause nonexistant task \"" +  
                                    taskName + "\".");
    }
}

void TaskManager::unpauseTask(const std::string& taskName)
{
    // attempt to find the task
    std::list<TaskPtr>::iterator task = std::find_if(tasks_.begin(), 
                                tasks_.end(),
                                std::bind2nd(TaskNameEq(), taskName) );
    
    if(task != tasks_.end())    // unpause task if found
    {
        (*task)->onUnpause();
    }
    else
    {
        throw PreconditionException("Attempted to unpause nonexistant task \"" +
                                    taskName + "\".");
    }
}

void TaskManager::killAllTasks()
{
    // set all tasks to dead
    for(std::list<TaskPtr>::iterator it = tasks_.begin(); 
        it != tasks_.end(); 
        ++it)
    {
        (*it)->kill();
    }
}

bool TaskManager::TaskNameEq::operator()(const TaskPtr& lhs, 
                                    const std::string& rhs) const
{
    return lhs->getName() == rhs;
}

}
}
