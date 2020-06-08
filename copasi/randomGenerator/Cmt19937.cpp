// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Cmt19937 class implementing the Mersenne Twister random number generator,
 *
 * Created for Copasi by Stefan Hoops
 *
 * A C-program for MT19937, with initialization improved 2002/2/10.
 * Coded by Takuji Nishimura and Makoto Matsumoto.
 * This is a faster version by taking Shawn Cokus's optimization,
 * Matthe Bellew's simplification, Isaku Wada's real version.
 *
 * Before using, initialize the state by using init_genrand(seed)
 * or init_by_array(init_key, key_length).
 *
 * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. The names of its contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Any feedback is very welcome.
 * http://www.math.keio.ac.jp/matumoto/emt.html
 * email: matumoto@math.keio.ac.jp
 */

#include "copasi/copasi.h"
#include "CRandom.h"

/* Period parameters */
#define Cmt19937_M 397
#define Cmt19937_MATRIX_A 0x9908b0dfUL /* constant vector a */
#define Cmt19937_UMASK    0x80000000UL /* most significant w-r bits */
#define Cmt19937_LMASK    0x7fffffffUL /* least significant r bits */
#define Cmt19937_MIXBITS(u,v) \
  (((u) & Cmt19937_UMASK) | ((v) & Cmt19937_LMASK))
#define Cmt19937_TWIST(u,v) \
  ((Cmt19937_MIXBITS(u,v) >> 1) ^ ((v)&1UL ? Cmt19937_MATRIX_A : 0UL))

Cmt19937::Cmt19937(unsigned C_INT32 seed):
  CRandom(),
  mLeft(1),
  mNext(NULL)
{
  setModulus(0xffffffffUL);
  initialize(seed);
}

Cmt19937::~Cmt19937() {}

