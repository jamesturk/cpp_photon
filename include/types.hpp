//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: types.hpp,v 1.2 2005/02/16 06:58:05 cozman Exp $

#ifndef PHOTON_TYPES_HPP
#define PHOTON_TYPES_HPP

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

// Title: Basic Types

namespace photon {

// Group: Types

    // Type: ubyte
    //  Unsigned byte, alias for unsigned char.
    typedef unsigned char ubyte;

    // Type: uint
    //  Alias for unsigned integer.
    typedef unsigned int uint;

    // Type: scalar
    //  Scalar value, used throughout photon. (double or float)
    typedef double scalar;
    
    // Type: StrVec
    //  Typedef for vector of strings, which is used all throughout photon.
    typedef std::vector<std::string> StrVec;
    
    // Type: shared_ptr
    //  Shared pointer type. (uses the boost implementation)
    using boost::shared_ptr;

}

#endif  //PHOTON_TYPES_HPP