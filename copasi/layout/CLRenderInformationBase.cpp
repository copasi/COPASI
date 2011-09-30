// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLRenderInformationBase.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:21 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#define USE_LAYOUT 1

#ifdef USE_CRENDER_EXTENSION
#define USE_RENDER 1
#endif // USE_CRENDER_EXTENSION

#include <sbml/layout/render/RenderInformationBase.h>
#include <sbml/layout/render/ColorDefinition.h>
#include <sbml/layout/render/GradientBase.h>
#include <sbml/layout/render/LinearGradient.h>
#include <sbml/layout/render/RadialGradient.h>
#include <sbml/layout/render/LineEnding.h>

#include "CLRenderInformationBase.h"
#include "CLGradientBase.h"
#include "CLLinearGradient.h"
#include "CLRadialGradient.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"


/**
 * Constructor.
 */
CLRenderInformationBase::CLRenderInformationBase(const std::string& name, CCopasiContainer* pParent):
    CLBase(),
    CCopasiContainer(name, pParent),
    mKey(""),
    mName("")
{
}

/**
 * Copy constructor.
 */
CLRenderInformationBase::CLRenderInformationBase(const CLRenderInformationBase& source, CCopasiContainer* pParent):
    CLBase(source),
    CCopasiContainer(source, pParent),
    mReferenceRenderInformation(source.mReferenceRenderInformation),
    mBackgroundColor(source.mBackgroundColor),
    mListOfColorDefinitions(source.mListOfColorDefinitions, this),
    mListOfGradientDefinitions(source.mListOfGradientDefinitions, this),
    mListOfLineEndings(source.mListOfLineEndings, this),
    mKey(""),
    mName(source.mName)
{
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLRenderInformationBase::CLRenderInformationBase(const RenderInformationBase& source,
    const std::string& name,
    /*
    std::map<std::string,std::string>& colorIdToKeyMap,
    std::map<std::string,std::string>& gradientIdToKeyMap,
    std::map<std::string,std::string>& lineEndingIdToKeyMap,
    */
    CCopasiContainer* pParent):

    CLBase(),
    CCopasiContainer(name, pParent),
    mReferenceRenderInformation(source.getReferenceRenderInformationId()),
    mBackgroundColor(source.getBackgroundColor()),
    mKey(""),
    mName(source.getName())
{
  size_t i, iMax = source.getNumColorDefinitions();
  const ColorDefinition* pCD = NULL;
  CLColorDefinition* pLCD = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pCD = source.getColorDefinition((unsigned int) i);
      pLCD = new CLColorDefinition(*pCD);
      this->mListOfColorDefinitions.add(pLCD, true);
      //colorIdToKeyMap.insert(std::pair<std::string,std::string>(pCD->getId(),pLCD->getKey()));
    }

  const GradientBase* pGD = NULL;

  CLGradientBase* pLGD = NULL;

  iMax = source.getNumGradientDefinitions();

  for (i = 0; i < iMax; ++i)
    {
      pGD = source.getGradientDefinition((unsigned int) i);

      if (dynamic_cast<const LinearGradient*>(pGD))
        {
          pLGD = new CLLinearGradient(*static_cast<const LinearGradient*>(pGD));
          this->mListOfGradientDefinitions.add(pLGD, true);
        }
      else if (dynamic_cast<const RadialGradient*>(source.getGradientDefinition((unsigned int) i)))
        {
          pLGD = new CLRadialGradient(*static_cast<const RadialGradient*>(pGD));
          this->mListOfGradientDefinitions.add(pLGD, true);
        }

      //gradientIdToKeyMap.insert(std::pair<std::string,std::string>(pGD->getId(),pLGD->getKey()));
    }

  const LineEnding* pLE = NULL;

  CLLineEnding* pLLE = NULL;

  iMax = source.getNumLineEndings();

  for (i = 0; i < iMax; ++i)
    {
      pLE = source.getLineEnding((unsigned int) i);
      pLLE = new CLLineEnding(*pLE);
      this->mListOfLineEndings.add(pLLE, true);
      //lineEndingIdToKeyMap.insert(std::pair<std::string,std::string>(pLE->getId(),pLLE->getKey()));
    }
}

/**
 * Destructor
 */
