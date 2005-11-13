//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ConfigFile.hpp,v 1.7 2005/11/13 07:59:48 cozman Exp $

#ifndef PHOTON_UTIL_CONFIGFILE_HPP
#define PHOTON_UTIL_CONFIGFILE_HPP

#include <string>
#include <list>
#include <sstream>
#include <functional>

namespace photon
{ 
namespace util
{ 

// Class: ConfigFile
//  ConfigFile class, for reading/writing INI-style config files.
//
//  File format is fairly flexible, whitespace and comments beginning with # or
//  ; are ignored & left intact.
//
//  Use []'s to denote sections.
//
//  Variables are defined in var=val format.
class ConfigFile
{

public: // types used in ConfigFile

    //predicate for search
    template<class pairT>
    class StrPairEq : public std::binary_function<pairT, std::string, bool>
    {
    public:
        bool operator()(const pairT& lhs, const std::string& rhs) const;
    };

    typedef std::pair<std::string,std::string> Variable;
    typedef std::list< Variable > Section;
    typedef std::pair< std::string, Section > NamedSection;
    typedef std::list< NamedSection > Layout;
    
// Group: (Con/De)structors
public:

    // Function: ConfigFile
    //  Default constructor for ConfigFile.
    ConfigFile();

    // Function: ConfigFile
    //  Constructor for ConfigFile, calls <open>.
    //
    // Parameters:
    //  filename - Name of ConfigFile to open.
    ConfigFile(const std::string& filename);

    // Function: ~ConfigFile
    //  Calls close upon the ConfigFile.
    virtual ~ConfigFile();

// Group: File Access
public:

    // Function: open
    //  Open a file, processing it as an INI-like config file.
    //
    // Parameters:
    //  filename - Name of ConfigFile to open.
    void open(const std::string& filename);

    // Function: flush
    //  Flushes the data written to the config file to disk, generally needs
    //  not be called.
    void flush();

    // Function: close
    //  Flushes the data and closes, open must be called again before using same
    //  ConfigFile.
    void close();

    // Function: setVariable
    //  Template function for setting variables in the config file.
    //
    //  WARNING: Do not try to use this with user-defined types, numeric types
    //   and strings work fine, and this is all that should be contained in
    //   an INI.
    //
    // Parameters:
    //  sec - section name within config file
    //  var - variable name within section
    //  value - value to set variable equal to
    template<class varType>
    void setVariable(const std::string& sec,
                        const std::string& var,
                        varType value);

    // Function: getVariable
    //  Template function for getting values from the config file. Supports
    //  returning a default value if the desired variable was not found.
    //
    //  WARNING: Do not try to use this with user-defined types, numeric types
    //   and strings work fine, and this is all that should be contained in
    //   an INI.
    //
    // Parameters:
    //  sec - section name within config file
    //  var - variable name within section
    //  defVal - value to return if variable does not exist
    //
    // Returns:
    //  Value of variable within config file or defVal if value was not found.
    template<class varType>
    varType getVariable(const std::string& sec,
                        const std::string& var,
                        varType defVal) const;

// behind the scenes utils
private:
    static std::string cleanString(const std::string& str);
    static std::string bracketString(const std::string& str);
    
private:
    Layout layout_;
    std::string filename_;

};

//predicate for search
template<class pairT>
bool ConfigFile::StrPairEq<pairT>::operator()(const pairT& lhs,
                                        const std::string& rhs) const
{
    return ConfigFile::cleanString(lhs.first) == ConfigFile::cleanString(rhs);
}

//Template implementation
template<class varType>
void
ConfigFile::setVariable(const std::string& sec,
                        const std::string& var,
                        varType value)
{
    std::string secBrac(bracketString(sec));
    Layout::iterator secIter;
    Section::iterator varIter;
    std::ostringstream ss;

    ss << value;            //write value to string

    //search for section
    secIter = std::find_if( layout_.begin(),
                            layout_.end(),
                            std::bind2nd(StrPairEq<NamedSection>(), secBrac) );

    // add the section if it does not exist
    if(secIter == layout_.end())
    {
        layout_.push_back( NamedSection( secBrac, Section() )  );
        
        // search again
        secIter = std::find_if( layout_.begin(),
                                layout_.end(),
                                std::bind2nd(StrPairEq<NamedSection>(), 
                                                secBrac) );
    }

    // search for variable
    varIter = std::find_if( secIter->second.begin(),
                            secIter->second.end(),
                            std::bind2nd(StrPairEq<Variable>(), var) );

    // add the variable if it does not exist
    if(varIter == secIter->second.end())
    {
        secIter->second.push_back( Variable(var, ss.str()) );
    }
    else
    {
        varIter->second = ss.str();
    }
}

//template specialization for setVariable<std::string> (DISABLED)
#if 0
template<>
void
ConfigFile::setVariable(std::string sec, std::string var, std::string value)
{
    sec = "[" + sec + "]";          //add []s to section name
    value = "\"" + value + "\"";    //add ""s to value

    layout_[sec][var] = value;   //actually set it
}
#endif

template<class varType>
varType
ConfigFile::getVariable(const std::string& sec,
                        const std::string& var,
                        varType defVal) const
{
    std::string secBrac(bracketString(sec));
    std::stringstream ss;
    varType ret(defVal);
    Layout::const_iterator secIter;
    Section::const_iterator varIter;

    secIter = std::find_if( layout_.begin(),
                            layout_.end(),
                            std::bind2nd(StrPairEq<NamedSection>(), secBrac) );
    if(secIter != layout_.end())
    {
        varIter = std::find_if( secIter->second.begin(),
                                secIter->second.end(),
                                std::bind2nd(StrPairEq<Variable>(), var) );
        if(varIter != secIter->second.end())
        {
            ss.str(varIter->second);
            ss >> ret;
        }
    }
    
    return ret;
}

}
}

#endif  //PHOTON_UTIL_CONFIGFILE_HPP
