// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include <limits>
#include <algorithm>
#include <cmath>

#include <copasi/plotUI/CSpectorgramData.h>

CSpectorgramData::CSpectorgramData()
  : QwtRasterData()
  , mpX(NULL)
  , mpY(NULL)
  , mpZ(NULL)
  , mSize(0)
  , mMaxSize(0)
  , mLastRectangle(0)
  , mMinX(std::numeric_limits<double>::quiet_NaN())
  , mMaxX(std::numeric_limits<double>::quiet_NaN())
  , mMinY(std::numeric_limits<double>::quiet_NaN())
  , mMaxY(std::numeric_limits<double>::quiet_NaN())
  , mMinZ(std::numeric_limits<double>::quiet_NaN())
  , mMaxZ(std::numeric_limits<double>::quiet_NaN())
  , mpMatrix(NULL)
  , mLogZ(false)
  , mLimitZ(std::numeric_limits<double>::quiet_NaN())
  , mBilinear(true)
  , mDistanceX()
  , mDistanceY()
  , mSizeX(0)
  , mSizeY(0)
{
}

CSpectorgramData::CSpectorgramData(const CVector<double> &x,
                                   const CVector<double> &y,
                                   const CVector<double> &z,
                                   size_t size,
                                   bool logZ,
                                   double limitZ,
                                   bool bilinear)
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  : QwtRasterData()
#else
  : QwtRasterData(QwtDoubleRect(0, 0, 100, 100))
#endif
  , mpX(x.array())
  , mpY(y.array())
  , mpZ(z.array())
  , mSize(size)
  , mMaxSize(x.size())
  , mLastRectangle(0)
  , mMinX(std::numeric_limits<double>::quiet_NaN())
  , mMaxX(std::numeric_limits<double>::quiet_NaN())
  , mMinY(std::numeric_limits<double>::quiet_NaN())
  , mMaxY(std::numeric_limits<double>::quiet_NaN())
  , mMinZ(std::numeric_limits<double>::quiet_NaN())
  , mMaxZ(std::numeric_limits<double>::quiet_NaN())
  , mpMatrix(NULL)
  , mLogZ(logZ)
  , mLimitZ(limitZ)
  , mBilinear(bilinear)
  , mDistanceX()
  , mDistanceY()
  , mSizeX(0)
  , mSizeY(0)
{
}

CSpectorgramData::CSpectorgramData(const CSpectorgramData& other)
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  : QwtRasterData()
#else
  : QwtRasterData(other)
#endif
  , mpX(other.mpX)
  , mpY(other.mpY)
  , mpZ(other.mpZ)
  , mSize(other.mSize)
  , mMaxSize(other.mMaxSize)
  , mLastRectangle(other.mLastRectangle)
  , mMinX(other.mMinX)
  , mMaxX(other.mMaxX)
  , mMinY(other.mMinY)
  , mMaxY(other.mMaxY)
  , mMinZ(other.mMinZ)
  , mMaxZ(other.mMaxZ)
  , mpMatrix(NULL)
  , mLogZ(other.mLogZ)
  , mLimitZ(other.mLimitZ)
  , mBilinear(other.mBilinear)
  , mDistanceX(other.mDistanceX)
  , mDistanceY(other.mDistanceY)
  , mSizeX()
  , mSizeY(0)

{
}

CSpectorgramData &CSpectorgramData::operator =(const CSpectorgramData &rhs)
{
  if (&rhs == this) return *this;

  mpX = rhs.mpX;
  mpY = rhs.mpY;
  mpZ = rhs.mpZ;

  mSize = rhs.mSize;
  mMaxSize = rhs.mMaxSize;
  mLastRectangle = rhs.mLastRectangle;

  mMinX = rhs.mMinX;
  mMaxX = rhs.mMaxX;
  mMinY = rhs.mMinY;
  mMaxY = rhs.mMaxY;
  mMinZ = rhs.mMinZ;
  mMaxZ = rhs.mMaxZ;

  mpMatrix = NULL;

  mLogZ = rhs.mLogZ;
  mLimitZ = rhs.mLimitZ;
  mBilinear = rhs.mBilinear;

  return *this;
}

CSpectorgramData::~CSpectorgramData()
{
  pdelete(mpMatrix);
}

QwtRasterData *CSpectorgramData::copy() const
{
  CSpectorgramData * pCopy = new CSpectorgramData(*this);

  return pCopy;
}

