//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Input_test.cpp,v 1.13 2005/11/15 02:59:08 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

class MainState : public State
{

public:
    MainState() :
        app(Application::getInstance())
    {
        // add archives to search path
        util::filesys::addToSearchPath("data/fonts.zip");

        video::Font::addResource("font","FreeMono.ttf",20);
        font.open("font");
    }
    
    // listen for events and set the last event string
    void onKeyPress(KeyCode key) 
    {
        lastEvent = "key " + boost::lexical_cast<std::string>(key) + 
            " pressed";
    }
    
    void onKeyRelease(KeyCode key)
    {
        lastEvent = "key " + boost::lexical_cast<std::string>(key) + 
            " released";
    }
    
    void onMouseButtonPress(MouseButton button)  
    {
        lastEvent = "mouse button " + boost::lexical_cast<std::string>(button) +
            " pressed";
    }
    
    void onMouseButtonRelease(MouseButton button)
    {
        lastEvent = "mouse button " + boost::lexical_cast<std::string>(button) +
            " released";
    }
    
    void onMouseMove(const math::Vector2& delta)
    {
        lastEvent = "mouse moved by " + boost::lexical_cast<std::string>(delta); 
    }
    
    void onMouseScroll(ScrollDir dir)
    {
        lastEvent = "mouse wheel scrolled " +
            std::string(dir == SCROLL_UP ? "up" : "down");
    }

    void render()
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
