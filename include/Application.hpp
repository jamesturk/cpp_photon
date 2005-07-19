//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.hpp,v 1.9 2005/07/19 01:31:37 cozman Exp $

#ifndef PHOTON_APPLICATION_HPP
#define PHOTON_APPLICATION_HPP

#include <vector>
#include <string>

#include <boost/utility.hpp>

#include "types.hpp"
#include "util/VersionInfo.hpp"
#include "Task.hpp"

namespace photon
{

// Class: Application
//  Abstract main class, all photon applications should derive from Application.
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

// Group: Main
public:
    // Function: main
    //  Pure virtual, must be defined by derived class, using some preprocessor
    //  magic (<MAINCLASS>) on the derived class
    //  this becomes the entry point for a Photon application.
    //
    // Parameters:
    //  args - <ArgList> containing arguments passed to program.
    //
    // Returns: 0 upon success, other upon failure.
    //          (Same as main in Standard C/C++).
    //
    // See Also:
    //  <ENTRYPOINT>
    virtual int main(const StrVec& args)=0;

// behind the scenes
public:
    static void setInitOptions(const char* arg0);

// Group: API Initialization
private:
    util::VersionInfo initPhysFS();

private:
    // version number for photon
    util::VersionInfo photonVer_;

    static std::string arg0_;
};

}

#endif  //PHOTON_APPLICATION_HPP
