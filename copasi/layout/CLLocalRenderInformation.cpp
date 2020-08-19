// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <assert.h>

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/LocalRenderInformation.h>

#include "CLLocalRenderInformation.h"
#include "CLGraphicalObject.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

// static
CLLocalRenderInformation * CLLocalRenderInformation::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLLocalRenderInformation(NO_PARENT);
}

// virtual
CData CLLocalRenderInformation::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLLocalRenderInformation::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

/**
 *  Constructor.
 */
CLLocalRenderInformation::CLLocalRenderInformation(CDataContainer* pParent):
  CLRenderInformationBase("LocalRenderInformation", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LocalRenderInformation", this);
}

/**
 * Copy constructor
 */
CLLocalRenderInformation::CLLocalRenderInformation(const CLLocalRenderInformation& source, CDataContainer* pParent):
  CLRenderInformationBase(source, pParent),
  mListOfStyles(source.mListOfStyles, this)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LocalRenderInformation", this);
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
    CDataContainer* pParent):
  //CLRenderInformationBase(source,"LocalRenderInformation",colorIdToKeyMap,gradientIdToKeyMap,lineEndingIdToKeyMap,pParent)
  CLRenderInformationBase(source, "LocalRenderInformation", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LocalRenderInformation", this);
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
CDataVector<CLLocalStyle>* CLLocalRenderInformation::getListOfStyles()
{
  return &(this->mListOfStyles);
}

/**
 * Returns a pointer to the LitOfStyles object.
 */
const CDataVector<CLLocalStyle>* CLLocalRenderInformation::getListOfStyles() const
{
  return &(this->mListOfStyles);
}

/**
 * Returns a pointer to the style with the given index.
 * If the index is invalid, NULL is returned.
 */
CLLocalStyle* CLLocalRenderInformation::getStyle(size_t i)
{
  return (i < this->mListOfStyles.size()) ? &this->mListOfStyles[i] : NULL;
}

/**
 * Returns a pointer to the style with the given index.
 * If the index is invalid, NULL is returned.
 */
const CLLocalStyle* CLLocalRenderInformation::getStyle(size_t i) const
{
  return (i < this->mListOfStyles.size()) ? &this->mListOfStyles[i] : NULL;
}

CLStyle * CLLocalRenderInformation::createStyle()
{
  CLLocalStyle* pStyle = new CLLocalStyle();
  this->mListOfStyles.add(pStyle, true);
  return pStyle;
}

const CLStyle * CLLocalRenderInformation::getStyleForGraphicalObject(const CLGraphicalObject * pObject) const
{
  if (!pObject)
    return NULL;

  std::vector< const CLStyle * > possibleRoles;
  std::vector< const CLStyle * > possibleTypes;

for (const CLLocalStyle & pStyle : mListOfStyles)
    {
      if (pStyle.isKeyInSet(pObject->getKey()))
        return &pStyle;

      if (pStyle.isInRoleList(pObject->getObjectRole()))
        {
          possibleRoles.push_back(&pStyle);
          continue;
        }

      if (pStyle.isInTypeList(pObject->getObjectType()))
        {
          possibleTypes.push_back(&pStyle);
          continue;
        }
    }

  if (!possibleRoles.empty())
    return possibleRoles.front();

  if (!possibleTypes.empty())
    return possibleTypes.front();

  return NULL;

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
