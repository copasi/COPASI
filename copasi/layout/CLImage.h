// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLImage.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLImage_H__
#define CLImage_H__

#include <copasi/layout/CLTransformation2D.h>
#include <copasi/layout/CLRelAbsVector.h>
#include <copasi/report/CCopasiObject.h>

#include <string>

#include <sbml/layout/render/Image.h>

class CCopasiContainer;

class CLImage : public CLTransformation2D, public CCopasiObject
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
  CLImage(CCopasiContainer* pParent = NULL);

  /**
   * Copy Constructor.
   */
  CLImage(const CLImage& source, CCopasiContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLImage(const Image& source, CCopasiContainer* pParent = NULL);

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
  Image* toSBML() const;
};

#endif /* CLImage_H__ */
