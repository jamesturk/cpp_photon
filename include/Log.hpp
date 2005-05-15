//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Log.hpp,v 1.6 2005/05/15 02:51:10 cozman Exp $

#ifndef PHOTON_LOG_HPP
#define PHOTON_LOG_HPP

#include <string>
#include <list>
#include <sstream>

#include "util/Singleton.hpp"
#include "LogSink.hpp"

namespace photon
{ 

// Class: Log
//  Log class for photon, Log passes all messages to any attached <LogSinks>,
//  which can then take care of any output which is desired.
class Log
{

// Group: (Con/De)structors
public:
    // Function: Log
    //  Log constructor, initializes log singleton.
    Log();
    
    // Function: ~Log
    //  Log destructor, destroys log singleton.
    ~Log();

// Group: Sink Maintenance
public:

    // Function: addSink
    //  Adds a sink to the Log, sinks are given access to all messages passed
    //  into the log.
    //
    // Parameters:
    //  sink - Pointer to <LogSink> to add to Log.
    void addSink(LogSinkPtr sink);

    // Function: removeSink
    //  Remove a sink from the log by name.
    //
    //  Parameters:
    //      sinkName - Name of sink to remove.
    void removeSink(const std::string& sinkName);

    // Function: removeSink
    //  Remove a sink from the log.
    //
    // Parameters:
    //  sink - Pointer to sink to remove.
    void removeSink(LogSinkPtr sink);

    // Function: removeSinks
    //  Remove all sinks from log.
    void removeSinks();

// Group: Stream Access
public:

    // Function: note
    //  Accesses stream, any messages passed into note are given to associated
    //  <LogSinks> with a <LogLevel> of LOG_NOTE.
    //
    // Returns:
    //  Stream to pass errors to.
    std::ostream& note();

    // Function: verbose
    //  Accesses stream, any messages passed into verbose are given to
    //  associated <LogSinks> with a <LogLevel> of LOG_VERBOSE.
    //
    // Returns:
    //  Stream to pass errors to.
    std::ostream& verbose();

    // Function: warning
    //  Accesses stream, any messages passed into warning are given to
    //  associated <LogSinks> with a <LogLevel> of LOG_WARNING.
    //
    // Returns:
    //  Stream to pass errors to.
    std::ostream& warning();

    // Function: error
    //  Accesses stream, any messages passed into error are given to associated
    //  <LogSinks> with a <LogLevel> of LOG_ERROR.
    //
    // Returns:
    //  Stream to pass errors to.
    std::ostream& error();

    // Function: critical
    //  Accesses stream, any messages passed into critical are given to
    //  associated <LogSinks> with a <LogLevel> of LOG_CRITICAL.
    //
    // Returns:
    //  Stream to pass errors to.
    std::ostream& critical();

    // Function: flush
    //  Flushes the log, is generally not required.  Output is handed to the
    //  sinks when flush is called.
    void flush();
    
private:
    std::stringstream buffer_;
    LogLevel lastLevel_;
    std::list<LogSinkPtr> sinks_;
};

}

#endif  //PHOTON_LOG_HPP
