// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/packages/layout/sbml/BoundingBox.h>

#include "CLBase.h"

//sbml constructors

CLPoint::CLPoint(const Point& p) :
  mX(p.getXOffset())
  , mY(p.getYOffset())
  , mZ(p.getZOffset())
{}

Point CLPoint::getSBMLPoint() const
{
  LayoutPkgNamespaces NameSpaces;

  Point p(&NameSpaces, mX, mY, mZ);
  return p;
}

//***********************************************************

CLDimensions::CLDimensions(const Dimensions& d) :
  mWidth(d.getWidth())
  , mHeight(d.getHeight())
  , mDepth(d.getDepth())
{}

Dimensions CLDimensions::getSBMLDimensions() const
{
  LayoutPkgNamespaces NameSpaces;

  Dimensions d(&NameSpaces
               , mWidth
               , mHeight
               , mDepth
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
  LayoutPkgNamespaces NameSpaces;

  return BoundingBox(&NameSpaces, "", mPosition.getX(), mPosition.getY(),
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
