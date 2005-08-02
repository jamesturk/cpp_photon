//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VideoCore.hpp,v 1.5 2005/08/02 23:07:52 cozman Exp $

#ifndef PHOTON_VIDEO_VIDEOCORE_HPP
#define PHOTON_VIDEO_VIDEOCORE_HPP

#include "types.hpp"
#include "Task.hpp"

namespace photon
{
namespace video
{

// Class: VideoCore
//  Photon's core for graphics behavior.  Defines the interface through which 
//  all graphics related functions are performed.
//
//  VideoCore is the Core that interfaces with the actual drawing/updating of
//  the display.
//
// See Also:
//  <AppCore>
class VideoCore
{
// Group: (Con/De)structors
public:
    // Function: VideoCore
    //  Initialize underlying APIs and setup <Task> internals.
    //
    // Parameters:
    //  width - Width of display.
    //  height - height of display
    VideoCore(uint width, uint height);
    
    // Function: ~VideoCore
    //  Shutdown underlying APIs.
    ~VideoCore();

// Group: Viewport 
//  Functions to set the working viewport and perspective. Orthographic and
//  standard 3D perspective modes are available.
public:
    // Function: setOrthoView
    //  Sets new ortho viewport within a rectangular portion of the screen.
    //  All drawing is relative to the rectangle, x,y becomes 0,0 and anything  
    //  drawn outside rect is clipped.
    // 
    // Parameters:
    //  x - X coord for top left corner of new viewport.
    //  y - Y coord for top left corner of new viewport.
    //  viewWidth - Width of new viewport.
    //  viewHeight - Height of new viewport.
    //  orthoWidth - Width of ortho perspective.
    //  orthoHeight - Height of ortho perspective.
    void setOrthoView(int x, int y, int viewWidth, int viewHeight, 
                            scalar orthoWidth, scalar orthoHeight);

    // Function: setOrthoView
    //  Sets entire screen as current viewport with a given ortho perspective.
    // 
    // Parameters:
    //  width - Width of view.
    //  height - Height of view.
    void setOrthoView(scalar width, scalar height);

    // Function: setOrthoView
    //  Sets entire screen as current viewport with a given ortho perspective.
    void setOrthoView();

// Group: Perspective
public:
    // Function: setPerspectiveView
    //  Creates a viewport with a given 3D perspective inside of a rectangular
    //  portion of the screen.
    // 
    // Parameters:
    //  x - X coord for top left corner of new viewport.
    //  y - Y coord for top left corner of new viewport.
    //  width - Width of new viewport.
    //  height - Height of new viewport.
    //  fovy - The y axis field of view angle, in degrees.
    //  zNear - Distance from viewer to near clipping plane.
    //  zFar - Distance from viewer to far clipping plane.
    void setPerspectiveView(int x, int y, int width, int height, 
                                scalar fovy, scalar zNear, scalar zFar);
    
    // Function: setPerspectiveView
    //  Sets entire screen as current viewport with a given 3D perspective.
    //
    //  Same as call to setPerspective
    // 
    // Parameters:
    //  fovy - The y axis field of view angle, in degrees.
    //  zNear - Distance from viewer to near clipping plane.
    //  zFar - Distance from viewer to far clipping plane.
    void setPerspectiveView(scalar fovy, scalar zNear, scalar zFar);
    
// Group: Viewport/Projection 
//  These functions are called by the above Ortho/Perspective functions, very 
//  rarely do they need to be called directly.
public:
    // Function: setViewport
    //  Set the current viewport rectangle within the screen.
    void setViewport(int x, int y, int width, int height);
    
    // Function: setOrthoProjection
    //  Sets an orthographic projection matrix.
    // 
    // Parameters:
    //  width - Width of view.
    //  height - Height of view.
    void setOrthoProjection(scalar width, scalar height);
    
    // Function: setPerspectiveProjection
    //  Sets a perspective projection matrix.
    // 
    // Parameters:
    //  fovy - The y axis field of view angle, in degrees.
    //  zNear - Distance from viewer to near clipping plane.
    //  zFar - Distance from viewer to far clipping plane.
    void setPerspectiveProjection(scalar fovy, scalar zNear, scalar zFar);
    
// Group: Display 
public:
    // Function: setDisplaySize
    //  Set the new display size, should be called whenever window size changes.
    //
    // Parameters:
    //  width - Width of display.
    //  height - height of display
    void setDisplaySize(uint width, uint height);
    
    // Function: getDisplayWidth
    //  Get the width of the display.
    //
    // Returns:
    //  Width of display in pixels.
    uint getDisplayWidth();

    // Function: getDisplayHeight
    //  Get the height of the display.
    //
    // Returns:
    //  Height of display in pixels.
    uint getDisplayHeight();

// behind the scenes
private: 
    void initOpenGL();  // set desired OpenGL options
    
    // UpdateTask, does the updating work of VideoCore, registered as a Task
    //  so that user need not call something akin to VideoCore::update() every 
    //  frame
    class UpdateTask : public Task
    {

    friend class VideoCore;

    public:
        UpdateTask();

        void update();
    };
    
// data members
private:
    uint displayWidth_;
    uint displayHeight_;
    uint viewportWidth_;
    uint viewportHeight_;
};

}
}

#endif  //PHOTON_VIDEO_VIDEOCORE_HPP
