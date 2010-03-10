// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalPrimitive1D.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGraphicalPrimitive1D_H__
#define CLGraphicalPrimitive1D_H__

#include <copasi/layout/CLTransformation2D.h>

#include <string>
#include <vector>

#include <sbml/layout/render/GraphicalPrimitive1D.h>

class CLGraphicalPrimitive1D : public CLTransformation2D
{
protected:
  std::string mStroke;
  double mStrokeWidth;
  std::vector<unsigned int> mStrokeDashArray;

public:
  /**
   * Constructor.
   */
  CLGraphicalPrimitive1D();

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGraphicalPrimitive1D(const GraphicalPrimitive1D& source);

  /**
   * Sets the stroke color.
   */
  void setStroke(const std::string& key);

  /**
   * Sets the stroke width.
   */
  void setStrokeWidth(double width);

  /**
   * Sets the dasharray.
   */
  void setDashArray(const std::vector<unsigned int>& array);

  /**
   * Returns the stroke color.
   */
  const std::string& getStroke() const;

  /**
   * Returns the stroke width.
   */
  double getStrokeWidth() const;
  /**
   * Returns the stroke color.
   */
  const std::vector<unsigned int>& getDashArray() const;

  /**
   * Returns true is the stroke width has been set or false otherwise.
   */
  bool isSetStrokeWidth() const;

  /**
   * Returns true is the stroke has been set or false otherwise.
   */
  bool isSetStroke() const;

  /**
   * Returns true is the dash array has been set or false otherwise.
   */
  bool isSetDashArray() const;

  void parseDashArray(const std::string& s);

  /**
   * Adds the attributes for a graphical primitive 1D object to the passed in.
   * object.
   */
  virtual void addSBMLAttributes(GraphicalPrimitive1D* pPrimitive) const;
};

#endif /* CLGraphicalPrimitive1D_H__ */
