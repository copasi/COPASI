/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/randomGenerator/CRandom.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:30:25 $
   End CVS Header */

#include <time.h>
#include <sys/timeb.h>
#include <math.h>
#include <algorithm>

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

#ifdef Darwin
#include <mach/mach_init.h> 
/*
 * References to host objects are returned by:
 *      mach_host_self() - trap
 *
 * extern mach_port_t mach_host_self(void);
 */

#include <mach/mach_host.h> 
/*
 *      Get service port for a processor set.
 *      Available to all.
 *
 * extern kern_return_t host_get_clock_service(host_t host,
 *                                             clock_id_t clock_id,
 *                                             clock_serv_t *clock_serv);
 */

#include <mach/clock.h> 
/**
 *      Get the clock time.
 *      Available to all.
 *
 * extern kern_return_t clock_get_time(clock_serv_t clock_serv,
 *                                     mach_timespec_t *cur_time);
 */

void ftime(timeb * pTime);

void ftime(timeb * pTime)
{
  mach_port_t host = mach_host_self();
  clock_serv_t clock_serv;
  host_get_clock_service(host, 1, & clock_serv);

  mach_timespec_t time;
  clock_get_time(clock_serv, &time);

  pTime->time = time.tv_sec;
  pTime->millitm = time.tv_nsec / 1000;

  return;
}
#endif // __MacOsX__

unsigned C_INT32 CRandom::getSystemSeed()
{
  /* :TODO: MacOS X does not provide ftime we need to supply it */
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
 * @return unsigned C_INT32 random
 */
unsigned C_INT32 CRandom::getRandomU()
{
  /* Every random number generator has to implement this. */
  fatalError();
  return mNumberU;
}

/**
 * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
 * @return C_INT32 random
 */
C_INT32 CRandom::getRandomS()
{
  return getRandomU(std::min(mModulus, (unsigned C_INT32) 0x7ffffff));
  //  The method below only works for mModulus = 0xffffffff.
  //  return getRandomU() & 0x7ffffff;
}

/**
 * Get a random number in 0 <= n <= max
 * Note: max must be smaller than Modulus (no check for performance)
 * @param const unsigned C_INT32 & max
 * @return unsigned C_INT32 random
 */
unsigned C_INT32 CRandom::getRandomU(const unsigned C_INT32 & max)
{
  unsigned C_INT32 Max = max + 1;
  unsigned C_INT32 Limit = (mModulus / Max) * Max - 1;
  unsigned C_INT32 NumberU;

  do
    NumberU = getRandomU();
  while (NumberU >= Limit);

  return NumberU % Max;
}

/**
 * Get a random number in 0 <= n <= max
 * Note: max must be smaller than Modulus (no check for performance)
 * @param const C_INT32 & max
 * @return C_INT32 random
 */
C_INT32 CRandom::getRandomS(const C_INT32 & max)
{
  unsigned C_INT32 Max = max + 1;
  unsigned C_INT32 Limit = (mModulus / Max) * Max - 1;
  unsigned C_INT32 NumberU;

  do
    NumberU = getRandomU();
  while (NumberU >= Limit);

  return mNumberU % Max;
}

/**
 * Produces a uniformly distributed random number in 0 <= x <= 1.
 * @return C_FLOAT64 random
 */
C_FLOAT64 CRandom::getRandomCC()
{
  return getRandomU() * mModulusInv;
}

/**
 * Produces a uniformly distributed random number in 0 <= x < 1.
 * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
 * @return C_FLOAT64 random
 */
C_FLOAT64 CRandom::getRandomCO()
{
  return getRandomU() * mModulusInv1;
}

/**
 * Produces a uniformly distributed random number in 0 < x < 1.
 * @return C_FLOAT64 random
 */
C_FLOAT64 CRandom::getRandomOO()
{
  return (getRandomU() + .5) * mModulusInv1;
}

/* a normal distribution with mean 0 and S.D. 1 */

C_FLOAT64 CRandom::getRandomNormal01()
{
  static bool HaveValue = true;
  static C_FLOAT64 SavedValue;
  C_FLOAT64 a, b, s;

  /* negate the flag */
  HaveValue = !HaveValue;

  /* return the stored number (if one is there) */
  if (HaveValue) return SavedValue;

  do
    {
      a = 2.0 * getRandomOO() - 1.0;
      b = 2.0 * getRandomOO() - 1.0;
      s = a * a + b * b;
    }
  while (s >= 1.0 || s == 0);

  s = sqrt(-2.0 * log(s) / s);

  // save one of the numbers for the next time
  SavedValue = s * a;

  // and return the other
  return s * b;
}

/* a normal distribution with mean m and S.D. sd */

C_FLOAT64 CRandom::getRandomNormal(const C_FLOAT64 & mean,
                                   const C_FLOAT64 & sd)
{return getRandomNormal01() * sd + mean;}

/* a strictly positive normal distribution with mean m and S.D. sd */

C_FLOAT64 CRandom::getRandomNormalPositive(const C_FLOAT64 & mean,
    const C_FLOAT64 & sd)
{
  C_FLOAT64 x;

  while ((x = getRandomNormal(mean, sd)) < 0);

  return x;
}

/* a tentative normal distribution in logarithmic space */

C_FLOAT64 CRandom::getRandomNormalLog(const C_FLOAT64 & mean,
                                      const C_FLOAT64 & sd)
{return mean * pow(10, getRandomNormal01() * sd);}
