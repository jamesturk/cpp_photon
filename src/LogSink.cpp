//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: LogSink.cpp,v 1.1 2005/01/27 03:35:24 cozman Exp $
//
// Revisions:
//  $Log: LogSink.cpp,v $
//  Revision 1.1  2005/01/27 03:35:24  cozman
//  initial import (exceptions,types, and logging,oh my!)
//
//

#include "LogSink.h"

#include <iostream>

namespace photon
{ 

//LogSink

LogSink::LogSink(std::string name, bool dynamic) :
    name_(name),dynamic_(dynamic)
{
}

LogSink::~LogSink()
{
}

std::string LogSink::getName() const
{
    return name_;
}

bool LogSink::isDynamic() const
{
    return dynamic_;
}

//ConsoleSink

ConsoleSink::ConsoleSink(std::string name, bool dynamic) :
    LogSink(name,dynamic)
{
}

ConsoleSink::~ConsoleSink()
{
}

void ConsoleSink::writeMessage(LogLevel level, std::string msg)
{
    static char* pre[] = { "    NOTE: ",
                           " VERBOSE: ",
                           " WARNING: ",
                           "   ERROR: ",
                           "CRITICAL: " };

    std::cerr << pre[static_cast<int>(level)] << msg << std::endl;
}

//TextSink

TextSink::TextSink(std::string name, bool dynamic) :
    LogSink(name,dynamic),
    out_(std::string(name+".txt").c_str())
{
}

TextSink::~TextSink()
{
    out_.close();
}

void TextSink::writeMessage(LogLevel level, std::string msg)
{
    static char* pre[] = { "    NOTE: ",
                           " VERBOSE: ",
                           " WARNING: ",
                           "   ERROR: ",
                           "CRITICAL: " };

    out_ << pre[static_cast<int>(level)] << msg << std::endl;
}

//HtmlSink

HtmlSink::HtmlSink(std::string name, bool dynamic) :
    LogSink(name,dynamic),
    out_(std::string(name+".html").c_str())
{
    out_ << "<html><head><title>Error Log</title>\n<style type=\"text/css\">"
         << std::endl << "<!--" << std::endl
         << "p { margin: 0 }" << std::endl
         << ".note { font-style:italic color:gray }" << std::endl
         << ".verbose { font-style:italic; background:yellow; font-size:small }"
         << std::endl
         << ".warning { font-weight:bold; background:yellow }" << std::endl
         << ".error { font-weight:bold; background:orange }" << std::endl
         << ".critical { font-weight:bold; background:red; color:white }"
         << std::endl
         << "-->" << std::endl << "</style>" << std::endl << "</head>"
         << std::endl << "<body>" << std::endl;
}

HtmlSink::~HtmlSink()
{
    out_ << "</body></html>" << std::endl;
    out_.close();
}

void HtmlSink::writeMessage(LogLevel level, std::string msg)
{
    static char* css[] = {"note","verbose","warning","error","critical"};
    static char* pre[] = { "    NOTE: ",
                           " VERBOSE: ",
                           " WARNING: ",
                           "   ERROR: ",
                           "CRITICAL: " };

    out_ << "<p class=\"" << css[static_cast<int>(level)] << "\">"
            << pre[static_cast<int>(level)] << msg << "</p>" << std::endl;
}

}
