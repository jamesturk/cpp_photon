//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: SampleResourceManager.cpp,v 1.5 2005/10/28 22:13:03 cozman Exp $

#ifdef PHOTON_USE_OPENAL

#include "audio/SampleResourceManager.hpp"
#include "audio/AudioCore.hpp"
#include "util/FileBuffer.hpp"

#include "AL/al.h"

#include <iostream>

namespace photon
{
namespace audio
{

void SampleResourceManager::getAudioData(const std::string& name,  
                                            uint& bufferID)
{
    // not much to do here, get the resource, set the ID
    SampleResource resource( getResource(name) );
    bufferID = resource.bufferID;
}

void SampleResourceManager::loadResourceData(SampleResource &res, 
                                            const ResourceDescriptor& desc)
{
    util::FileBuffer buf(desc.path);
    // OpenAL variables to load into.
    ALenum format;
    uint size;
    ubyte* data;
    uint freq;
    
    // load from FileBuffer (allows loading from zip via PhysFS)
    std::vector<ubyte> filedata = buf.getData();
    size = filedata.size();

    alGenBuffers(1, &res.bufferID);    // create OpenAL buffer
    
    OALAudioCore::throwOpenALError("alGenBuffers");

    // load WAV and pass it into OpenAL buffer
    loadWAVMemory(&filedata[0], format, data, size, freq);
    alBufferData(res.bufferID, format, (ALvoid*)data, size, freq);
    freeWAVMemory(data);
    
    OALAudioCore::throwOpenALError("alBufferData");
}

void SampleResourceManager::freeResourceData(SampleResource& res)
{
    if(alIsBuffer(res.bufferID))
    {
        // delete buffers, just like textures in GL
        alDeleteBuffers(1, &res.bufferID);
    }
}

void SampleResourceManager::loadWAVMemory(const ubyte* memory, ALenum& format, ubyte*& data, 
                    uint& size, uint& freq)
{
    WaveHeader wavHeader;

    std::memcpy(&wavHeader, memory, sizeof(WaveHeader));

    // check vital fields of WAV file for validation
    if(wavHeader.fmt.format != 1)
    {
        throw ResourceException("Error loading WAV: Non-PCM format WAV");
    }
    if(wavHeader.riff.chunkID != WaveHeader::RIFF)
    {
        throw ResourceException("Error loading WAV: Invalid RIFF chunk."); 
    }
    if(wavHeader.riff.format != WaveHeader::WAVE)
    {
        throw ResourceException("Error loading WAV: Invalid WAVE header.");
    }
    if(wavHeader.fmt.chunkID != WaveHeader::FMT)
    {
        throw ResourceException("Error loading WAV: Invalid FMT chunk.");
    }
    if(wavHeader.chunkID != WaveHeader::DATA)
    {
        throw ResourceException("Error loading WAV: Invalid DATA chunk.");
    }
    
    // set OpenAL format based on channels & bitsPerSample
    if(wavHeader.fmt.numChannels == 1 && wavHeader.fmt.bitsPerSample == 8)
    {
        format = AL_FORMAT_MONO8;
    }
    else if(wavHeader.fmt.numChannels == 1 && wavHeader.fmt.bitsPerSample == 16)
    {
        format = AL_FORMAT_MONO16;
    }
    else if(wavHeader.fmt.numChannels == 2 && wavHeader.fmt.bitsPerSample == 8)
    {
        format = AL_FORMAT_STEREO8;
    }
    else if(wavHeader.fmt.numChannels == 2 && wavHeader.fmt.bitsPerSample == 16)
    {
        format = AL_FORMAT_STEREO16;
    }
    else
    {
        throw ResourceException("Error loading WAV: Invalid audio format.");
    }

    // copy size and frequency
    size = wavHeader.dataSize;
    freq = wavHeader.fmt.sampleRate;

    // allocate space and copy data
    data = new ubyte[size];
    std::memcpy(data, memory+sizeof(WaveHeader), size);
}

void SampleResourceManager::freeWAVMemory(ubyte*& data)
{
    if(data == 0)
    {
        assert(0);
    }
    
    delete[] data;
    data = 0;
}

}
}

#endif  //PHOTON_USE_OPENAL
