// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/RenderCubicBezier.h>

#include "CLRenderCubicBezier.h"

/**
 * Creates a CLRenderCubicBezier and returns the pointer.
 */
CLRenderCubicBezier::CLRenderCubicBezier(): CLRenderPoint()
{
  mBasePoint1_X = mXOffset;
  mBasePoint1_Y = mYOffset;
  mBasePoint1_Z = mZOffset;
  mBasePoint2_X = mXOffset;
  mBasePoint2_Y = mYOffset;
  mBasePoint2_Z = mZOffset;
}

/**
 * Creates a CubicBezier with the given points and returns the pointer.
 */
CLRenderCubicBezier::CLRenderCubicBezier(const CLRelAbsVector& bp1_x, const CLRelAbsVector& bp1_y, const CLRelAbsVector& bp1_z, const CLRelAbsVector& bp2_x, const CLRelAbsVector& bp2_y, const CLRelAbsVector& bp2_z, const CLRelAbsVector& end_x, const CLRelAbsVector& end_y, const CLRelAbsVector& end_z): CLRenderPoint(end_x, end_y, end_z),
  mBasePoint1_X(bp1_x),
  mBasePoint1_Y(bp1_y),
  mBasePoint1_Z(bp1_z),
  mBasePoint2_X(bp2_x),
  mBasePoint2_Y(bp2_y),
  mBasePoint2_Z(bp2_z)
{
}

/**
 * Copy constructor.
 */
