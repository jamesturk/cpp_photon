//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Pen_test.cpp,v 1.2 2005/07/17 06:19:18 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include <boost/lexical_cast.hpp>

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
        
        r.setColor(255, 0, 0);
        g.setColor(0, 255, 0);
        b.setColor(0, 0, 255);
    }

    void update()
    {   
        static double t=0;
        static const math::Point2 center(400, 300);

        if(app.getTime() - t > 1.0)
        {            
            app.setTitle("FPS: " + 
                    boost::lexical_cast<std::string>(app.getFramerate()) );
            t = app.getTime();
        }

        video.clear();
        
        unsigned int i,j;   //used throughout demo
        
        // points
        for(i=0; i < 400; ++i)
        {
            r.drawPoint(math::Point2(i, 2*i));
            g.drawPoint(math::Point2(i, 3*i));
            b.drawPoint(math::Point2(i, 4*i));
        }
        
        // lines
        for(i=100; i <= 200; i += 10)
        {
            for(j=100; j <= 200; j += 10)
            {
                g.drawLine(math::Point2(100,i), math::Point2(j, 200)); 
            }
        }
        
        // circles
        b.fillCircle(math::Circle(center, 60));
        g.drawCircle(math::Circle(center, 60));
        g.drawCircle(math::Circle(center, 50));
        
        // vectors
        math::Vector2 clockHand;
        clockHand.resolveDeg(50, 20*app.getTime());
        r.drawVector(center, clockHand);
        
        // rectangles
        math::Rect rect1(math::Point2(500, 300), 200, 100);
        math::Rect rect2(math::Point2(550, 375), 100, 200);
        r.drawRectangle(rect1);
        b.drawRectangle(rect2);
        g.fillRectangle(rect1.calcIntersection(rect2));
    }

private:
    video::Pen r,g,b;
    

    Log log;
    AppCore& app;
    video::VideoCore& video;
};

class PenTest : public Application
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

ENTRYPOINT(PenTest)
