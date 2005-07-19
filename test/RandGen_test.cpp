//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: RandGen_test.cpp,v 1.2 2005/07/19 21:02:04 cozman Exp $

#include <iostream>
#include <iomanip>
#include "photon.hpp"
using namespace photon::util;
using namespace std;

// simple demo of RandGen
int main() 
{
    RandGen g1;
    RandGen g2(0);  // seed randgen 2 and 3 with same number so they are in sync
    RandGen g3(0);
    const int N=100;    // number of iterations
    double v[6] = {0};
    double s[6] = {0};
    double approx[6] = {3.5, 3.5, 3.5, 50, 0, 0.5};
    
    // draw explanation of what each column is
    std::cout << "d6       |d6        |d6     | [1,100]  | +/-   | [0,1)  \n";
    std::cout << "----------------------------------------------------------\n";
    for(int i=0; i < N; ++i)
    {
        // first 3 columns are 6 sided die
        v[0] = g1.genRand(1,6);
        v[1] = g2.genRand(1,6);
        v[2] = g3.genRand(1,6);
        // random scalar between 0 and 100
        v[3] = g1.genRand(0.0,100.0);
        // random sign (+1 or -1)
        v[4] = g1.genRandSign();
        // probability [0,1)
        v[5] = g1.genRand01();
        
        // do output of all 6 in columns
        for(int j=0; j < 6; ++j) 
        {
            std::cout.setf(ios::left);
            std::cout << std::setw(9) << v[j] << " ";
            s[j] += v[j];   // accumulate sum for each column
        }
        std::cout << std::endl;
    }
    
    // output averages
    std::cout << "-average--------------------------------------------------\n";
    for(int j=0; j < 6; ++j)
    {
        std::cout << std::setw(9) << s[j]/N << " ";
    }
    
    // output 'expected' averages
    std::cout << "\n-expected average---------------------------------------\n";
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
