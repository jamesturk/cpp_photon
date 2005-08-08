//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Source.hpp,v 1.4 2005/08/08 21:39:41 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#ifndef PHOTON_AUDIO_SOURCE_HPP
#define PHOTON_AUDIO_SOURCE_HPP

#include "AL/al.h"

#include "ResourceManaged.hpp"
#include "audio/AudioCore.hpp"

namespace photon
{
namespace audio
{

// Class: Source
//  Simple OO wrapper around an OpenAL source, defines the interface used for
//  Sample and Music.
//
//  Source is a template class and can not be used directly, use either Sample
//  or Music.  Sample is for playing small files such as sound effects.  Music
//  is for streaming files such as background music.
// 
// Operators:
//  - Source = Source
//  - bool : True if source has loaded buffer, false if not.
//  - ostream& << Source
template <class ResMgrT>
class Source : public ResourceManaged<ResMgrT>
{
// Group: (Con/De)structors 
public:

    // Function: Source
    //  Default constructor, initalizes internal state of Source.
    Source();

    // Function: Source
    //  Copy constructor, copies another Source.
    // 
    // Parameters:
    //  rhs - Source to construct copy of.
    Source(const Source &rhs);

    // Function: Source
    //  Initializing constructor, loads Source via call to <open>.
    // 
    // Parameters:
    //  name - Name of the Source <Resource> to open.
    // 
    // See Also: 
    //  <open>
    Source(const std::string& name);
    
    // Function: ~Source
    //  Destructor for source, frees the OpenAL source resource.
    ~Source();

// Group: General
public:

    // Function: open
    //  Opens an audio file, supported formats are WAV and Ogg.
    // 
    // Parameters:
    //  name - Name of the Source <Resource> to open.
    void open(const std::string& name);

    Source& operator=(const Source& rhs);
    operator bool() const;

// Group: Source Control
public:
    
    // Function: play
    //  Starts the playback of the sound attached to the source.
    void play();
    
    // Function: stop
    //  Stops the playback of the sound attached to the source.
    void stop();
    
    // Function: pause
    //  Pauses the playback of the sound attached to the source.
    void pause();
    
    // Function: rewind
    //  Rewinds the position of the sound attached to the source.
    void rewind();
    
    // Function: setLooping
    //  Sets if the source's sound is looping or is played only once.
    //
    // Parameters:
    //  loop - If true, will make sound loop, otherwise will play only once.
    void setLooping(bool loop);

// Group: Accessors
public:

    // Function: isValid
    //  Determine status of Source.
    //
    // Returns:
    //  True if source is loaded, false if source is not loaded/initialized.
    bool isValid() const;

    // Function: isPlaying
    //  Determine if source is playing.
    //
    // Returns:
    //  True if source is playing, false if source is stopped.
    bool isPlaying() const;
    
    // Function: isLooping
    //  Determine if source is looping.
    //
    // Returns:
    //  True if source is looping, false if source is not looping.
    bool isLooping() const;

    //friend std::ostream& operator<<(std::ostream& o, const Source& rhs);
    
// Group: Resource Creation
public:

    // Function: addResource
    //  Define a new named resource.
    //  (Ex. Image::addResource("monkey","images/monkey.png") would 
    //   make it so that any attempts to load "monkey" would load the image 
    //   images/monkey.png)
    //
    // Parameters:
    //  name - Name to give to resource.
    //  path - Path of resource data file.
    static void addResource(const std::string& name, const std::string& path);
    
    // Function: addResource
    //  Define a new unaliased resource. (name == path).
    //  (Ex. Image::addResource("images/monkey.png") is essentially the same as
    //   Image::addResource("images/monkey.png","images/monkey.png")
    //
    // Parameters:.
    //  path - Path of resource data file.
    static void addResource(const std::string& path);
    
private:
    uint sourceID_; // sources store their own sourceID (can't resource manage)
    
