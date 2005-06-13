//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Texture_test.cpp,v 1.1 2005/06/13 05:38:06 cozman Exp $

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

        video::Texture::addResource("data/test.png");
        img.open("data/test.png");
        
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

        img.bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);  glVertex2f(0,0);
        glTexCoord2f(1,0);  glVertex2f(100,0);
        glTexCoord2f(1,1);  glVertex2f(100,100);
        glTexCoord2f(0,1);  glVertex2f(0,100);
        glEnd();
    }

private:
    video::Texture img;
    
    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class Test00 : public Application
{
public:
    Test00()
    {
        //Log::getInstance().addSink(LogSinkPtr(new ConsoleSink("out")));
        //Log::getInstance().addSink(LogSinkPtr(new HTMLSink("debug")));
    }

    int main(const StrVec& args)
    {
        AppCore::getInstance().createDisplay(800,600,32,0,0,false);

        Kernel::getInstance().addTask(TaskPtr(new MainTask()));

        Kernel::getInstance().run();

        return 0;
    }
};

ENTRYPOINT(Test00)
