//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VersionInfo.hpp,v 1.2 2005/02/16 06:58:06 cozman Exp $

#ifndef PHOTON_UTIL_VERSIONINFO_HPP
#define PHOTON_UTIL_VERSIONINFO_HPP

#include <string>
#include <ostream>

namespace photon { 
namespace util { 

// Class: VersionInfo
//  Class which stores version information, such as release numbers.
//  Format is Major.Minor.Release [ExtraInfo].
//
// Operators:
//   - VersionInfo < VersionInfo
//   - VersionInfo <= VersionInfo
//   - VersionInfo == VersionInfo
//   - VersionInfo >= VersionInfo
//   - VersionInfo > VersionInfo
//   - ostream& << VersionInfo
class VersionInfo
{
public:
    // Group: Variables

    // Variable: major
    //  Major version number, should be changed when major changes take place.
    unsigned int major;

    // Variable: minor
    //  Minor version number, should be changed when key features are
    //  added/removed/changed.
    unsigned int minor;

    // Variable: patch
    //  Patch number, should be changed upon every release that isn't
    //  signifigant enough to reflect a change in the minor versioning number.
    unsigned int patch;

    // Variable: extra
    //  String for holding extra data, such as a release name or special tag.
    std::string extra;

    // Group: (Con/De)structors
    
    // Function: VersionInfo
    //  Default constructor.
    VersionInfo();

    // Function: VersionInfo
    //  Initializing constructor.
    //
    // Parameters:
    //  maj - Major version number.
    //  min - Minor version number.
    //  pat - Patch number.
    //  ext - Extra info string. [default: ""]
    VersionInfo(unsigned int maj, unsigned int min, unsigned int pat,
                std::string ext="");

    //operators
    bool operator<(const VersionInfo &rhs) const;
    bool operator<=(const VersionInfo &rhs) const;
    bool operator==(const VersionInfo &rhs) const;
    bool operator>=(const VersionInfo &rhs) const;
    bool operator>(const VersionInfo &rhs) const;

    //output operator
    friend std::ostream& operator<<(std::ostream &o, const VersionInfo &rhs);
};

}
}

#endif  //PHOTON_UTIL_VERSIONINFO_HPP
