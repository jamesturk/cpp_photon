//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.hpp,v 1.5 2005/03/01 07:51:04 cozman Exp $

#ifndef PHOTON_APPLICATION_HPP
#define PHOTON_APPLICATION_HPP

#include <vector>
#include <string>

#include <boost/utility.hpp>

#include "types.hpp"
#include "util/VersionInfo.hpp"

namespace photon
{

// Class: Application
//  Abstract main class, all photon applications should derive from API-specific
//  implementations of Application.
//
//  Derived classes are made entrypoint via <ENTRYPOINT>.
class Application : public boost::noncopyable
{

// Group: (Con/De)structors 
public:
    // Function: Application
    //  Default constructor, initializes the internal state & dependencies.
    Application();

    // Function: ~Application
    //  Default destructor, shuts down dependencies.
    virtual ~Application();

    // Function: main
    //  Pure virtual, must be defined by derived class, using some preprocessor
    //  magic (<MAINCLASS>) on the derived class
    //  this becomes the entry point for a Amph application. 
    //
    // Parameters:
    //  args - <ArgList> containing arguments passed to program.
    //
    // Returns: 0 upon success, other upon failure.
    //          (Same as main in Standard C/C++).
    //
    // See Also:
    //  <ENTRYPOINT>
    virtual int main(StrVec args)=0;

// Behind the scenes
public:
    // Function: setInitOptions(const char* arg0)
    //  Internal use function, used to set initialization options.
    //  (params not documented since function signature is subject to change and
    //  should not be relied on by user-level code)
    static void setInitOptions(const char* appPath);
    
// Group: API Initialization
private:
    // Function: initPhysFS
    //  Initialize PhysFS for use.
    //
    // Parameters:
    //  arg0 - Path to application (argv[0])
    //
    // Returns:
    //  <VersionInfo> with PhysFS version.
    util::VersionInfo initPhysFS(const char* arg0);

// Data Members
private:
    scalar secPerFrame_;
    scalar lastUpdate_;
    bool active_;
    bool unpauseOnActive_;
    bool quitRequested_;

    // version number for photon
    util::VersionInfo photonVer_;

    // arg0 from command line
    static std::string arg0_;
};

}

#endif  //PHOTON_APPLICATION_HPP
