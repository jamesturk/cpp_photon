//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: entrypoint.cpp,v 1.1 2005/08/08 19:19:22 cozman Exp $

#include "entrypoint.hpp"
#include "Log.hpp"
#include "types.hpp"
#include "Application.hpp"

int main(int argc, const char** argv)
{
    // logging of uncaught exceptions to console
    photon::Log log;
    log.addSink(photon::LogSinkPtr(new photon::ConsoleSink("out")));

    try
    {
        new photon::Application(argv[0]);

        // push arguments into StrVec
        photon::StrVec args;
        for(int i=0; i < argc; ++i)
        {
            args.push_back(argv[i]);
        }
        
        int retVal = PhotonMain(args);
        
        photon::Application::destroy();

        return retVal;
    }
    catch(photon::Exception &e)     // log exceptions as errors (confusing?)
    {
        log.error() << e;
        return 1;
    }
    catch(photon::Error &e)         // log errors as critical errors 
    {
        log.critical() << e;
        return 1;
    }
}
