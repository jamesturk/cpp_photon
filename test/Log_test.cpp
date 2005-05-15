//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Log_test.cpp,v 1.1 2005/05/15 02:50:07 cozman Exp $

#include "photon.hpp"
using namespace photon;


class LogTest : public Application
{
public:
    int main(const StrVec& args)
    {
        Log log;
        LogSinkPtr a( new ConsoleSink("console") );
        LogSinkPtr b( new TextSink("text") );
        LogSinkPtr c( new HTMLSink("html") );
        
        log.note() << "this isn't seen";
        
        log.addSink(a);
        log.addSink(b);
        log.addSink(c);
        
        log.note() << "notice?";
        log.verbose() << "(insert verbosity here)";
        log.warning() << "consider yourself warned.";
        log.error() << "erroneous!";
        log.critical() << "Al the critic?";
        
        log.removeSink(b);
        
        log.note() << "only seen by a and c"  ;
        
        log.removeSinks();
        
        log.note() << "not seen at all!";
        
        return 0;
    }
};

ENTRYPOINT(LogTest)

