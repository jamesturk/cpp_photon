//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: VersionInfo.cpp,v 1.2 2005/02/05 02:57:07 cozman Exp $
//
// Revisions:
//  $Log: VersionInfo.cpp,v $
//  Revision 1.2  2005/02/05 02:57:07  cozman
//  *** empty log message ***
//
//  Revision 1.1  2005/01/27 03:35:24  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#include "util/VersionInfo.h"

namespace photon { 
namespace util { 

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int rel,
                            std::string ext) :
    major(maj), minor(min), release(rel), extra(ext)
{
}

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
            if(this->release < rhs.release)
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
    return this->extra == rhs.extra && this->release == rhs.release &&
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
    return o << rhs.major << '.' << rhs.minor << '.' << rhs.release <<
            " [" << rhs.extra << "]";
}

}
}
