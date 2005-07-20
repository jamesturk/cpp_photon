//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Input_test.cpp,v 1.4 2005/07/20 06:12:13 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

class MainTask : public Task, public InputListener
{

public:
    MainTask() :
        Task("MainTask"),
        app(AppCore::getInstance()),
        video(video::VideoCore::getInstance())
    {
        video.setOrthoView(800,600);

        video::Font::addResource("font","data/FreeMono.ttf",20);
        font.open("font");
    }
    
    // listen for events and set the last event string
    void onKeyPress(int key) 
    {
        lastEvent = "key " + boost::lexical_cast<std::string>(key) + 
            " pressed";
    }
    
    void onKeyRelease(int key)
    {
        lastEvent = "key " + boost::lexical_cast<std::string>(key) + 
            " released";
    }
    
    void onMouseButtonPress(int button)  
    {
        lastEvent = "mouse button " + boost::lexical_cast<std::string>(button) +
            " pressed";
    }
    
    void onMouseButtonRelease(int button)
    {
        lastEvent = "mouse button " + boost::lexical_cast<std::string>(button) +
            " released";
    }
    
    void onMouseMove(const math::Vector2& pos)
    {
        lastEvent = "mouse moved to " +  boost::lexical_cast<std::string>(pos); 
    }

    void update()
    {
        // used for spacing text vertically
        static const photon::uint fontHeight(font.getHeight());
        photon::uint curHeight(0);
        
        // draw input event/status notifications, increment curHeight on each 
        //  draw so that text is properly spaced vertically
        font.beginDraw(0,curHeight) << "Last event: " << lastEvent <<
            font.endDraw();
        curHeight += fontHeight;
        
        font.beginDraw(0,curHeight) << "Mouse at " << app.getMouseX() << "," <<
            app.getMouseY() << " wheel = " << app.getMouseWheelPos() <<
            font.endDraw();
        curHeight += fontHeight;
        
        font.beginDraw(0,curHeight) << "#Pressed Keys = " << 
            app.getPressedKeys().size() << font.endDraw();
        curHeight += fontHeight;
        
        if(app.keyPressed(KEY_SPACE))
        {
            font.drawText(0,curHeight, "Space key is pressed.");
            curHeight += fontHeight;
        }
        if(!app.keyPressed(KEY_RETURN))
        {
            font.drawText(0,curHeight, "Return key is NOT pressed.");
            curHeight += fontHeight;
        }
        if(app.mouseButtonPressed(MB_LEFT))
        {
            font.drawText(0,curHeight, "Left mouse button is pressed.");
            curHeight += fontHeight;
        }
        if(app.mouseButtonPressed(MB_MIDDLE))
        {
            font.drawText(0,curHeight, "Center mouse button is pressed.");
            curHeight += fontHeight;
        }
        if(app.mouseButtonPressed(MB_RIGHT))
        {
            font.drawText(0,curHeight, "Right mouse button is pressed.");
            curHeight += fontHeight;
        }

    }

private:
    video::Font font;
    std::string lastEvent;

    AppCore& app;
    video::VideoCore& video;
};

// standard application, creates window, registers task and runs
class InputTest : public Application
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

ENTRYPOINT(InputTest)
