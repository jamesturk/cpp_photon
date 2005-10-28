//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.cpp,v 1.15 2005/10/28 22:13:03 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#include "audio/AudioCore.hpp"

#include <string>
#include "exceptions.hpp"

namespace photon
{
namespace audio
{


OALAudioCore::OALAudioCore(const std::string& deviceName) : 
    AudioCore(deviceName)
{ 
    //util::VersionInfo oalReq(0,0,7);    // requires OpenAL 1.0 (TODO: check?)
    //util::ensureVersion("OpenAL", initOpenAL(), oalReq);
    
    initOpenAL(deviceName);   // don't check version for now
}

OALAudioCore::~OALAudioCore()
{
    // retrieve both the context and device
    ALCcontext* context( alcGetCurrentContext() );
    ALCdevice*  device( alcGetContextsDevice(context) );

    // destroy context & device
    alcDestroyContext(context);
    alcCloseDevice(device);

    // set current context to null
    alcMakeContextCurrent(0);
}

std::string OALAudioCore::getAudioDeviceName() const
{
    ALCdevice* device (alcGetContextsDevice( alcGetCurrentContext() ));
    std::string name ( reinterpret_cast<const char*>(
                        alcGetString(device, ALC_DEVICE_SPECIFIER)) );
                        
    return name;
}

std::string OALAudioCore::checkOpenALError()
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

void OALAudioCore::throwOpenALError(const std::string& func)
{
    std::string err( checkOpenALError() );
    if(err.length())    // throw exception if non-empty string
    {
        throw APIError(err + " within " + func);
    }
}

util::VersionInfo OALAudioCore::initOpenAL(const std::string& deviceName)
{
    ALCdevice* device(0);
    ALCcontext* context(0);
    std::stringstream ss;   // stream for parsing version
    char junkc;             // junk character for parsing
    uint major,minor;       // version numbers
    std::string extra;      // extra string for OpenAL extra info

    // obtain default device if no deviceName is set, otherwise use deviceName
    device = alcOpenDevice(deviceName.empty() ? 0 :
                reinterpret_cast<const ALchar*>(deviceName.c_str()) );

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

    // format is major.minor extra-info
    ss << alGetString(AL_VERSION);
    ss >> major >> junkc >> minor >> extra;

    throwOpenALError("OALAudioCore::initOpenAL");
    
    return util::VersionInfo(major,minor,0,extra);
}

}
}

#endif  //PHOTON_USE_OPENAL
