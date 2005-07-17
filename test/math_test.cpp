//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: math_test.cpp,v 1.3 2005/07/17 02:40:39 cozman Exp $

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

// example checks should always contain a positive check followed by a negative
// ex:
//  a contains origin
//  b doesn't contain origin

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
