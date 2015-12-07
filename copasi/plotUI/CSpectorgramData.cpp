// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


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
{

}

CSpectorgramData::CSpectorgramData(const CVector<double> &x,
                                   const CVector<double> &y,
                                   const CVector<double> &z,
                                   size_t size,
                                   bool logZ,
                                   double limitZ,
                                   bool bilinear)
#if QWT_VERSION > 0x060000
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

{

}


CSpectorgramData::CSpectorgramData(const CSpectorgramData& other)
#if QWT_VERSION > 0x060000
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
  bool MinXisNaN = isnan(mMinX);
  bool MaxXisNaN = isnan(mMaxX);
  bool MinYisNaN = isnan(mMinY);
  bool MaxYisNaN = isnan(mMaxY);
  bool MinZisNaN = isnan(mMinZ);
  bool MaxZisNaN = isnan(mMaxZ);

  while (xIt < end)
    {
      const double xv = *xIt++;

      if (!isnan(xv))
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

      if (!isnan(yv))
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

      if (!isnan(zv))
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

  if (isnan(mMinX + mMaxX + mMinY + mMaxY))
    return;

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
}


QwtDoubleRect CSpectorgramData::boundingRect() const
{
  if (mSize <= 0)
    return QwtDoubleRect(1.0, 1.0, -0.1, -0.1); // invalid

  calculateExtremes();

  if (isnan(mMinX + mMaxX + mMinY + mMaxY))
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
  int dimX = mValuesX.size();
  int dimY = mValuesY.size();

  double x1 = mValuesX[xIndex];
  double y1 = mValuesY[yIndex];
  double diffXX1 = x - x1;
  double diffYY1 = y - y1;
  int xNeighbor = xIndex +
                  (std::signbit(diffXX1) ? -1 : 1);

  if (xNeighbor >= dimX) xNeighbor = dimX - 1;

  if (xNeighbor < 0) xNeighbor = 0;

  int yNeighbor = yIndex +
                  (std::signbit(diffYY1) ? -1 : 1);

  if (yNeighbor >= dimY) yNeighbor = dimY - 1;

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

  if (mpMatrix == NULL || mSize == 0 || mValuesX.size() < 2 || mValuesY.size() < 2)
    return 0;

  double distanceX = fabs(mValuesX[1] - mValuesX[0]);
  double distanceY = fabs(mValuesY[1] - mValuesY[0]);

  int xpos = 0;
  int ypos = 0;
  std::vector<double>::const_iterator curX = mValuesX.begin();

  for (; curX != mEndX; ++curX)
    {
      if (fabs(*curX - x) < distanceX)
        break;

      ++xpos;
    }

  std::vector<double>::const_iterator curY = mValuesY.begin();

  for (; curY != mEndY; ++curY)
    {
      if (fabs(*curY - y) < distanceY)
        break;

      ++ypos;
    }

  if (xpos == mValuesX.size()) --xpos;

  if (ypos == mValuesY.size()) --ypos;

  double value = mBilinear
                 ? bilinearAround(xpos, ypos, x, y)
                 : mpMatrix->operator()(xpos, ypos);

  if (value != value)
    return 0;

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

#if QWT_VERSION > 0x060000
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

  std::sort(mValuesX.begin(), mValuesX.end());
  std::sort(mValuesY.begin(), mValuesY.end());

  mEndX = mValuesX.end();
  mEndY = mValuesY.end();

  mpMatrix = new CMatrix<double>(mValuesX.size(), mValuesY.size());
  *mpMatrix = std::numeric_limits<double>::quiet_NaN();

  xIt = mpX;
  yIt = mpY;
  const double *zIt = mpZ;

  std::vector<double>::const_iterator curX;
  std::vector<double>::const_iterator curY;

  for (; xIt != end; ++xIt, ++yIt, ++zIt)
    {
      double dX = *xIt; double dY = *yIt;
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

