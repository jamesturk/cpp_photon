//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Texture_test.cpp,v 1.4 2005/07/04 03:06:48 cozman Exp $

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
        video::Texture::addResource("test2","data/test2.png");
        
        // Testing of errors
        //video::Texture::addResource("nonfile");
        //video::Texture::addResource("Texture_test.cpp");
        //tex[0].open("test0");
        
        tex[0].open("data/test.png");
        tex[1].open("test2");
        tex[2] = tex[1];
        
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

        tex[0].bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);  glVertex2f(0,0);
        glTexCoord2f(1,0);  glVertex2f(100,0);
        glTexCoord2f(1,1);  glVertex2f(100,100);
        glTexCoord2f(0,1);  glVertex2f(0,100);
        glEnd();
        
        tex[1].bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);  glVertex2f(250,200);
        glTexCoord2f(1,0);  glVertex2f(300,250);
        glTexCoord2f(1,1);  glVertex2f(250,300);
        glTexCoord2f(0,1);  glVertex2f(200,250);
        glEnd();
        
        if(tex[2])
        {
            tex[2].bind();
            glBegin(GL_QUADS);
            glTexCoord2f(0,0);  glVertex2f(400,400);
            glTexCoord2f(1,0);  glVertex2f(500,400);
            glTexCoord2f(1,1);  glVertex2f(500,500);
            glTexCoord2f(0,1);  glVertex2f(400,500);
            glEnd();
        }
    }

private:
    video::Texture tex[3];
    
    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class TextureTest : public Application
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

ENTRYPOINT(TextureTest)
