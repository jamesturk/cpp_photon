//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: RandGen_test.cpp,v 1.1 2005/05/15 02:50:07 cozman Exp $

#include <iostream>
#include <iomanip>
#include "photon.hpp"
using namespace photon::util;
using namespace std;

int main() 
{
    RandGen g1;
    RandGen g2(0);
    RandGen g3(0);
    const int N=100;
    double v[6] = {0};
    double s[6] = {0};
    double approx[6] = {3.5, 3.5, 3.5, 50, 0, 0.5};
    
    std::cout << "d6       |d6        |d6     | [1,100]  | +/-   | [0,1)  \n";
    std::cout << "---------------------------------------------------------------\n";
    for(int i=0; i < N; ++i)
    {
        v[0] = g1.genRand(1,6);
        v[1] = g2.genRand(1,6);
        v[2] = g3.genRand(1,6);
        v[3] = g1.genRand(0.0,100.0);
        v[4] = g1.genRandSign();
        v[5] = g1.genRand01();
        for(int j=0; j < 6; ++j) 
        {
            std::cout.setf(ios::left);
            std::cout << std::setw(9) << v[j] << " ";
            s[j] += v[j];
        }
        std::cout << std::endl;
    }
    std::cout << "-average-------------------------------------------------------\n";
    for(int j=0; j < 6; ++j)
    {
        std::cout << std::setw(9) << s[j]/N << " ";
    }
    std::cout << "\n-should be near------------------------------------------------\n";
    for(int j=0; j < 6; ++j)
    {
        std::cout.setf(ios::left);
        std::cout << std::setw(9) << approx[j] << " ";
    }
    std::cout << std::endl;
    
    //Yes I realize what is incorrect about this, "should be near" has no 
    // meaning since random data can disobey all reason and give you a string
    // of 20 billion 6's when rolling a 6-sided die.  Most of the time however
    // the values will fall within a small deviation from the "expected" and 
    // they are there for reference when ensuring that the bounds are set
    // properly on the generators.
}
