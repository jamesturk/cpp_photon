//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ConfigFile.cpp,v 1.5 2005/03/03 09:25:47 cozman Exp $

#include "util/ConfigFile.hpp"
#include "exceptions.hpp"
#include <cctype>
#include <fstream>

namespace photon
{ 
namespace util
{

//(Con/De)structors

ConfigFile::ConfigFile()
{
}

ConfigFile::ConfigFile(const std::string& filename)
{
    open(filename);
}

ConfigFile::~ConfigFile()
{
    close();
}

//File Access

void ConfigFile::open(const std::string& filename)
{
    filename_ = filename;
    if(filename_.empty())
    {
        throw PreconditionException("Empty filename in ConfigFile::open");
    }

    std::string section, var, val, str, clean;
    std::ifstream file(filename_.c_str());
    
    if(!file)
    {
        throw Error("Unable to open " + filename_ +
                    " for reading in ConfigFile::open");
    }

    layout_.clear();    //clear layout, just in case

    while(file)  //parses entire file
    {
        std::getline(file,str);    //read in a line
        clean = cleanString(str);    //get a clean version

        //if std::string is bracketed it is a section
        if(clean[0] == '[' && clean[clean.length()-1] == ']')
        {
            section = str;
        }
        else if(std::isalpha(clean[0]))   //variables must start with a letter
        {
            //split at the equals sign
            var = str.substr(0,str.find('='));
            val = str.substr(str.find('=')+1);
            setVariable(section,var,val);
        }
        else if(clean[0] == '#' || clean[0] == ';') //comments
        {
            setVariable(section,"_comment",str);
        }
        else if(clean.length() == 0 && !file.eof())  //save blank lines
        {
            setVariable(section,"_newline",str);
        }

    }
    file.close();
}

void ConfigFile::flush() 
{
    Layout::iterator sec;
    Section::iterator var;
    std::string secName;

    //in case the filename is already cleared
    if(filename_.empty())
    {
        throw PreconditionException("No filename in ConfigFile::flush");
    }

    //open the file blanked out, to not duplicate entries
    std::ofstream file(filename_.c_str(), std::ios::out|std::ios::trunc);

    if(!file)
    {
        throw Error("Unable to open " + filename_ +
                    " for writing in ConfigFile::flush");
    }

    //iteration through sections
    for(sec = layout_.begin(); sec != layout_.end(); ++sec)
    {
        //ensure that section is valid
        secName = cleanString(sec->first);
        if(secName[0] == '[' && secName[secName.length()-1] == ']')
        {
            file << sec->first << std::endl;    //write out raw section title

            //for each variable in section, write out variable=value
            for(var = sec->second.begin(); var != sec->second.end(); ++var)
            {
                if(var->first[0] == '_')    //special values start with _
                {
                    if(var->first.substr(1) == "comment")
                    {
                        file << var->second << std::endl;
                    }
                    else if(var->first.substr(1) == "newline")
                    {
                        file << std::endl;
                    }
                }
                else if(!cleanString(var->first).empty())   //a variable
                {
                    file << var->first << '=' << var->second << std::endl;
                }
            }
        }
    }
    file.close();
}

void ConfigFile::close()
{
    //flush and clear out the data members
    flush();
    filename_ = std::string();
    layout_.clear();
}

std::string ConfigFile::cleanString(const std::string& str)
{
    std::string ret(str);
    
    //convert to lower case
    std::transform( ret.begin(), ret.end(), ret.begin(),
                    static_cast<int(*)(int)>(std::tolower) );
                    
    //remove all spaces
    for(std::string::iterator i=ret.begin(); i != ret.end(); ++i)
    {
        if(std::isspace(*i))
        {
            i = ret.erase(i);
        }
    }

    return ret;
}

std::string ConfigFile::bracketString(const std::string& str)
{
    std::string ret( cleanString(str) );
    
    //add brackets if they do not exist, unless the string is empty
    if(!ret.empty() && ret[0] != '[' || ret[ret.length()-1] != ']')
    {
        ret = "["+ret+"]";
    }
    
    return ret;
}

}
}
