//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.h,v 1.1 2005/02/07 02:00:48 cozman Exp $
//
// Revisions:
//  $Log: Application.h,v $
//  Revision 1.1  2005/02/07 02:00:48  cozman
//  Application re-integrated
//
//

#ifndef PHOTON_APPLICATION_H
#define PHOTON_APPLICATION_H

#include <vector>
#include <string>

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
    //
    // Parameters:
    //  arg0 - Path to application (argv[0])
    Application(const char* arg0);

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
};

}

#endif  //PHOTON_APPLICATION_H
