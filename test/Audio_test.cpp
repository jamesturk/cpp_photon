//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Audio_test.cpp,v 1.1 2005/07/06 02:10:07 cozman Exp $

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

        Sample::addResource("wavdata/ocean.wav");
        sample.open("wavdata/ocean.wav");
        sample.play();
    }

    void update()
    {   
        static double t=0;
        
        if(app.getTime() - t > 1.0)
        {            
            app.setTitle("FPS: " + 
                    boost::lexical_cast<std::string>(app.getFramerate()) );
            t = app.getTime();
        }

        video.clear();
        
    }

private:
    audio::Sample sample;
    
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
        
        AudioCore::setDesiredDevice("OSS");
        new AudioCore;

        Kernel::getInstance().addTask(TaskPtr(new MainTask()));

        Kernel::getInstance().run();

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
