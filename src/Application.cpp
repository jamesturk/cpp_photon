//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.1 2005/02/07 02:00:49 cozman Exp $
//
// Revisions:
//  $Log: Application.cpp,v $
//  Revision 1.1  2005/02/07 02:00:49  cozman
//  Application re-integrated
//
//


#include "Application.h"

#include "physfs.h"

namespace photon
{

Application::Application(const char* arg0)
{
    PHYSFS_init(arg0);  //init PhysFS
}

Application::~Application()
{
    PHYSFS_deinit();    //shutdown PhysFS
}

}
