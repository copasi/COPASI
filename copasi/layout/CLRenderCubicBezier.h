// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRenderCubicBezier.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:21 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRenderCubicBezier_H__
#define CLRenderCubicBezier_H__

#include <string>

#include "copasi/layout/CLRenderPoint.h"
#include "copasi/layout/CLRelAbsVector.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class RenderCubicBezier;
LIBSBML_CPP_NAMESPACE_END

class CLRenderCubicBezier : public CLRenderPoint
{
protected:
  CLRelAbsVector mBasePoint1_X;
  CLRelAbsVector mBasePoint1_Y;
  CLRelAbsVector mBasePoint1_Z;
  CLRelAbsVector mBasePoint2_X;
  CLRelAbsVector mBasePoint2_Y;
  CLRelAbsVector mBasePoint2_Z;

public:

  /**
   * Creates a CubicBezier and returns the pointer.
   */
  CLRenderCubicBezier();

  /**
   * Copy constructor.
   */
  CLRenderCubicBezier(const CLRenderCubicBezier& orig);

  /**
   * Creates a CubicBezier with the given points and returns the pointer.
   */
  CLRenderCubicBezier(const CLRelAbsVector& bp1_x, const CLRelAbsVector& bp1_y, const CLRelAbsVector& bp1_z, const CLRelAbsVector& bp2_x, const CLRelAbsVector& bp2_y, const CLRelAbsVector& bp2_z, const CLRelAbsVector& end_x, const CLRelAbsVector& end_y, const CLRelAbsVector& end_z);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLRenderCubicBezier(const RenderCubicBezier& source);

  /**
   * Destructor.
   */
  virtual ~CLRenderCubicBezier();

  /**
   * Assignment operator
   */
  virtual CLRenderCubicBezier& operator=(const CLRenderCubicBezier& orig);

  /**
   * Returns the x value of the first base point of the curve (the one closer to the
   * starting point).
   */
  const CLRelAbsVector& basePoint1_X() const;

  /**
   * Returns the y value of the first base point of the curve (the one closer to the
   * starting point).
   */
  const CLRelAbsVector& basePoint1_Y() const;

  /**
   * Returns the z value of the first base point of the curve (the one closer to the
   * starting point).
   */
  const CLRelAbsVector& basePoint1_Z() const;

  /**
   * Returns the x value of the second base point of the curve (the one closer to the
   * end point).
   */
  const CLRelAbsVector& basePoint2_X() const;

  /**
   * Returns the y value of the second base point of the curve (the one closer to the
   * end point).
   */
  const CLRelAbsVector& basePoint2_Y() const;

  /**
   * Returns the z value of the second base point of the curve (the one closer to the
   * end point).
   */
  const CLRelAbsVector& basePoint2_Z() const;

  /**
   * Returns the x value of the first base point of the curve (the one closer to the
   * starting point).
   */
  CLRelAbsVector& basePoint1_X();

  /**
   * Returns the y value of the first base point of the curve (the one closer to the
   * starting point).
   */
  CLRelAbsVector& basePoint1_Y();

  /**
   * Returns the z value of the first base point of the curve (the one closer to the
   * starting point).
   */
  CLRelAbsVector& basePoint1_Z();

  /**
   * Returns the x value of the second base point of the curve (the one closer to the
   * end point).
   */
  CLRelAbsVector& basePoint2_X();

  /**
   * Returns the y value of the second base point of the curve (the one closer to the
   * end point).
   */
  CLRelAbsVector& basePoint2_Y();

  /**
   * Returns the z value of the second base point of the curve (the one closer to the
   * end point).
   */
  CLRelAbsVector& basePoint2_Z();

  /**
   * Sets the x value of the first base point of the curve (the one closer to the
   * starting point).
   */
  void setBasePoint1_X(const CLRelAbsVector& v);

  /**
   * Sets the y value of the first base point of the curve (the one closer to the
   * starting point).
   */
  void setBasePoint1_Y(const CLRelAbsVector& v);

  /**
   * Sets the z value of the first base point of the curve (the one closer to the
   * starting point).
   */
  void setBasePoint1_Z(const CLRelAbsVector& v);

  /**
   * Sets the x value of the second base point of the curve (the one closer to the
   * end point).
   */
  void setBasePoint2_X(const CLRelAbsVector& v);

  /**
   * Sets the y value of the second base point of the curve (the one closer to the
   * end point).
   */
  void setBasePoint2_Y(const CLRelAbsVector& v);

  /**
   * Sets the z value of the second base point of the curve (the one closer to the
   * end point).
   */
  void setBasePoint2_Z(const CLRelAbsVector& v);

  /**
   * Sets the first basepoint to the given values.
   */
  void setBasePoint1(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0));

  /**
   * Sets the second basepoint to the given values.
   */
  void setBasePoint2(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0));

  /**
   * Converts this object to the corresponding SBML object.
   */
  virtual RenderPoint* toSBML(unsigned int level, unsigned int version) const;
};

#endif  /* CLCubicBezier_H__ */
