//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.5 2005/02/27 07:43:37 cozman Exp $


#include "Application.hpp"
#include "exceptions.hpp"

#include "physfs.h"

#include <sstream>

namespace photon
{

Application::Application() :
    photonVer_(0,0,1)    // this is the current version
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0

    util::ensureVersion("PhysFS", initPhysFS(arg0_.c_str()), physfsReq);
}

Application::~Application()
{
    PHYSFS_deinit();    //shutdown PhysFS
}

util::VersionInfo Application::initPhysFS(const char* arg0)
{
    PHYSFS_Version ver;
    PHYSFS_init(arg0);
    PHYSFS_addToSearchPath(arg0,0);
    PHYSFS_getLinkedVersion(&ver);
    return util::VersionInfo(ver.major, ver.minor, ver.patch);
}

void Application::setInitOptions(const char* appPath) 
{
    arg0_ = appPath;
}

std::string Application::arg0_; //static initializer

}
