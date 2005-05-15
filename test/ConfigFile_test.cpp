//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: ConfigFile_test.cpp,v 1.1 2005/05/15 02:50:07 cozman Exp $

#include "photon.hpp"

#include <iostream>
#include <cassert>

using namespace photon;
using namespace photon::util;


class ConfigTest : public Application
{
public:

    int main(const StrVec& args)
    {
        ConfigFile c1("config1.ini"),c2;
        c2.open("config2.ini");
        
        c1.setVariable("sec","int",3);
        c1.setVariable("sec","float",3.0f);
        c1.setVariable("sec","string","three");
        
        assert(c1.getVariable("sec","int",0) == 3);
        assert(c1.getVariable("sec","float",0.0f) == 3.0f);
        assert(c1.getVariable("sec","string",std::string()) == "three");
        
        assert(c2.getVariable("sec","var",-1) != -1);
        assert(c2.getVariable("sec2","var",-1) != -1);
        assert(c2.getVariable("sec2","hex",0) == 0);
    
        c1.close();
        c2.close();
        
        return 0;
    }
};

ENTRYPOINT(ConfigTest)
