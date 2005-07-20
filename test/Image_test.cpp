//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Image_test.cpp,v 1.6 2005/07/20 01:35:11 cozman Exp $

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

        // clear screen
        video.clear();

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

    AppCore& app;
    video::VideoCore& video;
};

// standard application, creates window, registers task and runs
class ImageTest : public Application
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

ENTRYPOINT(ImageTest)
