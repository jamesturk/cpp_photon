//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: SampleResourceManager.hpp,v 1.1 2005/07/05 06:44:56 cozman Exp $

#ifndef PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP
#define PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP

#include "ResourceManager.hpp"
#include "audio/Source.hpp"

namespace photon
{
namespace audio
{

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

typedef Source<SampleResourceManager> Sample;

}
}

#endif  //PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP
