// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#include <copasi/plotUI/CLinearColorMap.h>

CLinearColorMap::CLinearColorMap(const QColor &from, const QColor &to, QwtColorMap::Format format)
  : QwtLinearColorMap(from, to, format)
  , mMissingColor(Qt::white)
{

}

CLinearColorMap::CLinearColorMap(const CLinearColorMap &other)
  : QwtLinearColorMap(other)
  , mMissingColor(other.mMissingColor)
{

}

CLinearColorMap::~CLinearColorMap()
{

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

  return QwtLinearColorMap::rgb(interval, value);
}
