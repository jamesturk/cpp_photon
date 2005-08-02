//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.hpp,v 1.10 2005/08/02 23:07:52 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#ifndef PHOTON_AUDIO_AUDIOCORE_HPP
#define PHOTON_AUDIO_AUDIOCORE_HPP

#include "AL/al.h"
#include "AL/alc.h"

#include "util/Singleton.hpp"
#include "util/VersionInfo.hpp"

namespace photon
{
namespace audio
{

// Class: AudioCore
//  Photon's core for audio manipulation/control.  Defines the interface through
//  which all audio related functions are performed.
class AudioCore
{

// Group: (Con/De)structors
public:
    // Function: AudioCore
    //  Initialize underlying APIs and setup <Task> internals.
    //AudioCore();
    AudioCore(const std::string& deviceName);
    
    // Function: ~AudioCore
    //  Shutdown underlying APIs.
    ~AudioCore();

// Group: Accessors
public:
    // Function: getAudioDeviceName
    //  Get name of active audio device.
    //
    // Returns:
    //  Name of audio device currently in use.
    std::string getAudioDeviceName() const;

// Group: Initialization
public:
    // Function: initAudioDevice
    //  Initialize audio device.  _MUST_ be called prior to any use of audio
    //  functionality.
    //
    //  Takes an optional parameter, if existant the initialization of the audio
    //  library will attempt to use the specified audio device, otherwise the 
    //  default device will be used.
    //
    // Parameters:
    //  deviceName - Name of audio device to use. (optional, default=default) 
    static void initAudioDevice(const std::string& deviceName="");
    
// Group: Error Checking
public:
    // Function: checkOpenALError
    //  Checks for OpenAL internal errors, returning a descriptive string if
    //  the OpenAL error state is currently set.  Will return an empty string
    //  if there is no error set.
    //
    // Returns:
    //  String describing OpenAL error, empty string if no error exists.
    static std::string checkOpenALError();
    
    // Function: throwOpenALError
    //  Checks for OpenAL internal errors, throwing an <APIError> if the OpenAL
    //  error state is set and doing nothing if not.  Optionally makes the
    //  thrown exception more descriptive by adding in a function string
    //  that describes then the OpenAL error was flagged.
    //
    // Parameters:
    //  func - Function in/after which the check for an OpenAL error takes place
    //
    // Throws:
    //  <APIError> if an OpenAL error state has been set.
    static void throwOpenALError(const std::string& func);

// OpenAL specifics
private:
    util::VersionInfo initOpenAL(const std::string& deviceName);

// data members
private:
    ALfloat listenerPos_[3];
    ALfloat listenerVel_[3];
    ALfloat listenerOri_[6];
};


}
}

#endif  //PHOTON_AUDIO_AUDIOCORE_HPP

#endif  //PHOTON_USE_OPENAL
