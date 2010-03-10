// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRelAbsVector.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLCLRelAbsVector_H__
#define CLCLRelAbsVector_H__

#include <string>
#include <ostream>

#include <sbml/layout/render/RelAbsVector.h>

class CLRelAbsVector
{
protected:
  double mAbs; // absolute coordinate value
  double mRel; // relative coordinate value

public:
  /**
   * Constructor with two values.
   * First value sets the absolute value, econd sets the relative value.
   */
  CLRelAbsVector(double a = 0.0, double r = 0.0);

  /**
   * Constructor with a string.
   * The string has to be parsed.
   * If the string does not represent a valid value, the relative and the
   * absolute component of the CLRelAbsVector are set to NaN.
   */
  CLRelAbsVector(const std::string& coordString);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLRelAbsVector(const RelAbsVector& source);

  /**
   * Sets the coordiantes.
   */
  void setCoordinate(double abs, double rel = 0.0);

  /**
   * Sets the coordiantes from the given string.
   */
  void setCoordinate(const std::string& coordString);

  /**
   * Sets the absolute coordinate value.
   */
  void setAbsoluteValue(double abs);

  /**
   * Sets the relative coordinate value.
   */
  void setRelativeValue(double rel);

  /**
   * Returns the absolute coordinate value.
   */
  double getAbsoluteValue() const;

  /**
   * Returns the relative coordinate value.
   */
  double getRelativeValue() const;

  /**
   * addition operator
   */
  CLRelAbsVector operator+(const CLRelAbsVector& other) const;

  /**
   * division by a double.
   */
  CLRelAbsVector operator/(double x) const;

  bool operator==(const CLRelAbsVector& other) const;

  bool operator!=(const CLRelAbsVector& other) const;

  CLRelAbsVector& operator=(const CLRelAbsVector& src);

  /**
   * Converts this object to the corresponding SBML object.
   */
  RelAbsVector* toSBML() const;

  std::string toString() const;
};

std::ostream& operator<<(std::ostream& os, const CLRelAbsVector& v);

#endif // CLRelAbsVector_H__
