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

#include <sstream>
#include <assert.h>

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/sbml/GlobalRenderInformation.h>

#include "CLGlobalRenderInformation.h"
#include "CLGraphicalObject.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

// static
CLGlobalRenderInformation * CLGlobalRenderInformation::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLGlobalRenderInformation(NO_PARENT);
}

// virtual
CData CLGlobalRenderInformation::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLGlobalRenderInformation::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
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

const CLStyle * CLGlobalRenderInformation::getStyleForGraphicalObject(const CLGraphicalObject * pObject) const
{
  if (!pObject)
    return NULL;

  std::vector< const CLStyle * > possibleTypes;

for (const CLStyle & pStyle : mListOfStyles)
    {
      if (pStyle.isInRoleList(pObject->getObjectRole()))
        {
          return &pStyle;
        }

      if (pStyle.isInTypeList(getTypeForObject(pObject)))
        {
          possibleTypes.push_back(&pStyle);
          continue;
        }
    }

  if (!possibleTypes.empty())
    return possibleTypes.front();

  return NULL;
}

#include "CLGlyphs.h"
#include "CLReactionGlyph.h"

std::string CLGlobalRenderInformation::getTypeForObject(const CLGraphicalObject * pObject)
{
  if (dynamic_cast< const CLCompartmentGlyph * >(pObject) != NULL)
    return "COMPARTMENTGLYPH";

  if (dynamic_cast< const CLMetabGlyph * >(pObject) != NULL)
    return "SPECIESGLYPH";

  if (dynamic_cast< const CLReactionGlyph * >(pObject) != NULL)
    return "REACTIONGLYPH";

  if (dynamic_cast< const CLMetabReferenceGlyph * >(pObject) != NULL)
    return "SPECIESREFERENCEGLYPH";

  if (dynamic_cast< const CLTextGlyph* >(pObject) != NULL)
    return "TEXTGLYPH";

  if (dynamic_cast< const CLGeneralGlyph * >(pObject) != NULL)
    return "GENERALGLYPH";

  return std::string("GRAPHICALOBJECT");
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
