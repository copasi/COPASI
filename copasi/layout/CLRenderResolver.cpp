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



#include "CLRenderResolver.h"

#include <set>
#include <assert.h>

#include "copasi/layout/CLRenderInformationBase.h"
#include "copasi/layout/CLStyle.h"
#include "copasi/layout/CLColorDefinition.h"
#include "copasi/layout/CLLineEnding.h"
#include "copasi/layout/CLGradientBase.h"
#include "copasi/layout/CLGraphicalObject.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLReactionGlyph.h"

#include "CLRenderFlattener.h"

/**
 * Constructor that takes a local render information object as the argument
 * as well as a list of local and a list of global render information objects
 * that are needed to resolve external references.
 */
CLRenderResolver::CLRenderResolver(const CLLocalRenderInformation& renderInformation,
                                   const CDataVector<CLLocalRenderInformation>& localList,
                                   const CDataVector<CLGlobalRenderInformation>& globalList)
  : mpRenderInformation(CLRenderFlattener::flatten_render_information(renderInformation, localList, globalList)),
    mLocal(true),
    mpBackgroundColor(NULL)
{
  // fill the maps
  this->fill_base_maps(this->mpRenderInformation);
  this->fill_local_maps(dynamic_cast<const CLLocalRenderInformation*>(mpRenderInformation));
  this->setBackgroundColor();
}

void CLRenderResolver::setBackgroundColor()
{
  if (this->mpRenderInformation)
    {
      std::string id = this->mpRenderInformation->getBackgroundColor();

      if (id.empty())
        {
          id = "#ffffff";
          mpRenderInformation->setBackgroundColor(id);
        }

      // must be a color value
      if (id[0] == '#')
        {
          assert(id.length() == 7 || id.length() == 9);
          this->mpBackgroundColor = new CLColorDefinition();
          this->mpBackgroundColor->setColorValue(id);
        }
      else // must be an id
        {
          const CLColorDefinition* pColor = this->getColorDefinition(id);

          if (pColor)
            {
              // make a copy
              this->mpBackgroundColor = new CLColorDefinition(*pColor);
            }
        }
    }
}

/**
 * Constructor that takes a global render information object as the argument
 * and a list of additional global render information objects that might be
 * needed to resolve external references.
 * means it should contain all information from referenced render information objects.
 */
CLRenderResolver::CLRenderResolver(const CLGlobalRenderInformation& renderInformation,
                                   const CDataVector<CLGlobalRenderInformation>& globalList)
  : mpRenderInformation(CLRenderFlattener::flatten_render_information(renderInformation, globalList)),
    mLocal(false),
    mpBackgroundColor(NULL)
{
  // fill the maps
  this->fill_base_maps(this->mpRenderInformation);
  this->fill_global_maps(dynamic_cast<const CLGlobalRenderInformation*>(this->mpRenderInformation));
  this->setBackgroundColor();
}

CLRenderResolver::~CLRenderResolver()
{
  // we need to delete the render information object that has been created by
  // the flattener
  if (this->mpRenderInformation != NULL) delete this->mpRenderInformation;

  // delete the background color
  if (this->mpBackgroundColor != NULL) delete this->mpBackgroundColor;
}

/**
 * This method fills the color, gradient and line ending maps for a render
 * information object.
 */
void CLRenderResolver::fill_base_maps(const CLRenderInformationBase* pRenderInformation)
{
  // fill maps for colors, gradients and line endings
  size_t i, iMax = pRenderInformation->getNumColorDefinitions();
  const CLColorDefinition* pColor = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pColor = pRenderInformation->getColorDefinition(i);
      this->mColorMap[pColor->getId()] = pColor;
    }

  iMax = pRenderInformation->getNumGradientDefinitions();
  const CLGradientBase* pGradient = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pGradient = pRenderInformation->getGradientDefinition(i);
      this->mGradientMap[pGradient->getId()] = pGradient;
    }

  iMax = pRenderInformation->getNumLineEndings();
  const CLLineEnding* pLineEnding = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pLineEnding = pRenderInformation->getLineEnding(i);
      this->mLineEndingMap[pLineEnding->getId()] = pLineEnding;
    }
}

/**
 * This method fills the type and role maps for a global render information
 * object.
 */
