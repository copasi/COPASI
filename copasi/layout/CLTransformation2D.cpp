// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLTransformation2D.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:44:51 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string.h>
#include <stdlib.h>
#include <sstream>

#include <sbml/packages/render/sbml/Transformation2D.h>

#include "CLTransformation2D.h"

/**
 * Constructor.
 */
CLTransformation2D::CLTransformation2D(): CLTransformation()
{
  unsigned int i;

  for (i = 0; i < 12; ++i)
    {
      mMatrix[i] = IDENTITY3D[i];
    }

  this->updateMatrix2D();
}

/**
 * Constructor with values for the matrix.
 */
CLTransformation2D::CLTransformation2D(const double matrix[6]): CLTransformation()
{
  this->setMatrix2D(matrix);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLTransformation2D::CLTransformation2D(const Transformation2D& source):
    CLTransformation()
{
  if (source.isSetMatrix())
    {
      this->setMatrix2D(source.getMatrix2D());
    }
  else
    {
      this->updateMatrix2D();
    }
}

/**
 * Sets the matrix.
 */
void CLTransformation2D::setMatrix2D(const double m[6])
{
  unsigned int i;

  for (i = 0; i < 6; ++i)
    {
      mMatrix2D[i] = m[i];
    }

  this->updateMatrix3D();
}

/**
 * Returns the matrix.
 * The matrix contains 6 values.
 */
const double* CLTransformation2D::getMatrix2D() const
{
  return mMatrix2D;
}

/**
 * Returns a 2D identity matrix.
 * The matrix contains 6 values.
 */
const double* CLTransformation2D::getIdentityMatrix2D()
{
  return IDENTITY2D;
}

const double CLTransformation2D::IDENTITY2D[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

std::string CLTransformation2D::get2DTransformationString() const
{
  // transform the matrix to a string
  std::ostringstream os;
  unsigned int i;
  os << mMatrix2D[0];

  for (i = 1; i < 6; ++i)
    {
      os << "," << mMatrix2D[i];
    }

  return os.str();
}

/**
 * Sets the 3D matrix from the 2D matrix.
 */
void CLTransformation2D::updateMatrix3D()
{
  mMatrix[0] = mMatrix2D[0];
  mMatrix[1] = mMatrix2D[1];
  mMatrix[2] = 0.0;
  mMatrix[3] = mMatrix2D[2];
  mMatrix[4] = mMatrix2D[3];
  mMatrix[5] = 0.0;
  mMatrix[6] = 0.0;
  mMatrix[7] = 0.0;
  mMatrix[8] = 1.0;
  mMatrix[9] = mMatrix2D[4];
  mMatrix[10] = mMatrix2D[5];
  mMatrix[11] = 0.0;
}

/**
 * Fills the 2D matrix with data from the 3D matrix.
 */
void CLTransformation2D::updateMatrix2D()
{
  mMatrix2D[0] = mMatrix[0];
  mMatrix2D[1] = mMatrix[1];
  mMatrix2D[2] = mMatrix[3];
  mMatrix2D[3] = mMatrix[4];
  mMatrix2D[4] = mMatrix[9];
  mMatrix2D[5] = mMatrix[10];
}

void CLTransformation2D::setMatrix(const double m[12])
{
  this->CLTransformation::setMatrix(m);
  this->updateMatrix2D();
}

void CLTransformation2D::parseTransformation(const std::string& transformationString)
{
  // the string should contain a list of 6 komma seperated numbers
  // if it doesn't, we try to set the 3D matrix
  bool result = true;
  std::string delimiter = ",";
  std::size_t lastPos = transformationString.find_first_not_of(delimiter);
  std::size_t pos;
  unsigned int index = 0;

  while (lastPos != std::string::npos)
    {
      if (index > 5)
        {
          result = false;
          break;
        }

      pos = transformationString.find_first_of(delimiter, lastPos);
      double value = strtod(transformationString.substr(lastPos, pos - lastPos).c_str(), NULL);
      mMatrix2D[index] = value;
      index++;
      lastPos = transformationString.find_first_not_of(delimiter, pos);
    }

  if (!result || index != 6)
    {
      this->CLTransformation::parseTransformation(transformationString);
      this->updateMatrix2D();
    }
  else
    {
      this->updateMatrix3D();
    }
}

/**
 * Adds the attributes for a 2d transformation object to the passed in.
 * object.
 */
void CLTransformation2D::addSBMLAttributes(Transformation2D* pTransformation) const
{
  pTransformation->setMatrix2D(this->mMatrix2D);
}
