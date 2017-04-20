// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>
#include <assert.h>

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/GlobalRenderInformation.h>

#include "CLGlobalRenderInformation.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

// static
CLGlobalRenderInformation * CLGlobalRenderInformation::fromData(const CData & data)
{
  return new CLGlobalRenderInformation(NO_PARENT);
}

/**
 *  Constructor.
 */
CLGlobalRenderInformation::CLGlobalRenderInformation(CDataContainer* pParent):
  CLRenderInformationBase("GlobalRenderInformation", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("GlobalRenderInformation", this);
}

/**
 * Copy constructor
 */
CLGlobalRenderInformation::CLGlobalRenderInformation(const CLGlobalRenderInformation& source, CDataContainer* pParent):
  CLRenderInformationBase(source, pParent),
  mListOfStyles(source.mListOfStyles, this)
{
  this->mKey = CRootContainer::getKeyFactory()->add("GlobalRenderInformation", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLGlobalRenderInformation::CLGlobalRenderInformation(const GlobalRenderInformation& source,
    /*
            std::map<std::string,std::string>& colorIdToKeyMap,
            std::map<std::string,std::string>& gradientIdToKeyMap,
            std::map<std::string,std::string>& lineEndingIdToKeyMap,
      */
    CDataContainer* pParent):
  //CLRenderInformationBase(source,"GlobalRenderInformation",colorIdToKeyMap,gradientIdToKeyMap,lineEndingIdToKeyMap,pParent)
  CLRenderInformationBase(source, "GlobalRenderInformation", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("GlobalRenderInformation", this);
  unsigned int i, iMax = source.getNumStyles();

  for (i = 0; i < iMax; ++i)
    {
      this->mListOfStyles.add(new CLGlobalStyle(*static_cast<const GlobalStyle*>(source.getStyle(i))), true);
    }
}

/**
 * Returns the number of styles.
 */
size_t CLGlobalRenderInformation::getNumStyles() const
{
  return this->mListOfStyles.size();
}

/**
 * Returns a pointer to the LitOfStyles object.
 */
CDataVector<CLGlobalStyle>* CLGlobalRenderInformation::getListOfStyles()
{
  return &(this->mListOfStyles);
}

/**
 * Returns a pointer to the ListOfStyles object.
 */
const CDataVector<CLGlobalStyle>* CLGlobalRenderInformation::getListOfStyles() const
{
  return &(this->mListOfStyles);
}

/**
 * Returns a pointer to the style with the given index.
 * If the index is invalid, NULL is returned.
 */
CLStyle* CLGlobalRenderInformation::getStyle(size_t i)
{
  return (i < this->mListOfStyles.size()) ? &this->mListOfStyles[i] : NULL;
}

/**
 * Returns a pointer to the style with the given index.
 * If the index is invalid, NULL is returned.
 */
const CLStyle* CLGlobalRenderInformation::getStyle(size_t i) const
{
  return (i < this->mListOfStyles.size()) ? &this->mListOfStyles[i] : NULL;
}

CLStyle* CLGlobalRenderInformation::createStyle()
{
  CLGlobalStyle* pStyle = new CLGlobalStyle();
  this->mListOfStyles.add(pStyle, true);
  return pStyle;
}

void CLGlobalRenderInformation::addStyle(const CLGlobalStyle* pStyle)
{
  this->mListOfStyles.add(new CLGlobalStyle(*pStyle), true);
}

/**
 * Converts this object to the corresponding SBML object.
 *
 */
bool CLGlobalRenderInformation::toSBML(GlobalRenderInformation* pGRI, unsigned int level, unsigned int version) const
{
  bool result = true;
  this->addSBMLAttributes(pGRI);
  size_t i, iMax = this->mListOfStyles.size();

  for (i = 0; i < iMax; ++i)
    {
      GlobalStyle* pStyle = static_cast<const CLGlobalStyle*>(this->getStyle(i))->toSBML(level, version);
      int success = pGRI->addStyle(pStyle);
      assert(success == LIBSBML_OPERATION_SUCCESS);
      result = (result && (success == LIBSBML_OPERATION_SUCCESS));
      delete pStyle;
    }

  return result;
}
