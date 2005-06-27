//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exceptions.cpp,v 1.7 2005/06/27 04:24:16 cozman Exp $


#include "exceptions.hpp"


namespace photon 
{

Throwable::Throwable(const std::string& description,
                        const std::string& file, uint line) throw() :
    description_(description), file_(file), line_(line)
{}

Throwable::~Throwable() throw()
{}

std::string Throwable::what() const throw()
{
    std::ostringstream ss;

    ss << description_;
    if(!file_.empty())
    {
        ss << " (" << file_ << ":" << line_ << ")";
    }
    return ss.str();
}

std::string Throwable::getDesc() const throw()
{
    return description_;
}

std::ostream& operator<<(std::ostream& os, const Throwable& rhs)
{
    return os << rhs.what();
}

//exceptions//

Exception::Exception(const std::string& description,
                        const std::string& file, uint line) throw() :
    Throwable(description,file,line) {}
std::string Exception::what() const throw()
{
    return "General exception occured: " + Throwable::what();
}

ArgumentException::ArgumentException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::string ArgumentException::what() const throw()
{
    return "Invalid argument exception occured: " + Throwable::what();
}

PreconditionException::PreconditionException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::string PreconditionException::what() const throw()
{
    return "Precondition exception occured: " + Throwable::what();
}

RangeException::RangeException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::string RangeException::what() const throw()
{
    return "Out-of-range exception: " + Throwable::what();
}

ResourceException::ResourceException(const std::string& description,
                                const std::string& file, uint line) throw() :
    Exception(description,file,line) {}
std::string ResourceException::what() const throw()
{
    return "Resource exception: " + Throwable::what();
}

//errors//

Error::Error(const std::string& description,
                const std::string& file, uint line) throw() :
    Throwable(description,file,line) {}
std::string Error::what() const throw()
{
    return "General error occured: " + Throwable::what();
}

MemoryError::MemoryError(const std::string& description,
                            const std::string& file, uint line) throw() :
    Error(description,file,line) {}
std::string MemoryError::what() const throw()
{
    return "Memory error occured: " + Throwable::what();
}

APIError::APIError(const std::string& description,
                    const std::string& file, uint line) throw() :
    Error(description,file,line) {}
std::string APIError::what() const throw()
{
    return "Error occured within another library: " + Throwable::what();
}

}