/* initializes mState[Cmt19937_N] with a seed */
void Cmt19937::initialize(unsigned C_INT32 seed)
{
  int j;
  mState[0] = seed & 0xffffffffUL;

  for (j = 1; j < Cmt19937_N; j++)
    {
      mState[j] = (1812433253UL * (mState[j - 1] ^ (mState[j - 1] >> 30)) + j);
      /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
      /* In the previous versions, MSBs of the seed affect   */
      /* only MSBs of the array mState[].                        */
      /* 2002/01/09 modified by Makoto Matsumoto             */
      mState[j] &= 0xffffffffUL;  /* for >32 bit machines */
    }

  mLeft = 1;
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void Cmt19937::init_by_array(unsigned C_INT32 init_key[],
                             C_INT32 key_length)
{
  int i, j, k;
  initialize(19650218UL);
  i = 1;
  j = 0;
  k = (Cmt19937_N > key_length ? Cmt19937_N : key_length);

  for (; k; k--)
    {
      mState[i] = (mState[i] ^ ((mState[i - 1] ^ (mState[i - 1] >> 30)) * 1664525UL))
                  + init_key[j] + j; /* non linear */
      mState[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
      i++;
      j++;

      if (i >= Cmt19937_N)
        {mState[0] = mState[Cmt19937_N - 1]; i = 1;}

      if (j >= key_length)
        j = 0;
    }

  for (k = Cmt19937_N - 1; k; k--)
    {
      mState[i] = (mState[i] ^ ((mState[i - 1] ^ (mState[i - 1] >> 30)) * 1566083941UL))
                  - i; /* non linear */
      mState[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
      i++;

      if (i >= Cmt19937_N)
        {mState[0] = mState[Cmt19937_N - 1]; i = 1;}
    }

  mState[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
  mLeft = 1;
}

void Cmt19937::next_state()
{
  unsigned C_INT32 *p = mState;
  int j;

  mLeft = Cmt19937_N;
  mNext = mState;

  for (j = Cmt19937_N - Cmt19937_M + 1; --j; p++)
    *p = p[Cmt19937_M] ^ Cmt19937_TWIST(p[0], p[1]);

  for (j = Cmt19937_M; --j; p++)
    *p = p[Cmt19937_M - Cmt19937_N] ^ Cmt19937_TWIST(p[0], p[1]);

  *p = p[Cmt19937_M - Cmt19937_N] ^ Cmt19937_TWIST(p[0], mState[0]);
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned C_INT32 Cmt19937::getRandomU()
{
  if (--mLeft == 0)
    next_state();

  mNumberU = *mNext++;

  /* Tempering */
  mNumberU ^= (mNumberU >> 11);
  mNumberU ^= (mNumberU << 7) & 0x9d2c5680UL;
  mNumberU ^= (mNumberU << 15) & 0xefc60000UL;
  mNumberU ^= (mNumberU >> 18);

  return mNumberU;
}

/* generates a random number on [0,0x7fffffff]-interval */
C_INT32 Cmt19937::getRandomS()
{
  if (--mLeft == 0)
    next_state();

  mNumberU = *mNext++;

  /* Tempering */
  mNumberU ^= (mNumberU >> 11);
  mNumberU ^= (mNumberU << 7) & 0x9d2c5680UL;
  mNumberU ^= (mNumberU << 15) & 0xefc60000UL;
  mNumberU ^= (mNumberU >> 18);

  return mNumberU >> 1;
}

/* generates a random number on [0,1]-real-interval */
C_FLOAT64 Cmt19937::getRandomCC()
{
  if (--mLeft == 0)
    next_state();

  mNumberU = *mNext++;

  /* Tempering */
  mNumberU ^= (mNumberU >> 11);
  mNumberU ^= (mNumberU << 7) & 0x9d2c5680UL;
  mNumberU ^= (mNumberU << 15) & 0xefc60000UL;
  mNumberU ^= (mNumberU >> 18);

  return ((C_FLOAT64) mNumberU) * (1.0 / 4294967295.0);
  /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
C_FLOAT64 Cmt19937::getRandomCO()
{
  if (--mLeft == 0)
    next_state();

  mNumberU = *mNext++;

  /* Tempering */
  mNumberU ^= (mNumberU >> 11);
  mNumberU ^= (mNumberU << 7) & 0x9d2c5680UL;
  mNumberU ^= (mNumberU << 15) & 0xefc60000UL;
  mNumberU ^= (mNumberU >> 18);

  return ((C_FLOAT64) mNumberU) * (1.0 / 4294967296.0);
  /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
C_FLOAT64 Cmt19937::getRandomOO()
{
  if (--mLeft == 0)
    next_state();

  mNumberU = *mNext++;

  /* Tempering */
  mNumberU ^= (mNumberU >> 11);
  mNumberU ^= (mNumberU << 7) & 0x9d2c5680UL;
  mNumberU ^= (mNumberU << 15) & 0xefc60000UL;
  mNumberU ^= (mNumberU >> 18);

  return (((C_FLOAT64) mNumberU) + 0.5) * (1.0 / 4294967296.0);
  /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
C_FLOAT64 Cmt19937::genrand_res53()
{
  unsigned C_INT32 a = getRandomU() >> 5, b = getRandomU() >> 6;
  return mFloat = (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}
/* These real versions are due to Isaku Wada, 2002/01/09 added */

Cmt19937HR::Cmt19937HR(unsigned C_INT32 seed):
  Cmt19937(seed)
{}

/* generates a random number on [0,1]-real-interval */
C_FLOAT64 Cmt19937HR::getRandomCC()
{
  unsigned C_INT32 a = getRandomU() >> 5, b = getRandomU() >> 6;
  return mFloat = (a * 67108864.0 + b) * (1.0 / 9007199254740991.0);
}

/* generates a random number on [0,1)-real-interval */
C_FLOAT64 Cmt19937HR::getRandomCO()
{
  unsigned C_INT32 a = getRandomU() >> 5, b = getRandomU() >> 6;
  return mFloat = (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}

/* generates a random number on (0,1)-real-interval */
C_FLOAT64 Cmt19937HR::getRandomOO()
{
  unsigned C_INT32 a = getRandomU() >> 5, b = getRandomU() >> 6;
  return mFloat = (a * 67108864.0 + b + 0.5) * (1.0 / 9007199254740992.0);
}

/* These real versions are due to Isaku Wada, 2002/01/09 added */

#ifdef XXXX
int main()
{
  int i;
  unsigned C_INT32 init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
  init_by_array(init, length);
  /* This is an example of initializing by an array.       */
  /* You may use init_genrand(seed) with any 32bit integer */
  /* as a seed for a simpler initialization                */
  printf("1000 outputs of getRandomU()\n");

  for (i = 0; i < 1000; i++)
    {
      printf("%10lu ", getRandomU());

      if (i % 5 == 4)
        printf("\n");
    }

  printf("\n1000 outputs of genrand_real2()\n");

  for (i = 0; i < 1000; i++)
    {
      printf("%10.8f ", getRandomCO());

      if (i % 5 == 4)
        printf("\n");
    }

  return 0;
}
#endif // XXXX
