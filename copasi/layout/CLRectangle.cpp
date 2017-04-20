// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/packages/render/sbml/Rectangle.h>

#define sbmlRectangle Rectangle
#include "CLRectangle.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLRectangle::CLRectangle(CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Rectangle", pParent),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Rectangle", this);
}

/**
 * Copy Constructor.
 */
CLRectangle::CLRectangle(const CLRectangle& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataObject(source, pParent),
  mX(source.mX),
  mY(source.mY),
  mZ(source.mZ),
  mWidth(source.mWidth),
  mHeight(source.mHeight),
  mRX(source.mRX),
  mRY(source.mRY),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Rectangle", this);
}

/**
 * Constructor that takes an id, the x, y and z coordinate values, the width and the
 * height.
 */
CLRectangle::CLRectangle(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, const CLRelAbsVector& w, const CLRelAbsVector& h, CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Rectangle", pParent),
  mX(x),
  mY(y),
  mZ(z),
  mWidth(w),
  mHeight(h),
  mRX(CLRelAbsVector(0.0, 0.0)),
  mRY(CLRelAbsVector(0.0, 0.0)),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Rectangle", this);
}

/**
 * Constructor that takes an id, x and y coordinate values, the width and the
 * height.
 */
CLRectangle::CLRectangle(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& w, const CLRelAbsVector& h, CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Rectangle", pParent),
  mX(x),
  mY(y),
  mZ(CLRelAbsVector(0.0, 0.0)),
  mWidth(w),
  mHeight(h),
  mRX(CLRelAbsVector(0.0, 0.0)),
  mRY(CLRelAbsVector(0.0, 0.0)),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Rectangle", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLRectangle::CLRectangle(const Rectangle& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataObject("Rectangle", pParent),
  mX(source.getX()),
  mY(source.getY()),
  mZ(source.getZ()),
  mWidth(source.getWidth()),
  mHeight(source.getHeight()),
  mRX(source.getRadiusX()),
  mRY(source.getRadiusY()),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Rectangle", this);
}

/**
 * Destructor
 */
CLRectangle::~CLRectangle()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Sets the position, the width and the height.
 */
void CLRectangle::setCoordinatesAndSize(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, const CLRelAbsVector& w, const CLRelAbsVector& h)
{
  this->setCoordinates(x, y, z);
  this->setSize(w, h);
}

/**
 * Sets the position.
 */
void CLRectangle::setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mX = x;
  this->mY = y;
  this->mZ = z;
}

/**
 * Sets the size.
 */
void CLRectangle::setSize(const CLRelAbsVector& w, const CLRelAbsVector& h)
{
  this->mWidth = w;
  this->mHeight = h;
}

/**
 * Sets the size.
 */
void CLRectangle::setRadii(const CLRelAbsVector& rx, const CLRelAbsVector& ry)
{
  this->mRX = rx;
  this->mRY = ry;
}

/**
 * Returns the x coordinate.
 */
const CLRelAbsVector& CLRectangle::getX() const
{
  return this->mX;
}

/**
 * Returns the y coordinate.
 */
const CLRelAbsVector& CLRectangle::getY() const
{
  return this->mY;
}

/**
 * Returns the z coordinate.
 */
const CLRelAbsVector& CLRectangle::getZ() const
{
  return this->mZ;
}

/**
 * Returns the width.
 */
const CLRelAbsVector& CLRectangle::getWidth() const
{
  return this->mWidth;
}

/**
 * Returns the height.
 */
const CLRelAbsVector& CLRectangle::getHeight() const
{
  return this->mHeight;
}

/**
 * Returns the corner radius along th x axis.
 */
const CLRelAbsVector& CLRectangle::getRadiusX() const
{
  return this->mRX;
}

/**
 * Returns the corner radius along the y axis.
 */
const CLRelAbsVector& CLRectangle::getRadiusY() const
{
  return this->mRY;
}

/**
 * Returns the x coordinate.
 */
CLRelAbsVector& CLRectangle::getX()
{
  return this->mX;
}

/**
 * Returns the y coordinate.
 */
CLRelAbsVector& CLRectangle::getY()
{
  return this->mY;
}

/**
 * Returns the z coordinate.
 */
CLRelAbsVector& CLRectangle::getZ()
{
  return this->mZ;
}

/**
 * Returns the width.
 */
CLRelAbsVector& CLRectangle::getWidth()
{
  return this->mWidth;
}

/**
 * Returns the height.
 */
CLRelAbsVector& CLRectangle::getHeight()
{
  return this->mHeight;
}

/**
 * Returns the corner radius along th x axis.
 */
CLRelAbsVector& CLRectangle::getRadiusX()
{
  return this->mRX;
}

/**
 * Returns the corner radius along the y axis.
 */
CLRelAbsVector& CLRectangle::getRadiusY()
{
  return this->mRY;
}

/**
 * Sets the width.
 */
void CLRectangle::setWidth(const CLRelAbsVector& w)
{
  this->mWidth = w;
}

/**
 * Sets the height.
 */
void CLRectangle::setHeight(const CLRelAbsVector& h)
{
  this->mHeight = h;
}

/**
 * Sets the x radius for the corners.
 */
void CLRectangle::setRadiusX(const CLRelAbsVector& rx)
{
  this->mRX = rx;
}

/**
 * Sets the y radius for the corners.
 */
void CLRectangle::setRadiusY(const CLRelAbsVector& ry)
{
  this->mRY = ry;
}

/**
 * Sets the x position.
 */
void CLRectangle::setX(const CLRelAbsVector& x)
{
  this->mX = x;
}

/**
 * Sets the y position.
 */
void CLRectangle::setY(const CLRelAbsVector& y)
{
  this->mY = y;
}

/**
 * Sets the z position.
 */
void CLRectangle::setZ(const CLRelAbsVector& z)
{
  this->mZ = z;
}

/**
 * Returns the key of the rectangle
 */
const std::string& CLRectangle::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
Rectangle* CLRectangle::toSBML(unsigned int level, unsigned int version) const
{
  Rectangle* pRectangle = new Rectangle(level, version);
  RelAbsVector* pV1 = this->mX.toSBML();
  RelAbsVector* pV2 = this->mY.toSBML();
  RelAbsVector* pV3 = this->mZ.toSBML();
  RelAbsVector* pV4 = this->mWidth.toSBML();
  RelAbsVector* pV5 = this->mHeight.toSBML();
  pRectangle->setCoordinatesAndSize(*pV1, *pV2, *pV3, *pV4, *pV5);
  delete pV1;
  delete pV2;
  delete pV3;
  delete pV4;
  delete pV5;
  this->addSBMLAttributes(pRectangle);
  pV1 = this->mRX.toSBML();
  pV2 = this->mRY.toSBML();
  pRectangle->setRadii(*pV1, *pV2);
  delete pV1;
  delete pV2;
  return pRectangle;
}
