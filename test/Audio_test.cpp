//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Audio_test.cpp,v 1.14 2005/08/12 06:26:00 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

// actual test is only compiled if OpenAL is in use
#ifdef PHOTON_USE_OPENAL

using namespace photon::audio;

// sole task of AudioTest
class MainState : public State
{

public:
    MainState()
    {
        // add archives to search path
        util::filesys::addToSearchPath("data/fonts.zip");
        util::filesys::addToSearchPath("data/wavdata.zip");
        
        // load a font
        video::Font::addResource("font","FreeMono.ttf",20);
        font.open("font");
        
        // load the 6 sound effects
        Sample::addResource("chimes","chimes.wav");
        Sample::addResource("ocean","ocean.wav");
        Sample::addResource("rain","rain.wav");
        Sample::addResource("stream","stream.wav");
        Sample::addResource("thunder","thunder.wav");
        Sample::addResource("waterdrop","waterdrop.wav");
        
        // open the sounds
        chimes.open("chimes");
        ocean.open("ocean");
        rain.open("rain");
        stream.open("stream");
        thunder.open("thunder");
        waterdrop.open("waterdrop");
        
        // make all sounds looping
        chimes.setLooping(true);
        ocean.setLooping(true);
        rain.setLooping(true);
        stream.setLooping(true);
        thunder.setLooping(true);
        
        // test Sample::isLooping via assertions
        assert(!waterdrop.isLooping());
        waterdrop.setLooping(true);
        assert(waterdrop.isLooping());
        
        // status holds strings describing playing status for nice output
        for(int i=0; i < 6; ++i)
            status[i] = "NOT ";
    }
    
    // executes the checking of the keys, when a key is pressed 
    //  the state is toggled
    void onKeyPress(KeyCode key)
    {
        static const std::string NOT_PLAYING = "NOT ";
        
        switch(key)
        {
   
        case KEY_C:
            if(!chimes.isPlaying())
            {
                chimes.play();
                status[0] = "";
            }
            else
            {
                chimes.stop();
                status[0] = NOT_PLAYING;
            }
            break;
            
        case KEY_O:
            if(!ocean.isPlaying())
            {
                ocean.play();
                status[1] = "";
            }
            else
            {
                ocean.stop();
                status[1] = NOT_PLAYING;
            }
            break;
            
        case KEY_R:
            if(!rain.isPlaying())
            {
                rain.play();
                status[2] = "";
            }
            else
            {
                rain.stop();
                status[2] = NOT_PLAYING;
            }
            break;
            
        case KEY_S:
            if(!stream.isPlaying())
            {
                stream.play();
                status[3] = "";
            }
            else
            {
                stream.stop();
                status[3] = NOT_PLAYING;
            }
            break;
            
        case KEY_T:
            if(!thunder.isPlaying())
            {
                thunder.play();
                status[4] = "";
            }
            else
            {
                thunder.stop();
                status[4] = NOT_PLAYING;
            }
            break;
            
        case KEY_W:
            if(!waterdrop.isPlaying())
            {
                waterdrop.play();
                status[5] = "";
            }
            else
            {
                waterdrop.stop();
                status[5] = NOT_PLAYING;
            }
            break;

        default:
            break;
        }
    }
    
    void render()
    {
        // used for calculating draw position
        static const photon::uint fontHeight(font.getHeight());
        
        // draw the status of all 6 sounds
        font.beginDraw(0, 0*fontHeight) << "(C)himes is " << status[0] << 
            "playing" << font.endDraw();
        font.beginDraw(0, 1*fontHeight) << "(O)cean is " << status[1] << 
            "playing" << font.endDraw();
        font.beginDraw(0, 2*fontHeight) << "(R)ain is " << status[2] << 
            "playing" << font.endDraw();
        font.beginDraw(0, 3*fontHeight) << "(S)tream is " << status[3] << 
            "playing" << font.endDraw();
        font.beginDraw(0, 4*fontHeight) << "(T)hunder is " << status[4] << 
            "playing" << font.endDraw();
        font.beginDraw(0, 5*fontHeight) << "(W)aterdrop is " << status[5] << 
            "playing" << font.endDraw();
    }

private:
    video::Font font;
    audio::Sample chimes, ocean, rain, stream, thunder, waterdrop;
    std::string status[6];
};

int PhotonMain(const StrVec& args)
{
    // create window
    Application::getInstance().createDisplay(800,600,32,0,0,false);
    // initialize audio core
    Application::getInstance().initAudioCore();

    // be sure to add FPSDisplayTask
    Kernel::getInstance().addTask(TaskPtr(new FPSDisplayTask()));

    // register state and make active
    Application::getInstance().setState<MainState>();

    // run until finished
    Kernel::getInstance().run();
    
    return 0;
}

#else

// alternate application if OpenAL was not available
#include <iostream>
int PhotonMain(const StrVec& args)
{
    std::cerr << "Photon compiled without OpenAL support.\n"; 
}

#endif //PHOTON_USE_OPENAL
