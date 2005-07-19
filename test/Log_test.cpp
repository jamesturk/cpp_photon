//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Log_test.cpp,v 1.2 2005/07/19 20:37:04 cozman Exp $

#include "photon.hpp"
using namespace photon;

// extremely simple log test application
class LogTest : public Application
{
public:
    int main(const StrVec& args)
    {
        // create the log and add three sinks
        Log log;
        LogSinkPtr a( new ConsoleSink("console") ); // standard error output
        LogSinkPtr b( new TextSink("textlog") );        // plaintext log
        LogSinkPtr c( new HTMLSink("htmllog") );        // html formatted log
        
        // logged before sinks are added, so not shown
        log.note() << "this isn't seen";
        
        // add the three sinks
        log.addSink(a);
        log.addSink(b);
        log.addSink(c);
        
        // demo of the 5 log levels
        log.note() << "notice?";
        log.verbose() << "(insert verbosity here)";
        log.warning() << "consider yourself warned.";
        log.error() << "erroneous!";
        log.critical() << "Al the critic?";
        
        log.removeSink(b);  // remove b and log a message to a and c
        log.note() << "only seen by a and c"  ;
        
        // remove all sinks and log a message that is not shown
        log.removeSinks();
        log.note() << "not seen at all!";
        
        return 0;
    }
};

ENTRYPOINT(LogTest)

