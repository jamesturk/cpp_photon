//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.7 2005/04/21 19:30:19 cozman Exp $

#include "Application.hpp"

#include "physfs.h"
#include "GL/gl.h"

#include <boost/lexical_cast.hpp>

#include "exceptions.hpp"
#include "Log.hpp"
#include "Kernel.hpp"
#include "AppCore.hpp"
#include "video/VideoCore.hpp"

namespace photon
{

Application::Application() :
    photonVer_(0,0,1)    // this is the current version
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0
    
    // create the singletons
    new Log;
    new Kernel;
    new AppCore;
    new video::VideoCore;

    // StrVec args;
    // 
    // for(int i=0; i < argc; ++i)
    // {
    //     args.push_back(argv[i]);
    // }
    
    util::ensureVersion("PhysFS", initPhysFS(arg0_.c_str()), physfsReq);
}

Application::~Application()
{
    PHYSFS_deinit();    //shutdown PhysFS

    // destroy the singletons
    AppCore::destroy();
    video::VideoCore::destroy();
    Kernel::destroy();
    Log::destroy();
}

void Application::setInitOptions(const char* arg0)
{
    arg0_ = arg0;
}

util::VersionInfo Application::initPhysFS(const char* arg0)
{
    PHYSFS_Version ver;
    PHYSFS_init(arg0);
    PHYSFS_addToSearchPath(arg0,0);
    PHYSFS_getLinkedVersion(&ver);
    return util::VersionInfo(ver.major, ver.minor, ver.patch);
}

std::string Application::arg0_;

}
