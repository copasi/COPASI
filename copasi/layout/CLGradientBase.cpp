// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGradientBase.cpp,v $
//   $Revision: 1.3.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:01:27 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <assert.h>

#include <sbml/layout/render/GradientBase.h>

#include "CLGradientBase.h"

#include "CLLinearGradient.h"
#include "CLRadialGradient.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLGradientBase::CLGradientBase(const std::string& name, CCopasiContainer* pParent):
    CLBase(),
    CCopasiContainer(name, pParent),
    mSpreadMethod(CLGradientBase::PAD),
    mKey(""),
    mId("")
{
}

/**
 * Copy Constructor.
 */
CLGradientBase::CLGradientBase(const CLGradientBase& source, CCopasiContainer* pParent):
    CLBase(source),
    CCopasiContainer(source, pParent),
    mSpreadMethod(source.mSpreadMethod),
    mGradientStops(source.mGradientStops, this),
    mKey(""),
    mId(source.mId)
{
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGradientBase::CLGradientBase(const GradientBase& source, const std::string& name, CCopasiContainer* pParent):
    CLBase(),
    CCopasiContainer(name, pParent),
    mKey(""),
    mId(source.getId())
{
  switch (source.getSpreadMethod())
    {
      case GradientBase::REFLECT:
        this->mSpreadMethod = CLGradientBase::REFLECT;
        break;
      case GradientBase::REPEAT:
        this->mSpreadMethod = CLGradientBase::REPEAT;
        break;
      default:
        this->mSpreadMethod = CLGradientBase::PAD;
        break;
    }

  size_t i, iMax = source.getNumGradientStops();

  for (i = 0; i < iMax; ++i)
    {
      CLGradientStop* pStop = new CLGradientStop(*source.getGradientStop((unsigned int) i));
      this->addGradientStop(pStop);
      delete pStop;
    }
}

/**
 * Destructor.
 */
CLGradientBase::~CLGradientBase()
{
  CCopasiRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Returns the spreadmethod of he gradient.
 */
CLGradientBase::SPREADMETHOD CLGradientBase::getSpreadMethod() const
{
  return this->mSpreadMethod;
}

/**
 * Sets the spread method.
 */
void CLGradientBase::setSpreadMethod(CLGradientBase::SPREADMETHOD method)
{
  this->mSpreadMethod = method;
}

/**
 * Returns the number of gradient stops.
 */
size_t CLGradientBase::getNumGradientStops() const
{
  return this->mGradientStops.size();
}

/**
 * Returns a pointer to the gradient stop vector.
 */
CCopasiVector<CLGradientStop>* CLGradientBase::getListOfGradientStops()
{
  return &(this->mGradientStops);
}

/**
 * Returns a const pointer to the gradient stop vector.
 */
const CCopasiVector<CLGradientStop>* CLGradientBase::getListOfGradientStops() const
{
  return &(this->mGradientStops);
}

/**
 * Returns a pointer to the gradient stop with the given index or NULL
 * if the index is invalid.
 */
CLGradientStop* CLGradientBase::getGradientStop(size_t i)
{
  return (i < this->mGradientStops.size()) ? (this->mGradientStops[i]) : NULL;
}

/**
 * Returns a const pointer to the gradient stop with the given index or NULL
 * if the index is invalid.
 */
const CLGradientStop* CLGradientBase::getGradientStop(size_t i) const
{
  return (i < this->mGradientStops.size()) ? (this->mGradientStops[i]) : NULL;
}

/**
 * Creates a new CLGradientStop.
 */
CLGradientStop* CLGradientBase::createGradientStop()
{
  CLGradientStop* pStop = new CLGradientStop();
  this->mGradientStops.add(pStop, true);
  return pStop;
}

/**
 * Adds a copy of the given CLGradientStop object.
 */
void CLGradientBase::addGradientStop(const CLGradientStop* pStop)
{
  this->mGradientStops.add(new CLGradientStop(*pStop, this), true);
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLGradientBase::getKey() const
{
  return this->mKey;
}

/**
 * Returns the id of the object.
 */
const std::string& CLGradientBase::getId() const
{
  return this->mId;
}

/**
 * Sets the id of the object.
 */
void CLGradientBase::setId(const std::string& id)
{
  this->mId = id;
}

/**
 * Adds gradient base attributes to the gradient passed as the argument.
 */
void CLGradientBase::addSBMLAttributes(GradientBase* pBase) const
{
  pBase->setId(this->mId);

  switch (this->mSpreadMethod)
    {
      case CLGradientBase::REFLECT:
        pBase->setSpreadMethod(GradientBase::REFLECT);
        break;
      case CLGradientBase::REPEAT:
        pBase->setSpreadMethod(GradientBase::REPEAT);
        break;
      default:
        pBase->setSpreadMethod(GradientBase::PAD);
        break;
    }

  size_t i, iMax = this->mGradientStops.size();

  for (i = 0; i < iMax; ++i)
    {
      pBase->addGradientStop(this->mGradientStops[i]->toSBML(pBase->getLevel(), pBase->getVersion()));
    }
}
