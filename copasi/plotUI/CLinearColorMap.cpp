// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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
  , mpLower(NULL)
  , mpUpper(NULL)
{

}

CLinearColorMap::CLinearColorMap(const CLinearColorMap &other)
  : QwtLinearColorMap(other)
  , mMissingColor(other.mMissingColor)
  , mAbsoluteStop(other.mAbsoluteStop)
  , mAbsoluteStopColor(other.mAbsoluteStopColor)
  , mpLower(NULL)
  , mpUpper(NULL)
{
  if (other.mpLower != NULL)
    mpLower = new CLinearColorMap(*other.mpLower);

  if (other.mpUpper != NULL)
    mpUpper = new CLinearColorMap(*other.mpUpper);
}

CLinearColorMap::~CLinearColorMap()
{
  pdelete(mpLower);
  pdelete(mpUpper);
}

CLinearColorMap &CLinearColorMap::operator=(const CLinearColorMap &rhs)
{
  if (&rhs == this) return *this;

  QwtLinearColorMap::operator =(rhs);
  mMissingColor = rhs.mMissingColor;

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
