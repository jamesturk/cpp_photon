//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Image_test.cpp,v 1.4 2005/07/04 03:06:48 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include <boost/lexical_cast.hpp>

// This is a simple framework for writing extremely simple Photon applications
//  it simply displays a blank window and the framerate in the titlebar of
//  the created window.  This is meant to show basic interaction between the
//  user and the more common features of the AppCore and the Kernel.

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

        video::Image::addResource("data/test.png");
        video::Texture::addResource("test2","data/test2.png");

        img[0].open("test2");
        img[0].setAlpha(128);
        img[0].resize(100,200);
        
        img[1].open("data/test.png");
        
        img[2] = img[0];
        img[2].flip(true,true);
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

        img[0].draw(0,0);
        
        img[1].drawRotated(200,200,app.getTime()*5);
        
        if(img[2])
        {
            img[2].draw(100,400);
        }
    }

private:
    video::Image img[3];
    
    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class ImageTest : public Application
{
public:

    int main(const StrVec& args)
    {
        AppCore::getInstance().createDisplay(800,600,32,0,0,false);

        Kernel::getInstance().addTask(TaskPtr(new MainTask()));

        Kernel::getInstance().run();

        return 0;
    }
};

ENTRYPOINT(ImageTest)
