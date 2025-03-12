// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <math.h>

#include "copasi/randomGenerator/CIntervalValue.h"
#include "copasi/randomGenerator/CRandom.h"

CIntervalValue::CIntervalValue(const C_FLOAT64 *& pMinimum, const C_FLOAT64 *& pMaximum)
  : mpMinimum(pMinimum)
  , mpMaximum(pMaximum)
  , mSize(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mRange(CIntervalValue::Range::invalid)
  , mIsLogarithmic(false)
  , mLogarithmicScale(0)
{
  compile();
}

void CIntervalValue::compile()
{
  if (mpMaximum == nullptr
      || mpMinimum == nullptr)
    {
      mRange = CIntervalValue::Range::invalid;
      mLogarithmicScale = 0;
      mIsLogarithmic = false;

      return;
    }

  try
    {
      mSize = *mpMaximum - *mpMinimum;

      // First determine the location of the interval
      // Secondly determine whether to distribute the parameter linearly or not
      // depending on the location and act upon it.
      if (mSize < 0)
        {
          mRange = CIntervalValue::Range::invalid;
          mLogarithmicScale = 0;
          mIsLogarithmic = false;
        }
      else if (0.0 <= *mpMinimum) // the interval [*mpMinimum, *mpMaximum) is in [0, inf)
        {
          mRange = CIntervalValue::Range::positive;
          mLogarithmicScale = log10(*mpMaximum) - log10(std::max(*mpMinimum, std::numeric_limits< C_FLOAT64 >::min()));
          mIsLogarithmic = mLogarithmicScale > 1.8 && *mpMinimum > 0.0;
        }
      else if (*mpMaximum > 0) // 0 is in the interval (*mpMinimum, *mpMaximum)
        {
          mRange = CIntervalValue::Range::containsZero;
          mLogarithmicScale = log10(*mpMaximum) - log10(-*mpMinimum);
          mIsLogarithmic = fabs(mLogarithmicScale) > 1.8;
        }
      else // the interval (*mpMinimum, *mpMaximum] is in (-inf, 0]
        {
          mRange = CIntervalValue::Range::negative;
          mLogarithmicScale = log10(-*mpMinimum) - log10(std::max(-*mpMaximum, std::numeric_limits< C_FLOAT64 >::min()));
          mIsLogarithmic = mLogarithmicScale > 1.8 && *mpMaximum < 0.0;
        }
    }

  catch (...)
    {
      mRange = CIntervalValue::Range::invalid;
      mLogarithmicScale = 0;
      mIsLogarithmic = false;
    }
}

C_FLOAT64 CIntervalValue::randomValue(CRandom * pRandom) const
{
  C_FLOAT64 result = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  try
    {
      if (mIsLogarithmic)
        switch (mRange)
          {
          case CIntervalValue::Range::positive:
            result = pow(10.0, log10(std::max(*mpMinimum, std::numeric_limits< C_FLOAT64 >::min())) + mLogarithmicScale * pRandom->getRandomCC());
            break;

          case CIntervalValue::Range::containsZero:
            if (mLogarithmicScale > 0)
              {
                C_FLOAT64 R = 2.0 / (2.0 + mLogarithmicScale);
                C_FLOAT64 Sample = pRandom->getRandomCC();

                if (Sample < R)
                  result = *mpMinimum * (1.0 - 2.0 * Sample/R);
                else
                  result = pow(10.0, log10(std::max(-*mpMinimum, std::numeric_limits< C_FLOAT64 >::min())) + mLogarithmicScale * (Sample - R)/(Sample-R));
              }
            else
              {
                C_FLOAT64 R = 2.0 / (2.0 - mLogarithmicScale);
                C_FLOAT64 Sample = pRandom->getRandomCC();

                if (Sample < R)
                  result = *mpMaximum * (1.0 - 2.0 * Sample/R);
                else
                  result = -pow(10.0, log10(std::max(*mpMaximum, std::numeric_limits< C_FLOAT64 >::min())) - mLogarithmicScale * (Sample - R)/(Sample-R));
              }
            break;

          case CIntervalValue::Range::negative:
            result = -pow(10.0, log10(std::max(-*mpMaximum, std::numeric_limits< C_FLOAT64 >::min())) + mLogarithmicScale * pRandom->getRandomCC());
            break;

          case CIntervalValue::Range::invalid:
            result = (*mpMaximum + *mpMinimum) * 0.5;
            break;
          }
      else
        result = *mpMinimum + pRandom->getRandomCC() * (*mpMaximum - *mpMinimum);
    }

  catch (...)
    {
      result = (*mpMaximum + *mpMinimum) * 0.5;
    }

  return result;
}

const CIntervalValue::Range & CIntervalValue::getRange() const
{
  return mRange;
}

const bool & CIntervalValue::isLogarithmic() const
{
  return mIsLogarithmic;
}

const C_FLOAT64 & CIntervalValue::getMinimum() const
{
  return *mpMinimum;
}

const C_FLOAT64 & CIntervalValue::getMaximum() const
{
  return *mpMaximum;
}

const C_FLOAT64 & CIntervalValue::getSize() const
{
  return mSize;
}

const C_FLOAT64 & CIntervalValue::getLogarithmicScale() const
{
  return mLogarithmicScale;
}
