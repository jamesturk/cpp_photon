//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VersionInfo.cpp,v 1.6 2005/03/03 09:25:47 cozman Exp $

#include "util/VersionInfo.hpp"

#include <sstream>

#include "exceptions.hpp"

namespace photon 
{ 
namespace util 
{ 

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int pat,
                            std::string ext) :
    major(maj), minor(min), patch(pat), extra(ext)
{}

VersionInfo::VersionInfo() :
    major(0), minor(0), patch(0)
{}

bool VersionInfo::operator<(const VersionInfo &rhs) const
{
    bool less(false);
    
    //chained compares, compare numbers in order of importance
    if(this->major < rhs.major)
    {
        less = true;
    }
    else if(this->major == rhs.major)
    {
        if(this->minor < rhs.minor)
        {
            less = true;
        }
        else if(this->minor == rhs.minor)
        {
            if(this->patch < rhs.patch)
            {
                less = true;
            }
        }
    }
    
    return less;    //false unless set to true within if-chain
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
    // output major.minor.path [extra] (extra is only printed if not empty)
    return o << rhs.major << '.' << rhs.minor << '.' << rhs.patch <<
            (rhs.extra.empty() ? "" : " [" + rhs.extra + "]");
}

void ensureVersion(const std::string& library,
                    const util::VersionInfo& version,
                    const util::VersionInfo& required)
{
    std::stringstream ss;

    if(version < required)
    {
        ss << library << " version " << required << " required; " <<
            version << " used, please update.";
        throw APIError(ss.str());   // throw APIError if requirement isn't met
    }
}

}
}
