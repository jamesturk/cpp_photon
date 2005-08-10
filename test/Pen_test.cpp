//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Pen_test.cpp,v 1.8 2005/08/10 21:22:33 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

class MainState : public State
{

public:
    MainState() :
        app(Application::getInstance())
    {
        // initialize three pens, red, blue and green
        r.setColor(255, 0, 0);
        g.setColor(0, 255, 0);
        b.setColor(0, 0, 255);
    }

    void render()
    {   
        static const math::Point2 center(400, 300); // used for clock
        
        unsigned int i,j;   //used throughout demo
        
        // draw points in a traveling sine curve
        g.fillRect(math::Rect(math::Point2(0,0), 800, 100));
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
        r.drawRect(rect1);
        b.drawRect(rect2);
        g.fillRect(rect1.calcIntersection(rect2));
    }

private:
    video::Pen r,g,b;

    Application& app;
};

int PhotonMain(const StrVec& args)
{
    // create window
    Application::getInstance().createDisplay(800,600,32,0,0,false);

    // be sure to add FPSDisplayTask
    Kernel::getInstance().addTask(TaskPtr(new FPSDisplayTask()));

    // set current state
    Application::getInstance().setState<MainState>();

    // run until finished
    Kernel::getInstance().run();
    
    return 0;
}
