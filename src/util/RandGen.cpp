//This file is part of Photon (http://photon.sourceforge.net)
//Copyright (C) 2004-2005 James Turk
//
// Author:
//  James Turk (jpt2433@rit.edu)
//
// Version:
//  $Id: RandGen.cpp,v 1.5 2005/03/03 09:25:47 cozman Exp $

//  The source in this file is based on MT19937, with much of the source
// replicated from mt19937ar.c, because of this the original license
// for that file is below.
//      -James
//
//
//A C-program for MT19937, with initialization improved 2002/1/26.
//Coded by Takuji Nishimura and Makoto Matsumoto.
//
//Before using, initialize the state by using init_genrand(seed)
//or init_by_array(init_key, key_length).
//
//Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    1. Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//    2. Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//
//    3. The names of its contributors may not be used to endorse or promote
//        products derived from this software without specific prior written
//        permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//
//Any feedback is very welcome.
//http://www.math.keio.ac.jp/matumoto/emt.html
//email: matumoto@math.keio.ac.jp

#include "util/RandGen.hpp"
#include <ctime>

namespace photon 
{ 
namespace util 
{ 

//static consts
const unsigned long RandGen::N;
const unsigned long RandGen::M;
const unsigned long RandGen::MATRIX_A;
const unsigned long RandGen::UPPER_MASK;
const unsigned long RandGen::LOWER_MASK;

RandGen::RandGen()
{
    seed(static_cast<unsigned long>(std::time(0)));
}

RandGen::RandGen(unsigned long seedVal)
{
    seed(seedVal);
}

//adapted directly from mt19937ar : void init_genrand(unsigned long s)
void RandGen::seed(unsigned long seedVal)
{
    stateVector_[0]= seedVal & 0xffffffffUL;
    for(stateVectorIndex_=1; stateVectorIndex_<N; ++stateVectorIndex_)
    {
        stateVector_[stateVectorIndex_] =
            (1812433253UL * (stateVector_[stateVectorIndex_-1] ^
             (stateVector_[stateVectorIndex_-1] >> 30)) + stateVectorIndex_);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array stateVector_[].              */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        stateVector_[stateVectorIndex_] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

unsigned long RandGen::genRand(unsigned long max)
{
    return genrand_int32()%max;
}

int RandGen::genRand(int min, int max)
{
    return min + genrand_int32()%(max-min+1);
}

//mostly adapted from mt19937ar : double genrand_real1(void)
double RandGen::genRand(double min, double max)
{
    return min + ((genrand_int32()*(1.0/4294967295.0))*(max-min));
}

double RandGen::genRandSign()
{
    return genrand_int32()%2 == 0 ? -1.0 : 1.0;
}

//adapted directly from mt19937ar : double genrand_real2(void)
double RandGen::genRand01()
{
    return genrand_int32()*(1.0/4294967296.0);
}

//adapted directly from mt19937ar : unsigned long genrand_int32(void)
unsigned long RandGen::genrand_int32()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (stateVectorIndex_ >= N) { /* generate N words at one time */
        unsigned int kk;

        //Removed uninitialized check, class initializes in constructor. -James

        for (kk=0;kk<N-M;++kk) {
            y = (stateVector_[kk]&UPPER_MASK)|(stateVector_[kk+1]&LOWER_MASK);
            stateVector_[kk] = stateVector_[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;++kk) {
            y = (stateVector_[kk]&UPPER_MASK)|(stateVector_[kk+1]&LOWER_MASK);
            stateVector_[kk] = stateVector_[kk+(M-N)] ^ (y >> 1) ^
                                mag01[y & 0x1UL];
        }
        y = (stateVector_[N-1]&UPPER_MASK)|(stateVector_[0]&LOWER_MASK);
        stateVector_[N-1] = stateVector_[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        stateVectorIndex_ = 0;
    }

    y = stateVector_[stateVectorIndex_++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}


}
}
