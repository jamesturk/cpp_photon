//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Kernel.cpp,v 1.2 2005/07/19 01:31:38 cozman Exp $

#include "Kernel.hpp"

#include "exceptions.hpp"

#include "Log.hpp"

namespace photon
{

Kernel::Kernel()
{
}

Kernel::~Kernel()
{
}
    
void Kernel::run()
{
    // loop on activeTasks
    while(!tasks_.empty())
    {
        std::list<TaskPtr>::iterator it;
        
        // loop through active tasks, updating each one
        for(it = tasks_.begin(); it != tasks_.end(); ++it)
        {
            TaskPtr& task(*it);
            
            // only update alive, non-paused tasks
            if(task->isAlive() && !task->isPaused())
            {
                task->update();
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
}

void Kernel::addTask(TaskPtr task)
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
    while(it != tasks_.end() && task->getPriority() <= (*it)->getPriority())
    {
        ++it;
    }
    tasks_.insert(it, task);    // insert task after iterator
}

void Kernel::killTask(const std::string& taskName)
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

void Kernel::pauseTask(const std::string& taskName)
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

void Kernel::unpauseTask(const std::string& taskName)
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

void Kernel::killAllTasks()
{
    // set all tasks to dead
    for(std::list<TaskPtr>::iterator it = tasks_.begin(); 
        it != tasks_.end(); 
        ++it)
    {
        (*it)->kill();
    }
}

bool Kernel::TaskNameEq::operator()(const TaskPtr& lhs, 
                                    const std::string& rhs) const
{
    return lhs->getName() == rhs;
}

}
