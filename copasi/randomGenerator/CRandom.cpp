#include <sys/timeb.h> 
// #include <time.h>

#include "copasi.h"
#include "CRandom.h"

const string CRandom::TypeName[] =
  {
    "R250"
  };

CRandom * CRandom::createGenerator(CRandom::Type type,
                                   unsigned C_INT32 seed)
{
  CRandom * RandomGenerator = NULL;

  if (!seed)
    seed = getSystemSeed();

  switch (type)
    {
    case R250:
      RandomGenerator = new Cr250(seed);
      RandomGenerator->mType = type;
      break;

    default:
      break;
    }

  return RandomGenerator;
}
CRandom::CRandom(C_INT32 seed) {}
CRandom::~CRandom() {}
void CRandom::initialize(C_INT32 seed) {}
const unsigned C_INT32 & CRandom::getRandom() { return mNumber; }

const unsigned C_INT32 & CRandom::getRandom(const unsigned C_INT32 & modulus)
{ return mNumber; }
const unsigned C_INT32 & CRandom::getModulus() const { return mModulus; }
const C_FLOAT64 & CRandom::getRandomF() { return mFloat; }

unsigned C_INT32 CRandom::getSystemSeed()
{
  struct timeb init_time;
  ftime(&init_time);

  return ((init_time.time & 0xffff) + 1) * 1000 + init_time.millitm;
}
