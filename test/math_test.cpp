//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: math_test.cpp,v 1.1 2005/07/06 04:27:23 cozman Exp $

// Tests almost everything within photon::math
// Doesn't test:
//  -Circle-Rectangle intersection: hard to test without graphics
//  -Accessors: so many of them, simple to detect problems, possibly add later
//  -Rect: coming soon
//  -Vector2: coming soon

#include <iostream>
#include <iomanip>
#include "photon.hpp"
using namespace photon;
using namespace std;

int main() 
{
    // Show sample usage of all functions in math.hpp
    cout << "--General Math-------------------------------------------------\n";
    cout << "PI = " << setprecision(10) << math::PI << "\n";
    cout << "clamp(2.5, 0, 5)  = " << math::clamp(2.5, 0, 5) << "\n";
    cout << "clamp(-1, 0, 5)  = " << math::clamp(-1, 0, 5) << "\n";
    cout << "clamp(1000, 0, 5)  = " << math::clamp(1000, 0, 5) << "\n";
    cout << "scalarCompare(3.0, 3.0000001) are " << 
            (math::scalarCompare(3.0, 3.0000001) ? "" : "not") << " equal\n";
    cout << "scalarCompare(3.0, 3.1) are " << 
            (math::scalarCompare(3.0, 3.1) ? "" : "not") << " equal\n";
    cout << "PI/6 radians = " << math::radToDeg(math::PI/6) << " degrees\n";
    cout << "45 degrees = " << math::degToRad(45) << " radians\n";
    cout << endl;
    
    // Demo Circle class
    cout << "--Circles------------------------------------------------------\n";
    math::Circle a( math::Point2(0, 0), 1);     // circle at origin w/ radius 5
    math::Circle b( math::Point2(10, 10), 25);  // circle at 10,10 w/ radius 25
    math::Circle c( math::Point2(-10, -10), 1); // circle at -10,-10 w/ radius 1
    math::Point2 ori(0, 0); //origin
    cout << "a: " << a << "\nb: " << b << "\n";
    cout << (a == a ? "a ==" : "a !=") << " a\n";
    cout << (a == b ? "a ==" : "a !=") << " b\n"; 
    cout << "Moving a to 100,100: ";
    a.moveTo( math::Point2(100, 100) );
    cout << "a: " << a << "\n";
    cout << "Moving a by -100,-100: ";
    a.moveRel( -100, -100 );
    cout << "a: " << a << "\n";
    cout << "Resizing a's radius to 2: ";
    a.resize(2);
    cout << "a: " << a << "\n";
    cout << "Resizing a's radius by -3 (can't have negative radius): ";
    a.resizeRel(-3);
    cout << "a: " << a << "\n";
    cout << "Resizing a's radius by +3: ";
    a.resizeRel(3);
    cout << "a: " << a << "\n";
    cout << "a and b " << (a.intersects(b) ? "" : "do not") << " intersect.\n";
    cout << "a and c " << (a.intersects(c) ? "" : "do not") << " intersect.\n";
    cout << "a " << (a.contains(ori) ? "contains " : "doesn't contain ") << ori 
        << ".\n";
    cout << "c " << (c.contains(ori) ? "contains " : "doesn't contain ") << ori
        << ".\n";
    
    cout << endl;
    
    // Demo Rect class
    cout << "--Rects--------------------------------------------------------\n";

}
