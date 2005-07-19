//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Pen_test.cpp,v 1.3 2005/07/19 20:55:40 cozman Exp $

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
        video.setOrthoView(800,600);
        
        // initialize three pens, red, blue and green
        r.setColor(255, 0, 0);
        g.setColor(0, 255, 0);
        b.setColor(0, 0, 255);
    }

    void update()
    {   
        // used to measure FPS and display it in the title bar
        static double t=0;
        if(app.getTime() - t > 1.0)
        {            
            app.setTitle("FPS: " + 
                    boost::lexical_cast<std::string>(app.getFramerate()) );
            t = app.getTime();
        }
        
        static const math::Point2 center(400, 300); // used for clock

        video.clear();
        
        unsigned int i,j;   //used throughout demo
        
        // draw points in a traveling sine curve
        g.fillRectangle(math::Rect(math::Point2(0,0), 800, 100));
        for(i=0; i < 800; i += 5)
        {
            scalar ang = math::degToRad(i+100*app.getTime());
            r.drawPoint(math::Point2(i, 50+50*std::sin(ang) ));
        }
        
        // draw lines in a fancy pattern
        for(i=100; i <= 200; i += 20)
        {
            for(j=100; j <= 200; j += 20)
            {
                g.drawLine(math::Point2(100,i), math::Point2(j, 200)); 
            }
        }
        
        // draw circles to create a clock
        b.fillCircle(math::Circle(center, 60));
        g.drawCircle(math::Circle(center, 60));
        g.drawCircle(math::Circle(center, 50));
        
        // draw vector as clock hand
        math::Vector2 clockHand;
        clockHand.resolveDeg(50, 20*app.getTime());
        r.drawVector(center, clockHand);
        
        // draw rectangles to show Rect::calcIntersection in action
        math::Rect rect1(math::Point2(500, 300), 200, 100);
        math::Rect rect2(math::Point2(550, 375), 100, 200);
        r.drawRectangle(rect1);
        b.drawRectangle(rect2);
        g.fillRectangle(rect1.calcIntersection(rect2));
    }

private:
    video::Pen r,g,b;

    AppCore& app;
    video::VideoCore& video;
};

// standard application, creates window, registers task and runs
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
