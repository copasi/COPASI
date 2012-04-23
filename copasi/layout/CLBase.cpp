// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLBase.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:44:51 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/packages/layout/sbml/BoundingBox.h>

#include "CLBase.h"

//sbml constructors

CLPoint::CLPoint(const Point& p) :
    mX(p.getXOffset())
    , mY(p.getYOffset())
#ifdef USE_CRENDER_EXTENSION
    , mZ(p.getZOffset())
#endif // USE_CRENDER_EXTENSION
{}

Point CLPoint::getSBMLPoint() const
{
#ifdef USE_CRENDER_EXTENSION
  Point p(new LayoutPkgNamespaces(), mX, mY, mZ);
#else
  Point p(new LayoutPkgNamespaces(), mX, mY);
#endif // USE_CRENDER_EXTENSION
  return p;
}

//***********************************************************

CLDimensions::CLDimensions(const Dimensions& d) :
    mWidth(d.getWidth())
    , mHeight(d.getHeight())
#ifdef USE_CRENDER_EXTENSION
    , mDepth(d.getDepth())
#endif // USE_CRENDER_EXTENSION
{}

Dimensions CLDimensions::getSBMLDimensions() const
{
  Dimensions d(new LayoutPkgNamespaces()
               , mWidth
               , mHeight
#ifdef USE_CRENDER_EXTENSION
               , mDepth
#endif // USE_CRENDER_EXTENSION
              );
  return d;
}

//***********************************************************

CLBoundingBox::CLBoundingBox(const BoundingBox & bb)
    : mPosition(*bb.getPosition()),
    mDimensions(*bb.getDimensions())
{}

BoundingBox CLBoundingBox::getSBMLBoundingBox() const
{
  return BoundingBox(new LayoutPkgNamespaces(), "", mPosition.getX(), mPosition.getY(),
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
