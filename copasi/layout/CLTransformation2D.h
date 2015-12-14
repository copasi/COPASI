// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLTransformation2D.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:20 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLTransformation2D_H__
#define CLTransformation2D_H__

#include "copasi/layout/CLTransformation.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class Transformation2D;
LIBSBML_CPP_NAMESPACE_END

class CLTransformation2D : public CLTransformation
{
public:
  static const double IDENTITY2D[6];

  /**
   * Returns a 2D identity matrix.
   * The matrix contains 6 values.
   */
  static const double* getIdentityMatrix2D();

  /**
   * Constructor.
   */
  CLTransformation2D();

  /**
   * Constructor with a matrix.
   */
  CLTransformation2D(const double m[6]);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLTransformation2D(const Transformation2D& source);

  /**
   * Sets the 2D matrix.
   * The 3D matrix is updated accordingly.
   */
  void setMatrix2D(const double m[6]);

  /**
   * Sets the 3D matrix.
   * The 2D matrix is updated accordingly.
   */
  void setMatrix(const double m[12]);

  /**
   * Returns the matrix.
   * The matrix contains 6 values.
   */
  const double* getMatrix2D() const;

  /**
   * Returns a string to represent the 2D transformation.
   */
  std::string get2DTransformationString() const;

  /**
   * Sets the transformation matrix from the given string.
   * The string has to contain either 6 or 12 numerical values seperated by ",".
   * Otherwise the matrix is set to the identity matrix.
   */
  virtual void parseTransformation(const std::string& transformationString);

protected:

  /**
   * Sets the 3D matrix from the 2D matrix.
   */
  void updateMatrix3D();

  /**
   * Fills the 2D matrix with data from the 3D matrix.
   */
  void updateMatrix2D();

  /**
   * the 2D matrix.
   */
  double mMatrix2D[6];

  /**
   * Adds the attributes for a 2d transformation object to the passed in.
   * object.
   */
  virtual void addSBMLAttributes(Transformation2D* pTransformation) const;
};

#endif /* CLTransformation2D_H__ */
