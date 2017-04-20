// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLEllipse_H__
#define CLEllipse_H__

#include <string>

#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLRelAbsVector.h"
#include "copasi/core/CDataObject.h"

class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class sbmlEllipse;
LIBSBML_CPP_NAMESPACE_END

class CLEllipse : public CLGraphicalPrimitive2D, public CDataObject
{
private:
  // prevent the compiler from generating the assignment operator
  CLEllipse& operator=(const CLEllipse& source);

protected:
  CLRelAbsVector mCX;
  CLRelAbsVector mCY;
  CLRelAbsVector mCZ;
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
  CLEllipse(CDataContainer* pParent = NULL);

  /**
   * Constructor with 2D center and radius.
   */
  CLEllipse(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& r, CDataContainer* pParent = NULL);

  /**
   * Constructor with 2D center and radii.
   */
  CLEllipse(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& rx, const CLRelAbsVector& ry, CDataContainer* pParent = NULL);

  /**
   * Constructor with 3D center and radii.
   */
  CLEllipse(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& cz, const CLRelAbsVector& rx, const CLRelAbsVector& ry, CDataContainer* pParent = NULL);

  /**
   * Copy Constructor
   */
  CLEllipse(const CLEllipse& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLEllipse(const sbmlEllipse& source, CDataContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLEllipse();

  /**
   * Returns the x component of the center.
   */
  const CLRelAbsVector& getCX() const;

  /**
   * Returns the y component of the center.
   */
  const CLRelAbsVector& getCY() const;

  /**
   * Returns the z component of the center.
   */
  const CLRelAbsVector& getCZ() const;

  /**
   * Returns the radius along the x axis.
   */
  const CLRelAbsVector& getRX() const;

  /**
   * Returns the radius along the y axis.
   */
  const CLRelAbsVector& getRY() const;

  /**
   * Returns the x component of the center.
   */
  CLRelAbsVector& getCX();

  /**
   * Returns the y component of the center.
   */
  CLRelAbsVector& getCY();

  /**
   * Returns the z component of the center.
   */
  CLRelAbsVector& getCZ();

  /**
   * Returns the radius along the x axis.
   */
  CLRelAbsVector& getRX();

  /**
   * Returns the radius along the y axis.
   */
  CLRelAbsVector& getRY();

  /**
   * Sets the x component of the center.
   */
  void setCX(const CLRelAbsVector& cx);

  /**
   * Sets the y component of the center.
   */
  void setCY(const CLRelAbsVector& cy);

  /**
   * Sets the z component of the center.
   */
  void setCZ(const CLRelAbsVector& cz);

  /**
   * Sets the radius along the x axis.
   */
  void setRX(const CLRelAbsVector& rx);

  /**
   * Sets the radius along the y axis.
   */
  void setRY(const CLRelAbsVector& ry);

  /**
   * Sets the 2D center.
   */
  void setCenter2D(const CLRelAbsVector& cx, const CLRelAbsVector& cy);

  /**
   * Sets the 3D center.
   */
  void setCenter3D(const CLRelAbsVector& cx, const CLRelAbsVector& cy, const CLRelAbsVector& cz);

  /**
   * Sets the radii.
   */
  void setRadii(const CLRelAbsVector& rx, const CLRelAbsVector& ry);

  /**
   * Returns the key string of the object.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  sbmlEllipse* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLEllipse_H__ */
