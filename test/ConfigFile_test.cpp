//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ConfigFile_test.cpp,v 1.2 2005/07/19 18:41:36 cozman Exp $

#include "photon.hpp"

#include <iostream>
#include <cassert>

using namespace photon;

// Simple test of ConfigFile functionality
// Tests reading/writing to a ConfigFile
// Successful test will simply output a message indicating success.
class ConfigTest : public Application
{
public:

    int main(const StrVec& args)
    {
        util::ConfigFile c1("config1.ini"),c2;
        c2.open("config2.ini");
        
        // set three variables
        c1.setVariable("sec","int",3);
        c1.setVariable("sec","float",3.0f);
        c1.setVariable("sec","string","three");
        
        // ensure all 3 variables were written correctly
        assert(c1.getVariable("sec","int",0) == 3);
        assert(c1.getVariable("sec","float",0.0f) == 3.0f);
        assert(c1.getVariable("sec","string",std::string()) == "three");
        
        // check reading/default value functionality
        assert(c2.getVariable("sec","var",-1) != -1);
        assert(c2.getVariable("sec2","var",-1) != -1);
        assert(c2.getVariable("sec2","hex",0) == 0);
    
        c1.close();
        c2.close();
        
        // got here, meaning success
        std::cerr << "ConfigFile test completed successfully!\n";
        
        return 0;
    }
};

ENTRYPOINT(ConfigTest)  // make ConfigTest the entrypoint class
