/**
 * CRange
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CRange.h"
#include "utilities/utilities.h"

CRange::CRange()
{
  CONSTRUCTOR_TRACE;
  mLow = CRange::NoRange;
  mHigh = CRange::NoRange;
}

CRange::CRange(const CRange & src)
{
  CONSTRUCTOR_TRACE;
  mLow = src.mLow;
  mHigh = src.mHigh;
}

CRange::CRange(const unsigned C_INT32 & low,
               const unsigned C_INT32 & high)
{
  CONSTRUCTOR_TRACE;
  mLow = low;
  mHigh = high;
}
CRange::~CRange() {DESTRUCTOR_TRACE; }
void CRange::cleanup(){}

void CRange::load(CReadConfig & configBuffer,
                  CReadConfig::Mode mode)
{
  configBuffer.getVariable("Low", "C_INT32", &mLow, mode);
  configBuffer.getVariable("High", "C_INT32", &mHigh);
}

void CRange::save(CWriteConfig & configBuffer)
{
  configBuffer.setVariable("Low", "C_INT32", &mLow);
  configBuffer.setVariable("High", "C_INT32", &mHigh);
}
void CRange::setLow(const unsigned C_INT32& low) {mLow = low; }
void CRange::setHigh(const unsigned C_INT32& high) {mHigh = high; }

void CRange::setRange(const unsigned C_INT32 & low,
                      const unsigned C_INT32 & high)
{
  mLow = low;
  mHigh = high;
}
const unsigned C_INT32& CRange::getLow() const { return mLow; }
const unsigned C_INT32& CRange::getHigh() const { return mHigh; }

const bool CRange::isRange() const
  { return (mHigh != (unsigned C_INT32) CRange::NoRange); }

const bool CRange::isInRange(const unsigned C_INT32 & value) const
  { return (mLow == value || (mLow < value && value <= mHigh)); }

void CRange::checkRange() const
  {
    if (mLow == (unsigned C_INT32) CRange::Infinity ||
        (isRange() && mLow > mHigh))
      CCopasiMessage(CCopasiMessage::ERROR, MCRange + 1, mLow, mHigh);
  }
