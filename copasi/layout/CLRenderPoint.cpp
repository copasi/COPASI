// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRenderPoint.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:44:50 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>
#include <limits>

#include <sbml/packages/render/sbml/RenderPoint.h>

#include "CLRenderPoint.h"

/**
 * Creates a new point with x,y and z set  to 0.0.
 */
CLRenderPoint::CLRenderPoint() :
    CLBase(),
    mXOffset(CLRelAbsVector(0.0, 0.0)),
    mYOffset(CLRelAbsVector(0.0, 0.0)),
    mZOffset(CLRelAbsVector(0.0, 0.0))
{
}

/**
 * Copy constructor.
 */
CLRenderPoint::CLRenderPoint(const CLRenderPoint& orig):
    CLBase(orig),
    mXOffset(orig.mXOffset),
    mYOffset(orig.mYOffset),
    mZOffset(orig.mZOffset)
{
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLRenderPoint::CLRenderPoint(const RenderPoint& source):
    CLBase(),
    mXOffset(source.x()),
    mYOffset(source.y()),
    mZOffset(source.z())
{
}

CLRenderPoint& CLRenderPoint::operator=(const CLRenderPoint & orig)
{
  if (&orig != this)
    {
      this->CLBase::operator=(orig);
      this->mXOffset = orig.mXOffset;
      this->mYOffset = orig.mYOffset;
      this->mZOffset = orig.mZOffset;
    }

  return *this;
}

/**
 * Creates a new point with the given ccordinates.
 */
CLRenderPoint::CLRenderPoint(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z) :
    CLBase()
    , mXOffset(x)
    , mYOffset(y)
    , mZOffset(z)
{
}

/**
 * Sets the Z offset to 0.0.
 */
void CLRenderPoint::initDefaults()
{
  this->setZOffset(0.0);
}

/**
 * Destructor.
 */
CLRenderPoint::~CLRenderPoint()
{
}

/**
 * Sets the coordinates to the given values.
 */
void
CLRenderPoint::setOffsets(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->setXOffset(x);
  this->setYOffset(y);
  this->setZOffset(z);
}

/**
 * Sets the x offset.
 */
void
CLRenderPoint::setXOffset(const CLRelAbsVector& x)
{
  this->setX(x);
}

/**
 * Sets the y offset.
 */
void
CLRenderPoint::setYOffset(const CLRelAbsVector& y)
{
  this->setY(y);
}

/**
 * Sets the z offset.
 */
void
CLRenderPoint::setZOffset(const CLRelAbsVector& z)
{
  this->setZ(z);
}

/**
 * Sets the x offset.
 */
void
CLRenderPoint::setX(const CLRelAbsVector& x)
{
  this->mXOffset = x;
}

/**
 * Sets the y offset.
 */
void
CLRenderPoint::setY(const CLRelAbsVector& y)
{
  this->mYOffset = y;
}

/**
 * Sets the z offset.
 */
void
CLRenderPoint::setZ(const CLRelAbsVector& z)
{
  this->mZOffset = z;
}

/**
 * Returns the x offset.
 */
const CLRelAbsVector&
CLRenderPoint::getXOffset() const
{
  return this->x();
}

/**
 * Returns the y offset.
 */
const CLRelAbsVector&
CLRenderPoint::getYOffset() const
{
  return this->y();
}

/**
 * Returns the z offset.
 */
const CLRelAbsVector&
CLRenderPoint::getZOffset() const
{
  return this->z();
}

/**
 * Returns the x offset.
 */
const CLRelAbsVector&
CLRenderPoint::x() const
{
  return this->mXOffset;
}

/**
 * Returns the y offset.
 */
const CLRelAbsVector&
CLRenderPoint::y() const
{
  return this->mYOffset;
}

/**
 * Returns the z offset.
 */
const CLRelAbsVector&
CLRenderPoint::z() const
{
  return this->mZOffset;
}

/**
 * Returns the x offset.
 */
CLRelAbsVector&
CLRenderPoint::getXOffset()
{
  return this->x();
}

/**
 * Returns the y offset.
 */
CLRelAbsVector&
CLRenderPoint::getYOffset()
{
  return this->y();
}

/**
 * Returns the z offset.
 */
CLRelAbsVector&
CLRenderPoint::getZOffset()
{
  return this->z();
}

/**
 * Returns the x offset.
 */
CLRelAbsVector&
CLRenderPoint::x()
{
  return this->mXOffset;
}

/**
 * Returns the y offset.
 */
CLRelAbsVector&
CLRenderPoint::y()
{
  return this->mYOffset;
}

/**
 * Returns the z offset.
 */
CLRelAbsVector&
CLRenderPoint::z()
{
  return this->mZOffset;
}

/**
 * Comparison operator.
 */
bool CLRenderPoint::operator==(const CLRenderPoint& left)
{
  return (this->mXOffset == left.mXOffset && this->mYOffset == left.mYOffset && this->mZOffset == left.mZOffset);
}

/**
 * Converts this object to the corresponding SBML object.
 */
RenderPoint* CLRenderPoint::toSBML(unsigned int level, unsigned int version) const
{
  RenderPoint* pP = new RenderPoint(level, version);
  this->addSBMLAttributes(pP);
  return pP;
}

/**
 * Adds the attributes for a render point object to the passed in.
 * object.
 */
void CLRenderPoint::addSBMLAttributes(RenderPoint* pPoint) const
{
  RelAbsVector* pV1 = this->mXOffset.toSBML();
  RelAbsVector* pV2 = this->mYOffset.toSBML();
  RelAbsVector* pV3 = this->mZOffset.toSBML();
  pPoint->setCoordinates(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
}
