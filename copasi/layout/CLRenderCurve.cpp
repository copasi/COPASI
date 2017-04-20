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

#include <sbml/packages/render/sbml/RenderCurve.h>

#include "CLRenderCurve.h"

#include "CLRenderPoint.h"
#include "CLRenderCubicBezier.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLRenderCurve::CLRenderCurve(CDataContainer* pParent):
  CLGraphicalPrimitive1D(),
  CDataObject("RenderCurve", pParent),
  mStartHead(""),
  mEndHead(""),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderCurve", this);
}

/**
 * Copy constructor
 */
CLRenderCurve::CLRenderCurve(const CLRenderCurve& source, CDataContainer* pParent):
  CLGraphicalPrimitive1D(source),
  CDataObject(source, pParent),
  mStartHead(source.mStartHead),
  mEndHead(source.mEndHead),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderCurve", this);
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
CLRenderCurve::CLRenderCurve(const RenderCurve& source, CDataContainer* pParent):
  CLGraphicalPrimitive1D(source),
  CDataObject("RenderCurve", pParent),
  mStartHead(source.getStartHead()),
  mEndHead(source.getEndHead()),
  mKey("")
{
  this->mKey = CRootContainer::getKeyFactory()->add("RenderCurve", this);
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
 * Destructor
 */
CLRenderCurve::~CLRenderCurve()
{
  CRootContainer::getKeyFactory()->remove(this->mKey);
  size_t i, iMax = this->mListOfElements.size();

  for (i = 0; i < iMax; ++i)
    {
      delete this->mListOfElements[i];
    }
}

/**
 * Sets the id of the start head.
 */
void CLRenderCurve::setStartHead(const std::string& startHead)
{
  this->mStartHead = startHead;
}

/**
 * Sets the id of the end head.
 */
void CLRenderCurve::setEndHead(const std::string& endHead)
{
  this->mEndHead = endHead;
}

/**
 * Returns the id of the start head.
 */
const std::string& CLRenderCurve::getStartHead() const
{
  return this->mStartHead;
}

/**
 * Returns the id of the end head.
 */
const std::string& CLRenderCurve::getEndHead() const
{
  return this->mEndHead;
}

/**
 * Returns the number of curve segments.
 */
size_t CLRenderCurve::getNumElements() const
{
  return this->mListOfElements.size();
}

/**
 * Creates a new cubic bezier curve segment.
 */
CLRenderCubicBezier* CLRenderCurve::createCubicBezier()
{
  CLRenderCubicBezier* pCS = new CLRenderCubicBezier();
  this->mListOfElements.push_back(pCS);
  return pCS;
}

/**
 * Creates a new curve segment.
 */
CLRenderPoint* CLRenderCurve::createPoint()
{
  CLRenderPoint* pCS = new CLRenderPoint();
  this->mListOfElements.push_back(pCS);
  return pCS;
}

/**
 * Returns a const pointer to the curve segment with the given index or NULL if
 * the id is invalid.
 */
const CLRenderPoint* CLRenderCurve::getCurveElement(size_t index) const
{
  return (index < this->mListOfElements.size()) ? (this->mListOfElements[index]) : NULL;
}

/**
 * Returns a pointer to the curve segment with the given index or NULL if
 * the id is invalid.
 */
CLRenderPoint* CLRenderCurve::getCurveElement(size_t index)
{
  return (index < this->mListOfElements.size()) ? (this->mListOfElements[index]) : NULL;
}

/**
 * Adds a copy of the given curve segment to the end of the list of
 *curve segments.
 */
void CLRenderCurve::addCurveElement(const CLRenderPoint* pCS)
{
  if (dynamic_cast<const CLRenderCubicBezier*>(pCS))
    {
      this->mListOfElements.push_back(new CLRenderCubicBezier(*static_cast<const CLRenderCubicBezier*>(pCS)));
    }
  else
    {
      this->mListOfElements.push_back(new CLRenderPoint(*pCS));
    }
}

/**
 * Removes the curve segment with the given index.
 */
void CLRenderCurve::removeCurveElement(size_t i)
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
 * Returns a const pointer to the list of curve segments.
 */
const std::vector<CLRenderPoint*>* CLRenderCurve::getListOfCurveElements() const
{
  return &(this->mListOfElements);
}

/**
 * Returns a pointer to the list of curve segments.
 */
std::vector<CLRenderPoint*>* CLRenderCurve::getListOfCurveElements()
{
  return &(this->mListOfElements);
}

/**
 * Returns true if the start head is set or false otherwise.
 */
bool CLRenderCurve::isSetStartHead() const
{
  return (!this->mStartHead.empty() && this->mStartHead != "none");
}

/**
 * Returns true if the start head is set or false otherwise.
 */
bool CLRenderCurve::isSetEndHead() const
{
  return (!this->mEndHead.empty() && this->mEndHead != "none");
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLRenderCurve::getKey() const
{
  return this->mKey;
}

/**
 * Converts this object to the corresponding SBML object.
 */
RenderCurve* CLRenderCurve::toSBML(unsigned int level, unsigned int version) const
{
  RenderCurve* pCurve = new RenderCurve(level, version);
  this->addSBMLAttributes(pCurve);
  pCurve->setStartHead(this->mStartHead);
  pCurve->setEndHead(this->mEndHead);
  size_t i, iMax = this->mListOfElements.size();

  for (i = 0; i < iMax; ++i)
    {
      const RenderPoint* pP = this->mListOfElements[i]->toSBML(level, version);
      pCurve->addElement(pP);
      delete pP;
    }

  return pCurve;
}
