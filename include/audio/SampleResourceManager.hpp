//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: SampleResourceManager.hpp,v 1.2 2005/07/18 05:14:18 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#ifndef PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP
#define PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP

#include "ResourceManager.hpp"
#include "audio/Source.hpp"

namespace photon
{
namespace audio
{

// All that a Sample is is a bufferID, extremely simple resource management
class SampleResource : public Resource
{
public:
    uint bufferID;
};

class SampleResourceManager : public ResourceManager<SampleResource>
{
public:
    void getAudioData(const std::string& name, uint& bufferID);

private:
    virtual void loadResourceData(SampleResource &res,  
                                    const ResourceDescriptor& path);
    virtual void freeResourceData(SampleResource &res);
};

// Allow users to simply call a Sample a Sample
typedef Source<SampleResourceManager> Sample;

}
}

#endif  //PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP

#endif  //PHOTON_USE_OPENAL
