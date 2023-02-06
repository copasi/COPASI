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

#include <copasi/plotUI/CBandedGraphData.h>

//********************  CBandedGraphData  *********************************
CBandedGraphData::CBandedGraphData():
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtSeriesData<QPointF>(),
#else
  QwtData(),
#endif
  mpX(NULL),
  mpY1(NULL),
  mpY2(NULL),
  mSize(0),
  mMaxSize(0),
  mLastRectangle(0),
  mMinX(std::numeric_limits<double>::quiet_NaN()),
  mMaxX(std::numeric_limits<double>::quiet_NaN()),
  mMinY(std::numeric_limits<double>::quiet_NaN()),
  mMaxY(std::numeric_limits<double>::quiet_NaN())
{}

CBandedGraphData::CBandedGraphData(const CVector< double > & x,
                                   const CVector< double > & y1,
                                   const CVector< double > & y2,
                                   size_t size):
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtSeriesData<QPointF>(),
#else
  QwtData(),
#endif
  mpX(x.array()),
  mpY1(y1.array()),
  mpY2(y2.array()),
  mSize(size),
  mMaxSize(x.size()),
  mLastRectangle(0),
  mMinX(std::numeric_limits<double>::quiet_NaN()),
  mMaxX(std::numeric_limits<double>::quiet_NaN()),
  mMinY(std::numeric_limits<double>::quiet_NaN()),
  mMaxY(std::numeric_limits<double>::quiet_NaN())
{
  assert(x.size() == y1.size());
  assert(x.size() == y2.size());
  assert(mSize <= mMaxSize);
}

CBandedGraphData::~CBandedGraphData()
{}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
QwtSeriesData<QPointF> *
CBandedGraphData::copy() const
{
  CBandedGraphData * pCopy = new CBandedGraphData();

  *pCopy = *this;

  return pCopy;
}

QPointF CBandedGraphData::sample(size_t i) const
{
  return QPointF(x(i), y(i));
}

#else
QwtData *
CBandedGraphData::copy() const
{
  CBandedGraphData * pCopy = new CBandedGraphData();

  *pCopy = *this;

  return pCopy;
}
#endif

size_t
CBandedGraphData::size() const
{return 2 * mSize;}

double CBandedGraphData::x(size_t i) const
{
  // to make a polygon out of the two data curves
  // one curve goes in order, the other backwards
  if (i >= mSize)
    i = (2 * mSize - i - 1);

  return *(mpX + i);
}

double CBandedGraphData::y(size_t i) const
{
  double ret;

  // to make a polygon out of the two data curves
  // one curve goes in order, the other backwards
  if (i < mSize)
    ret = *(mpY1 + i);
  else
    ret = *(mpY2 + (2 * mSize - i - 1));

  return ret;
}

double CBandedGraphData::y1(size_t i) const
{
  return *(mpY1 + i);
}

double CBandedGraphData::y2(size_t i) const
{
  return *(mpY2 + i);
}

QwtDoubleRect
CBandedGraphData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  if (mLastRectangle == mSize)
    return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);

  const double *xIt = mpX + mLastRectangle;
  const double *yIt1 = mpY1 + mLastRectangle;
  const double *yIt2 = mpY2 + mLastRectangle;
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
          if (xv < mMinX || MinXisNaN)
            {
              mMinX = xv;
              MinXisNaN = false;
            }

          if (xv > mMaxX || MaxXisNaN)
            {
              mMaxX = xv;
              MaxXisNaN = false;
            }
        }

      double yv1 = *yIt1++;
      double yv2 = *yIt2++;

      if (std::isnan(yv1) || std::isnan(yv2))
        {
          yv1 = std::isnan(yv1) ? yv2 : yv1;
          yv2 = yv1;
        }
      else if (yv1 > yv2)
        {
          double tmp = yv1;
          yv1 = yv2;
          yv2 = tmp;
        } // now: yv1 <= yv2

      if (!std::isnan(yv1))
        {
          if (yv1 < mMinY || MinYisNaN)
            {
              mMinY = yv1;
              MinYisNaN = false;
            }

          if (yv2 > mMaxY || MaxYisNaN)
            {
              mMaxY = yv2;
              MaxYisNaN = false;
            }
        }
    }

  if (std::isnan(mMinX + mMaxX + mMinY + mMaxY))
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  // We need to avoid very small data ranges (absolute and relative)
  C_FLOAT64 minRange = fabs(mMinX + mMaxX) * 5.e-5 + std::numeric_limits< C_FLOAT64 >::min() * 100.0;

  if (mMaxX - mMinX < minRange)
    {
      mMinX = mMinX - minRange * 0.5;
      mMaxX = mMaxX + minRange * 0.5;
    }

  minRange = fabs(mMinY + mMaxY) * 5e-5 + std::numeric_limits< C_FLOAT64 >::min() * 100.0;

  if (mMaxY - mMinY < minRange)
    {
      mMinY = mMinY - minRange * 0.5;
      mMaxY = mMaxY + minRange * 0.5;
    }

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

void
CBandedGraphData::setSize(const size_t & size)
{
  mSize = size;
  assert(mSize <= mMaxSize);
}

void
CBandedGraphData::reallocated(const CVector< double > * pX, const CVector< double > *pY1, const CVector< double > *pY2)
{
  mpX = pX->array();
  mpY1 = pY1->array();
  mpY2 = pY2->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

CBandedGraphData & CBandedGraphData::operator = (const CBandedGraphData & rhs)
{
  if (&rhs == this) return *this;

  mpX = rhs.mpX;
  mpY1 = rhs.mpY1;
  mpY2 = rhs.mpY2;
  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;
  mLastRectangle = rhs.mLastRectangle;
  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;

  return * this;
}
