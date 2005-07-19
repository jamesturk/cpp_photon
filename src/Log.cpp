//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Log.cpp,v 1.9 2005/07/19 01:31:38 cozman Exp $

#include "Log.hpp"

#include <algorithm>
#include "exceptions.hpp"

namespace photon
{ 

Log::Log()
{
}

Log::~Log()
{
    removeSinks();  // drop all sinks (also flushes output)
}

void Log::addSink(LogSinkPtr sink)
{
    flush();

    // search through list of sinks to avoid adding same sink twice
    for(std::list<LogSinkPtr>::iterator it = sinks_.begin();
        it != sinks_.end();
        ++it)
    {
        if(sink == *it || sink->getName() == (*it)->getName())
        {
            throw PreconditionException("Log already contains sink: " +
                                        sink->getName());
        }
    }

    sinks_.push_back(sink); // add sink if unique
}

void Log::removeSink(const std::string& sinkName)
{
    flush();
    
    // find sink and erase it
    for(std::list<LogSinkPtr>::iterator it = sinks_.begin();
        it != sinks_.end();
        ++it)
    {
        if((*it)->getName() == sinkName)
        {
            sinks_.erase(it);
        }
    }
}

void Log::removeSink(LogSinkPtr sink)
{
    flush();
    
    // search for sink 
    std::list<LogSinkPtr>::iterator it =
        std::find(sinks_.begin(),sinks_.end(),sink);

    // remove sink if it exists
    if(it != sinks_.end())
    {
        sinks_.erase(it);
    }
}

void Log::removeSinks()
{
    flush();    // make sure last message gets flushed to sinks

    sinks_.clear();     // empty entire sink list
}

void Log::flush()
{
    std::string str = buffer_.str();    // get string from buffer
    if(str.length())    // if a message exists, write it to all sinks
    {
        for(std::list<LogSinkPtr>::iterator it = sinks_.begin();
            it != sinks_.end();
            ++it)
        {
            (*it)->writeMessage(lastLevel_,str);
        }
        buffer_.str("");    // clear message
    }
}

// note, verbose, warning, error, critical all flush the existing buffer
// set the level and return the stringstream for writing
std::ostream& Log::note()
{
    flush();
    lastLevel_ = LOG_NOTE;
    return buffer_;
}

std::ostream& Log::verbose()
{
    flush();
    lastLevel_ = LOG_VERBOSE;
    return buffer_;
}

std::ostream& Log::warning()
{
    flush();
    lastLevel_ = LOG_WARNING;
    return buffer_;
}

std::ostream& Log::error()
{
    flush();
    lastLevel_ = LOG_ERROR;
    return buffer_;
}

std::ostream& Log::critical()
{
    flush();
    lastLevel_ = LOG_CRITICAL;
    return buffer_;
}

}
