//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: exception_test.cpp,v 1.2 2005/06/10 07:06:07 cozman Exp $

#include "photon.hpp"
#include "exceptions.hpp"
#include "entrypoint.hpp" 

using namespace photon;


class ExceptionTest : public Application
{
public:

    int main(const StrVec& args)
    {
        throw Error("catch this!");

        return 0;
    }
};

ENTRYPOINT(ExceptionTest)

