// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRenderCurve_H__
#define CLRenderCurve_H__

#include <string>
#include <vector>

#include "copasi/layout/CLGraphicalPrimitive1D.h"
#include "copasi/core/CDataObject.h"

class CLRenderCubicBezier;
class CLRenderPoint;

LIBSBML_CPP_NAMESPACE_BEGIN
class RenderCurve;
LIBSBML_CPP_NAMESPACE_END

class CLRenderCurve : public CLGraphicalPrimitive1D, public CDataObject
{
private:
  // prevent the compiler from generating an assignment operator
  CLRenderCurve& operator=(const CLRenderCurve& source);

protected:
  std::string mStartHead;
  std::string mEndHead;
  std::vector<CLRenderPoint*> mListOfElements;

  /**
   * key for the object.
   */
  std::string mKey;

public:
  /**
   * Constructor.
   */
  CLRenderCurve(CDataContainer* pParent = NULL);

  /**
   * Copy Constructor
   */
  CLRenderCurve(const CLRenderCurve& source, CDataContainer* pParent = NULL);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLRenderCurve(const RenderCurve& source, CDataContainer* pParent = NULL);

  /**
   * Destructor
   */
  ~CLRenderCurve();

  /**
   * Sets the id of the start head.
   */
  void setStartHead(const std::string& startHead);

  /**
   * Sets the id of the end head.
   */
  void setEndHead(const std::string& endHead);

  /**
   * Returns the id of the start head.
   */
  const std::string& getStartHead() const;

  /**
   * Returns the id of the end head.
   */
  const std::string& getEndHead() const;

  /**
   * Returns the number of curve segments.
   */
  size_t getNumElements() const;

  /**
   * Creates a new bezier element.
   * The element is added to the curve.
   */
  CLRenderCubicBezier* createCubicBezier();

  /**
   * Creates a new point element.
   * The element is added to the curve.
   */
  CLRenderPoint* createPoint();

  /**
   * Returns a const pointer to the curve segment with the given index or NULL if
   * the id is invalid.
   */
  const CLRenderPoint* getCurveElement(size_t index) const;

  /**
   * Returns a pointer to the curve segment with the given index or NULL if
   * the id is invalid.
   */
  CLRenderPoint* getCurveElement(size_t index);

  /**
   * Adds a copy of the given curve segment to the end of the list of
   *curve segments.
   */
  void addCurveElement(const CLRenderPoint* cs);

  /**
   * Removes the curve segment with the given index.
   */
  void removeCurveElement(size_t i);

  /**
   * Returns a const pointer to the list of curve segments.
   */
  const std::vector<CLRenderPoint*>* getListOfCurveElements() const;

  /**
   * Returns a pointer to the list of curve segments.
   */
  std::vector<CLRenderPoint*>* getListOfCurveElements();

  /**
   * Returns true if the start head is set or false otherwise.
   */
  bool isSetStartHead() const;

  /**
   * Returns true if the start head is set or false otherwise.
   */
  bool isSetEndHead() const;

  /**
   * Returns the key string of the object.
   */
  const std::string& getKey() const;

  /**
   * Converts this object to the corresponding SBML object.
   */
  RenderCurve* toSBML(unsigned int level, unsigned int version) const;

protected:
  friend class Group;
};

#endif /* CLRenderCurve_H__ */
