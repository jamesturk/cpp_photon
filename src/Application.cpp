//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Application.cpp,v 1.14 2005/08/02 23:07:52 cozman Exp $

#include "Application.hpp"

#include "physfs.h"
#include "GL/gl.h"

#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"
#include "Log.hpp"
#include "Kernel.hpp"
#include "AppCore.hpp"
#include "video/VideoCore.hpp"
#include "audio/AudioCore.hpp"
#include "util/filesys/filesys.hpp"


namespace photon
{

Kernel Application::kernel_;    
AppCore Application::appCore_;
std::auto_ptr<video::VideoCore> Application::videoCore_;
std::auto_ptr<audio::AudioCore> Application::audioCore_;
std::string Application::arg0_;

Application::Application() :
    photonVer_(0,0,1)    // this is the current version
{
    util::VersionInfo physfsReq(1,0,0); // requires PhysFS 1.0.0
    util::ensureVersion("PhysFS", initPhysFS(), physfsReq);
    
    appCore_.init();        // init appcore
}

Application::~Application()
{
    appCore_.shutdown();    // shutdown appcore
    
    PHYSFS_deinit();        // shutdown PhysFS
}

Kernel& Application::getKernel()
{
    return kernel_;
}

AppCore& Application::getAppCore()
{
    return appCore_;
}

video::VideoCore& Application::getVideoCore()
{
    // return VideoCore if it has been created
    if(videoCore_.get() == 0)
    {
        throw PreconditionException("call to Application::getVideoCore() before"
                                    " Application::initAudioDevice");
    }
    return *videoCore_;
}

audio::AudioCore& Application::getAudioCore()
{
    // return AudioCore if it has been created
    if(audioCore_.get() == 0)
    {
        throw PreconditionException("call to Application::getAudioCore() before"
                                    " Application::initAudioDevice");
    }
    return *audioCore_;
}

void Application::initVideoCore(uint width, uint height)
{
    // create VideoCore, avoid double initializaiton
    if(videoCore_.get() == 0)
    {
        videoCore_.reset(new video::VideoCore(width, height));
    }
    else
    {
        throw PreconditionException("Attempt to double initialize VideoCore");
    }
}

void Application::initAudioCore(const std::string& deviceName)
{
    // create AudioCore, avoid double initializaiton
    if(audioCore_.get() == 0)
    {
        audioCore_.reset(new audio::AudioCore(deviceName));
    }
    else
    {
        throw PreconditionException("Attempt to double initialize AudioCore");
    }
}

void Application::setInitOptions(const char* arg0)
{
    arg0_ = arg0;
}

util::VersionInfo Application::initPhysFS()
{
    PHYSFS_Version ver;
    PHYSFS_init(arg0_.c_str());
    PHYSFS_addToSearchPath(PHYSFS_getBaseDir(),0);
    PHYSFS_getLinkedVersion(&ver);
    return util::VersionInfo(ver.major, ver.minor, ver.patch);
}

}
