//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: AudioCore_test.cpp,v 1.1 2005/05/15 02:50:07 cozman Exp $

#include "photon.hpp"
#include <iostream>

using namespace photon;
using namespace photon::audio;

class AudioTest : public Application
{
public:

    int main(const StrVec& args)
    {
        //throw Error("zing!");
        
        AudioCore& audio(AudioCore::getInstance());
        std::cout << audio.getAudioDeviceName();

        return 0;
    }
};

ENTRYPOINT(AudioTest)
