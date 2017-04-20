// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLImage_H__
#define CLImage_H__

#include <string>

#include "copasi/layout/CLTransformation2D.h"
#include "copasi/layout/CLRelAbsVector.h"
#include "copasi/core/CDataObject.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class Image;
LIBSBML_CPP_NAMESPACE_END

class CLImage : public CLTransformation2D, public CDataObject
{
private:
  // prevent the compiler from generating the assignment operator
  CLImage& operator=(const CLImage& source);

protected:
  CLRelAbsVector mX;
  CLRelAbsVector mY;
  CLRelAbsVector mZ;
  CLRelAbsVector mWidth;
  CLRelAbsVector mHeight;
  std::string mHRef;

  /**
   * key for the object.
   */
  std::string mKey;

public:
  /**
   * Constructor.
   */
  CLImage(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLImage(const CLImage& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLImage(const Image& source, CDataContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLImage();

  /**
   * Sets the coordinates.
   */
  void setCoordinates(const CLRelAbsVector& x, const CLRelAbsVector& y, const CLRelAbsVector& z = CLRelAbsVector(0.0, 0.0));

  /**
   * Sets the x coordinate.
   */
  void setX(const CLRelAbsVector& coord);

  /**
   * Sets the y coordinate.
   */
  void setY(const CLRelAbsVector& coord);

  /**
   * Sets the z coordinate.
   */
  void setZ(const CLRelAbsVector& coord);

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
   * Sets the dimensions.
   */
  void setDimensions(const CLRelAbsVector& width, const CLRelAbsVector& height);

  /**
   * Sets the width.
   */
  void setWidth(const CLRelAbsVector& width);

  /**
   * Sets the height.
   */
  void setHeight(const CLRelAbsVector& height);

  /**
   * Returns the width.
   */
  const CLRelAbsVector& getWidth() const;

  /**
   * Returns the height.
   */
  const CLRelAbsVector& getHeight() const;

  /**
   * Sets the reference to the image location.
   */
  void setImageReference(const std::string& ref);

  /**
   * Returns the image reference.
   */
  const std::string& getImageReference() const;

  /**
   * Returns true if the image reference has been set.
   */
  bool isSetImageReference() const;

  /**
   * Returns the key string of the object.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  Image* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLImage_H__ */
