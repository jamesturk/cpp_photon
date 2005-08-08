//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: entrypoint.hpp,v 1.8 2005/08/08 19:19:25 cozman Exp $


#ifndef PHOTON_ENTRYPOINT_HPP
#define PHOTON_ENTRYPOINT_HPP

#include "Log.hpp"

// Title: PhotonMain
//  PhotonMain is the entrypoint for all Photon applications, attempting to use
//  main will result in an error message since main is defined within the 
//  library.  Using PhotonMain as an entrypoint allows you to bypass any manual
//  initialization of the core Photon library.
//
// Example PhotonMain Usage:
// (code)
//
// class MainMenu : public State
// {
//     ...
// };
//
// int PhotonMain(const StrVec& args)
// {
//     // create window
//     Application::getInstance().createDisplay(800,600,32,0,0,false);
// 
//     // set current state
//     Application::getInstance().setCurrentState<MainMenu>();
//
//     // can also add any tasks here 
// 
//     // run until finished
//     Kernel::getInstance().run();
//     
//     return 0;
// }
// (end)


// Function: PhotonMain
//  Entrypoint for Photon applications.
//
// Arguments:
//  args - <StrVec> containing command line arguments.
//
// Returns:
//  zero on success, non-zero on failure, just like standard main. 
int PhotonMain(const photon::StrVec& args);


int main(int argc, const char** argv);

#endif  //PHOTON_ENTRYPOINT_HPP
