#include <sys/timeb.h>
#include <math.h>

#include "copasi.h"
#include "CRandom.h"
#include "utilities/CCopasiMessage.h"

const std::string CRandom::TypeName[] =
  {
    "r250",
    "Mersenne Twister"
  };

CRandom * CRandom::createGenerator(CRandom::Type type,
                                   unsigned C_INT32 seed)
{
  CRandom * RandomGenerator = NULL;

  if (!seed)
    seed = getSystemSeed();

  switch (type)
    {
    case r250:
      RandomGenerator = new Cr250(seed);
      RandomGenerator->mType = type;
      break;

    case mt19937:
      RandomGenerator = new Cmt19937(seed);
      RandomGenerator->mType = type;
      break;

    default:
      RandomGenerator = new Cmt19937(seed);
      RandomGenerator->mType = type;
      break;
    }

  return RandomGenerator;
}
CRandom::CRandom() {}
CRandom::~CRandom() {}
const CRandom::Type & CRandom::getType() const {return mType;}
const unsigned C_INT32 & CRandom::getModulus() const {return mModulus;}

void CRandom::setModulus(const unsigned C_INT32 & modulus)
{
  mModulus = modulus;
  mModulusInv = 1.0 / mModulus;
  mModulusInv1 = 1.0 / (mModulus + 1.0);
}

unsigned C_INT32 CRandom::getSystemSeed()
{
  struct timeb init_time;
  ftime(&init_time);

  return ((init_time.time & 0xffff) + 1) * 1000 + init_time.millitm;
}

void CRandom::initialize(unsigned C_INT32 C_UNUSED(seed))
{
  /* Every random number generator has to implement this. */
  fatalError();
  return;
}

/**
 * Get a random number in 0 <= n <= Modulus
 * @return const unsigned C_INT32 & random
 */
const unsigned C_INT32 & CRandom::getRandomU()
{
  /* Every random number generator has to implement this. */
  fatalError();
  return mNumberU;
}

/**
 * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
 * @return const C_INT32 & random
 */
const C_INT32 & CRandom::getRandomS()
{
  return mNumberS = getRandomU() & 0x7ffffff;
}

/**
 * Get a random number in 0 <= n <= max
 * Note: max must be smaller than Modulus (no check for performance)
 * @param const unsigned C_INT32 & max
 * @return const unsigned C_INT32 & random
 */
const unsigned C_INT32 & CRandom::getRandomU(const unsigned C_INT32 & max)
{
  unsigned C_INT32 Max = max + 1;
  unsigned C_INT32 Limit = (mModulus / Max) * Max;

  do
    getRandomU();
  while (mNumberU >= Limit);

  return mNumberU %= Max;
}

/**
 * Get a random number in 0 <= n <= max
 * Note: max must be smaller than Modulus (no check for performance)
 * @param const C_INT32 & max
 * @return const C_INT32 & random
 */
const C_INT32 & CRandom::getRandomS(const C_INT32 & max)
{
  unsigned C_INT32 Max = max + 1;
  unsigned C_INT32 Limit = (mModulus / Max) * Max - 1;

  do
    getRandomU();
  while (mNumberU >= Limit);

  return mNumberS = mNumberU % Max;
}

/**
 * Produces a uniformly distributed random number in 0 <= x <= 1.
 * @return const C_FLOAT64 & random
 */
const C_FLOAT64 & CRandom::getRandomCC()
{
  return mFloat = getRandomU() * mModulusInv;
}

/**
 * Produces a uniformly distributed random number in 0 <= x < 1.
 * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
 * @return const C_FLOAT64 & random
 */
const C_FLOAT64 & CRandom::getRandomCO()
{
  return mFloat = getRandomU() * mModulusInv1;
}

/**
 * Produces a uniformly distributed random number in 0 < x < 1.
 * @return const C_FLOAT64 & random
 */
const C_FLOAT64 & CRandom::getRandomOO()
{
  return mFloat = (getRandomU() + .5) * mModulusInv1;
}

/* a normal distribution with mean 0 and S.D. 1 */

const C_FLOAT64 & CRandom::getRandomNormal01()
{
  static char f = 1;
  static C_FLOAT64 y;
  C_FLOAT64 a, b, s;
  C_FLOAT64 mean = 0;
  C_FLOAT64 sd = 1;

  /* negate the flag */
  f = -f;
  /* return the stored number (if one is there) */
  if (f > 0) return y;
  for (;;)
    {
      a = 2.0 * getRandomCO() - 1.0;
      b = 2.0 * getRandomCO() - 1.0;
      s = a * a + b * b;
      if ((s < 1.0) && (s != 0)) break;
    }
  s = sqrt(-2.0 * log(s) / s);
  // save one of the numbers for the next time
  y = sd * s * a + mean;
  // and return the other
  return sd * s*b + mean;
}

/* a normal distribution with mean m and S.D. sd */

const C_FLOAT64 & CRandom::getRandomNormal(const C_FLOAT64 & mean, const C_FLOAT64 & sd)
{
  C_FLOAT64 psd;
  /* force the std.dev. to be positive */
  psd = fabs(sd);
  return getRandomNormal01() * psd + mean;
}

/* a strictly positive normal distribution with mean m and S.D. sd */

const C_FLOAT64 & CRandom::getRandomNormalPositive(const C_FLOAT64 & mean, const C_FLOAT64 & sd)
{
  C_FLOAT64 x, positive_mean, positive_sd;
  /* force the mean and std.dev. to be positive */
  positive_mean = fabs(mean);
  positive_sd = fabs(sd);
  for (;;)
    if ((x = getRandomNormal(positive_mean, positive_sd)) > 0.0) return x;
}

/* a tentative normal distribution in logarithmic space */

const C_FLOAT64 & CRandom::getRandomNormalLog(const C_FLOAT64 & mean, const C_FLOAT64 & sd)
{
  C_FLOAT64 positive_sd;
  /* force the std.dev. to be positive */
  positive_sd = fabs(sd);
  return mean * pow(10, getRandomNormal01() * positive_sd);
}
