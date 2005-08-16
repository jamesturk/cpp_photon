//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: State_test.cpp,v 1.4 2005/08/16 06:32:39 cozman Exp $

#include "photon.hpp"
using namespace photon;

class Demo2D : public State
{
    
// basic struct used to represent a bouncing robot head
struct MovingRect
{
    math::Rect pos;
    math::Vector2 vel;
};

public:
    Demo2D()
    {
        util::RandGen rand;

        // load the robot image
        video::Image::addResource("robo","data/robo.png");
        roboImg.open("robo");
        
        // create 5 robots
        robots.resize(5);
        
        // initialize all the robot MovingRects
        for(std::vector<MovingRect>::iterator robot( robots.begin() );
            robot != robots.end();
            ++robot)
        {
            // randomly position robots
            robot->pos.moveTo(math::Point2(
                                rand.genRand(0.,800-roboImg.getWidth()), 
                                rand.genRand(0.,600-roboImg.getHeight())));
            // set size to image size
            robot->pos.resize(roboImg.getWidth(), roboImg.getHeight());

            // generates -400 or +400 initial velocity
            robot->vel.x = rand.genRandSign()*400;
            robot->vel.y = rand.genRandSign()*400;
        }
        
        Application::getInstance().setOrthoView();
    }
    
    // leave the 2D test if the user presses escape
    void onKeyPress(KeyCode key)
    {
        if(key == KEY_ESC)
        {
            Application::getInstance().popState();
        }
    }
    
    void update(scalar timeDelta)
    {
        // loop through and update all active robots
        for(std::vector<MovingRect>::iterator robot( robots.begin() );
            robot != robots.end();
            ++robot)
        {
            // calculate velocity
            math::Vector2 vel(robot->vel * timeDelta); 
            
            // move
            robot->pos.moveRel(vel.x, vel.y);
            
            // bounce if robot tries to go off screen
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
        // loop through robots, drawing each
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
        // free lists on exit of 3D demo
        glDeleteLists(boxList, 1);
    }
    
    // leave the 3D test if the user presses escape
    void onKeyPress(KeyCode key)
    {
        if(key == KEY_ESC)
        {
            Application::getInstance().popState();
        }
    }

    void update(scalar timeDelta)
    {
        // rotate the cube on all 3 axes
        xRot += 30*timeDelta;
        yRot += 40*timeDelta;
        zRot += 50*timeDelta;
    }

    void render()
    {
        // draw the cube each frame
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
    
// simple Menu::Item class used for a mouse-based menu
struct Item
{
    std::string text;
    math::Rect rect; 
};

public:
    Menu() :
        app(Application::getInstance())
    {
        // load the fonts
        video::Font::addResource("menufont","FreeMono.ttf",64);
        font.open("menufont");
        font.setColor(video::Color(255, 128, 0));
        
        // name the menuItems
        menuItems[0].text = "2D Demo";
        menuItems[1].text = "3D Demo";
        menuItems[2].text = "Quit";
        
        // generate the bounding rectangles for the menuItems
        const photon::uint ySkip(font.getHeight() + 20);
        scalar curY(100);
        scalar width;
        for(int i=0; i < 3; ++i)
        {
            // find width to center text
            width = font.calcStringWidth(menuItems[i].text);
            menuItems[i].rect.moveRel((app.getDisplayWidth()-width) / 2, curY);
            menuItems[i].rect.resize(width, font.getHeight());
            curY += ySkip;  // move down (don't write text on top of itself)
        }
        
        app.setOrthoView();
    }

    void onMouseButtonPress(MouseButton button)  
    {
        // handle mouse clicks inside bounding rectangles
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
            app.quit();
        }
    }

    void render()
    {
        video::Color c( font.getColor() );
        video::Pen p;
        
        // draw the menu items
        for(int i=0; i < 3; ++i)
        {
            // change color to white if mouse is within it's bounding rect
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
        // when resumed, select a new random color
        font.setColor(video::Color(rand.genRand(0,255), rand.genRand(0,255), 
                        rand.genRand(0,255)));
        // return to orthoView, 3D demo might have put us in perspective
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
    Application& app(Application::getInstance());
    
    app.createDisplay(800,600,32,0,0,false);    // create window
    app.setFixedUpdateStep(true, .01);

    // add archives to search path
    util::filesys::addToSearchPath("data/fonts.zip");

    app.setState<Menu>();   // register state and make active
    app.run();              // run until finished
    
    return 0;
}
