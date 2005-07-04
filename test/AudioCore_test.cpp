//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore_test.cpp,v 1.2 2005/07/04 03:06:48 cozman Exp $

#include "photon.hpp"
#include <iostream>

using namespace photon;

#ifdef PHOTON_USE_OPENAL

using namespace photon::audio;

class AudioTest : public Application
{
public:

    int main(const StrVec& args)
    {

        AudioCore& audio(AudioCore::getInstance());
        std::cout << audio.getAudioDeviceName();

        return 0;
    }
};

ENTRYPOINT(AudioTest)

#else

int main()
{
    std::cerr << "Photon compiled without OpenAL support.\n"; 
}

#endif //PHOTON_USE_OPENAL
