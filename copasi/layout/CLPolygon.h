// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLPolygon.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/17 14:00:26 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLPolygon_H__
#define CLPolygon_H__

#include <string>

#include <copasi/layout/CLGraphicalPrimitive2D.h>
#include <copasi/report/CCopasiObject.h>

class CLRenderPoint;
class CLRenderCubicBezier;
class CCopasiContainer;
class sbmlPolygon;

class CLPolygon : public CLGraphicalPrimitive2D, public CCopasiObject
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
  CLPolygon(CCopasiContainer* pParent = NULL);

  /**
   * Copy constructor
   */
  CLPolygon(const CLPolygon& source, CCopasiContainer* pParent);

  /**
   * Constructor to generate object from the corresponding SBML object.
   */
  CLPolygon(const sbmlPolygon& source, CCopasiContainer* pParent = NULL);

  /**
   * Destructor.
   */
  ~CLPolygon();

  /**
   * Returns the number of line segments.
   */
  unsigned int getNumElements() const;

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
  CLRenderPoint* getElement(unsigned int index);

  /**
   * Returns const a pointer to the line segement with with the given index or
   * NULL if the index is invalid.
   */
  const CLRenderPoint* getElement(unsigned int index) const;

  /**
   * Adds a copy of the given line segment to the list of line segements.
   */
  void addElement(const CLRenderPoint* ls);

  /**
   * Removes the curve segment with the given index.
   */
  void removeElement(unsigned int i);

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
