//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.2 2005/02/13 22:12:03 cozman Exp $
//
// Revisions:
//  $Log: Application.cpp,v $
//  Revision 1.2  2005/02/13 22:12:03  cozman
//  .h->.hpp
//
//  Revision 1.1  2005/02/07 02:00:49  cozman
//  Application re-integrated
//
//


#include "Application.hpp"
#include "exceptions.hpp"

#include "physfs.h"
#include "glfw.h"

#include <sstream>

namespace photon
{

Application::Application(const char* arg0) :
    photonVer(0,0,1)    // this is the current version
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0
    util::VersionInfo glfwReq(2,4,2);   // requires GLFW 2.4.2
    
    ensureVersion("PhysFS", initPhysFS(arg0), physfsReq);
    ensureVersion("GLFW", initGLFW(), glfwReq);
}

Application::~Application()
{
    PHYSFS_deinit();    //shutdown PhysFS
    glfwTerminate();    //shutdown GLFW
}

void Application::ensureVersion(const std::string& library,
                                const util::VersionInfo& version,
                                const util::VersionInfo& required)
{
    std::stringstream ss;

    if(version < required)
    {
        ss << library << " version " << required << " required; " <<
            version << "used, please update.";
        throw APIError(ss.str());
    }
}

util::VersionInfo Application::initPhysFS(const char* arg0)
{
    PHYSFS_Version ver;
    PHYSFS_init(arg0);
    PHYSFS_addToSearchPath(arg0,0);
    PHYSFS_getLinkedVersion(&ver);
    return util::VersionInfo(ver.major, ver.minor, ver.patch);
}

util::VersionInfo Application::initGLFW()
{
    int maj,min,patch;
    glfwInit();
    glfwGetVersion(&maj,&min,&patch);
    return util::VersionInfo(maj,min,patch);
}

}