void
CSpectorgramData::calculateExtremes() const
{
  if (mLastRectangle == mSize)
    return;

  const double *xIt = mpX + mLastRectangle;
  const double *yIt = mpY + mLastRectangle;
  const double *zIt = mpZ + mLastRectangle;
  const double *end = mpX + mSize;

  mLastRectangle = mSize;

  // We have to remember whether we have an initial NaN
  bool MinXisNaN = std::isnan(mMinX);
  bool MaxXisNaN = std::isnan(mMaxX);
  bool MinYisNaN = std::isnan(mMinY);
  bool MaxYisNaN = std::isnan(mMaxY);
  bool MinZisNaN = std::isnan(mMinZ);
  bool MaxZisNaN = std::isnan(mMaxZ);

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

      double yv = *yIt++;

      if (!std::isnan(yv))
        {
          if (yv < mMinY || MinYisNaN)
            {
              mMinY = yv;
              MinYisNaN = false;
            }

          if (yv > mMaxY || MaxYisNaN)
            {
              mMaxY = yv;
              MaxYisNaN = false;
            }
        }

      double zv = *zIt++;

      if (!std::isnan(zv))
        {
          if (zv < mMinZ || MinZisNaN)
            {
              mMinZ = zv;
              MinZisNaN = false;
            }

          if (zv > mMaxZ || MaxZisNaN)
            {
              mMaxZ = zv;
              MaxZisNaN = false;
            }
        }
    }

  if (std::isnan(mMinX + mMaxX + mMinY + mMaxY))
    return;
}

QwtDoubleRect CSpectorgramData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -0.1, -0.1); // invalid

  calculateExtremes();

  if (std::isnan(mMinX + mMaxX + mMinY + mMaxY))
    return QwtDoubleRect(1.0, 1.0, -0.1, -0.1); // invalid

  return QwtDoubleRect(mMinX, mMinY, mMaxX - mMinX, mMaxY - mMinY);
}

QwtDoubleInterval CSpectorgramData::range() const
{
  if (mSize == 0)
    return QwtDoubleInterval(0, 1);

  if (mLimitZ == mLimitZ)
    return QwtDoubleInterval(mMinZ, std::min(mMaxZ, mLimitZ));

  return QwtDoubleInterval(mMinZ, mMaxZ);
}

size_t CSpectorgramData::size() const
{
  return 2 * mSize;
}

double
CSpectorgramData::bilinearAround(int xIndex, int yIndex,
                                 double x,
                                 double y) const
{
  double x1 = mValuesX[xIndex];
  double y1 = mValuesY[yIndex];
  double diffXX1 = x - x1;
  double diffYY1 = y - y1;
  int xNeighbor = xIndex +
                  (diffXX1 < 0.0 ? -1 : 1);

  if (xNeighbor >= (int)mSizeX) xNeighbor = mSizeX - 1;

  if (xNeighbor < 0) xNeighbor = 0;

  int yNeighbor = yIndex +
                  (diffYY1 < 0.0 ? -1 : 1);

  if (yNeighbor >= (int)mSizeY) yNeighbor = mSizeY - 1;

  if (yNeighbor < 0) yNeighbor = 0;

  double x2 = mValuesX[xNeighbor];
  double y2 = mValuesY[yNeighbor];

  double x1y1 = (*mpMatrix)(xIndex, yIndex);

  if (x2 == x1 || y2 == y1) return  x1y1;

  double x2y1 = (*mpMatrix)(xNeighbor, yIndex);
  double x1y2 = (*mpMatrix)(xIndex, yNeighbor);
  double x2y2 = (*mpMatrix)(xNeighbor, yNeighbor);

  return
    ((y2 - y) / (y2 - y1))
    * ((x2 - x) / (x2 - x1) * x1y1 + (x - x1) / (x2 - x1) * x2y1)
    + ((y - y1) / (y2 - y1))
    * ((x2 - x) / (x2 - x1) * x1y2 + (x - x1) / (x2 - x1) * x2y2);
}

bool
CSpectorgramData::getBilinear() const
{
  return mBilinear;
}

void
CSpectorgramData::setBilinear(bool bilinear)
{
  mBilinear = bilinear;
}

