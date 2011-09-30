// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalPrimitive2D.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:20 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGraphicalPrimitvide2D_H__
#define CLGraphicalPrimitvide2D_H__

#include "copasi/layout/CLGraphicalPrimitive1D.h"
#include "copasi/report/CCopasiContainer.h"

#include <string>

class GraphicalPrimitive2D;

class CLGraphicalPrimitive2D: public CLGraphicalPrimitive1D
{
public:
  enum FILL_RULE
  {
    UNSET,
    NONZERO,
    EVENODD,
    INHERIT
  };

protected:
  FILL_RULE mFillRule;
  std::string mFill;

public:
  /**
   * Constructor.
   */
  CLGraphicalPrimitive2D();

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLGraphicalPrimitive2D(const GraphicalPrimitive2D& source);

  /**
   * Set fill color.
   */
  void setFillColor(const std::string& color);

  /**
   * Sets the fill rule
   */
  void setFillRule(FILL_RULE rule);

  /**
   * Returns the fill color.
   */
  const std::string& getFillColor() const;

  /**
   * Returns the fill rule.
   */
  FILL_RULE getFillRule() const;

  /**
   * Returns true if the fill attribute is set or false otherwise.
   */
  bool isSetFill() const;

  /**
   * Returns true if the fill rule attribute is set or false otherwise.
   */
  bool isSetFillRule() const;

  /**
   * Adds the attributes for a 2d graphical primitive object to the passed in.
   * object.
   */
  virtual  void addSBMLAttributes(GraphicalPrimitive2D* pPrimitive) const;
};

#endif /* CLGraphicalPrimitive2D_H__ */