void CLRenderResolver::fill_global_maps(const CLGlobalRenderInformation* pRenderInformation)
{
  size_t i, iMax = pRenderInformation->getNumStyles();
  const CLStyle* pStyle = NULL;

  for (i = 0 ; i < iMax ; ++i)
    {
      pStyle = pRenderInformation->getStyle(i);
      const std::set<std::string>& roleList = pStyle->getRoleList();
      std::set<std::string>::const_iterator it = roleList.begin(), endit = roleList.end();

      while (it != endit)
        {
          this->mRoleMap[*it] = pStyle;
          ++it;
        }

      const std::set<std::string>& typeList = pStyle->getTypeList();

      it = typeList.begin();

      endit = typeList.end();

      while (it != endit)
        {
          this->mTypeMap[*it] = pStyle;
          ++it;
        }
    }
}

/**
 * This method fills the type, role and id maps for a local render information
 * object.
 */
void CLRenderResolver::fill_local_maps(const CLLocalRenderInformation* pRenderInformation)
{
  size_t i, iMax = pRenderInformation->getNumStyles();
  const CLStyle* pStyle = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pStyle = pRenderInformation->getStyle(i);
      const std::set<std::string>& roleList = pStyle->getRoleList();
      std::set<std::string>::const_iterator it = roleList.begin(), endit = roleList.end();

      while (it != endit)
        {
          this->mRoleMap[*it] = pStyle;
          ++it;
        }

      const std::set<std::string>& typeList = pStyle->getTypeList();

      it = typeList.begin();

      endit = typeList.end();

      while (it != endit)
        {
          this->mTypeMap[*it] = pStyle;
          ++it;
        }

      const CLLocalStyle* pLocalStyle = dynamic_cast<const CLLocalStyle*>(pStyle);

      const std::set<std::string>& keyList = pLocalStyle->getKeyList();

      it = keyList.begin();

      endit = keyList.end();

      while (it != endit)
        {
          this->mKeyMap[*it] = pStyle;
          ++it;
        }
    }
}

/**
 * Method that tries to find the style for the given graphical
 * object that fits best.
 * If no style is found NULL is returned.
 */
const CLStyle* CLRenderResolver::resolveStyle(const CLGraphicalObject* pObject) const
{
  const CLStyle* pResult = NULL;
  // try to resolve the id first
  pResult = this->resolveStyleForKey(pObject->getKey());

  // next try the role
  if (pResult == NULL)
    {
      std::string role = pObject->getObjectRole();
      const CLReferenceGlyph* pRG = dynamic_cast<const CLReferenceGlyph*>(pObject);

      if (pRG != NULL && role.empty())
        role = pRG->getRole();

      const CLMetabReferenceGlyph* pSRG = dynamic_cast<const CLMetabReferenceGlyph*>(pObject);

      if (pSRG != NULL && role.empty())
        {
          CLMetabReferenceGlyph::Role role_t = pSRG->getRole();

          switch (role_t)
            {
              case CLMetabReferenceGlyph::SUBSTRATE:
                role = "substrate";
                break;

              case CLMetabReferenceGlyph::PRODUCT:
                role = "product";
                break;

              case CLMetabReferenceGlyph::SIDESUBSTRATE:
                role = "sidesubstrate";
                break;

              case CLMetabReferenceGlyph::SIDEPRODUCT:
                role = "sideproduct";
                break;

              case CLMetabReferenceGlyph::MODIFIER:
                role = "modifier";
                break;

              case CLMetabReferenceGlyph::ACTIVATOR:
                role = "activator";
                break;

              case CLMetabReferenceGlyph::INHIBITOR:
                role = "inhibitor";
                break;

              default:
                role = "";
            }

          // try if we can find a role in the deduced role map
          if (role.empty())
            {
              std::map<const CLMetabReferenceGlyph*, std::string>::const_iterator pos = this->mDeducedObjectRoles.find(pSRG);

              if (pos != this->mDeducedObjectRoles.end())
                {
                  role = pos->second;
                }
            }
        }

      if (!role.empty())
        {
          pResult = this->resolveStyleForRole(role);
        }

      // last try the type
      if (pResult == NULL)
        {
          std::string type = "GRAPHICALOBJECT";

          if (dynamic_cast<const CLCompartmentGlyph*>(pObject))
            {
              type = "COMPARTMENTGLYPH";
            }
          else if (dynamic_cast<const CLMetabGlyph*>(pObject))
            {
              type = "SPECIESGLYPH";
            }
          else if (dynamic_cast<const CLReactionGlyph*>(pObject))
            {
              type = "REACTIONGLYPH";
            }
          else if (dynamic_cast<const CLMetabReferenceGlyph*>(pObject))
            {
              type = "SPECIESREFERENCEGLYPH";
            }
          else if (dynamic_cast<const CLTextGlyph*>(pObject))
            {
              type = "TEXTGLYPH";
            }

          pResult = this->resolveStyleForType(type);
        }
    }

  return pResult;
}