CLRenderInformationBase::~CLRenderInformationBase()
{
  CCopasiRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Returns the id of the referenced render information object..
 */
const std::string& CLRenderInformationBase::getReferenceRenderInformationKey() const
{
  return this->mReferenceRenderInformation;
}

/**
 * Sets the id of the referenced render information object.
 */
void CLRenderInformationBase::setReferenceRenderInformationKey(const std::string& key)
{
  this->mReferenceRenderInformation = key;
}

/**
 * Returns the number of color definitions.
 */
size_t CLRenderInformationBase::getNumColorDefinitions() const
{
  return this->mListOfColorDefinitions.size();
}

/**
 * Returns a pointer to the list of color definitions.
 */
CCopasiVector<CLColorDefinition>* CLRenderInformationBase::getListOfColorDefinitions()
{
  return &(this->mListOfColorDefinitions);
}

/**
 * Returns a const pointer to the list of color definitions.
 */
const CCopasiVector<CLColorDefinition>* CLRenderInformationBase::getListOfColorDefinitions() const
{
  return &(this->mListOfColorDefinitions);
}

/**
 * Returns a pointer to the color definition with the given index, or NULL
 *if the index is invalid.
 */
CLColorDefinition* CLRenderInformationBase::getColorDefinition(size_t index)
{
  return (index < this->mListOfColorDefinitions.size()) ? this->mListOfColorDefinitions[index] : NULL;
}

/**
 * Returns a const pointer to the color definition with the given index, or NULL
 *if the index is invalid.
 */
const CLColorDefinition* CLRenderInformationBase::getColorDefinition(size_t index) const
{
  return (index < this->mListOfColorDefinitions.size()) ? this->mListOfColorDefinitions[index] : NULL;
}

/**
 * Creates a new color definition.
 */
CLColorDefinition* CLRenderInformationBase::createColorDefinition()
{
  CLColorDefinition* pCD = new CLColorDefinition();
  this->mListOfColorDefinitions.add(pCD, true);
  return pCD;
}

/**
 * Removes the color definition with the given index.
 */
void CLRenderInformationBase::removeColorDefinition(size_t index)
{
  if (index < this->mListOfColorDefinitions.size())
    {
      this->mListOfColorDefinitions.remove(index);
    }
}

/**
 * Adds a copy of the given color definition to the end of the list of
 * color definitions.
 */
void CLRenderInformationBase::addColorDefinition(const CLColorDefinition* pCD)
{
  this->mListOfColorDefinitions.add(new CLColorDefinition(*pCD), true);
}

/**
 * Returns the number of gradient definitions.
 */
size_t CLRenderInformationBase::getNumGradientDefinitions() const
{
  return this->mListOfGradientDefinitions.size();
}

/**
 * Returns a pointer to the list of gradient definitions.
 */
CCopasiVector<CLGradientBase>* CLRenderInformationBase::getListOfGradientDefinitions()
{
  return &(this->mListOfGradientDefinitions);
}

/**
 * Returns a const pointer to the list of gradient definitions.
 */
const CCopasiVector<CLGradientBase>* CLRenderInformationBase::getListOfGradientDefinitions() const
{
  return &(this->mListOfGradientDefinitions);
}

/**
 * Returns a pointer to the gradient definition with the given index, or NULL
 *if the index is invalid.
 */
CLGradientBase* CLRenderInformationBase::getGradientDefinition(size_t index)
{
  return (index < this->mListOfGradientDefinitions.size()) ? this->mListOfGradientDefinitions[index] : NULL;
}

/**
 * Returns a const pointer to the gradient definition with the given index, or NULL
 *if the index is invalid.
 */
const CLGradientBase* CLRenderInformationBase::getGradientDefinition(size_t index) const
{
  return (index < this->mListOfGradientDefinitions.size()) ? this->mListOfGradientDefinitions[index] : NULL;
}

/**
 * Creates a new radial gradient definition.
 */
CLRadialGradient* CLRenderInformationBase::createRadialGradientDefinition()
{
  CLRadialGradient* pRG = new CLRadialGradient();
  this->mListOfGradientDefinitions.add(pRG, true);
  return pRG;
}

/**
 * Creates a new linear gradient definition.
 */
CLLinearGradient* CLRenderInformationBase::createLinearGradientDefinition()
{
  CLLinearGradient* pLG = new CLLinearGradient();
  this->mListOfGradientDefinitions.add(pLG, true);
  return pLG;
}

/**
 * Removes the gradient definition with the given index.
 */
void CLRenderInformationBase::removeGradientDefinition(size_t index)
{
  if (index < this->mListOfGradientDefinitions.size())
    {
      this->mListOfGradientDefinitions.remove(index);
    }
}

/**
 * Adds a copy of the given gradient definition to the end of the list of
 * gradient definitions.
 */
void CLRenderInformationBase::addGradientDefinition(const CLGradientBase* pGradient)
{
  if (dynamic_cast<const CLLinearGradient*>(pGradient))
    {
      this->mListOfGradientDefinitions.add(new CLLinearGradient(*static_cast<const CLLinearGradient*>(pGradient)), true);
    }
  else if (dynamic_cast<const CLRadialGradient*>(pGradient))
    {
      this->mListOfGradientDefinitions.add(new CLRadialGradient(*static_cast<const CLRadialGradient*>(pGradient)), true);
    }
}

/**
 * Returns the number of line endings.
 */
size_t CLRenderInformationBase::getNumLineEndings() const
{
  return this->mListOfLineEndings.size();
}

/**
 * Returns a pointer to the list of line endings.
 */
CCopasiVector<CLLineEnding>* CLRenderInformationBase::getListOfLineEndings()
{
  return &(this->mListOfLineEndings);
}

/**
 * Returns a const pointer to the list of line endings.
 */
const CCopasiVector<CLLineEnding>* CLRenderInformationBase::getListOfLineEndings() const
{
  return &(this->mListOfLineEndings);
}

/**
 * Returns a pointer to the line ending with the given index, or NULL
 *if the index is invalid.
 */
CLLineEnding* CLRenderInformationBase::getLineEnding(size_t index)
{
  return (index < this->mListOfLineEndings.size()) ? this->mListOfLineEndings[index] : NULL;
}

/**
 * Returns a const pointer to the line ending with the given index, or NULL
 *if the index is invalid.
 */
const CLLineEnding* CLRenderInformationBase::getLineEnding(size_t index) const
{
  return (index < this->mListOfLineEndings.size()) ? this->mListOfLineEndings[index] : NULL;
}

/**
 * Creates a new line ending.
 */
CLLineEnding* CLRenderInformationBase::createLineEnding()
{
  CLLineEnding* pLE = new CLLineEnding();
  this->mListOfLineEndings.add(pLE, true);
  return pLE;
}

/**
 * Removes the line ending with the given index.
 */
void CLRenderInformationBase::removeLineEnding(size_t index)
{
  if (index < this->mListOfLineEndings.size())
    {
      this->mListOfLineEndings.remove(index);
    }
}

/**
 * Adds a copy of the given line ending to the end of the list of line
 *endings.
 */
void CLRenderInformationBase::addLineEnding(const CLLineEnding* pLE)
{
  this->mListOfLineEndings.add(new CLLineEnding(*pLE), true);
}

const std::string& CLRenderInformationBase::getBackgroundColor() const
{
  return mBackgroundColor;
}

void CLRenderInformationBase::setBackgroundColor(const std::string& bg)
{
  this->mBackgroundColor = bg;
}

/**
 * Returns the key of the color definition.
 */
const std::string& CLRenderInformationBase::getKey() const
{
  return this->mKey;
}

/**
 * Adds the attributes for a graphical primitive 1D object to the passed in.
 * object.
 */
void CLRenderInformationBase::addSBMLAttributes(RenderInformationBase* pBase
    /*
        ,std::map<std::string,std::string>& colorKeyToIdMap
        ,std::map<std::string,std::string>& gradientKeyToIdMap
        ,std::map<std::string,std::string>& lineEndingKeyToIdMap
    */
                                               ) const
{
  pBase->setReferenceRenderInformationId(this->getReferenceRenderInformationKey());
  pBase->setBackgroundColor(this->getBackgroundColor());
  size_t i, iMax = this->mListOfColorDefinitions.size();
  int result;

  for (i = 0; i < iMax; ++i)
    {
      ColorDefinition* pCD = this->getColorDefinition(i)->toSBML(pBase->getLevel(), pBase->getVersion());
      result = pBase->addColorDefinition(pCD);
      assert(result == LIBSBML_OPERATION_SUCCESS);
      //colorKeyToIdMap.insert(std::pair<std::string,std::string>(this->getColorDefinition(i)->getKey(),pCD->getId()));
      delete pCD;
    }

  iMax = this->mListOfGradientDefinitions.size();
  GradientBase* pGB = NULL;
  const CLGradientBase* pLGB = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pLGB = this->getGradientDefinition(i);

      if (dynamic_cast<const CLRadialGradient*>(pLGB))
        {
          pGB = static_cast<const CLRadialGradient*>(pLGB)->toSBML(pBase->getLevel(), pBase->getVersion());
        }
      else
        {
          pGB = static_cast<const CLLinearGradient*>(pLGB)->toSBML(pBase->getLevel(), pBase->getVersion());
        }

      result = pBase->addGradientDefinition(pGB);
      assert(result == LIBSBML_OPERATION_SUCCESS);
      //gradientKeyToIdMap.insert(std::pair<std::string,std::string>(pLGB->getKey(),pGB->getId()));
      delete pGB;
    }

  iMax = this->mListOfLineEndings.size();

  for (i = 0; i < iMax; ++i)
    {
      LineEnding* pLE = this->getLineEnding(i)->toSBML(pBase->getLevel(), pBase->getVersion());
      result = pBase->addLineEnding(pLE);
      assert(result == LIBSBML_OPERATION_SUCCESS);
      //lineEndingKeyToIdMap.insert(std::pair<std::string,std::string>(this->getLineEnding(i)->getKey(),pLE->getId()));
      delete pLE;
    }
}

/**
 * Sets the name of the object.
 */
void CLRenderInformationBase::setName(const std::string& name)
{
  this->mName = name;
}

/**
 * Returns the name of the object.
 */
const std::string& CLRenderInformationBase::getName() const
{
  return this->mName;
}
