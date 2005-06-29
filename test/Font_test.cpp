//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font_test.cpp,v 1.1 2005/06/29 04:30:40 cozman Exp $

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

        video::Font::addResource("font","data/arial.ttf");
        
        font.open("font");
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
        
        glColor4ub(255,0,0,255);
        glEnable(GL_TEXTURE_2D);
        glScaled(1.0/.75,1,1);
        font.write("he");
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);  glVertex2f(150,200);
        glTexCoord2f(1,0);  glVertex2f(300,350);
        glTexCoord2f(1,1);  glVertex2f(150,300);
        glTexCoord2f(0,1);  glVertex2f(200,350);
        glEnd();
        glColor4ub(255,255,255,255);
    }

private:
    video::Font font;
    
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
