// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRadialGradient.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CLRadialGradient.h"

#include <limits>

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLRadialGradient::CLRadialGradient(CCopasiContainer* pParent)
    : CLGradientBase("RadialGradient", pParent),
    mCX(CLRelAbsVector(0.0, 50.0)),
    mCY(CLRelAbsVector(0.0, 50.0)),
    mCZ(CLRelAbsVector(0.0, 50.0)),
    mRadius(CLRelAbsVector(0.0, 50.0)),
    mFX(CLRelAbsVector(0.0, 50.0)),
    mFY(CLRelAbsVector(0.0, 50.0)),
    mFZ(CLRelAbsVector(0.0, 50.0))
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("RadialGradient", this);
}

/**
 * Copy Constructor.
 */
CLRadialGradient::CLRadialGradient(const CLRadialGradient& source, CCopasiContainer* pParent):
    CLGradientBase(source, pParent),
    mCX(source.mCX),
    mCY(source.mCY),
    mCZ(source.mCZ),
    mRadius(source.mRadius),
    mFX(source.mFX),
    mFY(source.mFY),
    mFZ(source.mFZ)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("RadialGradient", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLRadialGradient::CLRadialGradient(const RadialGradient& source, CCopasiContainer* pParent):
    CLGradientBase(source, "RadialGradient", pParent),
    mCX(source.getCenterX()),
    mCY(source.getCenterY()),
    mCZ(source.getCenterZ()),
    mRadius(source.getRadius()),
    mFX(source.getFocalPointX()),
    mFY(source.getFocalPointY()),
    mFZ(source.getFocalPointZ())
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("RadialGradient", this);
}

/**
 * Sets the 3D coordinates for the center and the focal
 * point as well as the radius.
 */
void CLRadialGradient::setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, const CLRelAbsVector& r, const CLRelAbsVector& fx, const CLRelAbsVector& fy, const CLRelAbsVector& fz)
{
  this->setCenter(x, y, z);
  this->setRadius(r);
  this->setFocalPoint(fx, fy, fz);
}

/**
 * Sets the 2D coordinates for center and the focal point as well as
 * the radius.
 */
void CLRadialGradient::setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& r, const CLRelAbsVector& fx, const CLRelAbsVector& fy)
{
  this->setCoordinates(x, y, CLRelAbsVector(0.0, 50.0), r, fx, fy, CLRelAbsVector(0.0, 50.0));
}

/**
 * Sets the coordinates for the first point.
 */
void CLRadialGradient::setCenter(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mCX = x;
  this->mCY = y;
  this->mCZ = z;
}

/**
 * Sets the coordinates for the second point.
 */
void CLRadialGradient::setFocalPoint(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mFX = x;
  this->mFY = y;
  this->mFZ = z;
}

/**
 * Sets the radius.
 */
void CLRadialGradient::setRadius(const CLRelAbsVector& r)
{
  this->mRadius = r;
}

/**
 * Returns the x coordinate for the center point.
 */
const CLRelAbsVector& CLRadialGradient::getCenterX() const
{
  return this->mCX;
}

/**
 * Returns the y coordinate for the center point.
 */
const CLRelAbsVector& CLRadialGradient::getCenterY() const
{
  return this->mCY;
}

/**
 * Returns the z coordinate for the center point.
 */
const CLRelAbsVector& CLRadialGradient::getCenterZ() const
{
  return this->mCZ;
}

/**
 * Returns the x coordinate for the focal point.
 */
const CLRelAbsVector& CLRadialGradient::getFocalPointX() const
{
  return this->mFX;
}

/**
 * Returns the x coordinate for the focal point.
 */
const CLRelAbsVector& CLRadialGradient::getFocalPointY() const
{
  return this->mFY;
}

/**
 * Returns the x coordinate for the focal point.
 */
const CLRelAbsVector& CLRadialGradient::getFocalPointZ() const
{
  return this->mFZ;
}

/**
 * Returns the radius.
 */
const CLRelAbsVector& CLRadialGradient::getRadius() const
{
  return this->mRadius;
}

/**
 * Returns the x coordinate for the center point.
 */
CLRelAbsVector& CLRadialGradient::getCenterX()
{
  return this->mCX;
}

/**
 * Returns the y coordinate for the center point.
 */
CLRelAbsVector& CLRadialGradient::getCenterY()
{
  return this->mCY;
}

/**
 * Returns the z coordinate for the center point.
 */
CLRelAbsVector& CLRadialGradient::getCenterZ()
{
  return this->mCZ;
}

/**
 * Returns the x coordinate for the focal point.
 */
CLRelAbsVector& CLRadialGradient::getFocalPointX()
{
  return this->mFX;
}

/**
 * Returns the x coordinate for the focal point.
 */
CLRelAbsVector& CLRadialGradient::getFocalPointY()
{
  return this->mFY;
}

/**
 * Returns the x coordinate for the focal point.
 */
CLRelAbsVector& CLRadialGradient::getFocalPointZ()
{
  return this->mFZ;
}

/**
 * Returns the radius.
 */
CLRelAbsVector& CLRadialGradient::getRadius()
{
  return this->mRadius;
}

/**
 * Converts this object to the corresponding SBML object.
 */
RadialGradient* CLRadialGradient::toSBML() const
{
  RadialGradient* pRG = new RadialGradient();
  this->addSBMLAttributes(pRG);
  RelAbsVector* pV1 = this->getCenterX().toSBML();
  RelAbsVector* pV2 = this->getCenterY().toSBML();
  RelAbsVector* pV3 = this->getCenterZ().toSBML();
  pRG->setCenter(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
  pV1 = this->getFocalPointX().toSBML();
  pV2 = this->getFocalPointY().toSBML();
  pV3 = this->getFocalPointZ().toSBML();
  pRG->setFocalPoint(*pV1, *pV2, *pV3);
  pV1 = this->getRadius().toSBML();
  pRG->setRadius(*pV1);
  delete pV1;
  return pRG;
}
