// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLBase.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/29 13:17:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/layout/BoundingBox.h>

#include "CLBase.h"

//sbml constructors

CLPoint::CLPoint(const Point& p)
    : mX(p.getXOffset()),
    mY(p.getYOffset())
{}

CLDimensions::CLDimensions(const Dimensions& d)
    : mWidth(d.getWidth()),
    mHeight(d.getHeight())
{}

CLBoundingBox::CLBoundingBox(const BoundingBox & bb)
    : mPosition(*bb.getPosition()),
    mDimensions(*bb.getDimensions())
{}

std::ostream & operator<<(std::ostream &os, const CLPoint & p)
{
  os << "(x=" << p.mX << ", y=" << p.mY << ")";
  return os;
}

std::ostream & operator<<(std::ostream &os, const CLDimensions & d)
{
  os << "(w=" << d.mWidth << ", h=" << d.mHeight << ")";
  return os;
}

std::ostream & operator<<(std::ostream &os, const CLBoundingBox & bb)
{
  os << "[" << bb.mPosition << bb.mDimensions << "]";
  return os;
}
