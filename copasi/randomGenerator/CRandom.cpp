/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/randomGenerator/CRandom.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/02/02 15:12:14 $
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
    "Mersenne Twister",
    ""
  };

const char * CRandom::XMLType[] =
  {
    "r250",
    "MersenneTwister",
    NULL
  };

CRandom::Type CRandom::TypeNameToEnum(const std::string & typeName)
{
  unsigned C_INT32 i = 0;
  while (TypeName[i] != typeName && TypeName[i] != "") i++;

  if (CRandom::TypeName[i] != "") return (CRandom::Type) i;
  else return CRandom::mt19937;
}

CRandom::Type CRandom::XMLNameToEnum(const char * xmlTypeName)
{
  unsigned C_INT32 i = 0;
  while (strcmp(xmlTypeName, XMLType[i]) && XMLType[i]) i++;

  if (XMLType[i]) return (CRandom::Type) i;
  else return CRandom::mt19937;
}

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
CRandom::CRandom()
{
  varp.a0 = -0.5;
  varp.a1 = 0.3333333;
  varp.a2 = -0.2500068;
  varp.a3 = 0.2000118;
  varp.a4 = -0.1661269;
  varp.a5 = 0.1421878;
  varp.a6 = -0.1384794;
  varp.a7 = 0.125006;
  varp.muold = -1.0E37;
  varp.muprev = -1.0E37;
  varp.fact[0] = 1.0;
  varp.fact[1] = 1.0;
  varp.fact[2] = 2.0;
  varp.fact[3] = 6.0;
  varp.fact[4] = 24.0;
  varp.fact[5] = 120.0;
  varp.fact[6] = 720.0;
  varp.fact[7] = 5040.0;
  varp.fact[8] = 40320.0;
  varp.fact[9] = 362880.0;

  vare.q[0] = 0.6931472;
  vare.q[1] = 0.9333737;
  vare.q[2] = 0.9888778;
  vare.q[3] = 0.9984959;
  vare.q[4] = 0.9998293;
  vare.q[5] = 0.9999833;
  vare.q[6] = 0.9999986;
  vare.q[7] = 0.9999999;

  vare.q1 = vare.q;
}

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

