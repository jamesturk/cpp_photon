//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.cpp,v 1.9 2005/07/19 05:56:08 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#include "audio/AudioCore.hpp"

#include <string>
#include "exceptions.hpp"

namespace photon
{
namespace audio
{

AudioCore::AudioCore(const std::string& deviceName) 
{
    //util::VersionInfo oalReq(0,0,7);    // requires OpenAL 1.0 (TODO: check?)
    //util::ensureVersion("OpenAL", initOpenAL(), oalReq);
    
    initOpenAL(deviceName);   // don't check version for now 
}

AudioCore::~AudioCore()
{
    // retrieve both the context and device
    ALCcontext* context( alcGetCurrentContext() );
    ALCdevice*  device( alcGetContextsDevice(context) );

    // set current context to null
    alcMakeContextCurrent(0);

    // destroy context & device
    alcDestroyContext(context);
    alcCloseDevice(device);
}

std::string AudioCore::getAudioDeviceName() const
{
    ALCdevice* device (alcGetContextsDevice( alcGetCurrentContext() ));
    std::string name ( reinterpret_cast<const char*>(
                        alcGetString(device, ALC_DEVICE_SPECIFIER)) );
                        
    return name;
}

std::string AudioCore::checkOpenALError()
{
    ALenum errCode = alGetError();  // fetch error code
    std::string err;

    // interpret error code
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
    default:    // not sure how conforming implementations are with error codes
        err = "Unknown OpenAL error";
        break;
    }

    return err;
}

void AudioCore::throwOpenALError(const std::string& func)
{
    std::string err( checkOpenALError() );
    if(err.length())    // throw exception if non-empty string
    {
        throw APIError(err + " within " + func);
    }
}

util::VersionInfo AudioCore::initOpenAL(const std::string& deviceName)
{
    ALCdevice* device(0);
    ALCcontext* context(0);
    std::stringstream ss;   // stream for parsing version
    std::string junks;      // junk string for parsing
    char junkc;             // junk character for parsing
    uint major,minor,patch; // version numbers

    // obtain default device if no deviceName is set, otherwise use deviceName
    device = alcOpenDevice(deviceName.empty() ? 0 :
                reinterpret_cast<const ALubyte*>(deviceName.c_str()) );

    if(device == 0)
    {
        throw APIError("Failed to obtain OpenAL device " + deviceName + ": " +
                        checkOpenALError());
    }

    // create context
    context = alcCreateContext(device,0);

    if(context == 0)
    {
        throw APIError("Failed to obtain an OpenAL context: " +
                        checkOpenALError());
    }

    alcMakeContextCurrent(context); // context must be current to get version
    
    // setup listener to default position
    ALfloat posvel[] = { 0.0, 0.0, 0.0 };
    ALfloat ori[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
    alListenerfv(AL_POSITION, posvel);
	alListenerfv(AL_VELOCITY, posvel);
	alListenerfv(AL_ORIENTATION, ori);

    // OpenAL needs a standard version string format badly
    ss << alGetString(AL_VERSION);
#if defined(WINVER)
    ss >> junks >> major >> junkc >> minor;   // format is "OpenAL 1.0"
#elif defined(linux)
    ss >> major >> junkc >> minor >> junkc >> patch;
#else
    #warning OpenAL only built on Windows/Linux, find out version on OSX
#endif
    
    return util::VersionInfo(major,minor,patch);
}

void AudioCore::initAudioDevice(const std::string& deviceName)
{
    new AudioCore(deviceName);
}


}
}

#endif  //PHOTON_USE_OPENAL
