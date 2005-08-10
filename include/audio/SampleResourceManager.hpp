//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: SampleResourceManager.hpp,v 1.3 2005/08/10 05:36:31 cozman Exp $

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
    
    void loadWAVMemory(const ubyte* memory, ALenum& format, ubyte*& data, 
                        uint& size, uint& freq);
    void freeWAVMemory(ubyte*& data);
};

// Allow users to simply call a Sample a Sample
typedef Source<SampleResourceManager> Sample;

// Structure defined to specification of WAV file
// Based on http://ccrma.stanford.edu/CCRMA/Courses/422/projects/WaveFormat/
struct WaveHeader
{
    // Big Endian
    // static const uint RIFF = 0x52494646;
    // static const uint WAVE = 0x57415645;
    // static const uint FMT  = 0x666d7420;
    // static const uint DATA = 0x64617461;
    
    // Little Endian
    static const uint RIFF = 0x46464952;
    static const uint WAVE = 0x45564157;
    static const uint FMT  = 0x20746d66;
    static const uint DATA = 0x61746164;
    
    struct RIFFHeader
    {
        uint chunkID;   // 4 bytes
        uint chunkSize; // 4 bytes
        uint format;    // 4 bytes
    } riff;  // 16 bytes
    
    struct WaveFormat
    {
        uint chunkID;           // 4 bytes
        uint size;              // 4 bytes
        short format;           // 2 bytes
        short numChannels;      // 2 bytes
        uint sampleRate;        // 4 bytes
        uint byteRate;          // 4 bytes
        short blockAlign;       // 2 bytes
        short bitsPerSample;    // 2 bytes
    } fmt;  // 24 bytes

    uint chunkID;       // 4 bytes
    uint dataSize;      // 4 bytes
};  // 38 bytes

}
}

#endif  //PHOTON_AUDIO_SAMPLERESOURCEMANAGER_HPP

#endif  //PHOTON_USE_OPENAL
