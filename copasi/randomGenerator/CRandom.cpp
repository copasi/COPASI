#include "copasi.h"
#include "CRandom.h"
CRandom::CRandom(C_INT32 seed) {}
CRandom::~CRandom() {}
void CRandom::initialize(C_INT32 seed) {}
const unsigned C_INT32 & CRandom::getRandom() { return mNumber; }

const unsigned C_INT32 & CRandom::getRandom(const unsigned C_INT32 & modulus)
{ return mNumber; }
const unsigned C_INT32 & CRandom::getModulus() const { return mModulus; }
const C_FLOAT64 &CRandom:: getRandomF() { return mFloat; }
