//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.cpp,v 1.1 2005/02/27 05:55:18 cozman Exp $

#include "audio/AudioCore.hpp"

#include <string>
#include "exceptions.hpp"

namespace photon
{
namespace audio
{
    
std::string AudioCore::getAudioDeviceName() const
{
    ALCdevice* device (alcGetContextsDevice( alcGetCurrentContext() ));
    std::string name ( reinterpret_cast<const char*>(
                        alcGetString(device, ALC_DEVICE_SPECIFIER)) );
    return name;
}

util::VersionInfo AudioCore::initOpenAL()
{
    ALCdevice* device;
    ALCcontext* context;
    std::stringstream ss;
    std::string junks;
    char junkc;
    uint major,minor;

    // obtain default device if no deviceName is set, otherwise use deviceName
    device = alcOpenDevice(deviceName_.empty() ? 0 : 
                reinterpret_cast<const ALubyte*>(deviceName_.c_str()) );

    if(device == 0)
    {
        throw APIError("Failed to obtain OpenAL device " + deviceName_ + ": " + 
                        checkOpenALError());
    }

    // create context
    context = alcCreateContext(device,0);

    if(context == 0)
    {
        throw APIError("Failed to obtain an OpenAL context: " + 
                        checkOpenALError());
    }

    alcMakeContextCurrent(context);

    ss << alGetString(AL_VERSION);
    ss >> junks >> major >> junkc >> minor;
    return util::VersionInfo(major,minor,0);
}

std::string AudioCore::checkOpenALError()
{
    ALenum errCode = alGetError();
    std::string err;

    switch(errCode)
    {
    case AL_NO_ERROR:
        // do nothing
        break;
    case AL_INVALID_NAME:
        err = "Invalid name/ID parameter in OpenAL call";
        break;
    case AL_INVALID_ENUM:
        err = "Invalid enum parameter in OpenAL call";
        break;
    case AL_INVALID_VALUE:
        err = "Invalid value parameter in OpenAL call";
        break;
    case AL_INVALID_OPERATION:
        err = "Invalid OpenAL operation";
        break;
    case AL_OUT_OF_MEMORY:
        err = "OpenAL out of memory";
        break;
    default:
        err = "Unknown OpenAL error.";
        break;
    }

    return err;
}

void AudioCore::setDesiredDevice(const std::string& name)
{
    deviceName_ = name;
}
    
std::string AudioCore::deviceName_; 

AudioCore::AudioCore()
{
    util::VersionInfo oalReq(1,0,0);    // requires OpenAL 1.0

    util::ensureVersion("OpenAL", initOpenAL(), oalReq);
}

AudioCore::~AudioCore()
{
    ALCcontext* context( alcGetCurrentContext() );
    ALCdevice*  device( alcGetContextsDevice(context) );

    // set current context to null
    alcMakeContextCurrent(0);

    // destroy context & device
    alcDestroyContext(context);
    alcCloseDevice(device);
}

}
}