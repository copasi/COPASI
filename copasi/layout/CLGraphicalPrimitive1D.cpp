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

#include <limits>
#include <sstream>

#include <sbml/packages/render/sbml/GraphicalPrimitive1D.h>

#include "CLGraphicalPrimitive1D.h"

/**
 * Constructor.
 */
CLGraphicalPrimitive1D::CLGraphicalPrimitive1D():
  CLTransformation2D(),
  mStroke(""),
  mStrokeWidth(std::numeric_limits<double>::quiet_NaN())
{
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGraphicalPrimitive1D::CLGraphicalPrimitive1D(const GraphicalPrimitive1D& source):
  CLTransformation2D(source),
  mStroke(source.getStroke()),
  mStrokeWidth(source.getStrokeWidth()),
  mStrokeDashArray(source.getDashArray())
{
}

/**
 * Sets the stroke color.
 */
void CLGraphicalPrimitive1D::setStroke(const std::string& key)
{
  this->mStroke = key;
}

/**
 * Sets the stroke width.
 */
void CLGraphicalPrimitive1D::setStrokeWidth(double width)
{
  this->mStrokeWidth = (width > 0 || width != width) ? width : 0.0;
}

/**
 * Sets the dasharray.
 */
void CLGraphicalPrimitive1D::setDashArray(const std::vector<unsigned int>& array)
{
  this->mStrokeDashArray = array;
}

/**
 * Returns the stroke color.
 */
const std::string& CLGraphicalPrimitive1D::getStroke() const
{
  return this->mStroke;
}

/**
 * Returns the stroke width.
 */
double CLGraphicalPrimitive1D::getStrokeWidth() const
{
  return this->mStrokeWidth;
}

/**
 * Returns the stroke color.
 */
const std::vector<unsigned int>& CLGraphicalPrimitive1D::getDashArray() const
{
  return this->mStrokeDashArray;
}

/**
 * Returns true is the stroke width has been set or false otherwise.
 */
bool CLGraphicalPrimitive1D::isSetStrokeWidth() const
{
  return (mStrokeWidth == mStrokeWidth);
}

/**
 * Returns true is the stroke has been set or false otherwise.
 */
bool CLGraphicalPrimitive1D::isSetStroke() const
{
  return (!this->mStroke.empty() && this->mStroke != "none");
}

/**
 * Returns true is the dash array has been set or false otherwise.
 */
bool CLGraphicalPrimitive1D::isSetDashArray() const
{
  bool result = true;

  if (mStrokeDashArray.size() < 2 || mStrokeDashArray[0] != mStrokeDashArray[0])
    {
      result = false;
    }

  return result;
}

void CLGraphicalPrimitive1D::parseDashArray(const std::string& s)
{
  this->mStrokeDashArray.clear();

  if (!s.empty())
    {
      std::istringstream is(s);
      size_t size = s.size() + 1;
      char* tmp = new char[size];
      char* tmp2 = tmp;
      char* tmp3;
      char** endptr;
      long value;
      is.getline(tmp2, size, ',');

      // continue until the string is empty or the stream is
      // no longer usable
      while (tmp2[0] != 0 && is.good())
        {
          endptr = &tmp2;
          tmp3 = tmp2;
          value = strtol(tmp2, endptr, 10);

          if (value < 0 || *endptr == tmp3 || (**endptr != '\0' && **endptr != ' ' && **endptr != '\t'))
            {
              this->mStrokeDashArray.clear();
            }
          else
            {
              this->mStrokeDashArray.push_back((unsigned int)value);
            }

          // read next element
          is.getline(tmp2, size, ',');
        }

      // check if the string was parsed to the end
      if (is.eof())
        {
          // we have to parse the current tmp2
          // and check if that was ok
          endptr = &tmp2;
          tmp3 = tmp2;
          value = strtol(tmp2, endptr, 10);

          if (value < 0 || *endptr == tmp3 || (**endptr != '\0' && **endptr != ' ' && **endptr != '\t'))
            {
              this->mStrokeDashArray.clear();
            }
          else
            {
              this->mStrokeDashArray.push_back((unsigned int)value);
            }
        }
      else
        {
          // since we did not parse to the end,
          // there most have been an error
          this->mStrokeDashArray.clear();
        }

      delete[] tmp;
    }
}

/**
 * Converts this object to the corresponding SBML object.
 */
void CLGraphicalPrimitive1D::addSBMLAttributes(GraphicalPrimitive1D* pPrimitive) const
{
  this->CLTransformation2D::addSBMLAttributes(pPrimitive);

  if (!mStroke.empty())
    pPrimitive->setStroke(this->mStroke);

  if (mStrokeWidth == mStrokeWidth)
    pPrimitive->setStrokeWidth(this->mStrokeWidth);

  pPrimitive->setDashArray(this->mStrokeDashArray);
}
