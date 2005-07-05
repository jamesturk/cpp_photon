//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.hpp,v 1.7 2005/07/05 06:44:56 cozman Exp $

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
//  Photon's <Singleton> core for audio manipulation/control.  Defines the
//  interface through which all audio related functions are performed.
//
// Parent:
//  <Singleton>
class AudioCore : public util::Singleton<AudioCore>
{

// Group: (Con/De)structors
public:
    // Function: AudioCore
    //  Initialize underlying APIs and setup <Task> internals.
    AudioCore();

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
    // Function: setDesiredDevice
    //  Set the name of the desired audio device to use.  Static function of
    //  AudioCore, must be called before AudioCore::initialize() or not at all.
    //
    //  If called, the initialization of the audio library will attempt to
    //  use the specified audio device, otherwise the default device will be
    //  used.
    //
    // Parameters:
    //  name - Name of audio device to use.
    static void setDesiredDevice(const std::string& name);
    
// Group: Error Checking
public:
    static std::string checkOpenALError();
    static void throwOpenALError(const std::string& func);

// OpenAL specifics
private:
    util::VersionInfo initOpenAL();
    

// data members
private:
    static std::string deviceName_;
    ALfloat listenerPos_[3];
    ALfloat listenerVel_[3];
    ALfloat listenerOri_[6];
};


}
}

#endif  //PHOTON_AUDIO_AUDIOCORE_HPP

#endif  //PHOTON_USE_OPENAL
