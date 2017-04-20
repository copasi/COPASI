// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRectangle_H__
#define CLRectangle_H__

#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLRelAbsVector.h"
#include "copasi/core/CDataObject.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class sbmlRectangle;
LIBSBML_CPP_NAMESPACE_END

class CLRectangle : public CLGraphicalPrimitive2D, public CDataObject
{
private:
  // prevent the compiler from generating the assignment operator
  CLRectangle& operator=(const CLRectangle& source);

protected:
  CLRelAbsVector mX;
  CLRelAbsVector mY;
  CLRelAbsVector mZ;
  CLRelAbsVector mWidth;
  CLRelAbsVector mHeight;
  CLRelAbsVector mRX;
  CLRelAbsVector mRY;

  /**
   * key for the object.
   */
  std::string mKey;

public:
  /**
   * Constructor.
   */
  CLRectangle(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLRectangle(const CLRectangle& source, CDataContainer* pParent = NULL);

  /**
   * Constructor that takes x, y and z coordinate values, the width and the
   * height.
   */
  CLRectangle(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, const CLRelAbsVector& w, const CLRelAbsVector& h, CDataContainer* pParent = NULL);

  /**
   * Constructor that takes x and y coordinate values, the width and the
   * height.
   */
  CLRectangle(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& w, const CLRelAbsVector& h, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLRectangle(const sbmlRectangle& source, CDataContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLRectangle();

  /**
   * Sets the position, the width and the height.
   */
  void setCoordinatesAndSize(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z, const CLRelAbsVector& w, const CLRelAbsVector& h);

  /**
   * Sets the position.
   */
  void setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z);

  /**
   * Sets the size.
   */
  void setSize(const CLRelAbsVector& w, const CLRelAbsVector& h);

  /**
   * Sets the width.
   */
  void setWidth(const CLRelAbsVector& w);

  /**
   * Sets the height.
   */
  void setHeight(const CLRelAbsVector& h);

  /**
   * Sets the corner radii.
   */
  void setRadii(const CLRelAbsVector& rx, const CLRelAbsVector& ry);

  /**
   * Sets the x radius for the corners.
   */
  void setRadiusX(const CLRelAbsVector& rx);

  /**
   * Sets the y radius for the corners.
   */
  void setRadiusY(const CLRelAbsVector& ry);

  /**
   * Sets the x position.
   */
  void setX(const CLRelAbsVector& x);

  /**
   * Sets the y position.
   */
  void setY(const CLRelAbsVector& y);

  /**
   * Sets the z position.
   */
  void setZ(const CLRelAbsVector& z);

  /**
   * Returns the x coordinate.
   */
  const CLRelAbsVector& getX() const;

  /**
   * Returns the y coordinate.
   */
  const CLRelAbsVector& getY() const;

  /**
   * Returns the z coordinate.
   */
  const CLRelAbsVector& getZ() const;

  /**
   * Returns the width.
   */
  const CLRelAbsVector& getWidth() const;

  /**
   * Returns the height.
   */
  const CLRelAbsVector& getHeight() const;

  /**
   * Returns the corner radius along th x axis.
   */
  const CLRelAbsVector& getRadiusX() const;

  /**
   * Returns the corner radius along the y axis.
   */
  const CLRelAbsVector& getRadiusY() const;

  /**
   * Returns the x coordinate.
   */
  CLRelAbsVector& getX();

  /**
   * Returns the y coordinate.
   */
  CLRelAbsVector& getY();

  /**
   * Returns the z coordinate.
   */
  CLRelAbsVector& getZ();

  /**
   * Returns the width.
   */
  CLRelAbsVector& getWidth();

  /**
   * Returns the height.
   */
  CLRelAbsVector& getHeight();

  /**
   * Returns the corner radius along th x axis.
   */
  CLRelAbsVector& getRadiusX();

  /**
   * Returns the corner radius along the y axis.
   */
  CLRelAbsVector& getRadiusY();

  /**
   * Returns the key string of the object.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  sbmlRectangle* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLRectangle_H__ */
