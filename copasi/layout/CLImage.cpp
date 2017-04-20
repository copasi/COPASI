// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/packages/render/sbml/Image.h>

#include "CLImage.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLImage::CLImage(CDataContainer* pParent):
  CLTransformation2D(),
  CDataObject("Image", pParent),
  mX(CLRelAbsVector(0.0, 0.0)),
  mY(CLRelAbsVector(0.0, 0.0)),
  mZ(CLRelAbsVector(0.0, 0.0)),
  mWidth(CLRelAbsVector(0.0, 0.0)),
  mHeight(CLRelAbsVector(0.0, 0.0)),
  mHRef(""),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Image", this);
}

/**
 * Copy Constructor.
 */
CLImage::CLImage(const CLImage& source, CDataContainer* pParent):
  CLTransformation2D(source),
  CDataObject(source, pParent),
  mX(source.mX),
  mY(source.mY),
  mZ(source.mZ),
  mWidth(source.mWidth),
  mHeight(source.mHeight),
  mHRef(source.mHRef),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Image", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLImage::CLImage(const Image& source, CDataContainer* pParent):
  CLTransformation2D(source),
  CDataObject("Image", pParent),
  mX(source.getX()),
  mY(source.getY()),
  mZ(source.getZ()),
  mWidth(source.getWidth()),
  mHeight(source.getHeight()),
  mHRef(source.getImageReference()),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Image", this);
}

/**
 * Destructor
 */
CLImage::~CLImage()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Sets the dimensions.
 */
void CLImage::setDimensions(const CLRelAbsVector& width, const CLRelAbsVector& height)
{
  this->mWidth = width;
  this->mHeight = height;
}

/**
 * Sets the width.
 */
void CLImage::setWidth(const CLRelAbsVector& width)
{
  this->mWidth = width;
}

/**
 * Sets the height.
 */
void CLImage::setHeight(const CLRelAbsVector& height)
{
  this->mHeight = height;
}

/**
 * Returns the width.
 */
const CLRelAbsVector& CLImage::getWidth() const
{
  return this->mWidth;
}

/**
 * Returns the height.
 */
const CLRelAbsVector& CLImage::getHeight() const
{
  return this->mHeight;
}

/**
 * Sets the reference to the image location.
 */
void CLImage::setImageReference(const std::string& ref)
{
  this->mHRef = ref;
}

/**
 * Returns the image reference.
 */
const std::string& CLImage::getImageReference() const
{
  return this->mHRef;
}

/**
 * Sets the coordinates.
 */
void CLImage::setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mX = x;
  this->mY = y;
  this->mZ = z;
}

/**
 * Sets the x coordinate.
 */
void CLImage::setX(const CLRelAbsVector& coord)
{
  this->mX = coord;
}

/**
 * Sets the y coordinate.
 */
void CLImage::setY(const CLRelAbsVector& coord)
{
  this->mY = coord;
}

/**
 * Sets the z coordinate.
 */
void CLImage::setZ(const CLRelAbsVector& coord)
{
  this->mZ = coord;
}

/**
 * Returns the x coordinate.
 */
const CLRelAbsVector& CLImage::getX() const
{
  return this->mX;
}

/**
 * Returns the y coordinate.
 */
const CLRelAbsVector& CLImage::getY() const
{
  return this->mY;
}

/**
 * Returns the z coordinate.
 */
const CLRelAbsVector& CLImage::getZ() const
{
  return this->mZ;
}

/**
 * Returns the x coordinate.
 */
CLRelAbsVector& CLImage::getX()
{
  return this->mX;
}

/**
 * Returns the y coordinate.
 */
CLRelAbsVector& CLImage::getY()
{
  return this->mY;
}

/**
 * Returns the z coordinate.
 */
CLRelAbsVector& CLImage::getZ()
{
  return this->mZ;
}

/**
 * Returns true if the image reference has been set.
 */
bool CLImage::isSetImageReference() const
{
  std::string space = " \t\n\r";
  // the string may not be empty and it may not only contain whitespaces
  return (!this->mHRef.empty() && (this->mHRef.find_first_not_of(space) != std::string::npos));
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLImage::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
Image* CLImage::toSBML(unsigned int level, unsigned int version) const
{
  Image* pImg = new Image(level, version);
  this->addSBMLAttributes(pImg);
  RelAbsVector* pV = this->mX.toSBML();
  pImg->setX(*pV);
  delete pV;
  pV = this->mY.toSBML();
  pImg->setY(*pV);
  delete pV;
  pV = this->mZ.toSBML();
  pImg->setZ(*pV);
  delete pV;
  pV = this->mWidth.toSBML();
  pImg->setWidth(*pV);
  delete pV;
  pV = this->mHeight.toSBML();
  pImg->setHeight(*pV);
  delete pV;
  pImg->setImageReference(this->mHRef);
  return pImg;
}
