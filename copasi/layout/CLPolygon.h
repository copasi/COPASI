// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLPolygon_H__
#define CLPolygon_H__

#include <string>

#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/core/CDataObject.h"

class CLRenderPoint;
class CLRenderCubicBezier;
class CDataContainer;

LIBSBML_CPP_NAMESPACE_BEGIN
class sbmlPolygon;
LIBSBML_CPP_NAMESPACE_END

class CLPolygon : public CLGraphicalPrimitive2D, public CDataObject
{
private:
  // prevent the compiler from generating an assignment operator
  CLPolygon& operator=(const CLPolygon& source);

protected:
  std::vector<CLRenderPoint*> mListOfElements;

  /**
   * key for the object.
   */
  std::string mKey;

public:
  /**
   * Constructor.
   */
  CLPolygon(CDataContainer* pParent = NULL);

  /**
   * Copy constructor
   */
  CLPolygon(const CLPolygon& source, CDataContainer* pParent);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLPolygon(const sbmlPolygon& source, CDataContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLPolygon();

  /**
   * Returns the number of line segments.
   */
  size_t getNumElements() const;

  /**
   * Returns a pointer to the list of curve segments.
   */
  std::vector<CLRenderPoint*>* getListOfElements();

  /**
   * Returns a const pointer to the list of curve segments.
   */
  const std::vector<CLRenderPoint*>* getListOfElements() const;

  /**
   * Creates a new point object and adds it to the list of
   * elements.
   */
  CLRenderPoint* createPoint();

  /**
   * Creates a new cubicbezier object and adds it to the list of
   * elements.
   */
  CLRenderCubicBezier* createCubicBezier();

  /**
   * Returns a pointer to the point with with the given index or
   * NULL if the index is invalid.
   */
  CLRenderPoint* getElement(size_t index);

  /**
   * Returns const a pointer to the line segement with with the given index or
   * NULL if the index is invalid.
   */
  const CLRenderPoint* getElement(size_t index) const;

  /**
   * Adds a copy of the given line segment to the list of line segements.
   */
  void addElement(const CLRenderPoint* ls);

  /**
   * Removes the curve segment with the given index.
   */
  void removeElement(size_t i);

  /**
   * Returns the key string of the object.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  sbmlPolygon* toSBML(unsigned int level, unsigned int version) const;
};

#endif /* CLPolygon_H__ */
