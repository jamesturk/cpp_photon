//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: entrypoint.hpp,v 1.6 2005/07/19 01:31:37 cozman Exp $


#ifndef PHOTON_ENTRYPOINT_HPP
#define PHOTON_ENTRYPOINT_HPP

#include "Log.hpp"

// Title: Entrypoint 

//  Macro: ENTRYPOINT
//  A macro which is used to specify the class containing the entrypoint.
//  For example, if the class PongGame is the class derived from <Application>
//  which implements main, in the file defining PongGame it is important to
//  include ENTRYPOINT(PongGame) so that the entry point becomes PongGame::main.

#define ENTRYPOINT(className)    int main(int argc, const char** argv)  \
                            { return photon::mainclass<className>(argc,argv); }

namespace photon
{

// function which does all the work of ENTRYPOINT
template<class App>
int mainclass(int argc, const char** argv)
{
    // logging of uncaught exceptions to console
    Log log;
    log.addSink(LogSinkPtr(new photon::ConsoleSink("out")));
    
    try
    {
        App::setInitOptions(argv[0]);
        
        App app;
        
        // push arguments into StrVec
        StrVec args;
        for(int i=0; i < argc; ++i)
        {
            args.push_back(argv[i]);
        }

        // hand arguments to Application::main and return what main returns
        return app.main(args);  
    }
    catch(Exception &e)     // log exceptions as errors (wow that's confusing)
    {
        log.error() << e;
        return 1;   
    }
    catch(Error &e)         // log errors as critical errors 
    {
        log.critical() << e;
        return 1;
    }
}

}

#endif  //PHOTON_ENTRYPOINT_HPP
