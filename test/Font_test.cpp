//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Font_test.cpp,v 1.7 2005/07/20 06:12:13 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

class MainTask : public Task
{

public:
    MainTask() :
        Task("MainTask"),
        app(AppCore::getInstance()),
        video(video::VideoCore::getInstance())
    {
        video.setOrthoView(800,600);

        // show two different fonts
        video::Font::addResource("font1","data/FreeMono.ttf",32);
        video::Font::addResource("font2","data/FreeSerif.ttf",18);

        font.open("font1");
        font2.open("font2");
    }

    void update()
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
    
    AppCore& app;
    video::VideoCore& video;
};

// standard application, creates window, registers task and runs
class FontTest : public Application
{
public:

    int main(const StrVec& args)
    {
        AppCore::getInstance().createDisplay(800,600,32,0,0,false);

        // be sure to add FPSDisplayTask
        Kernel::getInstance().addTask(TaskPtr(new FPSDisplayTask()));
        Kernel::getInstance().addTask(TaskPtr(new MainTask()));

        Kernel::getInstance().run();

        return 0;
    }
};

ENTRYPOINT(FontTest)