    static const float ORIGIN[];    // use origin
};

template<class ResMgrT>
const float Source<ResMgrT>::ORIGIN[] = {0, 0, 0};

// you know the drill, Template Implementation //

template<class ResMgrT>
Source<ResMgrT>::Source()
{
    alGenSources(1, &sourceID_);
    AudioCore::throwOpenALError("Source::Source()");
}

template<class ResMgrT>
Source<ResMgrT>::Source(const Source &rhs) : 
    ResourceManaged<ResMgrT>(rhs)
{
    alGenSources(1, &sourceID_);
    AudioCore::throwOpenALError("Source::Source(const Source&)");
}

template<class ResMgrT>
Source<ResMgrT>::Source(const std::string& name)
{
    alGenSources(1, &sourceID_);
    AudioCore::throwOpenALError("Source::Source(const std::string&)");
    open(name);
}

template<class ResMgrT>
Source<ResMgrT>::~Source()
{
    if(alIsSource(sourceID_))
    {
        alDeleteSources(1, &sourceID_);
    }
}

template<class ResMgrT>
void Source<ResMgrT>::open(const std::string& name)
{
    uint bufferID;
    
    ResourceManaged<ResMgrT>::open(name);
    ResourceManaged<ResMgrT>::resMgr_.getAudioData(
        ResourceManaged<ResMgrT>::getName(), bufferID);
    
    // attach buffer to source
    alSourcei(sourceID_, AL_BUFFER, bufferID);
    alSourcef(sourceID_, AL_PITCH, 1.0);
    alSourcef(sourceID_, AL_GAIN, 1.0);
    alSourcefv(sourceID_, AL_POSITION, ORIGIN);
    alSourcefv(sourceID_, AL_VELOCITY, ORIGIN);
    
    AudioCore::throwOpenALError("Source::open");
}

template<class ResMgrT>
Source<ResMgrT>& Source<ResMgrT>::operator=(const Source<ResMgrT>& rhs)
{
    if(&rhs != this)
    {
        uint bufferID;
        
        ResourceManaged<ResMgrT>::operator=(rhs);
        ResourceManaged<ResMgrT>::resMgr_.getAudioData(
            ResourceManaged<ResMgrT>::getName(), bufferID);

        // attach buffer to source
        alSourcei(sourceID_, AL_BUFFER, bufferID);
        alSourcef(sourceID_, AL_PITCH, 1.0);
        alSourcef(sourceID_, AL_GAIN, 1.0);
        alSourcefv(sourceID_, AL_POSITION, ORIGIN);
        alSourcefv(sourceID_, AL_VELOCITY, ORIGIN);
        
        AudioCore::throwOpenALError("Source::operator=");
    }
    return *this;
}

template<class ResMgrT>
Source<ResMgrT>::operator bool() const
{
    return isValid();
}

template<class ResMgrT>
void Source<ResMgrT>::play()
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::play call.");
    }
    
    alSourcePlay(sourceID_);
}

template<class ResMgrT>
void Source<ResMgrT>::stop()
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::stop call.");
    }
    
    alSourceStop(sourceID_);
}

template<class ResMgrT>
void Source<ResMgrT>::pause()
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::pause call.");
    }
    
    alSourcePause(sourceID_);
}

template<class ResMgrT>
void Source<ResMgrT>::rewind()
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::rewind call.");
    }
    
    alSourceRewind(sourceID_);
}

template<class ResMgrT>
void Source<ResMgrT>::setLooping(bool loop)
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::setLooping call.");
    }
    
    alSourcei(sourceID_, AL_LOOPING, loop);
}

template<class ResMgrT>
bool Source<ResMgrT>::isValid() const
{
    return alIsSource(sourceID_) == AL_TRUE;
}

template<class ResMgrT>
bool Source<ResMgrT>::isPlaying() const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::isPlaying call.");
    }
    
    // check state 
    int state;
    alGetSourcei(sourceID_, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

template<class ResMgrT>
bool Source<ResMgrT>::isLooping() const
{
    if(!isValid())
    {
        throw PreconditionException("Invalid Source::isLooping call.");
    }
    
    // check looping status
    int loop;
    alGetSourcei(sourceID_, AL_LOOPING, &loop);
    return loop == AL_TRUE;
}

template<class ResMgrT>
void Source<ResMgrT>::addResource(const std::string& name, 
                                    const std::string& path)
{
    ResourceManaged<ResMgrT>::resMgr_.newResource(name, 
                                                    ResourceDescriptor(path));
}

template<class ResMgrT>
void Source<ResMgrT>::addResource(const std::string& path)
{
    ResourceManaged<ResMgrT>::resMgr_.newResource(path, 
                                                    ResourceDescriptor(path));
}

}
}

#endif  //PHOTON_AUDIO_SOURCE_HPP

#endif  //PHOTON_USE_OPENAL
