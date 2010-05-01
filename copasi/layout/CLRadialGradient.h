// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRadialGradient.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/05/01 14:35:04 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRadialGradient_H__
#define CLRadialGradient_H__

#include <copasi/layout/CLGradientBase.h>
#include <copasi/layout/CLRelAbsVector.h>

#include <string>

#include <sbml/layout/render/RadialGradient.h>

class CCopasiContainer;

class CLRadialGradient : public CLGradientBase
{
private:
  // prevent the compiler from generating the assignment operator
  CLRadialGradient& operator=(const CLRadialGradient& source);

protected:
  CLRelAbsVector mCX;
  CLRelAbsVector mCY;
  CLRelAbsVector mCZ;
  CLRelAbsVector mRadius;
  CLRelAbsVector mFX;
  CLRelAbsVector mFY;
  CLRelAbsVector mFZ;

public:
  /**
   * Constructor.
   */
  CLRadialGradient(CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLRadialGradient(const CLRadialGradient& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLRadialGradient(const RadialGradient& source, CCopasiContainer* pParent = NULL);

  /**
   * Sets the 3D coordinates for the center and the focal
   * point as well as the radius.
   */
  void setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, const CLRelAbsVector& r, const CLRelAbsVector& fx, const CLRelAbsVector& fy, const CLRelAbsVector& fz);

  /**
   * Sets the 2D coordinates for center and the focal point as well as
   * the radius.
   */
  void setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& r, const CLRelAbsVector& fx, const CLRelAbsVector& fy);

  /**
   * Sets the coordinates for the first point.
   */
  void setCenter(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0));

  /**
   * Sets the coordinates for the second point.
   */
  void setFocalPoint(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0));

  /**
   * Sets the radius.
   */
  void setRadius(const CLRelAbsVector& r);

  /**
   * Returns the x coordinate for the center point.
   */
  const CLRelAbsVector& getCenterX() const;

  /**
   * Returns the y coordinate for the center point.
   */
  const CLRelAbsVector& getCenterY() const;

  /**
   * Returns the z coordinate for the center point.
   */
  const CLRelAbsVector& getCenterZ() const;

  /**
   * Returns the x coordinate for the focal point.
   */
  const CLRelAbsVector& getFocalPointX() const;

  /**
   * Returns the x coordinate for the focal point.
   */
  const CLRelAbsVector& getFocalPointY() const;

  /**
   * Returns the x coordinate for the focal point.
   */
  const CLRelAbsVector& getFocalPointZ() const;

  /**
   * Returns the radius.
   */
  const CLRelAbsVector& getRadius() const;

  /**
   * Returns the x coordinate for the center point.
   */
  CLRelAbsVector& getCenterX();

  /**
   * Returns the y coordinate for the center point.
   */
  CLRelAbsVector& getCenterY();

  /**
   * Returns the z coordinate for the center point.
   */
  CLRelAbsVector& getCenterZ();

  /**
   * Returns the x coordinate for the focal point.
   */
  CLRelAbsVector& getFocalPointX();

  /**
   * Returns the x coordinate for the focal point.
   */
  CLRelAbsVector& getFocalPointY();

  /**
   * Returns the x coordinate for the focal point.
   */
  CLRelAbsVector& getFocalPointZ();

  /**
   * Returns the radius.
   */
  CLRelAbsVector& getRadius();

  /**
   * Converts this object to the corresponding SBML object.
   */
  virtual RadialGradient* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLRadialGradient_H__ */
