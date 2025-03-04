// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <math.h>

#include "copasi/randomGenerator/CIntervalValue.h"
#include "copasi/randomGenerator/CRandom.h"

CIntervalValue::CIntervalValue(const C_FLOAT64 & minimum, const C_FLOAT64 & maximum)
  : mMinimum(minimum)
  , mMaximum(maximum)
  , mRange(CIntervalValue::Range::invalid)
  , mIsLogarithmic(false)
  , mLogarithmicScale(0)
{
  try
    {
      // First determine the location of the interval
      // Secondly determine whether to distribute the parameter linearly or not
      // depending on the location and act upon it.
      if (0.0 <= mMinimum) // the interval [mMinimum, mMaximum) is in [0, inf)
        {
          mRange = CIntervalValue::Range::positive;
          mLogarithmicScale = log10(mMaximum) - log10(std::max(mMinimum, std::numeric_limits< C_FLOAT64 >::min()));
          mIsLogarithmic = mLogarithmicScale > 1.8 && mMinimum > 0.0;
        }
      else if (mMaximum > 0) // 0 is in the interval (mMinimum, mMaximum)
        {
          mRange = CIntervalValue::Range::containsZero;
          mLogarithmicScale = log10(mMaximum) + log10(-mMinimum);
          mIsLogarithmic = mLogarithmicScale > 3.6;
        }
      else // the interval (mMinimum, mMaximum] is in (-inf, 0]
        {
          mRange = CIntervalValue::Range::negative;
          mLogarithmicScale = log10(-mMinimum) - log10(std::max(-mMaximum, std::numeric_limits< C_FLOAT64 >::min()));
          mIsLogarithmic = mLogarithmicScale > 1.8 && mMaximum < 0.0;
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
      switch (mRange)
        {
        case CIntervalValue::Range::positive:
          if (mIsLogarithmic)
            result = pow(10.0, log10(std::max(mMinimum, std::numeric_limits< C_FLOAT64 >::min())) + mLogarithmicScale * pRandom->getRandomCC());
          else
            result = mMinimum + pRandom->getRandomCC() * (mMaximum - mMinimum);

          break;

        case CIntervalValue::Range::containsZero:
          if (mIsLogarithmic)
            {
              C_FLOAT64 mean = (mMaximum + mMinimum) * 0.5;
              C_FLOAT64 sigma = std::min(std::numeric_limits< C_FLOAT64 >::max(), mMaximum - mMinimum) / 3.0;

              do
                {
                  result = pRandom->getRandomNormal(mean, sigma);
              } while ((result < mMinimum) || (result > mMaximum));
            }
          else
            result = mMinimum + pRandom->getRandomCC() * (mMaximum - mMinimum);

          break;

        case CIntervalValue::Range::negative:
          if (mIsLogarithmic)
            result = -pow(10.0, log10(std::max(-mMaximum, std::numeric_limits< C_FLOAT64 >::min())) + mLogarithmicScale * pRandom->getRandomCC());
          else
            result = mMinimum + pRandom->getRandomCC() * (mMaximum - mMinimum);

          break;

        case CIntervalValue::Range::invalid:
          result = (mMaximum + mMinimum) * 0.5;

          break;
        }
    }

  catch (...)
    {
      result = (mMaximum + mMinimum) * 0.5;
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
  return mMinimum;
}

const C_FLOAT64 & CIntervalValue::getMaximum() const
{
  return mMaximum;
}

const C_FLOAT64 & CIntervalValue::getLogarithmicScale() const
{
  return mLogarithmicScale;
}
