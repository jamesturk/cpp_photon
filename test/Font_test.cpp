//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font_test.cpp,v 1.10 2005/08/08 06:37:10 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

class MainState : public State
{

public:
    MainState() :
        app(Application::getInstance())
    {
        // add archive to search path
        util::filesys::addToSearchPath("data/fonts.zip");
        
        // show two different fonts
        video::Font::addResource("font1","FreeMono.ttf",32);
        video::Font::addResource("font2","FreeSerif.ttf",18);

        font.open("font1");
        font2.open("font2");
    }

    void render()
    {
        // draw the three strings to the screen
        font.setColor(video::Color(0,128,128));
        font.drawText(0, 0, "Photon");
        font.setColor(video::Color(255,0,0));
        font.drawText(font.calcStringWidth("Photon"), font.getHeight(), 
                    "FPS: %.0f", app.getFramerate() );
        font2.beginDraw(200, 200) << "another (plain) font" << font2.endDraw();
    }

private:
    video::Font font;
    video::Font font2;
    
    Application& app;
};

int PhotonMain(const StrVec& args)
{
    // create window
    Application::getInstance().createDisplay(800,600,32,0,0,false);

    // be sure to add FPSDisplayTask
    Kernel::getInstance().addTask(TaskPtr(new FPSDisplayTask()));

    // set current state
    Application::getInstance().setCurrentState<MainState>();

    // run until finished
    Kernel::getInstance().run();
    
    return 0;
}
