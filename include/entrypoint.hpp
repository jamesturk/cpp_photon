//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: entrypoint.hpp,v 1.1 2005/02/13 22:12:03 cozman Exp $
//
// Revisions:
//  $Log: entrypoint.hpp,v $
//  Revision 1.1  2005/02/13 22:12:03  cozman
//  .h->.hpp
//
//  Revision 1.1  2005/02/07 02:00:48  cozman
//  Application re-integrated
//
//


#ifndef PHOTON_ENTRYPOINT_HPP
#define PHOTON_ENTRYPOINT_HPP

#include "Log.hpp"

/* Title: Entrypoint */

/*
    Macro: ENTRYPOINT
    A macro which is used to specify the class containing the entrypoint.
    For example, if the class PongGame is the class derived from <Application>
    which implements main, in the file defining PongGame it is important to
    include ENTRYPOINT(PongGame) so that the entry point becomes PongGame::main.
*/
#define ENTRYPOINT(className)    int main(int argc, char *argv[])  \
                            { return photon::mainclass<className>(argc,argv); }

namespace photon
{

// function which does all the work of MAINCLASS
template<class App>
int mainclass(int argc, char *argv[])
{
    try
    {
        StrVec args;
        for(int i=0; i < argc; ++i)
            args.push_back(argv[i]);
        App app(argv[0]);
        return app.main(args);
    }
    catch(photon::Exception &e)
    {
        photon::log.error() << e;
        return 0;
    }
    catch(photon::Error &e)
    {
        photon::log.critical() << e;
        return 1;
    }
}

}

#endif  //PHOTON_ENTRYPOINT_HPP
