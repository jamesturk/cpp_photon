//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.hpp,v 1.3 2005/02/16 06:58:05 cozman Exp $

#ifndef PHOTON_APPLICATION_HPP
#define PHOTON_APPLICATION_HPP

#include <vector>
#include <string>

#include "types.hpp"
#include "util/VersionInfo.hpp"

namespace photon
{

// Class: Application
//  Main class, from which all applications using Photon should be derived.
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
    // Function: ensureVersion
    //  Checks a version of a library against the required version, throws
    //  an APIError if the version is not met.
    //
    // Parameters:
    //  library - Name of library being initialized.
    //  version - Version of library being used.
    //  required - Required version of library.
    void ensureVersion(const std::string& library,
                        const util::VersionInfo& version,
                        const util::VersionInfo& required);
    
    // Function: initPhysFS
    //  Initialize PhysFS for use.
    //
    // Parameters:
    //  arg0 - Path to application (argv[0])
    util::VersionInfo initPhysFS(const char* arg0);
    
    // Function: initGLFW
    //  Initialize GLFW for use.
    util::VersionInfo initGLFW();
    
// Behind the scenes
public:
    // Function: setInitOptions(const char* arg0)
    //  Internal use function, used to set initialization options.
    //  (params not documented since function signature is subject to change and
    //  should not be relied on by user-level code)
    static void setInitOptions(const char* appPath);

// Data Members
private:
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
