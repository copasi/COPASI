// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLTransformation.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:21 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLTransformation_H__
#define CLTransformation_H__

#include <string>

#include "copasi/layout/CLBase.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class Transformation;
LIBSBML_CPP_NAMESPACE_END

class CLTransformation : public CLBase
{
protected:
  double mMatrix[12];

public:
  static const double IDENTITY3D[12];

  static const double* getIdentityMatrix();

  /**
   * Default constructor.
   * All matrix elements are set to NaN
   */
  CLTransformation();

  /**
   * Constructor with values for the matrix.
   */
  CLTransformation(const double matrix[12]);

  /**
   * Sets the matrix.
   */
  void setMatrix(const double m[12]);

  /**
   * Returns the matrix.
   */
  virtual const double* getMatrix() const;

  /**
   * Returns true if the matrix has been set or false otherwise.
   */
  bool isSetMatrix() const;

  /**
   * Returns true if the matrix is the identity matrix.
   */
  bool isIdentityMatrix() const;

  /**
   * Checks if the transformation is a 2D transformation, i.e.
   * we have to check some of the values.
   */
  bool is2DTransformation() const;

  /**
   * Returns a string to represent the 3D transformation.
   */
  std::string get3DTransformationString() const;

  /**
   * Sets the transformation matrix from the given string.
   * The string has to contain 12 numerical values seperated by ",".
   * Otherwise the matrix is set to the identity matrix.
   */
  virtual void parseTransformation(const std::string& transformationString);
};

#endif /* CLTransformation_H__ */
