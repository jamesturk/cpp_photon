//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: LogSink.h,v 1.3 2005/02/04 08:11:54 cozman Exp $
//
// Revisions:
//  $Log: LogSink.h,v $
//  Revision 1.3  2005/02/04 08:11:54  cozman
//  switched Log to shared_ptrs and added extra flushes
//
//  Revision 1.2  2005/01/27 05:24:11  cozman
//  minor documentation update
//
//  Revision 1.1  2005/01/27 03:35:23  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#ifndef PHOTON_LOGSINK_H
#define PHOTON_LOGSINK_H

#include <string>
#include <fstream>

#include "types.h"

namespace photon
{ 

// Title: Logging Utilities
    
// Enum: LogLevel
//      Enumeration defining severity of an error.
//
// Values:
//      LOG_NOTE        - A note, highest priority so that they are always
//                          printed, not used for errors, only for temporary
//                          notes.
//      LOG_VERBOSE     - Verbose warning, lowest priority.
//      LOG_WARNING     - A warning, used for non critical failures.
//      LOG_ERROR       - Normal error, used for potential serious failures.
//      LOG_CRITICAL    - Critical error, used for failures which are threats to
//                          stability.
enum LogLevel
{
    LOG_NOTE,
    LOG_VERBOSE,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
};

// Class: LogSink
//  Base class for all LogSinks to be used with <Log>, derived classes must
//  define message(LogLevel level, std::string string).
//  A LogSink recieves any messages passed to the log it's registered with.
//
// Children:
//  <ConsoleSink>
//  <TextSink>
//  <HTMLSink>
class LogSink
{

// Group: (Con/De)structors
public:

    // Function: LogSink
    //  LogSink constructor, requires a name.
    //
    // Parameters:
    //  name_ - Name of LogSink, every LogSink should have a unique name.
    LogSink(std::string name);

    // Function: ~LogSink
    //  Virtual destructor, available to make inheritance safe.
    virtual ~LogSink();

// Group: Functions
public:

    // Function: writeMessage
    //  Pure virtual function which derived classes must define to write the
    //  message.
    //
    // Parameters:
    //  level - <LogLevel> of log event.
    //  msg - String describing log message.
    virtual void writeMessage(LogLevel level, std::string msg)=0;

// Group: Accessors
public:

    // Function: getName
    //  Gets name of the sink.
    //
    // Returns:
    //  Name of the LogSink.
    std::string getName() const;
    
    virtual std::ostream& getStream()=0;
    
private:
    std::string name_;

    //assignment left undefined
    LogSink(const LogSink&);
    LogSink& operator=(const LogSink&);
};

// Type: LogSinkPtr
//  Pointer to a log sink, used since LogSink is abstract and will always
//  be accessed via a pointer.
typedef shared_ptr<LogSink> LogSinkPtr;

// Class: ConsoleSink
//  <LogSink> to be used with <Log> for simple console output.
//
// See Also:
//  <TextSink>, <HTMLSink>
//
// Parent:
//  <LogSink>
class ConsoleSink : public LogSink
{
public:
    ConsoleSink(std::string name);
    virtual ~ConsoleSink();
    
    virtual void writeMessage(LogLevel level, std::string msg);
    virtual std::ostream& getStream();
};

// Class: TextSink
//  <LogSink> to be used with <Log> for simple text file output.
//
// See Also:
//  <ConsoleSink>, <HTMLSink>
//
// Parent:
//  <LogSink>
class TextSink : public LogSink
{
public:
    TextSink(std::string name);
    virtual ~TextSink();
    
    virtual void writeMessage(LogLevel level, std::string msg);
    virtual std::ostream& getStream();
private:
    std::ofstream out_;
};

// Class: HTMLSink
//  <LogSink> to be used with <Log> for simple HTML output.
//
// See Also:
//  <TextSink>, <ConsoleSink>
//
// Parent:
//  <LogSink>
class HTMLSink : public LogSink
{
public:
    HTMLSink(std::string name);
    virtual ~HTMLSink();
    
    virtual void writeMessage(LogLevel level, std::string msg);
    virtual std::ostream& getStream();
private:
    std::ofstream out_;
};

}

#endif  //PHOTON_LOGSINK_H
