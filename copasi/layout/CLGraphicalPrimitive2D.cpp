// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/packages/render/sbml/GraphicalPrimitive2D.h>

#include "CLGraphicalPrimitive2D.h"

/**
 * Constructor.
 */
CLGraphicalPrimitive2D::CLGraphicalPrimitive2D()
  : CLGraphicalPrimitive1D(),
    mFillRule(CLGraphicalPrimitive2D::UNSET),
    mFill("")
{}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGraphicalPrimitive2D::CLGraphicalPrimitive2D(const GraphicalPrimitive2D& source):
  CLGraphicalPrimitive1D(source),
  mFill(source.getFillColor())
{
  switch (source.getFillRule())
    {
      case GraphicalPrimitive2D::UNSET:
        this->setFillRule(CLGraphicalPrimitive2D::UNSET);
        break;

      case GraphicalPrimitive2D::NONZERO:
        this->setFillRule(CLGraphicalPrimitive2D::NONZERO);
        break;

      case GraphicalPrimitive2D::EVENODD:
        this->setFillRule(CLGraphicalPrimitive2D::EVENODD);
        break;

      case GraphicalPrimitive2D::INHERIT:
        this->setFillRule(CLGraphicalPrimitive2D::INHERIT);
        break;
    }
}

/**
 * Set fill color.
 */
void CLGraphicalPrimitive2D::setFillColor(const std::string& color)
{
  this->mFill = color;
}

/**
 * Sets the fill rule
 */
void CLGraphicalPrimitive2D::setFillRule(CLGraphicalPrimitive2D::FILL_RULE rule)
{
  this->mFillRule = rule;
}

/**
 * Returns the fill color.
 */
const std::string& CLGraphicalPrimitive2D::getFillColor() const
{
  return this->mFill;
}

/**
 * Returns the fill rule.
 */
CLGraphicalPrimitive2D::FILL_RULE CLGraphicalPrimitive2D::getFillRule() const
{
  return this->mFillRule;
}

/**
 * Returns true if the fill attribute is set or false otherwise.
 */
bool CLGraphicalPrimitive2D::isSetFill() const
{
  return !this->mFill.empty();
}

/**
 * Returns true if the fill rule attribute is set or false otherwise.
 */
bool CLGraphicalPrimitive2D::isSetFillRule() const
{
  return this->mFillRule != CLGraphicalPrimitive2D::UNSET;
}

/**
 * Adds the attributes for a 2d graphical primitive object to the passed in.
 * object.
 */
void CLGraphicalPrimitive2D::addSBMLAttributes(GraphicalPrimitive2D* pPrimitive) const
{
  this->CLGraphicalPrimitive1D::addSBMLAttributes(pPrimitive);

  if (!mFill.empty())
    pPrimitive->setFillColor(this->mFill);

  switch (this->mFillRule)
    {
      case CLGraphicalPrimitive2D::UNSET:
        pPrimitive->setFillRule(GraphicalPrimitive2D::UNSET);
        break;

      case CLGraphicalPrimitive2D::NONZERO:
        pPrimitive->setFillRule(GraphicalPrimitive2D::NONZERO);
        break;

      case CLGraphicalPrimitive2D::EVENODD:
        pPrimitive->setFillRule(GraphicalPrimitive2D::EVENODD);
        break;

      case CLGraphicalPrimitive2D::INHERIT:
        pPrimitive->setFillRule(GraphicalPrimitive2D::INHERIT);
        break;
    }
}
