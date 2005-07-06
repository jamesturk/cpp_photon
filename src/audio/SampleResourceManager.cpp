//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: SampleResourceManager.cpp,v 1.2 2005/07/06 02:10:07 cozman Exp $

#include "audio/SampleResourceManager.hpp"
#include "audio/AudioCore.hpp"
#include "util/FileBuffer.hpp"

#include "AL/al.h"
#include "AL/alut.h"

namespace photon
{
namespace audio
{

void SampleResourceManager::getAudioData(const std::string& name,  
                                            uint& bufferID)
{
    SampleResource resource( getResource(name) );
    bufferID = resource.bufferID;
}

void SampleResourceManager::loadResourceData(SampleResource &res, 
                                            const ResourceDescriptor& desc)
{
    util::FileBuffer buf(desc.path);
    // OpenAL variables to load into.
    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;
    
    std::vector<ubyte> filedata = buf.getData();
    size = filedata.size();

    alGenBuffers(1, &res.bufferID);    // create OpenAL buffer
    
    AudioCore::throwOpenALError("alGenBuffers");

    alutLoadWAVMemory((ALbyte*)&filedata[0], &format, &data, &size, &freq, &loop);
    
    AudioCore::throwOpenALError("alutLoadWAVFile");
    
    alBufferData(res.bufferID, format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);
    
    AudioCore::throwOpenALError("SampleResourceManager::loadResourceData");
}

void SampleResourceManager::freeResourceData(SampleResource& res)
{
    if(alIsBuffer(res.bufferID))
    {
        alDeleteBuffers(1, &res.bufferID);
    }
}

}
}
