//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: LogSink.h,v 1.1 2005/01/27 03:35:23 cozman Exp $
//
// Revisions:
//  $Log: LogSink.h,v $
//  Revision 1.1  2005/01/27 03:35:23  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#ifndef PHOTON_LOGSINK_H
#define PHOTON_LOGSINK_H

#include <string>
#include <fstream>

namespace photon
{ 

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
class LogSink
{

// Group: (Con/De)structors
public:

    // Function: LogSink
    //  LogSink constructor, requires a name.
    //
    // Parameters:
    //  name_ - Name of LogSink, every LogSink should have a unique name.
    //  dynamic_ - Tells if the sink is dynamically allocated.
    //            This flag is false by default, and should be true if Log
    //            should delete the sink when it is done.
    LogSink(std::string name, bool dynamic=false);

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

    // Function: isDynamic
    //  Checks if sink is dynamic.
    //
    // Returns:
    //  True if log is dynamically allocated, false if not.
    bool isDynamic() const;
    
private:
    std::string name_;
    bool dynamic_;

    //assignment left undefined
    LogSink(const LogSink&);
    LogSink& operator=(const LogSink&);
};


// Class: ConsoleSink
//  <LogSink> to be used with <Log> for simple console output.
class ConsoleSink : public LogSink
{
public:
    ConsoleSink(std::string name, bool dynamic=false);
    virtual ~ConsoleSink();
    
    virtual void writeMessage(LogLevel level, std::string msg);
};

// Class: TextSink
//  <LogSink> to be used with <Log> for simple text file output.
class TextSink : public LogSink
{
public:
    TextSink(std::string name, bool dynamic=false);
    virtual ~TextSink();
    
    virtual void writeMessage(LogLevel level, std::string msg);
private:
    std::ofstream out_;
};

// Class: HtmlSink
//  <LogSink> to be used with <Log> for simple HTML output.
class HtmlSink : public LogSink
{
public:
    HtmlSink(std::string name, bool dynamic=false);
    virtual ~HtmlSink();
    
    virtual void writeMessage(LogLevel level, std::string msg);
private:
    std::ofstream out_;
};

}

#endif  //PHOTON_LOGSINK_H
