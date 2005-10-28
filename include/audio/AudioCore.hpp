//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.hpp,v 1.15 2005/10/28 22:13:33 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#ifndef PHOTON_AUDIO_AUDIOCORE_HPP
#define PHOTON_AUDIO_AUDIOCORE_HPP

#include "AL/al.h"      // This file depends on OpenAL
#include "AL/alc.h"

// define ALchar if it isn't available
#ifndef ALchar
#define ALchar ALubyte
#endif

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
    AudioCore(const std::string& deviceName) {};
    
    // Function: ~AudioCore
    //  Shutdown underlying APIs.
    virtual ~AudioCore() { };

// Group: Accessors
public:
    // Function: getAudioDeviceName
    //
    //  Returns name of audio device currently in use, if available from 
    //  underlying audio API..
    virtual std::string getAudioDeviceName() const=0;
};

class OALAudioCore : public AudioCore
{

public:
    OALAudioCore(const std::string& deviceName);
    ~OALAudioCore();

public:
    std::string getAudioDeviceName() const;


public:
    // No-Doc Function: checkOpenALError
    //  Checks for OpenAL internal errors, returning a descriptive string if
    //  the OpenAL error state is currently set.  Will return an empty string
    //  if there is no error set.
    //
    // Returns:
    //  String describing OpenAL error, empty string if no error exists.
    static std::string checkOpenALError();
    
    // No-Doc Function: throwOpenALError
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

// data members specific to implementation
private:
    ALfloat listenerPos_[3];
    ALfloat listenerVel_[3];
    ALfloat listenerOri_[6];
};

}
}

#endif  //PHOTON_AUDIO_AUDIOCORE_HPP

#endif  //PHOTON_USE_OPENAL
