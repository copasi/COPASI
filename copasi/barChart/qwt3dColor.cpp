// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dColor.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/20 08:32:24 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "qwt3dColor.h"
#include <iostream>

BarColor::BarColor(Qwt3D::Plot3D* data, unsigned size, double min, double max)
    : data_(data)
{
  Q_ASSERT(data_);
  reset(size);

  minZ = min;
  maxZ = max;
}

void BarColor::reset(unsigned size)
{
  unsigned int i;
  colors_ = Qwt3D::ColorVector(size);
  Qwt3D::RGBA elem;

  double dsize = size;

  for (i = 0; i != size; ++i)
    {
      elem.r = i / dsize;
      elem.g = i / dsize / 4;
      elem.b = 1 - i / dsize;
      elem.a = 1.0;
      colors_[i] = elem;
    }
}

/**
 * Assigns a new ColorVector (Also overwrites the constructors size argument)
 */
void BarColor::setColorVector(Qwt3D::ColorVector const& cv)
{
  colors_ = cv;
}

void BarColor::setAlpha(double a)
{
  unsigned int i;

  if (a < 0 || a > 1)
    return;

  Qwt3D::RGBA elem;

  for (i = 0; i != colors_.size(); ++i)
    {
      elem = colors_[i];
      elem.a = a;
      colors_[i] = elem;
    }
}

Qwt3D::RGBA BarColor::operator()(double, double, double z) const
  {
    Q_ASSERT(data_);

    int index = (int)((colors_.size() - 1) * (z - minZ) / (maxZ - minZ));
    if (index < 0)
      index = 0;
    if ((unsigned int)index > colors_.size() - 1)
      index = (int)(colors_.size() - 1);
    return colors_[index];
  }
