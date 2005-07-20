//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: math_test.cpp,v 1.4 2005/07/20 01:47:15 cozman Exp $

// Tests almost everything within photon::math (example run at bottom of file)
// Doesn't test:
//  -Circle-Rectangle intersection: hard to test without graphics
//  -Accessors: so many of them, simple to detect problems, possibly add later
//
// example checks should always contain a positive check followed by a negative
// ex:
//  a contains origin
//  b doesn't contain origin

#include <iostream>
#include <iomanip>
#include "photon.hpp"
using namespace photon;
using namespace std;


void testGeneral()
{
    // Show sample usage of all functions in math.hpp
    cout << "--General Math-------------------------------------------------\n";
    cout << "PI = " << setprecision(10) << math::PI << "\n";
    cout << setprecision(3);
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
}

void testCircle()
{
    // Demo Circle class
    cout << "--Circles------------------------------------------------------\n";
    math::Circle a( math::Point2(0, 0), 1);     // circle at origin w/ radius 5
    math::Circle b( math::Point2(10, 10), 25);  // circle at 10,10 w/ radius 25
    math::Circle c( math::Point2(-10, -10), 1); // circle at -10,-10 w/ radius 1
    math::Point2 ori(0, 0); //origin
    cout << "a: " << a << "\nb: " << b << "\nc: " << c << "\n";
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
    cout << "a and b" << (a.intersects(b) ? "" : " do not") << " intersect.\n";
    cout << "a and c" << (a.intersects(c) ? "" : " do not") << " intersect.\n";
    cout << "a " << (a.contains(ori) ? "contains " : "doesn't contain ") << ori 
        << ".\n";
    cout << "c " << (c.contains(ori) ? "contains " : "doesn't contain ") << ori
        << ".\n";
    cout << endl;
}

void testRect()
{
    // Demo Rect class
    cout << "--Rects--------------------------------------------------------\n";
    // show both construction methods
    math::Rect a(math::Point2(-4, -4), 4, 4);
    math::Rect b(math::Point2(-4, -4), math::Point2(6, 6));
    math::Rect c(a);  // copy of a for later use
    math::Rect d(math::Point2(-3, -3), 1, 1);
    math::Point2 ori(0, 0); //origin
    cout << "a: " << a << "\nb: " << b << "\nc: " << c << "\nd: " << d << "\n";
    cout << (a == a ? "a ==" : "a !=") << " a\n";
    cout << (a == b ? "a ==" : "a !=") << " b\n"; 
    cout << "Moving a to 0,0: ";
    a.moveTo( math::Point2(0, 0) );
    cout << "a: " << a << "\n";
    cout << "Moving a by 4,4: ";
    a.moveRel( 4, 4 );
    cout << "a: " << a << "\n";
    cout << "Resizing a to 8x8: ";
    a.resize( 8, 8 );
    cout << "a: " << a << "\n";
    cout << "Resizing a by 2 in each direction: ";
    a.resizeRel( 2, 2 );
    cout << "a: " << a << "\n";
    cout << "a and b" << (a.intersects(b) ? "" : " do not") << " intersect.\n";
    cout << "a and c" << (a.intersects(c) ? "" : " do not") << " intersect.\n";
    cout << "c " << (c.contains(d) ? "contains" : "doesn't contain") << " d\n";
    cout << "d " << (d.contains(c) ? "contains" : "doesn't contain") << " c\n";
    cout << "c " << (c.contains(ori) ? "contains " : "doesn't contain ") << ori 
        << ".\n";
    cout << "d " << (d.contains(ori) ? "contains " : "doesn't contain ") << ori
        << ".\n";
    cout << "a.calcIntersection(b) = " << a.calcIntersection(b) << "\n";
    cout << "a.calcIntersection(a) = " << a.calcIntersection(a) << "\n";
    cout << "a.calcIntersection(c) = " << a.calcIntersection(c) << "\n";
    cout << endl;
}

