//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Texture_test.cpp,v 1.11 2005/08/17 06:35:56 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

class MainState : public State
{

public:
    MainState() :
        app(Application::getInstance())
    {
        video::Texture::addResource("data/icon.png");
        video::Texture::addResource("robo","data/robo.png");
        
        // Testing of errors, uncomment to get various errors
        //video::Texture::addResource("nonfile");       // non-existant file
        //video::Texture::addResource("Texture_test.cpp");  // non-image file
        //tex[0].open("badresource");       // opening of non-existant resource
        
        tex[0].open("data/icon.png");
        tex[1].open("robo");
        tex[2] = tex[1];
        
    }
    
    void render()
    {   
        // draw first texture at actual size
        tex[0].bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);  glVertex2f(0,0);
        glTexCoord2f(1,0);  glVertex2f(tex[0].getWidth(),0);
        glTexCoord2f(1,1);  glVertex2f(tex[0].getWidth(),tex[0].getHeight());
        glTexCoord2f(0,1);  glVertex2f(0,100);
        glEnd();
        
        // draw second texture on a diamond shaped polygon
        tex[1].bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);  glVertex2f(250,200);
        glTexCoord2f(1,0);  glVertex2f(300,250);
        glTexCoord2f(1,1);  glVertex2f(250,300);
        glTexCoord2f(0,1);  glVertex2f(200,250);
        glEnd();
        
        // draw texture and test Texture's boolean operator
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

    Application& app;
};

int PhotonMain(const StrVec& args)
{
    Application& app(Application::getInstance());
    
    app.createDisplay(800,600,32,0,0,false);    // create window

    // be sure to add FPSDisplayTask
    app.getUpdateTaskManager().addTask(util::TaskPtr(new FPSDisplayTask()));

    app.setState<MainState>();  // register state and make active
    app.run();                  // run until finished
    
    return 0;
}
