// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLLinearGradient_H__
#define CLLinearGradient_H__

#include <string>

#include "copasi/layout/CLGradientBase.h"
#include "copasi/layout/CLRelAbsVector.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class LinearGradient;
LIBSBML_CPP_NAMESPACE_END

class CLLinearGradient : public CLGradientBase
{
private:
  // prevent the compiler from generating the assignment operator
  CLLinearGradient& operator=(const CLLinearGradient& source);

protected:
  CLRelAbsVector mX1;
  CLRelAbsVector mY1;
  CLRelAbsVector mZ1;
  CLRelAbsVector mX2;
  CLRelAbsVector mY2;
  CLRelAbsVector mZ2;

public:
  /**
   * Constructor.
   */
  CLLinearGradient(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor
   */
  CLLinearGradient(const CLLinearGradient& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLLinearGradient(const LinearGradient& source, CDataContainer* pParent = NULL);

  /**
   * Sets the 3D coordinates for both points.
   */
  void setCoordinates(const CLRelAbsVector& x1, const CLRelAbsVector& y1, const CLRelAbsVector& z1, const CLRelAbsVector& x2, const CLRelAbsVector& y2, const CLRelAbsVector& z2);

  /**
   * Sets the 3D coordinates for both points.
   */
  void setCoordinates(const CLRelAbsVector& x1, const CLRelAbsVector& y1, const CLRelAbsVector& x2, const CLRelAbsVector& y2);

  /**
   * Sets the coordinates for the first point.
   */
  void setPoint1(const CLRelAbsVector& x1, const CLRelAbsVector& y1, const CLRelAbsVector& z1 = CLRelAbsVector(0.0, 0.0));

  /**
   * Sets the coordinates for the second point.
   */
  void setPoint2(const CLRelAbsVector& x1, const CLRelAbsVector& y1, const CLRelAbsVector& z1 = CLRelAbsVector(0.0, 0.0));

  /**
   * Returns the x coordinate for the first point.
   */
  const CLRelAbsVector& getXPoint1() const;

  /**
   * Returns the y coordinate for the first point.
   */
  const CLRelAbsVector& getYPoint1() const;

  /**
   * Returns the z coordinate for the first point.
   */
  const CLRelAbsVector& getZPoint1() const;

  /**
   * Returns the x coordinate for the second point.
   */
  const CLRelAbsVector& getXPoint2() const;

  /**
   * Returns the y coordinate for the second point.
   */
  const CLRelAbsVector& getYPoint2() const;

  /**
   * Returns the z coordinate for the second point.
   */
  const CLRelAbsVector& getZPoint2() const;

  /**
   * Returns the x coordinate for the first point.
   */
  CLRelAbsVector& getXPoint1();

  /**
   * Returns the y coordinate for the first point.
   */
  CLRelAbsVector& getYPoint1();

  /**
   * Returns the z coordinate for the first point.
   */
  CLRelAbsVector& getZPoint1();

  /**
   * Returns the x coordinate for the second point.
   */
  CLRelAbsVector& getXPoint2();

  /**
   * Returns the y coordinate for the second point.
   */
  CLRelAbsVector& getYPoint2();

  /**
   * Returns the z coordinate for the second point.
   */
  CLRelAbsVector& getZPoint2();

  /**
   * Converts this object to the corresponding SBML object.
   */
  virtual LinearGradient* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLLinearGradient_H__ */
