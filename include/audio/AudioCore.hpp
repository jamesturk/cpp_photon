//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore.hpp,v 1.1 2005/02/27 05:55:18 cozman Exp $

#ifndef PHOTON_AUDIO_AUDIOCORE_HPP
#define PHOTON_AUDIO_AUDIOCORE_HPP

#include "al.h"
#include "alc.h"

#include "util/Singleton.hpp"
#include "util/VersionInfo.hpp"

namespace photon
{
namespace audio
{

class AudioCore : public util::Singleton<AudioCore>
{
public:
    std::string getAudioDeviceName() const;

private:
    util::VersionInfo initOpenAL();
    static std::string checkOpenALError();

public:
    static void setDesiredDevice(const std::string& name);
    
private:
    static std::string deviceName_; 
    
// Singleton-required code
private:  
    AudioCore();
    ~AudioCore();

    friend class util::Singleton<AudioCore>;
    friend class std::auto_ptr<AudioCore>;
};


}
}

#endif  //PHOTON_AUDIO_AUDIOCORE_HPP
