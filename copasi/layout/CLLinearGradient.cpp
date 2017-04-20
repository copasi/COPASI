// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/packages/render/sbml/LinearGradient.h>

#include "CLLinearGradient.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLLinearGradient::CLLinearGradient(CDataContainer* pParent)
  : CLGradientBase("LinearGradient", pParent),
    mX1(CLRelAbsVector(0.0, 0.0)),
    mY1(CLRelAbsVector(0.0, 0.0)),
    mZ1(CLRelAbsVector(0.0, 0.0)),
    mX2(CLRelAbsVector(0.0, 100.0)),
    mY2(CLRelAbsVector(0.0, 100.0)),
    mZ2(CLRelAbsVector(0.0, 100.0))
{
  this->mKey = CRootContainer::getKeyFactory()->add("LinearGradient", this);
}

/**
 * Copy Constructor
 */
CLLinearGradient::CLLinearGradient(const CLLinearGradient& source, CDataContainer* pParent):
  CLGradientBase(source, pParent),
  mX1(source.mX1),
  mY1(source.mY1),
  mZ1(source.mZ1),
  mX2(source.mX2),
  mY2(source.mY2),
  mZ2(source.mZ2)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LinearGradient", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLLinearGradient::CLLinearGradient(const LinearGradient& source, CDataContainer* pParent):
  CLGradientBase(source, "LinearGradient", pParent),
  mX1(source.getXPoint1()),
  mY1(source.getYPoint1()),
  mZ1(source.getZPoint1()),
  mX2(source.getXPoint2()),
  mY2(source.getYPoint2()),
  mZ2(source.getZPoint2())
{
  this->mKey = CRootContainer::getKeyFactory()->add("LinearGradient", this);
}

/**
 * Sets the 3D coordinates for both points.
 */
void CLLinearGradient::setCoordinates(const CLRelAbsVector& x1, const CLRelAbsVector& y1, const CLRelAbsVector& z1, const CLRelAbsVector& x2, const CLRelAbsVector& y2, const CLRelAbsVector& z2)
{
  this->setPoint1(x1, y1, z1);
  this->setPoint2(x2, y2, z2);
}

/**
 * Sets the 3D coordinates for both points.
 */
void CLLinearGradient::setCoordinates(const CLRelAbsVector& x1, const CLRelAbsVector& y1, const CLRelAbsVector& x2, const CLRelAbsVector& y2)
{
  this->setCoordinates(x1, y1, CLRelAbsVector(0.0, 0.0), x2, y2, CLRelAbsVector(0.0, 100.0));
}

/**
 * Sets the coordinates for the first point.
 */
void CLLinearGradient::setPoint1(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mX1 = x;
  this->mY1 = y;
  this->mZ1 = z;
}

/**
 * Sets the coordinates for the second point.
 */
void CLLinearGradient::setPoint2(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mX2 = x;
  this->mY2 = y;
  this->mZ2 = z;
}

/**
 * Returns the x coordinate for the first point.
 */
const CLRelAbsVector& CLLinearGradient::getXPoint1() const
{
  return this->mX1;
}

/**
 * Returns the x coordinate for the first point.
 */
const CLRelAbsVector& CLLinearGradient::getYPoint1() const
{
  return this->mY1;
}

/**
 * Returns the x coordinate for the first point.
 */
const CLRelAbsVector& CLLinearGradient::getZPoint1() const
{
  return this->mZ1;
}

/**
 * Returns the x coordinate for the second point.
 */
const CLRelAbsVector& CLLinearGradient::getXPoint2() const
{
  return this->mX2;
}

/**
 * Returns the x coordinate for the second point.
 */
const CLRelAbsVector& CLLinearGradient::getYPoint2() const
{
  return this->mY2;
}

/**
 * Returns the x coordinate for the second point.
 */
const CLRelAbsVector& CLLinearGradient::getZPoint2() const
{
  return this->mZ2;
}

/**
 * Returns the x coordinate for the first point.
 */
CLRelAbsVector& CLLinearGradient::getXPoint1()
{
  return this->mX1;
}

/**
 * Returns the x coordinate for the first point.
 */
CLRelAbsVector& CLLinearGradient::getYPoint1()
{
  return this->mY1;
}

/**
 * Returns the x coordinate for the first point.
 */
CLRelAbsVector& CLLinearGradient::getZPoint1()
{
  return this->mZ1;
}

/**
 * Returns the x coordinate for the second point.
 */
CLRelAbsVector& CLLinearGradient::getXPoint2()
{
  return this->mX2;
}

/**
 * Returns the x coordinate for the second point.
 */
CLRelAbsVector& CLLinearGradient::getYPoint2()
{
  return this->mY2;
}

/**
 * Returns the x coordinate for the second point.
 */
CLRelAbsVector& CLLinearGradient::getZPoint2()
{
  return this->mZ2;
}

/**
 * Converts this object to the corresponding SBML object.
 */
LinearGradient* CLLinearGradient::toSBML(unsigned int level, unsigned int version) const
{
  LinearGradient* pLG = new LinearGradient(level, version);
  this->addSBMLAttributes(pLG);
  RelAbsVector* pV1 = this->getXPoint1().toSBML();
  RelAbsVector* pV2 = this->getYPoint1().toSBML();
  RelAbsVector* pV3 = this->getZPoint1().toSBML();
  pLG->setPoint1(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
  pV1 = this->getXPoint2().toSBML();
  pV2 = this->getYPoint2().toSBML();
  pV3 = this->getZPoint2().toSBML();
  pLG->setPoint2(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
  return pLG;
}
