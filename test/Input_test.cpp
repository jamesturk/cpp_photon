//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Input_test.cpp,v 1.2 2005/07/19 05:57:43 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include <boost/lexical_cast.hpp>

class LastEventListener : public InputListener
{
public:
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
    
    std::string lastEvent;
};

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

        video::Font::addResource("font","data/FreeMono.ttf",20);
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
        
        static const photon::uint fontHeight(font.getHeight());
        photon::uint curHeight(0);
        
        video.clear();
        
        font.beginDraw(0,curHeight) << "Last event: " << lel.lastEvent <<
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
    LastEventListener lel;
    
    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class InputTest : public Application
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

ENTRYPOINT(InputTest)