/**
 * Method that tries to find the style for the given role.
 * If no style is found NULL is returned.
 */
const CLStyle* CLRenderResolver::resolveStyleForRole(const std::string& role) const
{
  const CLStyle* pResult = NULL;
  std::map<std::string, const CLStyle*>::const_iterator pos = this->mRoleMap.find(role);

  if (pos != this->mRoleMap.end())
    {
      pResult = pos->second;
    }

  return pResult;
}

/**
 * Method that tries to find the style for the given type.
 * If no style is found NULL is returned.
 */
const CLStyle* CLRenderResolver::resolveStyleForType(const std::string& type) const
{
  const CLStyle* pResult = NULL;
  std::map<std::string, const CLStyle*>::const_iterator pos = this->mTypeMap.find(type);

  if (pos != this->mTypeMap.end())
    {
      pResult = pos->second;
    }
  // look for a style that is valid for ANY type
  else
    {
      pos = this->mTypeMap.find("ANY");

      if (pos != this->mTypeMap.end())
        {
          pResult = pos->second;
        }
    }

  return pResult;
}

/**
 * Method that tries to find the style for the given key.
 * If no style is found NULL is returned.
 */
const CLStyle* CLRenderResolver::resolveStyleForKey(const std::string& key) const
{
  const CLStyle* pResult = NULL;
  std::map<std::string, const CLStyle*>::const_iterator pos = this->mKeyMap.find(key);

  if (pos != this->mKeyMap.end())
    {
      pResult = pos->second;
    }

  return pResult;
}

void CLRenderResolver::removeKeyFromMap(const std::string& key)
{
  std::map< std::string, const CLStyle * >::iterator pos = mKeyMap.find(key);

  if (pos != mKeyMap.end())
    {
      mKeyMap.erase(pos);
    }
}

void CLRenderResolver::addKeyToMap(const std::string& key, const CLStyle* pStyle)
{
  removeKeyFromMap(key);
  mKeyMap[key] = pStyle;
}

/**
 * Returns the gradient definition for a given id.
 */
const CLGradientBase* CLRenderResolver::getGradientBase(const std::string& id) const
{
  const CLGradientBase* pResult = NULL;
  std::map<std::string, const CLGradientBase*>::const_iterator pos = this->mGradientMap.find(id);

  if (pos != this->mGradientMap.end())
    {
      pResult = pos->second;
    }

  return pResult;
}

/**
 * Returns the color definition for a given id.
 */
const CLColorDefinition* CLRenderResolver::getColorDefinition(const std::string& id) const
{
  const CLColorDefinition* pResult = NULL;
  std::map<std::string, const CLColorDefinition*>::const_iterator pos = this->mColorMap.find(id);

  if (pos != this->mColorMap.end())
    {
      pResult = pos->second;
    }

  return pResult;
}

/**
 * Returns the line ending for a given id.
 */
const CLLineEnding* CLRenderResolver::getLineEnding(const std::string& id) const
{
  const CLLineEnding* pResult = NULL;
  std::map<std::string, const CLLineEnding*>::const_iterator pos = this->mLineEndingMap.find(id);

  if (pos != this->mLineEndingMap.end())
    {
      pResult = pos->second;
    }

  return pResult;
}

/**
 * Returns the background color.
 */
const CLColorDefinition* CLRenderResolver::getBackgroundColor() const
{
  return this->mpBackgroundColor;
}

/**
 * Sets the deduced object roles.
 */
void  CLRenderResolver::setDeducedObjectRoles(const std::map<const CLMetabReferenceGlyph*, std::string>& deducedObjectRoles)
{
  this->mDeducedObjectRoles = deducedObjectRoles;
}

CDataModel * CLRenderResolver::getObjectDataModel() const
{
  CDataModel * pDataModel = mpRenderInformation->getObjectDataModel();

  assert(pDataModel != NULL);

  return pDataModel;
}
