//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.hpp,v 1.4 2005/02/27 07:43:37 cozman Exp $

#ifndef PHOTON_APPLICATION_HPP
#define PHOTON_APPLICATION_HPP

#include <vector>
#include <string>

#include "types.hpp"
#include "util/VersionInfo.hpp"

namespace photon
{

// Class: Application
//  Abstract main class, all photon applications should derive from API-specific
//  implementations of Application.
//
//  Derived classes are made entrypoint via <ENTRYPOINT>.
class Application
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

// Behind the scenes
public:
    // Function: setInitOptions(const char* arg0)
    //  Internal use function, used to set initialization options.
    //  (params not documented since function signature is subject to change and
    //  should not be relied on by user-level code)
    static void setInitOptions(const char* appPath);

// Data Members
private:
    scalar secPerFrame_;
    scalar lastUpdate_;
    bool active_;
    bool unpauseOnActive_;
    bool quitRequested_;

    // Variable: photonVer_
    //  Contains version identifier for photon.
    util::VersionInfo photonVer_;

    // Variable: arg0_
    //  Contains 0th argument from command line, obtained via <setInitOptions>
    //  and used by PhysFS initialization.
    static std::string arg0_;
};

}

#endif  //PHOTON_APPLICATION_HPP