double
CSpectorgramData::value(double x, double y) const
{

  if (mpMatrix == NULL || mSize == 0)
    return 0;

  int xpos = 0;
  int ypos = 0;
  std::vector<double>::const_iterator curX = mValuesX.begin();

  for (; curX != mEndX; ++curX)
    {
      if (fabs(*curX - x) < mDistanceX)
        break;

      ++xpos;
    }

  std::vector<double>::const_iterator curY = mValuesY.begin();

  for (; curY != mEndY; ++curY)
    {
      if (fabs(*curY - y) < mDistanceY)
        break;

      ++ypos;
    }

  if (xpos == mSizeX) --xpos;

  if (ypos == mSizeY) --ypos;

  double value = mBilinear
                 ? bilinearAround(xpos, ypos, x, y)
                 : mpMatrix->operator()(xpos, ypos);

  if (value != value)
    return value;

  if (mLimitZ == mLimitZ && value > mLimitZ)
    return mLimitZ;

  if (mLogZ && value > 0)
    return log(value);

  return value;
}

void
CSpectorgramData::setSize(const size_t &size)
{
  if (size == mSize)
    return;

  mSize = size;

  initializeMatrix();

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  boundingRect();
  setInterval(Qt::XAxis, QwtInterval(mMinX, mMaxX));
  setInterval(Qt::YAxis, QwtInterval(mMinY, mMaxY));

  if (mLimitZ == mLimitZ)
    setInterval(Qt::ZAxis, QwtInterval(mMinZ, std::min(mMaxZ, mLimitZ)));
  else
    setInterval(Qt::ZAxis, QwtInterval(mMinZ, mMaxZ));

#else
  setBoundingRect(boundingRect());
#endif

  assert(mSize <= mMaxSize);
}

void
CSpectorgramData::reallocated(const CVector<double> *pX, const CVector<double> *pY, const CVector<double> *pZ)
{
  mpX = pX->array();
  mpY = pY->array();
  mpZ = pZ->array();
  mMaxSize = pX->size();

  assert(mSize <= mMaxSize);
}

void
CSpectorgramData::initializeMatrix()
{
  if (mSize == 0) return;

  pdelete(mpMatrix);

  calculateExtremes();

  const double *xIt = mpX;
  const double *yIt = mpY;
  const double *end = mpX + mSize;
  const double *endY = mpY + mSize;

  mValuesX.clear();
  mValuesY.clear();

  for (; xIt != end; ++xIt)
    {
      double current = *xIt;

      if (current != current)
        continue;

      if (std::find(mValuesX.begin(), mValuesX.end(), current) != mValuesX.end())
        continue;

      mValuesX.push_back(current);
    }

  for (; yIt != endY; ++yIt)
    {
      double current = *yIt;

      if (current != current)
        continue;

      if (std::find(mValuesY.begin(), mValuesY.end(), current) != mValuesY.end())
        continue;

      mValuesY.push_back(current);
    }

  mEndX = mValuesX.end();
  mEndY = mValuesY.end();

  std::sort(mValuesX.begin(), mEndX);
  std::sort(mValuesY.begin(), mEndY);

  mSizeX = mValuesX.size();
  mSizeY = mValuesY.size();

  if (mSizeX > 2)
    mDistanceX = fabs(mValuesX[1] - mValuesX[0]);

  if (mSizeY > 2)
    mDistanceY = fabs(mValuesY[1] - mValuesY[0]);

  mpMatrix = new CMatrix<double>(mSizeX, mSizeY);
  *mpMatrix = std::numeric_limits<double>::quiet_NaN();

  xIt = mpX;
  yIt = mpY;
  const double *zIt = mpZ;

  std::vector<double>::const_iterator curX;
  std::vector<double>::const_iterator curY;

  size_t count = 0;

  for (; count < mSize; ++count, ++xIt, ++yIt, ++zIt)
    {
      curX = std::find(mValuesX.begin(), mEndX, *xIt);

      if (curX == mEndX) continue;

      curY = std::find(mValuesY.begin(), mEndY, *yIt);

      if (curY == mEndY) continue;

      int xpos = curX - mValuesX.begin();
      int ypos = curY - mValuesY.begin();

      (*mpMatrix)(xpos, ypos) = *zIt;
    }
}
double
CSpectorgramData::getLimitZ() const
{
  return mLimitZ;
}

void
CSpectorgramData::setLimitZ(double limitZ)
{
  mLimitZ = limitZ;
}