void testVector2()
{
    // Demo Vector2 class
    cout << "--Vector2------------------------------------------------------\n";
    math::Vector2 a;
    math::Vector2 b(1, 2);
    cout << "a: " << a << "\nb: " << b << "\n";
    cout << "Setting a to [5,5]: ";
    a.set(5, 5);
    cout << "a: " << a << "\n";
    cout << "Setting a to 5 units long at 45 degrees: ";
    a.resolveDeg(5, 45);
    cout << "a: " << a << "\n";
    cout << "Setting a to 5 units long at pi radians: ";
    a.resolveRad(5, math::PI);
    cout << "a: " << a << "\n";
    cout << "Normalizing a: ";
    a.normalize();
    cout << "a: " << a << "\n";
    cout << (a == a ? "a ==" : "a !=") << " a\n";
    cout << (a == b ? "a ==" : "a !=") << " b\n";
    cout << "-a = " << -a << "\n";
    cout << "a.b = " << a.dot(b) << "\n";
    cout << "a+b = " << a+b << "\n";
    cout << "a-b = " << a-b << "\n";
    cout << "2*a = " << 2*a << "\n";
    cout << "a/2 = " << a/2 << "\n";
    a+=b;
    cout << "a += b: " << a << "\n";
    a-=b;
    cout << "a -= b: " << a << "\n";
    cout << "|a| = " << a.getMagnitude() << "\n";
    cout << "|b| = " << b.getMagnitude() << "\n";
    cout << "angle of a (deg) = " << a.getAngleDeg() << "\n";
    cout << "angle of b (deg) = " << b.getAngleDeg() << "\n";
    cout << "angle of a (rad) = " << a.getAngleRad() << "\n";
    cout << "angle of b (rad) = " << b.getAngleRad() << "\n";
    cout << "normal of a: " << a.calcNormal() << "\n";
    cout << "normal of b: " << b.calcNormal() << "\n";
    cout << "angle between a and b (deg): " << a.calcInnerAngleDeg(b) << "\n";
    cout << "angle between a and b (rad): " << b.calcInnerAngleRad(a) << "\n";
    cout << "distance between a and b: " << math::distance(a,b) << "\n";
    cout << endl;
}

int main() 
{
    testGeneral();
    testCircle();
    testRect();
    testVector2();
}

// Example run (values may vary slightly):
// --General Math-------------------------------------------------
// PI = 3.141592654
// clamp(2.5, 0, 5)  = 2.5
// clamp(-1, 0, 5)  = 0
// clamp(1000, 0, 5)  = 5
// scalarCompare(3.0, 3.0000001) are  equal
// scalarCompare(3.0, 3.1) are not equal
// PI/6 radians = 30 degrees
// 45 degrees = 0.785 radians
// 
// --Circles------------------------------------------------------
// a: Circle { Center: (0,0) Radius: 1 }
// b: Circle { Center: (10,10) Radius: 25 }
// c: Circle { Center: (-10,-10) Radius: 1 }
// a == a
// a != b
// Moving a to 100,100: a: Circle { Center: (100,100) Radius: 1 }
// Moving a by -100,-100: a: Circle { Center: (0,0) Radius: 1 }
// Resizing a's radius to 2: a: Circle { Center: (0,0) Radius: 2 }
// Resizing a's radius by -3 (can't have negative radius): a: Circle 
//      { Center: (0,0) Radius: 0 }
// Resizing a's radius by +3: a: Circle { Center: (0,0) Radius: 3 }
// a and b intersect.
// a and c do not intersect.
// a contains (0,0).
// c doesn't contain (0,0).
// 
// --Rects--------------------------------------------------------
// a: Rect { Top left: (-4,-4) Width: 4 Height: 4 }
// b: Rect { Top left: (-4,-4) Width: 10 Height: 10 }
// c: Rect { Top left: (-4,-4) Width: 4 Height: 4 }
// d: Rect { Top left: (-3,-3) Width: 1 Height: 1 }
// a == a
// a != b
// Moving a to 0,0: a: Rect { Top left: (0,0) Width: 4 Height: 4 }
// Moving a by 4,4: a: Rect { Top left: (4,4) Width: 4 Height: 4 }
// Resizing a to 8x8: a: Rect { Top left: (4,4) Width: 8 Height: 8 }
// Resizing a by 2 in each direction: a: 
//      Rect { Top left: (4,4) Width: 10 Height: 10 }
// a and b intersect.
// a and c do not intersect.
// c contains d
// d doesn't contain c
// c contains (0,0).
// d doesn't contain (0,0).
// a.calcIntersection(b) = Rect { Top left: (4,4) Width: 2 Height: 2 }
// a.calcIntersection(a) = Rect { Top left: (4,4) Width: 10 Height: 10 }
// a.calcIntersection(c) = Rect { Top left: (0,0) Width: 0 Height: 0 }
// 
// --Vector2------------------------------------------------------
// a: (0,0)
// b: (1,2)
// Setting a to [5,5]: a: (5,5)
// Setting a to 5 units long at 45 degrees: a: (3.54,-3.54)
// Setting a to 5 units long at pi radians: a: (-5,-6.12e-16)
// Normalizing a: a: (-1,-1.22e-16)
// a == a
// a != b
// -a = (1,1.22e-16)
// a.b = -1
// a+b = (0,2)
// a-b = (-2,-2)
// 2*a = (-2,-2.45e-16)
// a/2 = (-0.5,-6.12e-17)
// a += b: (0,2)
// a -= b: (-1,-2.22e-16)
// |a| = 1
// |b| = 2.24
// angle of a (deg) = -180
// angle of b (deg) = 63.4
// angle of a (rad) = -3.14
// angle of b (rad) = 1.11
// normal of a: (-1,-2.22e-16)
// normal of b: (0.447,0.894)
// angle between a and b (deg): 117
// angle between a and b (rad): 2.03
// distance between a and b: 2.83
