// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLLocalRenderInformation.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:21 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <assert.h>

#define USE_LAYOUT 1

#ifdef USE_CRENDER_EXTENSION
#define USE_RENDER 1
#endif // USE_CRENDER_EXTENSION

#include <sbml/layout/render/LocalRenderInformation.h>

#include "CLLocalRenderInformation.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 *  Constructor.
 */
CLLocalRenderInformation::CLLocalRenderInformation(CCopasiContainer* pParent):
    CLRenderInformationBase("LocalRenderInformation", pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LocalRenderInformation", this);
}

/**
 * Copy constructor
 */
CLLocalRenderInformation::CLLocalRenderInformation(const CLLocalRenderInformation& source, CCopasiContainer* pParent):
    CLRenderInformationBase(source, pParent),
    mListOfStyles(source.mListOfStyles, this)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LocalRenderInformation", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLLocalRenderInformation::CLLocalRenderInformation(const LocalRenderInformation& source,
    /*
            std::map<std::string,std::string>& colorIdToKeyMap,
            std::map<std::string,std::string>& gradientIdToKeyMap,
            std::map<std::string,std::string>& lineEndingIdToKeyMap,
        */
    CCopasiContainer* pParent):
    //CLRenderInformationBase(source,"LocalRenderInformation",colorIdToKeyMap,gradientIdToKeyMap,lineEndingIdToKeyMap,pParent)
    CLRenderInformationBase(source, "LocalRenderInformation", pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LocalRenderInformation", this);
  size_t i, iMax = source.getNumStyles();

  for (i = 0; i < iMax; ++i)
    {
      this->mListOfStyles.add(new CLLocalStyle(*source.getStyle((unsigned int) i)), true);
    }
}

/**
 * Returns the number of styles.
 */
size_t CLLocalRenderInformation::getNumStyles() const
{
  return this->mListOfStyles.size();
}

/**
 * Returns a pointer to the LitOfStyles object.
 */
CCopasiVector<CLLocalStyle>* CLLocalRenderInformation::getListOfStyles()
{
  return &(this->mListOfStyles);
}

/**
 * Returns a pointer to the LitOfStyles object.
 */
const CCopasiVector<CLLocalStyle>* CLLocalRenderInformation::getListOfStyles() const
{
  return &(this->mListOfStyles);
}

/**
 * Returns a pointer to the style with the given index.
 * If the index is invalid, NULL is returned.
 */
CLLocalStyle* CLLocalRenderInformation::getStyle(size_t i)
{
  return (i < this->mListOfStyles.size()) ? this->mListOfStyles[i] : NULL;
}

/**
 * Returns a pointer to the style with the given index.
 * If the index is invalid, NULL is returned.
 */
const CLLocalStyle* CLLocalRenderInformation::getStyle(size_t i) const
{
  return (i < this->mListOfStyles.size()) ? this->mListOfStyles[i] : NULL;
}

CLLocalStyle* CLLocalRenderInformation::createStyle()
{
  CLLocalStyle* pStyle = new CLLocalStyle();
  this->mListOfStyles.add(pStyle, true);
  return pStyle;
}

void CLLocalRenderInformation::addStyle(const CLLocalStyle* pStyle)
{
  this->mListOfStyles.add(new CLLocalStyle(*pStyle), true);
}

/**
 * Converts this object to the corresponding SBML object.
 */
LocalRenderInformation* CLLocalRenderInformation::toSBML(unsigned int level, unsigned int version) const
{
  LocalRenderInformation* pLRI = new LocalRenderInformation(level, version);
  //this->addSBMLAttributes(pLRI,colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
  this->addSBMLAttributes(pLRI);
  size_t i, iMax = this->mListOfStyles.size();

  for (i = 0; i < iMax; ++i)
    {
      LocalStyle* pStyle = this->getStyle(i)->toSBML(level, version);
      int result = pLRI->addStyle(pStyle);
      assert(result == LIBSBML_OPERATION_SUCCESS);
      delete pStyle;
    }

  return pLRI;
}
