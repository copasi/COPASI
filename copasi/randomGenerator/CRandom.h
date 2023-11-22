// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CRandom
#define COPASI_CRandom

#include <string>
#include "copasi/core/CCore.h"
class CRandom
{
  // Attributes
public:
  /**
   * The valid types of a function
   */
  struct PoissonVars
  {
    C_FLOAT64 a0;
    C_FLOAT64 a1;
    C_FLOAT64 a2;
    C_FLOAT64 a3;
    C_FLOAT64 a4;
    C_FLOAT64 a5;
    C_FLOAT64 a6;
    C_FLOAT64 a7;
    C_FLOAT64 muold;
    C_FLOAT64 muprev;
    C_FLOAT64 fact[10];

    C_INT32 ignpoi, j, k, kflag, l, ll, m;

    C_FLOAT64 b1, b2, c, c0, c1, c2, c3, d, del, difmuk, e, fk, fx, fy, g, omega, p, p0, px, py, q, s,
              t, u, v, x, xx, pp[35];
  };

  struct ExpVars
  {
    C_FLOAT64 q[8];
    C_INT32 i;
    C_FLOAT64 sexpo, a, u, ustar, umin;
    C_FLOAT64 *q1;
  };

  enum Type
  {
    r250 = 0,
    mt19937,
    mt19937HR,
    unkown
  };

  /**
   * String literals for the GUI to display type names of random number
   * generators known to COPASI.
   */
  static const std::string TypeName[];

  /**
   * XML type names of random number generators known to COPASI.
   */
  static const char * XMLType[];

protected:
  /**
   * A unsigned 32-bit integer random number.
   */
  unsigned C_INT32 mNumberU;

  /**
   * A signed 32-bit integer random number.
   */
  C_INT32 mNumberS;

  /**
   * A 64-bit floating point random number.
   */
  C_FLOAT64 mFloat;

  /**
   * The type of the generator
   */
  CRandom::Type mType;

  /**
   *
   */
  unsigned C_INT32 mModulus;

  /**
   *
   */
  C_FLOAT64 mModulusInv;

  /**
   *
   */
  C_FLOAT64 mModulusInv1;

private:

  PoissonVars varp;
  ExpVars vare;
  C_FLOAT64 fsign(C_FLOAT64 num, C_FLOAT64 sign);
  unsigned int& syscall(int arg1);

  // Operations
protected:
  /**
   * Default/Named constructor.
   * Seeds the random number generator with the given seed.
   */
  CRandom();

public:
  /**
   * get a system dependent seed (hopefully random)
   */
  static unsigned C_INT32 getSystemSeed();

  /**
   * Create a Generator.
   * Note: the returned object has to be released after use with delete
   * @param CRandom::Type type (default Mersenne Twister)
   * @param const C_INT32 & seed (default system generated seed)
   * @return CRandom * randomGenerator
   */
  static CRandom * createGenerator(CRandom::Type type = CRandom::mt19937,
                                   unsigned C_INT32 seed = 0);

  /**
   * The destructor.
   */
  virtual ~CRandom();

  /**
   * Create a copy of the generator
   */
  CRandom * copy();

  /**
   * Retrieve the type of the generator
   * @return const CRandom::Type & type
   */
  const CRandom::Type & getType() const;

  /**
   * Retrieve the method dependent modulus
   * @return const unsigned C_INT32 & modulus
   */
  const unsigned C_INT32 & getModulus() const;

  /**
   * Initialize or reinitialize the random number generator with
   * the given seed.
   * @param unsigned C_INT32 seed (default system seed)
   */
  virtual void initialize(unsigned C_INT32 seed = CRandom::getSystemSeed());

  /**
   * Get a random number in 0 <= n <= Modulus
   * @return unsigned C_INT32 random
   */
  virtual unsigned C_INT32 getRandomU();

  /**
   * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
   * @return C_INT32 random
   */
  virtual C_INT32 getRandomS();

  /**
   * Get a random number in 0 <= n <= max
   * Note: max must be smaller than Modulus (no check for performance)
   * @param const unsigned C_INT32 & max
   * @return unsigned C_INT32 random
   */
  virtual unsigned C_INT32 getRandomU(const unsigned C_INT32 & max);

  /**
   * Get a random number in 0 <= n <= max
   * Note: max must be smaller than Modulus (no check for performance)
   * @param const C_INT32 & max
   * @return C_INT32 random
   */
  virtual C_INT32 getRandomS(const C_INT32 & max);

  /**
   * Produces a uniformly distributed random number in 0 <= x <= 1.
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomCC();

  /**
   * Produces a uniformly distributed random number in 0 <= x < 1.
   * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomCO();

  /**
   * Produces a uniformly distributed random number in 0 < x < 1.
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomOO();

  /**
   * Produces a Normally distributed random number with mean=0 and SD=1
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomNormal01();

  /**
   * Produces a Normally distributed random number with Mean=mean and SD=sd
   * @param const C_FLOAT64 & mean
   * @param const C_FLOAT64 & sd
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomNormal(const C_FLOAT64 & mean,
                                    const C_FLOAT64 & sd);

  /**
   * Produces a Strictly Positive Normally distributed random number
   * with Mean=mean and SD=sd
   * @param const C_FLOAT64 & mean
   * @param const C_FLOAT64 & sd
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomNormalPositive(const C_FLOAT64 & mean,
      const C_FLOAT64 & sd);

  /**
   * Produces a Normally distributed random number with Mean=mean and SD=sd
   * in Logarithmic scale
   * @return C_FLOAT64 random
   */
  virtual C_FLOAT64 getRandomNormalLog(const C_FLOAT64 & mean,
                                       const C_FLOAT64 & sd);

  /**
   * Produces a Poisson distributed random number with Mean=mean
   * @param const C_FLOAT64 & mean
   * @return C_FLOAT64 random
   */

  virtual C_FLOAT64 getRandomPoisson(const C_FLOAT64 & mean);
  virtual C_FLOAT64 getRandomExp();
  /* Added on  Jan 31, 2005 */

  virtual C_FLOAT64 getRandomGamma(C_FLOAT64 shape, C_FLOAT64 scale);
  virtual C_FLOAT64 getRandomStdGamma(C_FLOAT64 shape);

protected:

  /**
      * Set the Modulus
      * @param
      */

  void setModulus(const unsigned C_INT32 & modulus);
};

#include "Cr250.h"
#include "Cmt19937.h"

#endif // COPASI_CRandom
