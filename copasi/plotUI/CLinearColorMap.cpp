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

#include <copasi/copasi.h>
#include <copasi/plotUI/CLinearColorMap.h>

CLinearColorMap::CLinearColorMap(const QColor &from, const QColor &to, QwtColorMap::Format format)
  : QwtLinearColorMap(from, to, format)
  , mMissingColor(Qt::white)
  , mAbsoluteStop(std::numeric_limits<double>::quiet_NaN())
  , mAbsoluteStopColor(Qt::white)
  , mFrom(from)
  , mTo(to)
  , mpLower(NULL)
  , mpUpper(NULL)
{
}

CLinearColorMap::CLinearColorMap(const CLinearColorMap &other)
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  : QwtLinearColorMap(other.mFrom, other.mTo, other.format())
#else
  : QwtLinearColorMap(other)
#endif
  , mMissingColor(other.mMissingColor)
  , mAbsoluteStop(other.mAbsoluteStop)
  , mAbsoluteStopColor(other.mAbsoluteStopColor)
  , mFrom(other.mFrom)
  , mTo(other.mTo)
  , mpLower(NULL)
  , mpUpper(NULL)
{
  if (other.mpLower != NULL)
    mpLower = new CLinearColorMap(*other.mpLower);

  if (other.mpUpper != NULL)
    mpUpper = new CLinearColorMap(*other.mpUpper);

  QVector<double> stops = other.colorStops();
  QVectorIterator<double> iter(stops);

  while (iter.hasNext())
    {
      double value = iter.next();

      if (value == 0.0 || value == 1.0)
        continue;

      addColorStop(value, other.color(QwtDoubleInterval(0, 1), value));
    }
}

CLinearColorMap::~CLinearColorMap()
{
  pdelete(mpLower);
  pdelete(mpUpper);
}

CLinearColorMap &CLinearColorMap::operator=(const CLinearColorMap &rhs)
{
  if (&rhs == this) return *this;

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)

#else
  QwtLinearColorMap::operator =(rhs);
#endif
  mFrom = rhs.mFrom;
  mTo = rhs.mTo;
  mMissingColor = rhs.mMissingColor;
  mAbsoluteStop = rhs.mAbsoluteStop;

  if (rhs.mpLower != NULL)
    mpLower = new CLinearColorMap(*rhs.mpLower);

  if (rhs.mpUpper != NULL)
    mpUpper = new CLinearColorMap(*rhs.mpUpper);

  QVector<double> stops = rhs.colorStops();
  QVectorIterator<double> iter(stops);

  while (iter.hasNext())
    {
      double value = iter.next();

      if (value == 0.0 || value == 1.0)
        continue;

      addColorStop(value, rhs.color(QwtDoubleInterval(0, 1), value));
    }

  return *this;
}

QwtColorMap *CLinearColorMap::copy() const
{
  return new CLinearColorMap(*this);
}

QRgb CLinearColorMap::rgb(const QwtDoubleInterval &interval, double value) const
{

  if (value != value)
    return mMissingColor.rgb();

  if (mpLower != NULL && mpUpper != NULL)
    {
      if (value < mAbsoluteStop)
        {
          return mpLower->rgb(QwtDoubleInterval(interval.minValue(), mAbsoluteStop), value);
        }
      else
        {
          return mpUpper->rgb(QwtDoubleInterval(mAbsoluteStop, interval.maxValue()), value);
        }
    }

  return QwtLinearColorMap::rgb(interval, value);
}

void CLinearColorMap::setAbsoluteStop(double value, const QColor & color)
{
  mAbsoluteStop = value;
  mAbsoluteStopColor = color;

  pdelete(mpLower);
  pdelete(mpUpper);

  mpLower = new CLinearColorMap(color1(), color, format());
  mpUpper = new CLinearColorMap(color, color2(), format());
}
