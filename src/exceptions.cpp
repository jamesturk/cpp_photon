//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exceptions.cpp,v 1.5 2005/02/16 06:58:26 cozman Exp $


#include "exceptions.hpp"


namespace photon 
{

Throwable::Throwable(const std::string& description,
                        const std::string& file, uint line) throw() :
    description_(description), file_(file), line_(line)
{}

Throwable::~Throwable() throw()
{}

std::string Throwable::getDesc() const throw()
{
    std::ostringstream ss;

    ss << description_;
    if(!file_.empty())
    {
        ss << " (" << file_ << ":" << line_ << ")";
    }
    return ss.str();
}

//exceptions//

Exception::Exception(const std::string& description,
                        const std::string& file, uint line) throw() :
    Throwable(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const Exception& rhs)
{
    return os << "General exception occured: " << rhs.getDesc();
}

ArgumentException::ArgumentException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const ArgumentException& rhs)
{
    return os << "Invalid argument exception occured. " << rhs.getDesc();
}

PreconditionException::PreconditionException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const PreconditionException& rhs)
{
    return os << "Precondition exception occured: " << rhs.getDesc();
}

RangeException::RangeException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const RangeException& rhs)
{
    return os << "Out-of-range exception: " << rhs.getDesc();
}

ResourceException::ResourceException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const ResourceException& rhs)
{
    return os << "Resource exception: " << rhs.getDesc();
}

//errors//

Error::Error(const std::string& description,
                const std::string& file, uint line) throw() :
    Throwable(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const Error& rhs)
{
    return os << "General error occured: " << rhs.getDesc();
}

MemoryError::MemoryError(const std::string& description,
                            const std::string& file, uint line) throw() :
    Error(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const MemoryError& rhs)
{
    return os << "Memory error occured: " << rhs.getDesc();
}

APIError::APIError(const std::string& description,
                    const std::string& file, uint line) throw() :
    Error(description,file,line) {}
std::ostream& operator<<(std::ostream& os, const APIError& rhs)
{
    return os << "Error occured within another library: " << rhs.getDesc();
}

}
