//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Audio_test.cpp,v 1.4 2005/07/19 05:57:58 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include <boost/lexical_cast.hpp>

#ifdef PHOTON_USE_OPENAL

using namespace photon::audio;

class MainTask : public Task
{

public:
    MainTask() :
        Task("MainTask"),
        app(AppCore::getInstance()),
        video(video::VideoCore::getInstance())
    {
        LogSinkPtr csp( new ConsoleSink("console") );
        log.addSink(csp);

        video.setOrthoView(800,600);
        
        video::Font::addResource("font","data/FreeMono.ttf",20);
        font.open("font");

        Sample::addResource("chimes","data/chimes.wav");
        Sample::addResource("ocean","data/ocean.wav");
        Sample::addResource("rain","data/rain.wav");
        Sample::addResource("stream","data/stream.wav");
        Sample::addResource("thunder","data/thunder.wav");
        Sample::addResource("waterdrop","data/waterdrop.wav");
        
        chimes.open("chimes");
        ocean.open("ocean");
        rain.open("rain");
        stream.open("stream");
        thunder.open("thunder");
        waterdrop.open("waterdrop");
        
        chimes.setLooping(true);
        ocean.setLooping(true);
        rain.setLooping(true);
        stream.setLooping(true);
        thunder.setLooping(true);
        
        assert(!waterdrop.isLooping());
        waterdrop.setLooping(true);
        assert(waterdrop.isLooping());
        
        for(int i=0; i < 6; ++i)
            status[i] = "NOT ";
    }
    
    void checkKeys()
    {
        static const std::string NOT_PLAYING = "NOT ";
        static scalar lastCheck = 0;
        
        if(app.getTime() - lastCheck > 0.1)
        {
            lastCheck = app.getTime();
            
            if(app.keyPressed(KEY_C))
            {
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
            }
            if(app.keyPressed(KEY_O))
            {
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
            }
            if(app.keyPressed(KEY_R))
            {
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
            }
            if(app.keyPressed(KEY_S))
            {
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
            }
            if(app.keyPressed(KEY_T))
            {
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
            }
            if(app.keyPressed(KEY_W))
            {
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
            }
        }
    }

    void update()
    {
        static const photon::uint fontHeight(font.getHeight());
        static double t=0;

        if(app.getTime() - t > 1.0)
        {            
            app.setTitle("FPS: " + 
                    boost::lexical_cast<std::string>(app.getFramerate()) );
            t = app.getTime();
        }
        
        checkKeys();
        
        video.clear();
        
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
    
    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class AudioTest : public Application
{
public:

    int main(const StrVec& args)
    {
        AppCore::getInstance().createDisplay(800,600,32,0,0,false);

        AudioCore::initAudioDevice("OSS");

        Kernel::getInstance().addTask(TaskPtr(new MainTask()));

        Kernel::getInstance().run();

        return 0;
    }
};

ENTRYPOINT(AudioTest)

#else
#include <iostream>

int main()
{
    std::cerr << "Photon compiled without OpenAL support.\n"; 
}

#endif //PHOTON_USE_OPENAL
