//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: FontResourceManager.cpp,v 1.2 2005/07/03 05:20:49 cozman Exp $

#include "video/FontResourceManager.hpp"

#include "util/FileBuffer.hpp"

namespace photon
{
namespace video
{

FontResourceManager::FontResourceManager()
{
    if(FT_Init_FreeType(&library_) != 0)
    {
        throw APIError("Could not initialize FreeType2 library.");
    }
}

FontResourceManager::~FontResourceManager()
{
    FT_Done_FreeType(library_);
}
    
void FontResourceManager::getFontData(const std::string& name, uint& texID, 
                                        uint& listBase, 
                                        std::vector<ubyte>& widths, 
                                        ubyte& height)
{
    FontResource resource( getResource(name) );
    texID = resource.texID;
    listBase = resource.listBase;
    widths = resource.widths;
    height = resource.height;
}

void FontResourceManager::loadResource(FontResource &res, 
                                            const std::string& path)
{
    throw Error("loadResource(FontResource&, const std::string& is undefined "
                " for Font.  A size must be specified.");
}

FontResource FontResourceManager::newResource(const std::string& name, 
                                                const std::string& path,
                                                uint size)
{
    FontResource resource;
    resource.name = name;
    resource.path = path;

    try
    {
        // attempt to load
        loadResource(resource, path, size);
    }
    catch(ResourceException& e)
    {
        // rethrow any exceptions with specific information 
        throw ResourceException("Could not load " + path + " as " + name + 
            ": " + e.getDesc());
    }

    resourceMap_[name] = resource;     // add the resource to resourceMap
}

void FontResourceManager::loadResource(FontResource &res, 
                                            const std::string& path, uint size)
{
    const size_t MARGIN = 3;
    
    res.widths.resize(NUM_CHARS);
    
    // Step 1: Open the font using FreeType //
    util::FileBuffer buf(path);
    std::vector<ubyte> data = buf.getData();

    FT_Face face;

    if(FT_New_Memory_Face(library_, (ubyte*)&data[0], data.size(), 0, &face) 
        != 0)
    {
        throw APIError("Could not load font file.");
    }

    // Abort if this is not a scalable font.
    if(!(face->face_flags & FT_FACE_FLAG_SCALABLE) ||
        !(face->face_flags & FT_FACE_FLAG_HORIZONTAL))
    {
        throw ResourceException("Invalid font: Error setting font size.");
    }
    
    // Set the font size
    FT_Set_Pixel_Sizes(face, size, 0);

    // Step 2: Find maxAscent/Descent to calculate imageHeight //
    size_t imageHeight = 0;
    size_t imageWidth = 256;
    int maxDescent = 0;
    int maxAscent = 0;
    size_t lineSpace = imageWidth - MARGIN;
    size_t lines = 1;
    size_t charIndex;

    for(unsigned int ch = 0; ch < NUM_CHARS; ++ch)
    {
        // Look up the character in the font file.
        charIndex = FT_Get_Char_Index(face, ch+SPACE);

        // Render the current glyph.
        FT_Load_Glyph(face, charIndex, FT_LOAD_RENDER);

        res.widths[ch] = (face->glyph->metrics.horiAdvance >> 6) + MARGIN;
        // If the line is full go to the next line
        if(res.widths[ch] > lineSpace)
        {
            lineSpace = imageWidth - MARGIN;
            ++lines;
        }
        lineSpace -= res.widths[ch];

        maxAscent = std::max(face->glyph->bitmap_top, maxAscent);
        maxDescent = std::max(face->glyph->bitmap.rows -
                                face->glyph->bitmap_top, maxDescent);
    }

    res.height = maxAscent + maxDescent;   // calculate height_ for text

    // Compute how high the texture has to be.
    size_t neededHeight = (maxAscent + maxDescent + MARGIN) * lines + MARGIN;
    // Get the first power of two in which it will fit
    imageHeight = 16;
    while(imageHeight < neededHeight)
    {
        imageHeight <<= 1;
    }

    // Step 3: Generation of the actual texture //

    // create and zero the memory
    unsigned char* image = new unsigned char[imageHeight * imageWidth];
    std::memset(image, 0, imageHeight * imageWidth);

    // These are the position at which to draw the next glyph
    size_t x = MARGIN;
    size_t y = MARGIN + maxAscent;
    float texX1, texX2, texY1, texY2;   // used for display list

    res.listBase = glGenLists(NUM_CHARS);  // generate the lists for filling

    // Drawing loop
    for(unsigned int ch = 0; ch < NUM_CHARS; ++ch)
    {
        size_t charIndex = FT_Get_Char_Index(face, ch+SPACE);

        // Render the glyph
        FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        // See whether the character fits on the current line
        if(res.widths[ch] > imageWidth - x)
        {
            x = MARGIN;
            y += (maxAscent + maxDescent + MARGIN);
        }

        // calculate texture coordinates of the character
        texX1 = static_cast<float>(x) / imageWidth;
        texX2 = static_cast<float>(x+res.widths[ch]) / imageWidth;
        texY1 = static_cast<float>(y - maxAscent) / imageHeight;
        texY2 = texY1 + static_cast<float>(res.height) / imageHeight;

        // generate the character's display list
        glNewList(res.listBase + ch, GL_COMPILE);
        glBegin(GL_QUADS);
        glTexCoord2f(texX1,texY1);  glVertex2i(0, 0);
        glTexCoord2f(texX2,texY1);  glVertex2i(res.widths[ch], 0);
        glTexCoord2f(texX2,texY2);  glVertex2i(res.widths[ch], res.height);
        glTexCoord2f(texX1,texY2);  glVertex2i(0, res.height);
        glEnd();
        glTranslatef(res.widths[ch],0,0);  // translate forward
        glEndList();

        // copy image generated by FreeType to the texture
        for(int row = 0; row < face->glyph->bitmap.rows; ++row)
        {
            for(int pixel = 0; pixel < face->glyph->bitmap.width; ++pixel)
            {
                // set pixel at position to intensity (0-255) at the position
                image[(x + face->glyph->bitmap_left + pixel) +
                    (y - face->glyph->bitmap_top + row) * imageWidth] =
                        face->glyph->bitmap.buffer[pixel +
                            row * face->glyph->bitmap.pitch];
            }
        }

        x += res.widths[ch];
    }

    // generate the OpenGL texture from the byte array
    glGenTextures(1, &res.texID);
    glBindTexture(GL_TEXTURE_2D, res.texID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA8, imageWidth, imageHeight, 0,
                    GL_ALPHA, GL_UNSIGNED_BYTE, image);

    delete[] image;     // now done with the image memory
    FT_Done_Face(face); // free the face data
}

void FontResourceManager::freeResource(FontResource &res)
{
    if(glIsList(res.listBase))
    {
        glDeleteLists(res.listBase, NUM_CHARS);
    }
    if(glIsTexture(res.texID))
    {
        glDeleteTextures(1, &res.texID);
    }
}

}
}