CLRenderCubicBezier::CLRenderCubicBezier(const CLRenderCubicBezier& orig):
  CLRenderPoint(orig),
  mBasePoint1_X(orig.mBasePoint1_X),
  mBasePoint1_Y(orig.mBasePoint1_Y),
  mBasePoint1_Z(orig.mBasePoint1_Z),
  mBasePoint2_X(orig.mBasePoint2_X),
  mBasePoint2_Y(orig.mBasePoint2_Y),
  mBasePoint2_Z(orig.mBasePoint2_Z)
{
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLRenderCubicBezier::CLRenderCubicBezier(const RenderCubicBezier& source):
  CLRenderPoint(source),
  mBasePoint1_X(source.basePoint1_X()),
  mBasePoint1_Y(source.basePoint1_Y()),
  mBasePoint1_Z(source.basePoint1_Z()),
  mBasePoint2_X(source.basePoint2_X()),
  mBasePoint2_Y(source.basePoint2_Y()),
  mBasePoint2_Z(source.basePoint2_Z())
{
}

/**
 * Assignment operator.
 */
CLRenderCubicBezier& CLRenderCubicBezier::operator=(const CLRenderCubicBezier & orig)
{
  if (&orig != this)
    {
      this->CLRenderPoint::operator=(orig);
      mBasePoint1_X = orig.mBasePoint1_X;
      mBasePoint1_Y = orig.mBasePoint1_Y;
      mBasePoint1_Z = orig.mBasePoint1_Z;
      mBasePoint2_X = orig.mBasePoint2_X;
      mBasePoint2_Y = orig.mBasePoint2_Y;
      mBasePoint2_Z = orig.mBasePoint2_Z;
    }

  return *this;
}

/**
 * Destructor.
 */
CLRenderCubicBezier::~CLRenderCubicBezier()
{
}

/**
 * Returns the x value of the first base point of the curve (the one closer to the
 * starting point).
 */
const CLRelAbsVector& CLRenderCubicBezier::basePoint1_X() const
{
  return this->mBasePoint1_X;
}

/**
 * Returns the y value of the first base point of the curve (the one closer to the
 * starting point).
 */
const CLRelAbsVector& CLRenderCubicBezier::basePoint1_Y() const
{
  return this->mBasePoint1_Y;
}

/**
 * Returns the z value of the first base point of the curve (the one closer to the
 * starting point).
 */
const CLRelAbsVector& CLRenderCubicBezier::basePoint1_Z() const
{
  return this->mBasePoint1_Z;
}

/**
 * Returns the x value of the second base point of the curve (the one closer to the
 * end point).
 */
const CLRelAbsVector& CLRenderCubicBezier::basePoint2_X() const
{
  return this->mBasePoint2_X;
}

/**
 * Returns the y value of the second base point of the curve (the one closer to the
 * end point).
 */
const CLRelAbsVector& CLRenderCubicBezier::basePoint2_Y() const
{
  return this->mBasePoint2_Y;
}

/**
 * Returns the z value of the second base point of the curve (the one closer to the
 * end point).
 */
const CLRelAbsVector& CLRenderCubicBezier::basePoint2_Z() const
{
  return this->mBasePoint2_Z;
}

/**
 * Returns the x value of the first base point of the curve (the one closer to the
 * starting point).
 */
CLRelAbsVector& CLRenderCubicBezier::basePoint1_X()
{
  return this->mBasePoint1_X;
}

/**
 * Returns the y value of the first base point of the curve (the one closer to the
 * starting point).
 */
CLRelAbsVector& CLRenderCubicBezier::basePoint1_Y()
{
  return this->mBasePoint1_Y;
}

/**
 * Returns the z value of the first base point of the curve (the one closer to the
 * starting point).
 */
CLRelAbsVector& CLRenderCubicBezier::basePoint1_Z()
{
  return this->mBasePoint1_Z;
}

/**
 * Returns the x value of the second base point of the curve (the one closer to the
 * end point).
 */
CLRelAbsVector& CLRenderCubicBezier::basePoint2_X()
{
  return this->mBasePoint2_X;
}

/**
 * Returns the y value of the second base point of the curve (the one closer to the
 * end point).
 */
CLRelAbsVector& CLRenderCubicBezier::basePoint2_Y()
{
  return this->mBasePoint2_Y;
}

/**
 * Returns the z value of the second base point of the curve (the one closer to the
 * end point).
 */
CLRelAbsVector& CLRenderCubicBezier::basePoint2_Z()
{
  return this->mBasePoint2_Z;
}

/**
 * Sets the x value of the first base point of the curve (the one closer to the
 * starting point).
 */
void CLRenderCubicBezier::setBasePoint1_X(const CLRelAbsVector& v)
{
  this->mBasePoint1_X = v;;
}

/**
 * Sets the y value of the first base point of the curve (the one closer to the
 * starting point).
 */
void CLRenderCubicBezier::setBasePoint1_Y(const CLRelAbsVector& v)
{
  this->mBasePoint1_Y = v;
}

/**
 * Sets the z value of the first base point of the curve (the one closer to the
 * starting point).
 */
void CLRenderCubicBezier::setBasePoint1_Z(const CLRelAbsVector& v)
{
  this->mBasePoint1_Z = v;
}

/**
 * Sets the x value of the second base point of the curve (the one closer to the
 * end point).
 */
void CLRenderCubicBezier::setBasePoint2_X(const CLRelAbsVector& v)
{
  this->mBasePoint2_X = v;
}

/**
 * Sets the y value of the second base point of the curve (the one closer to the
 * end point).
 */
void CLRenderCubicBezier::setBasePoint2_Y(const CLRelAbsVector& v)
{
  this->mBasePoint2_Y = v;
}

/**
 * Sets the z value of the second base point of the curve (the one closer to the
 * end point).
 */
void CLRenderCubicBezier::setBasePoint2_Z(const CLRelAbsVector& v)
{
  this->mBasePoint2_Z = v;
}

/**
 * Sets the first basepoint to the given values.
 */
void CLRenderCubicBezier::setBasePoint1(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mBasePoint1_X = x;
  this->mBasePoint1_Y = y;
  this->mBasePoint1_Z = z;
}

/**
 * Sets the second basepoint to the given values.
 */
void CLRenderCubicBezier::setBasePoint2(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z)
{
  this->mBasePoint2_X = x;
  this->mBasePoint2_Y = y;
  this->mBasePoint2_Z = z;
}

/**
 * Converts this object to the corresponding SBML object.
 */
RenderPoint * CLRenderCubicBezier::toSBML(unsigned int level, unsigned int version) const
{
  RenderCubicBezier* pCB = new RenderCubicBezier(level, version);
  this->addSBMLAttributes(pCB);
  RelAbsVector* pV1 = this->mBasePoint1_X.toSBML();
  RelAbsVector* pV2 = this->mBasePoint1_Y.toSBML();
  RelAbsVector* pV3 = this->mBasePoint1_Z.toSBML();
  pCB->setBasePoint1(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
  pV1 = this->mBasePoint2_X.toSBML();
  pV2 = this->mBasePoint2_Y.toSBML();
  pV3 = this->mBasePoint2_Z.toSBML();
  pCB->setBasePoint2(*pV1, *pV2, *pV3);
  delete pV1;
  delete pV2;
  delete pV3;
  return pCB;
}
