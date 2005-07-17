//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font_test.cpp,v 1.5 2005/07/17 07:14:09 cozman Exp $

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

        video::Font::addResource("font1","data/FreeMono.ttf",32);
        video::Font::addResource("font2","data/FreeSerif.ttf",18);

        font.open("font1");
        font2.open("font2");
        
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
        
        font.setColor(video::Color(0,128,128));
        font.drawText(0, 0, "Photon");
        font.setColor(video::Color(255,0,0));
        font.drawText(font.calcStringWidth("Photon"), font.getHeight(), 
                    "FPS: %.0f", app.getFramerate() );
        font2.beginDraw(200, 200) << "another plain font" << font2.endDraw();
    }

private:
    video::Font font;
    video::Font font2;
    
    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class FontTest : public Application
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

ENTRYPOINT(FontTest)
