//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Image_test.cpp,v 1.14 2005/11/15 02:59:08 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar



class MainState : public State
{

public:
    MainState() :
        app(Application::getInstance())
    {
        // load the images
        video::Image::addResource("data/icon.png");
        video::Texture::addResource("robo","data/robo.png");

        // load img[0], set to half translucency and resize
        img[0].open("robo");
        img[0].setAlpha(128);
        img[0].resize(100,200);

        // load img[1]
        img[1].open("data/icon.png");

        // copy img[0] into img[2] and flip it
        img[2] = img[0];
        img[2].flip(true,true);
    }
    
    void render()
    {   
        // draw in top left corner
        img[0].draw(0,0);

        // rotate according to timer
        img[1].drawRotated(200,200,app.getTime()*5);
        
        // example usage of Images boolean operator
        if(img[2])
        {
            img[2].draw(0,200);
        }
    }

private:
    video::Image img[3];
    
    Application& app;
};

int PhotonMain(const StrVec& args)
{
    Application& app(Application::getInstance());
    
    app.createDisplay(800,600,32,0,0,DISP_WINDOWED);    // create window

    // be sure to add FPSDisplayTask
    app.getUpdateTaskManager().addTask(util::TaskPtr(new FPSDisplayTask()));

    app.setState<MainState>();  // register state and make active
    app.run();                  // run until finished
    
    return 0;
}

