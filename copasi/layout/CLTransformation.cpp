// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>
#include <string.h> // for memcmp

#include <sbml/packages/render/sbml/Transformation.h>

#include "CLTransformation.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Default constructor.
 * All matrix elements are set to NaN
 */
CLTransformation::CLTransformation(): CLBase()
{
  unsigned int i;

  for (i = 0; i < 12; ++i)
    {
      mMatrix[i] = std::numeric_limits<double>::quiet_NaN();
    }
}

/**
 * Constructor with id and values for the matrix.
 */
CLTransformation::CLTransformation(const double matrix[12]): CLBase()
{
  unsigned int i;

  for (i = 0; i < 12; ++i)
    {
      mMatrix[i] = matrix[i];
    }
}

/**
 * Sets the matrix.
 */
void CLTransformation::setMatrix(const double m[12])
{
  unsigned int i;

  for (i = 0; i < 12; ++i)
    {
      mMatrix[i] = m[i];
    }
}

/**
 * Returns the matrix.
 * The matrix contains 12 values.
 */
const double* CLTransformation::getMatrix() const
{
  return mMatrix;
}

/**
 * Returns the 3D identity  matrix.
 * The matrix contains 12 values.
 */
const double* CLTransformation::getIdentityMatrix()
{
  return IDENTITY3D;
}

const double CLTransformation::IDENTITY3D[12] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0};

/**
 * Returns true if the matrix has been set or false otherwise.
 */
bool CLTransformation::isSetMatrix() const
{
  bool result = true;
  unsigned int i;

  for (i = 0; result && i < 12; ++i)
    {
      result = (mMatrix[i] == mMatrix[i]);
    }

  return result;
}

/**
 * Returns true if the matrix is the identity matrix.
 */
bool CLTransformation::isIdentityMatrix() const
{
  return !memcmp(mMatrix, CLTransformation::IDENTITY3D, sizeof(double) * 12);
}

/**
 * Checks if the transformation is a 2D transformation, i.e.
 * we have to check some of the values.
 */
bool CLTransformation::is2DTransformation() const
{
  return mMatrix[2] == 0.0 &&
         mMatrix[5] == 0.0 &&
         mMatrix[6] == 0.0 &&
         mMatrix[7] == 0.0 &&
         mMatrix[8] == 1.0 &&
         mMatrix[11] == 0.0;
}

/**
 * Returns a string to represent the 3D transformation.
 */
std::string CLTransformation::get3DTransformationString() const
{
  // transform the matrix to a string
  std::ostringstream os;
  unsigned int i;
  os << mMatrix[0];

  for (i = 1; i < 12; ++i)
    {
      os << "," << mMatrix[i];
    }

  return os.str();
}

/**
 * Sets the transformation matrix from the given string.
 * The string has to contain 12 numerical values seperated by ",".
 * Otherwise the matrix is set to the identity matrix.
 */
void CLTransformation::parseTransformation(const std::string& transformationString)
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
      if (index > 11)
        {
          result = false;
          break;
        }

      pos = transformationString.find_first_of(delimiter, lastPos);
      double value = strtod(transformationString.substr(lastPos, pos - lastPos).c_str(), NULL);
      mMatrix[index] = value;
      index++;
      lastPos = transformationString.find_first_not_of(delimiter, pos);
    }

  if (!result || index != 12)
    {
      this->setMatrix(CLTransformation::IDENTITY3D);
    }
}
