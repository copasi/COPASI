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

#include <copasi/plotUI/CHistoCurveData.h>

CHistoCurveData::CHistoCurveData():
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtSeriesData<QPointF>(),
#else
  QwtData(),
#endif
  mpX(NULL),
  mSize(0),
  mMaxSize(0),
  mLastRectangle(0),
  mCount(0),
  mMinX(std::numeric_limits<double>::quiet_NaN()),
  mMaxX(std::numeric_limits<double>::quiet_NaN()),
  mMinY(std::numeric_limits<double>::quiet_NaN()),
  mMaxY(std::numeric_limits<double>::quiet_NaN()),
  mIncrement(1.0),
  mMap(),
  mHistoX(0),
  mHistoY(0)
{}

CHistoCurveData::CHistoCurveData(const CVector< C_FLOAT64 > & x,
                                 size_t size,
                                 const C_FLOAT64 & increment):
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtSeriesData<QPointF>(),
#else
  QwtData(),
#endif
  mpX(x.array()),
  mSize(size),
  mMaxSize(x.size()),
  mLastRectangle(0),
  mCount(0),
  mMinX(std::numeric_limits<double>::quiet_NaN()),
  mMaxX(std::numeric_limits<double>::quiet_NaN()),
  mMinY(std::numeric_limits<double>::quiet_NaN()),
  mMaxY(std::numeric_limits<double>::quiet_NaN()),
  mIncrement(increment),
  mMap(),
  mHistoX(0),
  mHistoY(0)
{
  assert(mSize <= mMaxSize);
}

CHistoCurveData::~CHistoCurveData()
{}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
QwtSeriesData<QPointF>* CHistoCurveData::copy() const
{
  CHistoCurveData * pCopy = new CHistoCurveData();

  *pCopy = *this;

  return pCopy;
}

QPointF CHistoCurveData::sample(size_t i) const
{
  return QPointF(x(i), y(i));
}

#else
QwtData* CHistoCurveData::copy() const
{
  CHistoCurveData * pCopy = new CHistoCurveData();

  *pCopy = *this;

  return pCopy;
}
#endif

size_t CHistoCurveData::size() const
{
  return mHistoX.size();
}

double CHistoCurveData::x(size_t i) const
{
  return mHistoX[i];
}

double CHistoCurveData::y(size_t i) const
{
  return mHistoY[i];
}

QwtDoubleRect CHistoCurveData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid

  if (mLastRectangle == mSize)
    return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);

  const double *xIt = mpX + mLastRectangle;
  const double *end = mpX + mSize;

  mLastRectangle = mSize;

  double InvIncrement = 1.0 / mIncrement;

  for (; xIt != end; ++xIt)
    {
      //just ignore breaks. Later we perhaps want to start a new histogram...
      if (std::isnan(*xIt)) //NaN
        continue;

      ++mCount;

      if (-std::numeric_limits< C_FLOAT64 >::infinity() < *xIt &&
          *xIt < std::numeric_limits< C_FLOAT64 >::infinity())
        {
          mMap[(C_INT32) floor(*xIt * InvIncrement)]++;
          mMap[(C_INT32) floor(*xIt * InvIncrement) + 1];
        }
    }

  //construct arrays
  mHistoX.resize(mMap.size() + 1);
  mHistoY.resize(mMap.size() + 1);

  double *pX = mHistoX.array();
  double *pY = mHistoY.array();

  //add one bin to the left
  if (mMap.size() > 0)
    {
      *pX = (mMap.begin()->first - 1) * mIncrement;
    }
  else
    {
      *pX = 0.0;
    }

  *pY = 0.0;

  mMinX = mMaxX = *pX++;
  mMinY = mMaxY = *pY++;

  std::map<C_INT32, C_INT32>::const_iterator it = mMap.begin();
  std::map<C_INT32, C_INT32>::const_iterator itEnd = mMap.end();

  for (; it != itEnd; ++it, ++pX, ++pY)
    {
      *pX = it->first * mIncrement;
      *pY = (double)it->second * 100.0 / (double)mCount;

      if (*pX < mMinX)
        mMinX = *pX;

      if (*pX > mMaxX)
        mMaxX = *pX;

      if (*pY < mMinY)
        mMinY = *pY;

      if (*pY > mMaxY)
        mMaxY = *pY;
    }

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

void CHistoCurveData::setSize(const size_t & size)
{
  mSize = size;
  assert(mSize <= mMaxSize);
}

void CHistoCurveData::reallocated(const CVector< double > * pX)
{
  mpX = pX->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

CHistoCurveData & CHistoCurveData::operator = (const CHistoCurveData & rhs)
{
  mpX = rhs.mpX;
  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;

  mLastRectangle = rhs.mLastRectangle;
  mCount = rhs.mCount;
  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;

  mIncrement = rhs.mIncrement;
  mMap = rhs.mMap;
  mHistoX = rhs.mHistoX;
  mHistoY = rhs.mHistoY;

  return * this;
}
