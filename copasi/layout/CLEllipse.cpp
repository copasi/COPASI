// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string>

#include <sbml/packages/render/sbml/Ellipse.h>

#define sbmlEllipse Ellipse

#include "CLEllipse.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLEllipse::CLEllipse(CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Ellipse", pParent),
  mCX(0.0),
  mCY(0.0),
  mCZ(0.0),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Ellipse", this);
  setRadii(0.0, 0.0);
}

/**
 * Constructor with 2D center and radius.
 */
CLEllipse::CLEllipse(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& r, CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Ellipse", pParent),
  mCX(cx),
  mCY(cy),
  mCZ(0.0),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Ellipse", this);
  setRadii(r, r);
}

/**
 * Constructor with 2D center and radii.
 */
CLEllipse::CLEllipse(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& rx, const CLRelAbsVector& ry, CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Ellipse", pParent),
  mCX(cx),
  mCY(cy),
  mCZ(CLRelAbsVector(0.0, 50.0)),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Ellipse", this);
  setRadii(rx, ry);
}

/**
 * Constructor with 3D center and radii.
 */
CLEllipse::CLEllipse(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& cz, const CLRelAbsVector& rx, const CLRelAbsVector& ry, CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Ellipse", pParent),
  mCX(cx),
  mCY(cy),
  mCZ(cz),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Ellipse", this);
  setRadii(rx, ry);
}

/**
 * Copy Constructor
 */
CLEllipse::CLEllipse(const CLEllipse& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataObject(source, pParent),
  mCX(source.mCX),
  mCY(source.mCY),
  mCZ(source.mCZ),
  mRX(source.mRX),
  mRY(source.mRY),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Ellipse", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLEllipse::CLEllipse(const Ellipse& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataObject("Ellipse", pParent),
  mCX(source.getCX()),
  mCY(source.getCY()),
  mCZ(source.getCZ()),
  mRX(source.getRX()),
  mRY(source.getRY()),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Ellipse", this);
}

/**
 * Destructor
 */
CLEllipse::~CLEllipse()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Returns the x component of the center.
 */
const CLRelAbsVector& CLEllipse::getCX() const
{
  return this->mCX;
}

/**
 * Returns the y component of the center.
 */
const CLRelAbsVector& CLEllipse::getCY() const
{
  return this->mCY;
}

/**
 * Returns the z component of the center.
 */
const CLRelAbsVector& CLEllipse::getCZ() const
{
  return this->mCZ;
}

/**
 * Returns the radius along the x axis.
 */
const CLRelAbsVector& CLEllipse::getRX() const
{
  return this->mRX;
}

/**
 * Returns the radius along the y axis.
 */
const CLRelAbsVector& CLEllipse::getRY() const
{
  return this->mRY;
}

/**
 * Returns the x component of the center.
 */
CLRelAbsVector& CLEllipse::getCX()
{
  return this->mCX;
}

/**
 * Returns the y component of the center.
 */
CLRelAbsVector& CLEllipse::getCY()
{
  return this->mCY;
}

/**
 * Returns the z component of the center.
 */
CLRelAbsVector& CLEllipse::getCZ()
{
  return this->mCZ;
}

/**
 * Returns the radius along the x axis.
 */
CLRelAbsVector& CLEllipse::getRX()
{
  return this->mRX;
}

/**
 * Returns the radius along the y axis.
 */
CLRelAbsVector& CLEllipse::getRY()
{
  return this->mRY;
}

/**
 * Sets the x component of the center.
 */
void CLEllipse::setCX(const CLRelAbsVector& cx)
{
  this->mCX = cx;
}

/**
 * Sets the y component of the center.
 */
void CLEllipse::setCY(const CLRelAbsVector& cy)
{
  this->mCY = cy;
}

/**
 * Sets the z component of the center.
 */
void CLEllipse::setCZ(const CLRelAbsVector& cz)
{
  this->mCZ = cz;
}

/**
 * Sets the radius along the x axis.
 */
void CLEllipse::setRX(const CLRelAbsVector& rx)
{
  this->mRX = rx;
}

/**
 * Sets the radius along the y axis.
 */
void CLEllipse::setRY(const CLRelAbsVector& ry)
{
  this->mRY = ry;
}

/**
 * Sets the 2D center.
 */
void CLEllipse::setCenter2D(const CLRelAbsVector& cx, const CLRelAbsVector& cy)
{
  this->mCX = cx;
  this->mCY = cy;
  this->mCZ = CLRelAbsVector(0.0, 50.0);
}

/**
 * Sets the 3D center.
 */
void CLEllipse::setCenter3D(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& cz)
{
  this->mCX = cx;
  this->mCY = cy;
  this->mCZ = cz;
}

/**
 * Sets the radii.
 */
void CLEllipse::setRadii(const CLRelAbsVector& rx, const CLRelAbsVector& ry)
{
  this->mRX = rx;
  this->mRY = ry;
}

/**
 * Returns the key of the render information
 */
const std::string& CLEllipse::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
Ellipse* CLEllipse::toSBML(unsigned int level, unsigned int version) const
{
  Ellipse* pE = new Ellipse(level, version);
  this->addSBMLAttributes(pE);
  RelAbsVector* pV = this->getCX().toSBML();
  pE->setCX(*pV);
  delete pV;
  pV = this->getCY().toSBML();
  pE->setCY(*pV);
  delete pV;
  pV = this->getCZ().toSBML();
  pE->setCZ(*pV);
  delete pV;
  pV = this->getRX().toSBML();
  pE->setRX(*pV);
  delete pV;
  pV = this->getRY().toSBML();
  pE->setRY(*pV);
  delete pV;
  return pE;
}
