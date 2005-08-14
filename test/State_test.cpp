//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: State_test.cpp,v 1.3 2005/08/14 07:40:13 cozman Exp $

#include "photon.hpp"
using namespace photon;
#include "FPSDisplayTask.hpp"   // used to display FPS in title bar

#include <iostream>

class Demo2D : public State
{
    
struct MovingRect
{
    math::Rect pos;
    math::Vector2 vel;
};

public:
    Demo2D()
    {
        util::RandGen rand;

        video::Image::addResource("robo","data/robo.png");

        roboImg.open("robo");
        
        robots.resize(5);
        
        for(std::vector<MovingRect>::iterator robot( robots.begin() );
            robot != robots.end();
            ++robot)
        {
            robot->pos.moveTo(math::Point2(
                                rand.genRand(0.,800-roboImg.getWidth()), 
                                rand.genRand(0.,600-roboImg.getHeight())));
            robot->pos.resize(roboImg.getWidth(), roboImg.getHeight());

            // generates -400 or +400
            robot->vel.x = rand.genRandSign()*400;
            robot->vel.y = rand.genRandSign()*400;
        }
        
        Application::getInstance().setOrthoView();
    }
    
    void onKeyPress(KeyCode key)
    {
        if(key == KEY_ESC)
        {
            Application::getInstance().popState();
        }
    }
    
    void update()
    {
        for(std::vector<MovingRect>::iterator robot( robots.begin() );
            robot != robots.end();
            ++robot)
        {
            math::Vector2 vel(robot->vel * 
                Application::getInstance().getTimeDelta());
            
            robot->pos.moveRel(vel.x, vel.y);
            
            if(robot->pos.getLeft() < 0 || robot->pos.getRight() > 800)
            {
                robot->vel.x *= -1;
            }
            if(robot->pos.getTop() < 0 || robot->pos.getBottom() > 600)
            {
                robot->vel.y *= -1;
            }
            
            // check for robot-robot collisions
            for(std::vector<MovingRect>::iterator robot2( robot );
                robot2 != robots.end();
                ++robot2)
            {
                if(robot->pos.intersects(robot2->pos))
                {
                    std::swap(robot->vel, robot2->vel);
                }
            }
            
        }
    }
    
    void render()
    {
        for(std::vector<MovingRect>::iterator robot( robots.begin() );
            robot != robots.end();
            ++robot)
        {
            roboImg.draw(robot->pos.getX(), robot->pos.getY());
        }
    }
    
private:
    video::Image roboImg;
    std::vector<MovingRect> robots;
};

class Demo3D : public State
{
public:
    Demo3D() :
        xRot(0), yRot(0), zRot(0), 
        boxList(glGenLists(1))
    {
        video::Image::addResource("robo","data/robo.png");

        Application::getInstance().setPerspectiveView(45.0, 1.0, 100.0);

        glShadeModel(GL_SMOOTH);    // smooth shading
        glClearDepth(1.0f);         // set clear depth
        glEnable(GL_DEPTH_TEST);    // enable depth testing
        glDepthFunc(GL_LEQUAL);
        
        // create the list to display a box
        glNewList(boxList, GL_COMPILE);
        glBegin(GL_QUADS);
            // front - red
            glColor3ub(255, 0, 0);
            glVertex3f(-1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);
            // back - green
            glColor3ub(0, 255, 0);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f, -1.0f, -1.0f);
            // top - blue
            glColor3ub(0, 0, 255);
            glVertex3f(-1.0f,  1.0f, -1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
            // bottom - orange
            glColor3ub(255, 128, 0);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f( 1.0f, -1.0f, -1.0f);
            glVertex3f( 1.0f, -1.0f,  1.0f);
            glVertex3f(-1.0f, -1.0f,  1.0f);
            // right - purple
            glColor3ub(128, 0, 255);
            glVertex3f( 1.0f, -1.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f, -1.0f,  1.0f);
            // left - yellow
            glColor3ub(255, 255, 0);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f,  1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);
            glVertex3f(-1.0f,  1.0f, -1.0f);
        glEnd();
        glEndList();
    }
    
    ~Demo3D()
    {
        glDeleteLists(boxList, 1);
    }
    
    void onKeyPress(KeyCode key)
    {
        if(key == KEY_ESC)
        {
            Application::getInstance().popState();
        }
    }

    void update()
    {
        scalar dt = Application::getInstance().getTimeDelta();

        xRot += 30*dt;
        yRot += 40*dt;
        zRot += 50*dt;
    }

    void render()
    {
        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-5.0f);
        glRotated(xRot,1.0f,0.0f,0.0f);
        glRotated(yRot,0.0f,1.0f,0.0f);
        glRotated(zRot,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, 0);
        glCallList(boxList);
    }
    
private:
    video::Texture tex;
    scalar xRot, yRot, zRot;
    photon::uint boxList;
};

class Menu : public State
{
    
struct Item
{
    std::string text;
    math::Rect rect; 
};

public:
    Menu() :
        app(Application::getInstance())
    {
        video::Font::addResource("menufont","FreeMono.ttf",64);
        font.open("menufont");
        font.setColor(video::Color(255, 128, 0));
        
        menuItems[0].text = "2D Demo";
        menuItems[1].text = "3D Demo";
        menuItems[2].text = "Quit";
        
        const photon::uint ySkip(font.getHeight() + 20);
        scalar curY(100);
        scalar width;
        for(int i=0; i < 3; ++i)
        {
            width = font.calcStringWidth(menuItems[i].text);
            menuItems[i].rect.moveRel((app.getDisplayWidth() - width) / 2, curY);
            menuItems[i].rect.resize(width, font.getHeight());
            curY += ySkip;
        }
        
        app.setOrthoView();
        app.setTimeDeltaMode(TDM_AVERAGE, 250);
    }

    void onMouseButtonPress(MouseButton button)  
    {
        if(menuItems[0].rect.contains(math::Point2(app.getMouseX(), 
                                                    app.getMouseY())))
        {
            app.pushState<Demo2D>();
        }
        else if(menuItems[1].rect.contains(math::Point2(app.getMouseX(), 
                                                    app.getMouseY())))
        {
            app.pushState<Demo3D>();
        }
        else if(menuItems[2].rect.contains(math::Point2(app.getMouseX(), 
                                                    app.getMouseY())))
        {
            Kernel::getInstance().killAllTasks();
        }
    }

    void render()
    {
        video::Color c( font.getColor() );
        video::Pen p;
        
        for(int i=0; i < 3; ++i)
        {
            if(menuItems[i].rect.contains(math::Point2(app.getMouseX(), 
                                                        app.getMouseY())))
            {
                font.setColor(video::Color(255, 255, 255));
                p.drawRect(menuItems[i].rect);
            }
            
            font.drawText(menuItems[i].rect.getX(), menuItems[i].rect.getY(),
                            menuItems[i].text);
            font.setColor(c);
        }
        
        
    }

    void onResume()
    {
        font.setColor(video::Color(rand.genRand(0,255), rand.genRand(0,255), 
                        rand.genRand(0,255)));
        app.setOrthoView();
    }

private:
    video::Font font;
    Item menuItems[3];
    util::RandGen rand;

    Application& app;
};

int PhotonMain(const StrVec& args)
{
    // create window
    Application::getInstance().createDisplay(800,600,32,0,0,false);
    
    // add archives to search path
    util::filesys::addToSearchPath("data/fonts.zip");

    // set current state
    Application::getInstance().setState<Menu>();

    // run until finished
    Kernel::getInstance().run();
    
    return 0;
}