C_FLOAT64 CRandom::getRandomPoisson(const C_FLOAT64 & mu)
{
  if (mu == varp.muprev) goto S10;
  if (mu < 10.0) goto S120;
  varp.muprev = mu;
  varp.s = sqrt(mu);
  varp.d = 6.0 * mu * mu;
  varp.ll = (long) (mu - 1.1484);
S10:
  varp.g = mu + varp.s * getRandomNormal01();
  if (varp.g < 0.0) goto S20;
  varp.ignpoi = (long) (varp.g);
  if (varp.ignpoi >= varp.ll) return varp.ignpoi;
  varp.fk = (float)varp.ignpoi;
  varp.difmuk = mu - varp.fk;
  varp.u = getRandomCC();
  if (varp.d*varp.u >= varp.difmuk*varp.difmuk*varp.difmuk) return varp.ignpoi;
S20:
  if (mu == varp.muold) goto S30;
  varp.muold = mu;
  varp.omega = 0.3989423 / varp.s;
  varp.b1 = 4.166667E-2 / mu;
  varp.b2 = 0.3 * varp.b1 * varp.b1;
  varp.c3 = 0.1428571 * varp.b1 * varp.b2;
  varp.c2 = varp.b2 - 15.0 * varp.c3;
  varp.c1 = varp.b1 - 6.0 * varp.b2 + 45.0 * varp.c3;
  varp.c0 = 1.0 - varp.b1 + 3.0 * varp.b2 - 15.0 * varp.c3;
  varp.c = 0.1069 / mu;
S30:
  if (varp.g < 0.0) goto S50;
  varp.kflag = 0;
  goto S70;
S40:
  if (varp.fy - varp.u*varp.fy <= varp.py*exp(varp.px - varp.fx)) return varp.ignpoi;
S50:
  varp.e = getRandomExp();
  varp.u = getRandomCC();
  varp.u += (varp.u - 1.0);
  varp. t = 1.8 + fsign(varp.e, varp.u);
  if (varp.t <= -0.6744) goto S50;
  varp.ignpoi = (long) (mu + varp.s * varp.t);
  varp.fk = (float)varp.ignpoi;
  varp.difmuk = mu - varp.fk;
  varp.kflag = 1;
  goto S70;
S60:
  if (varp.c*fabs(varp.u) > varp.py*exp(varp.px + varp.e) - varp.fy*exp(varp.fx + varp.e)) goto S50;
  return varp.ignpoi;
S70:
  if (varp.ignpoi >= 10) goto S80;
  varp.px = -mu;
  varp.py = pow(mu, (double)varp.ignpoi) / *(varp.fact + varp.ignpoi);
  goto S110;
S80:
  varp.del = 8.333333E-2 / varp.fk;
  varp.del -= (4.8 * varp.del * varp.del * varp.del);
  varp.v = varp.difmuk / varp.fk;
  if (fabs(varp.v) <= 0.25) goto S90;
  varp.px = varp.fk * log(1.0 + varp.v) - varp.difmuk - varp.del;
  goto S100;
S90:
  varp.px = varp.fk * varp.v * varp.v * (((((((varp.a7 * varp.v + varp.a6) * varp.v + varp.a5) * varp.v\
                                          + varp.a4) * varp.v + varp.a3) * varp.v + varp.a2) * varp.v + varp.a1) * varp.v + varp.a0) - varp.del;
S100:
  varp.py = 0.3989423 / sqrt(varp.fk);
S110:
  varp.x = (0.5 - varp.difmuk) / varp.s;
  varp.xx = varp.x * varp.x;
  varp.fx = -0.5 * varp.xx;
  varp.fy = varp.omega * (((varp.c3 * varp.xx + varp.c2) * varp.xx + varp.c1) * varp.xx + varp.c0);
  if (varp.kflag <= 0) goto S40;
  goto S60;
S120:
  varp.muprev = -1.0E37;
  if (mu == varp.muold) goto S130;

  if (mu >= 0.0) goto S125;
  fprintf(stderr, "MU < 0 in IGNPOI: MU %16.6E\n", mu);
  fputs("Abort\n", stderr);
  exit(1);
S125:
  varp.muold = mu;
  varp.m = std::max(1L, (long) (mu));
  varp.l = 0;
  varp.p = exp(-mu);
  varp.q = varp.p0 = varp.p;
S130:
  varp.u = getRandomCC();
  varp.ignpoi = 0;
  if (varp.u <= varp.p0) return varp.ignpoi;
  if (varp.l == 0) goto S150;
  varp.j = 1;
  if (varp.u > 0.458) varp.j = std::min(varp.l, varp.m);
  for (varp.k = varp.j; varp.k <= varp.l; varp.k++)
    {
      if (varp.u <= *(varp.pp + varp.k - 1)) goto S180;
    }
  if (varp.l == 35) goto S130;
S150:
  varp.l += 1;
  for (varp.k = varp.l; varp.k <= 35; varp.k++)
    {
      varp.p = varp.p * mu / (float)varp.k;
      varp.q += varp.p;
      *(varp.pp + varp.k - 1) = varp.q;
      if (varp.u <= varp.q) goto S170;
    }
  varp.l = 35;
  goto S130;
S170:
  varp.l = varp.k;
S180:
  varp.ignpoi = varp.k;
  return varp.ignpoi;
}

C_FLOAT64 CRandom::fsign(C_FLOAT64 num, C_FLOAT64 sign)
{
  if ((sign > 0.0f && num < 0.0f) || (sign < 0.0f && num > 0.0f))
    return - num;
  else return num;
}

C_FLOAT64 CRandom::getRandomExp()
{
  vare.a = 0.0;
  vare.u = getRandomCC();
  goto S30;
S20:
  vare.a += *vare.q1;
S30:
  vare.u += vare.u;
  if (vare.u < 1.0) goto S20;
  vare.u -= 1.0;
  if (vare.u > *vare.q1) goto S60;
  vare.sexpo = vare.a + vare.u;
  return vare.sexpo;
S60:
  vare.i = 1;
  vare.ustar = getRandomCC();
  vare.umin = vare.ustar;
S70:
  vare.ustar = getRandomCC();
  if (vare.ustar < vare.umin) vare.umin = vare.ustar;
  vare.i += 1;
  if (vare.u > *(vare.q + vare.i - 1)) goto S70;
  vare.sexpo = vare.a + vare.umin**vare.q1;
  return vare.sexpo;
}
