//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: RandGen.hpp,v 1.5 2005/07/18 06:18:51 cozman Exp $

#ifndef PHOTON_UTIL_RANDGEN_HPP
#define PHOTON_UTIL_RANDGEN_HPP

namespace photon 
{ 
namespace util 
{ 

// Class: RandGen
//  Psuedorandom number generator class which uses Mersenne Twister.
//  MT19937 is described at <http://www.math.keio.ac.jp/matumoto/emt.html>.
class RandGen
{
// Group: (Con/De)structors
public:
    // Function: RandGen
    //  Constructor for random generator, using time as seed.
    RandGen();

    // Function: RandGen
    //  Constructor for random generator, allowing specific seed.
    //
    // Parameters:
    //  seedVal - Seed for random generator, a given seed will always turn out
    //              the same string of random numbers.
    //
    // See Also:
    //  <seed>
    RandGen(unsigned long seedVal);

// Group: General
public:

    // Function: seed
    //  Reseed random generator, a given seed will always turn out same string
    //      of random numbers.
    //
    // Parameters:
    //  seed - Seed for random generator.
    void seed(unsigned long seedVal);

    // Function: genRand
    //  Obtain random number in range [0,max).
    //
    // Parameters:
    //  max - Boundary for random number.
    //
    // Returns:
    //  Random number from 0 to max-1.
    unsigned long genRand(unsigned long max);

    // Function: genRand
    //  Obtain random integer in range [min,max].
    //
    // Parameters:
    //  min - Minimum boundary for random number.
    //  max - Maximum boundary for random number.
    //
    // Returns:
    //  Random number from min to max.
    int genRand(int min, int max);

    // Function: genRand
    //  Obtain random double in range [min,max].
    //
    // Parameters:
    //  min - Minimum boundary for random number.
    //  max - Maximum boundary for random number.
    //
    // Returns:
    //  Random number from min to max.
    double genRand(double min, double max);

    // Function: genRandSign
    //  Obtain random sign, positive or negative.
    //
    // Returns:
    //  Either -1.0 or +1.0
    double genRandSign();

    // Function: genRand01
    //  Obtain random double in range [0,1).
    //
    // Returns:
    //  Random number from 0 to under 1.
    double genRand01();

private:    // utilities
    unsigned long genrand_int32();  //base of all generation

private:    // constants
    static const unsigned long N          = 624;
    static const unsigned long M          = 397;
    static const unsigned long MATRIX_A   = 0x9908b0dfUL;
    static const unsigned long UPPER_MASK = 0x80000000UL;
    static const unsigned long LOWER_MASK = 0x7fffffffUL;

private:    //state data
    unsigned long stateVector_[N];
    unsigned long stateVectorIndex_;
};

}
}

#endif  //PHOTON_UTIL_RANDGEN_HPP
