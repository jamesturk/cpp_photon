//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Log.cpp,v 1.4 2005/02/13 22:12:03 cozman Exp $
//
// Revisions:
//  $Log: Log.cpp,v $
//  Revision 1.4  2005/02/13 22:12:03  cozman
//  .h->.hpp
//
//  Revision 1.3  2005/02/07 01:48:27  cozman
//  string references
//
//  Revision 1.2  2005/02/04 08:11:54  cozman
//  switched Log to shared_ptrs and added extra flushes
//
//  Revision 1.1  2005/01/27 03:35:24  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

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
    flush();
    removeSinks();
}

void Log::addSink(LogSinkPtr sink)
{
    flush();

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

    sinks_.push_back(sink);
}

void Log::removeSink(const std::string& sinkName)
{
    flush();
    
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
    
    std::list<LogSinkPtr>::iterator it =
        std::find(sinks_.begin(),sinks_.end(),sink);

    if(it != sinks_.end())
    {
        sinks_.erase(it);
    }
}

void Log::removeSinks()
{
    flush();

    sinks_.clear();
}

void Log::flush()
{
    std::string str = buffer_.str();
    if(str.length())
    {
        for(std::list<LogSinkPtr>::iterator it = sinks_.begin();
            it != sinks_.end();
            ++it)
        {
            (*it)->writeMessage(lastLevel_,str);
        }
        buffer_.str("");
    }
}

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

Log log;

}
