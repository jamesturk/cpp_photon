//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Log.h,v 1.3 2005/02/07 01:48:26 cozman Exp $
//
// Revisions:
//  $Log: Log.h,v $
//  Revision 1.3  2005/02/07 01:48:26  cozman
//  string references
//
//  Revision 1.2  2005/02/04 08:11:54  cozman
//  switched Log to shared_ptrs and added extra flushes
//
//  Revision 1.1  2005/01/27 03:35:23  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#ifndef PHOTON_LOG_H
#define PHOTON_LOG_H

#include <string>
#include <list>
#include <sstream>

#include "LogSink.h"

namespace photon
{ 

// Class: Log
//  Log class for photon, Log passes all messages to any attached <LogSinks>,
//  which can then take care of any output which is desired.
class Log
{

public:
    Log();
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

    //assignment left undefined
    Log(const Log &rhs);
    Log& operator=(const Log &rhs);
};

//Define a log to be used throughout photon
extern Log log;

}

#endif  //PHOTON_LOG_H
