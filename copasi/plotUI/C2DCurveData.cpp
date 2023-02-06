// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>

#include <copasi/plotUI/C2DCurveData.h>

C2DCurveData::C2DCurveData():
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtSeriesData<QPointF>(),
#else
  QwtData(),
#endif

  mpX(NULL),
  mpY(NULL),
  mSize(0),
  mMaxSize(0),
  mLastRectangle(0),
  mMinX(std::numeric_limits<double>::quiet_NaN()),
  mMaxX(std::numeric_limits<double>::quiet_NaN()),
  mMinY(std::numeric_limits<double>::quiet_NaN()),
  mMaxY(std::numeric_limits<double>::quiet_NaN())
{}

C2DCurveData::C2DCurveData(const CVector< C_FLOAT64 > & x, const CVector< C_FLOAT64 > & y, size_t size):
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtSeriesData<QPointF>(),
#else
  QwtData(),
#endif
  mpX(x.array()),
  mpY(y.array()),
  mSize(size),
  mMaxSize(x.size()),
  mLastRectangle(0),
  mMinX(std::numeric_limits<double>::quiet_NaN()),
  mMaxX(std::numeric_limits<double>::quiet_NaN()),
  mMinY(std::numeric_limits<double>::quiet_NaN()),
  mMaxY(std::numeric_limits<double>::quiet_NaN())
{
  assert(x.size() == y.size());
  assert(mSize <= mMaxSize);
}

C2DCurveData::~C2DCurveData()
{}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
QwtSeriesData<QPointF> * C2DCurveData::copy() const
{
  C2DCurveData * pCopy = new C2DCurveData();

  *pCopy = *this;

  return pCopy;
}

QPointF C2DCurveData::sample(size_t i) const
{
  return QPointF(x(i), y(i));
}

#else
QwtData * C2DCurveData::copy() const
{
  C2DCurveData * pCopy = new C2DCurveData();

  *pCopy = *this;

  return pCopy;
}
#endif

size_t C2DCurveData::size() const
{
  return mSize;
}

double C2DCurveData::x(size_t i) const
{
  return *(mpX + i);
}

double C2DCurveData::y(size_t i) const
{
  return *(mpY + i);
}

QwtDoubleRect C2DCurveData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  if (mLastRectangle == mSize)
    return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);

  const double *xIt = mpX + mLastRectangle;
  const double *yIt = mpY + mLastRectangle;
  const double *end = mpX + mSize;

  mLastRectangle = mSize;

  // We have to remember whether we have an initial NaN
  bool MinXisNaN = std::isnan(mMinX);
  bool MaxXisNaN = std::isnan(mMaxX);
  bool MinYisNaN = std::isnan(mMinY);
  bool MaxYisNaN = std::isnan(mMaxY);

  while (xIt < end)
    {
      const double xv = *xIt++;

      if (!std::isnan(xv))
        {
          if ((xv < mMinX || MinXisNaN) && xv > -std::numeric_limits< double >::infinity())
            {
              mMinX = xv;
              MinXisNaN = false;
            }

          if ((xv > mMaxX || MaxXisNaN) && xv < std::numeric_limits< double >::infinity())
            {
              mMaxX = xv;
              MaxXisNaN = false;
            }
        }

      const double yv = *yIt++;

      if (!std::isnan(yv))
        {
          if ((yv < mMinY || MinYisNaN) && yv > -std::numeric_limits< double >::infinity())
            {
              mMinY = yv;
              MinYisNaN = false;
            }

          if ((yv > mMaxY  || MaxYisNaN) && yv < std::numeric_limits< double >::infinity())
            {
              mMaxY = yv;
              MaxYisNaN = false;
            }
        }
    }

  if (std::isnan(mMinX + mMaxX + mMinY + mMaxY))
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  // We need to avoid very small data ranges (absolute and relative)
  C_FLOAT64 minRange;

  minRange = fabs(mMinY + mMaxY) * 5e-5 + std::numeric_limits< C_FLOAT64 >::min() * 100.0;

  if (mMaxY - mMinY < minRange)
    {
      mMinY = mMinY - minRange * 0.5;
      mMaxY = mMaxY + minRange * 0.5;
    }

  if (mMinX == 0 && mMaxX == 0)
    return QwtDoubleRect(0.1, mMinY, -0.2, mMaxY - mMinY); // invalid X

  minRange = fabs(mMinX + mMaxX) * 5.e-5 + std::numeric_limits< C_FLOAT64 >::min() * 100.0;

  if (mMaxX - mMinX < minRange)
    {
      mMinX = mMinX - minRange * 0.5;
      mMaxX = mMaxX + minRange * 0.5;
    }

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

void C2DCurveData::setSize(const size_t & size)
{
  mSize = size;
  assert(mSize <= mMaxSize);
}

void C2DCurveData::reallocated(const CVector< double > * pX, const CVector< double > *pY)
{
  mpX = pX->array();
  mpY = pY->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

C2DCurveData & C2DCurveData::operator = (const C2DCurveData & rhs)
{
  mpX = rhs.mpX;
  mpY = rhs.mpY;
  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;
  mLastRectangle = rhs.mLastRectangle;
  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;

  return * this;
}
