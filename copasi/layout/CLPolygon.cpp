// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/Polygon.h>

#define sbmlPolygon Polygon
#include "CLPolygon.h"

#include "CLRenderPoint.h"
#include "CLRenderCubicBezier.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLPolygon::CLPolygon(CDataContainer* pParent):
  CLGraphicalPrimitive2D(),
  CDataObject("Polygon", pParent),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Polygon", this);
}

/**
 * Copy constructor
 */
CLPolygon::CLPolygon(const CLPolygon& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataObject(source, pParent),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Polygon", this);
  size_t i, iMax = source.mListOfElements.size();

  for (i = 0; i < iMax; ++i)
    {
      if (dynamic_cast<const CLRenderCubicBezier*>(source.mListOfElements[i]))
        {
          this->mListOfElements.push_back(new CLRenderCubicBezier(*static_cast<const CLRenderCubicBezier*>(source.mListOfElements[i])));
        }
      else
        {
          this->mListOfElements.push_back(new CLRenderPoint(*source.mListOfElements[i]));
        }
    }
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLPolygon::CLPolygon(const Polygon& source, CDataContainer* pParent):
  CLGraphicalPrimitive2D(source),
  CDataObject("Polygon", pParent),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("Polygon", this);
  size_t i, iMax = source.getNumElements();

  for (i = 0; i < iMax; ++i)
    {
      CLRenderPoint* pElement = NULL;

      if (dynamic_cast<const RenderCubicBezier*>(source.getElement((unsigned int) i)))
        {
          pElement = new CLRenderCubicBezier(*static_cast<const RenderCubicBezier*>(source.getElement((unsigned int) i)));
        }
      else
        {
          pElement = new CLRenderPoint(*source.getElement((unsigned int) i));
        }

      this->mListOfElements.push_back(pElement);
    }
}

/**
 * Destructor.
 */
CLPolygon::~CLPolygon()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
  size_t i, iMax = this->mListOfElements.size();

  for (i = 0; i < iMax; ++i)
    {
      delete this->mListOfElements[i];
    }
}

/**
 * Returns the number of line segments.
 */
size_t CLPolygon::getNumElements() const
{
  return this->mListOfElements.size();
}

/**
 * Returns a pointer to the list of curve segments.
 */
std::vector<CLRenderPoint*>* CLPolygon::getListOfElements()
{
  return &(this->mListOfElements);
}

/**
 * Returns a const pointer to the list of curve segments.
 */
const std::vector<CLRenderPoint*>* CLPolygon::getListOfElements() const
{
  return &(this->mListOfElements);
}

/**
 * Creates a new point object and adds it to the list of curve
 * segments.
 */
CLRenderPoint* CLPolygon::createPoint()
{
  this->mListOfElements.push_back(new CLRenderPoint());
  return this->mListOfElements.back();
}

/**
 * Creates a new cubicbezier object and adds it to the list of curve
 * segments.
 */
CLRenderCubicBezier* CLPolygon::createCubicBezier()
{
  this->mListOfElements.push_back(new CLRenderCubicBezier());
  return static_cast<CLRenderCubicBezier*>(this->mListOfElements.back());
}

/**
 * Returns a pointer to the line segement with with the given index or
 * NULL if the index is invalid.
 */
CLRenderPoint* CLPolygon::getElement(size_t index)
{
  return (index < this->mListOfElements.size()) ? (this->mListOfElements[index]) : NULL;
}

/**
 * Returns const a pointer to the line segement with with the given index or
 * NULL if the index is invalid.
 */
const CLRenderPoint* CLPolygon::getElement(size_t index) const
{
  return (index < this->mListOfElements.size()) ? (this->mListOfElements[index]) : NULL;
}

/**
 * Adds a copy of the given line segment to the list of line segements.
 */
void CLPolygon::addElement(const CLRenderPoint* pLS)
{
  if (dynamic_cast<const CLRenderCubicBezier*>(pLS))
    {
      this->mListOfElements.push_back(new CLRenderCubicBezier(*static_cast<const CLRenderCubicBezier*>(pLS)));
    }
  else
    {
      this->mListOfElements.push_back(new CLRenderPoint(*pLS));
    }
}

/**
 * Removes the curve segment with the given index.
 */
void CLPolygon::removeElement(size_t i)
{
  if (i < this->mListOfElements.size())
    {
      std::vector<CLRenderPoint*>::iterator it = this->mListOfElements.begin();
      it += i;
      delete *it;
      this->mListOfElements.erase(it);
    }
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLPolygon::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
Polygon* CLPolygon::toSBML(unsigned int level, unsigned int version) const
{
  Polygon* pPolygon = new Polygon(level, version);
  this->addSBMLAttributes(pPolygon);
  size_t i, iMax = this->mListOfElements.size();

  for (i = 0; i < iMax; ++i)
    {
      const RenderPoint* pP = this->mListOfElements[i]->toSBML(level, version);
      pPolygon->addElement(pP);
      delete pP;
    }

  return pPolygon;
}
