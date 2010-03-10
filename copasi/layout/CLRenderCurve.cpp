// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRenderCurve.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CLRenderCurve.h"

#include "CLRenderPoint.h"
#include "CLRenderCubicBezier.h"

#include <copasi/report/CCopasiRootContainer.h>
#include <copasi/report/CKeyFactory.h>

/**
 * Constructor.
 */
CLRenderCurve::CLRenderCurve(CCopasiContainer* pParent):
    CLGraphicalPrimitive1D(),
    CCopasiObject("RenderCurve", pParent),
    mStartHead(""),
    mEndHead(""),
    mKey("")
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("RenderCurve", this);
}

/**
 * Copy constructor
 */
CLRenderCurve::CLRenderCurve(const CLRenderCurve& source, CCopasiContainer* pParent):
    CLGraphicalPrimitive1D(source),
    CCopasiObject(source, pParent),
    mStartHead(source.mStartHead),
    mEndHead(source.mEndHead),
    mKey("")
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("RenderCurve", this);
  unsigned int i, iMax = source.mListOfElements.size();

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
CLRenderCurve::CLRenderCurve(const RenderCurve& source, CCopasiContainer* pParent):
    CLGraphicalPrimitive1D(source),
    CCopasiObject("RenderCurve", pParent),
    mStartHead(source.getStartHead()),
    mEndHead(source.getEndHead()),
    mKey("")
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("RenderCurve", this);
  unsigned int i, iMax = source.getNumElements();

  for (i = 0; i < iMax; ++i)
    {
      CLRenderPoint* pElement = NULL;

      if (dynamic_cast<const RenderCubicBezier*>(source.getCurveElement(i)))
        {
          pElement = new CLRenderCubicBezier(*static_cast<const RenderCubicBezier*>(source.getCurveElement(i)));
        }
      else
        {
          pElement = new CLRenderPoint(*source.getCurveElement(i));
        }

      this->mListOfElements.push_back(pElement);
    }
}

/**
 * Destructor
 */
CLRenderCurve::~CLRenderCurve()
{
  CCopasiRootContainer::getKeyFactory()->remove(this->mKey);
  unsigned int i, iMax = this->mListOfElements.size();

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
unsigned int CLRenderCurve::getNumElements() const
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
const CLRenderPoint* CLRenderCurve::getCurveElement(unsigned int index) const
{
  return (index < this->mListOfElements.size()) ? (this->mListOfElements[index]) : NULL;
}

/**
 * Returns a pointer to the curve segment with the given index or NULL if
 * the id is invalid.
 */
CLRenderPoint* CLRenderCurve::getCurveElement(unsigned int index)
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
void CLRenderCurve::removeCurveElement(unsigned int i)
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
RenderCurve* CLRenderCurve::toSBML() const
{
  RenderCurve* pCurve = new RenderCurve();
  this->addSBMLAttributes(pCurve);
  pCurve->setStartHead(this->mStartHead);
  pCurve->setEndHead(this->mEndHead);
  unsigned int i, iMax = this->mListOfElements.size();

  for (i = 0; i < iMax; ++i)
    {
      const RenderPoint* pP = this->mListOfElements[i]->toSBML();
      pCurve->addCurveElement(pP);
      delete pP;
    }

  return pCurve;
}
