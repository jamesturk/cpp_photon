//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VersionInfo.cpp,v 1.4 2005/02/16 06:58:26 cozman Exp $

#include "util/VersionInfo.hpp"

namespace photon { 
namespace util { 

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int pat,
                            std::string ext) :
    major(maj), minor(min), patch(pat), extra(ext)
{}

VersionInfo::VersionInfo() :
    major(0), minor(0), patch(0)
{}

bool VersionInfo::operator<(const VersionInfo &rhs) const
{
    //chained compares, compare numbers in order of importance
    if(this->major < rhs.major)
        return true;
    else if(this->major == rhs.major)
    {
        if(this->minor < rhs.minor)
            return true;
        else if(this->minor == rhs.minor)
        {
            if(this->patch < rhs.patch)
                return true;
        }
    }
    return false;   //if it reaches this point rhs is >=
}

bool VersionInfo::operator<=(const VersionInfo &rhs) const
{
    return ((*this) < rhs || (*this) == rhs);
}

bool VersionInfo::operator==(const VersionInfo &rhs) const
{
    return this->extra == rhs.extra && this->patch == rhs.patch &&
            this->minor == rhs.minor && this->major == rhs.major;
}

bool VersionInfo::operator>=(const VersionInfo &rhs) const
{
    return ((*this) < rhs || (*this) == rhs);
}

bool VersionInfo::operator>(const VersionInfo &rhs) const
{
    return !((*this) <= rhs);
}

std::ostream& operator<<(std::ostream &o, const VersionInfo &rhs)
{
    return o << rhs.major << '.' << rhs.minor << '.' << rhs.patch <<
            " [" << rhs.extra << "]";
}

}
}
