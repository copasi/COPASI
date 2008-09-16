// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLBase.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/16 22:29:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

Point CLPoint::getSBMLPoint() const
  {
    Point p(mX, mY);
    return p;
  }

//***********************************************************

CLDimensions::CLDimensions(const Dimensions& d)
    : mWidth(d.getWidth()),
    mHeight(d.getHeight())
{}

Dimensions CLDimensions::getSBMLDimensions() const
  {
    Dimensions d(mWidth, mHeight);
    return d;
  }

//***********************************************************

CLBoundingBox::CLBoundingBox(const BoundingBox & bb)
    : mPosition(*bb.getPosition()),
    mDimensions(*bb.getDimensions())
{}

BoundingBox CLBoundingBox::getSBMLBoundingBox() const
  {
    return BoundingBox("", mPosition.getX(), mPosition.getY(),
                       mDimensions.getWidth(), mDimensions.getHeight());
  }

//***********************************************************

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
