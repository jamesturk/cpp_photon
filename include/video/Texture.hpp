//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: Texture.hpp,v 1.5 2005/11/13 07:59:49 cozman Exp $

#ifndef PHOTON_VIDEO_TEXTURE_HPP
#define PHOTON_VIDEO_TEXTURE_HPP

#include "video/TextureResourceManager.hpp"
#include "ResourceManaged.hpp"

namespace photon
{
namespace video
{
    
// Class: Texture
//  Simple OO wrapper around the concept of a texture in OpenGL. 
// 
//  Since Texture is a child of <ResourceManaged>, all memory management is 
//  taken care of.
//
//  Texture loading is done via Corona (<http://corona.sf.net>)
// 
//  Children:
//   <Image>
// 
// Operators:
//  - Texture = Texture
//  - bool : True if texture is loaded, false if not.
class Texture : public ResourceManaged<TextureResourceManager>
{

// Group: (Con/De)structors 
public:

    // Function: Texture
    //  Default constructor, initalizes internal state of Texture.
    Texture();

    // Function: Texture
    //  Copy constructor, copies another Texture.
    // 
    // Parameters:
    //  rhs - Texture to construct copy of.
    Texture(const Texture &rhs);

    // Function: Texture
    // Initializing constructor, loads Texture via call to <open>.
    // 
    // Parameters:
    //  name - Name of the Texture <Resource> to open.
    // 
    // See Also: 
    //  <open>
    Texture(const std::string& name);

// Group: General
public:

    // Function: open
    //  Opens an image file, currently supported image types are BMP, GIF, JPEG,
    //  PCX, PNG, and TGA. 
    // 
    //  Loading is done via Corona (<http://corona.sf.net>)
    // 
    // Parameters:
    //  name - Name of the Texture <Resource> to open.
    void open(const std::string& name);

    // Function: bind
    //  Makes texture the current OpenGL texture.
    void bind() const;

    Texture& operator=(const Texture &rhs);
    operator bool() const;

// Group: Accessors
public:

    // Function: getWidth
    //  Gets width of texture.
    // 
    // Returns:
    //  Width of texture.
    scalar getWidth() const;

    // Function: getHeight
    //  Gets height of texture.
    // 
    // Returns:
    //  Height of texture.
    scalar getHeight() const;

    friend std::ostream& operator<<(std::ostream &o, const Texture &rhs);
    
// Group: Resource Creation
public:

    // Function: addResource
    //  Define a new named resource.
    //  (Ex. Texture::addResource("monkey","images/monkey.png") would 
    //   make it so that any attempts to load "monkey" would load the image 
    //   images/monkey.png)
    //
    // Parameters:
    //  name - Name to give to resource.
    //  path - Path of resource data file.
    static void addResource(const std::string& name, const std::string& path);
    
    // Function: addResource
    //  Define a new unaliased resource. (name == path).
    //  (Ex. Texture::addResource("images/monkey.png") is essentially the same 
    //   as Texture::addResource("images/monkey.png","images/monkey.png")
    //
    // Parameters:
    //  path - Path of resource data file.
    static void addResource(const std::string& path);
    
private:
    scalar width_;
    scalar height_;
    uint texID_;
};

}
}

#endif //PHOTON_VIDEO_TEXTURE_HPP
