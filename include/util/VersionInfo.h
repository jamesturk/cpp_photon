//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VersionInfo.h,v 1.2 2005/02/05 02:57:07 cozman Exp $
//
// Revisions:
//  $Log: VersionInfo.h,v $
//  Revision 1.2  2005/02/05 02:57:07  cozman
//  *** empty log message ***
//
//  Revision 1.1  2005/01/27 03:35:23  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#ifndef PHOTON_UTIL_VERSIONINFO_H
#define PHOTON_UTIL_VERSIONINFO_H

#include <string>
#include <ostream>

namespace photon { 
namespace util { 

// Class: VersionInfo
//  Class which stores version information, such as release numbers.
//  Format is Major.Minor.Release [ExtraInfo].
//
// Operators:
//   VersionInfo < VersionInfo
//   VersionInfo <= VersionInfo
//   VersionInfo == VersionInfo
//   VersionInfo >= VersionInfo
//   VersionInfo > VersionInfo
//   ostream& << VersionInfo
class VersionInfo
{
public:
    // Group: Variables

    // Variable: Major
    //  Major version number, should be changed when major changes take place.
    unsigned int major;

    // Variable: Minor
    //  Minor version number, should be changed when key features are
    //  added/removed/changed.
    unsigned int minor;

    // Variable: Release
    //  Release number, should be changed upon every release that isn't
    //  signifigant enough to reflect a change in the minor versioning number.
    unsigned int release;

    // Variable: Extra
    //  String for holding extra data, such as a release name or special tag.
    std::string extra;

    // Group: (Con/De)structors

    // Function: VersionInfo
    //  Initializing constructor, VersionInfo must be initalized with this
    //  constructor.
    //
    // Parameters:
    //  maj - Major version number.
    //  min - Minor version number.
    //  rel - Release number.
    //  ext - Extra info string. [default: ""]
    VersionInfo(unsigned int maj, unsigned int min, unsigned int rel,
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

#endif  //PHOTON_UTIL_VERSIONINFO_H
