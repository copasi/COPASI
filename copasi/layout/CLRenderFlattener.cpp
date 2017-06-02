// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CLRenderFlattener.h"

#include <map>
#include <list>
#include <string>
#include <assert.h>
#include <typeinfo>
#include <algorithm>

#include "copasi/layout/CLLocalStyle.h"
#include "copasi/layout/CLGlobalStyle.h"
#include "copasi/layout/CLRenderInformationBase.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 * static method that takes a const reference to a global render
 * information object and resolves all references.
 * The returned object is a new global render information object and the
 * caller is responsible for freeing the memory once it is no longer used.
 * If references can not be resolved, an unresolved_reference_exception is
 * thrown.
 */
CLGlobalRenderInformation* CLRenderFlattener::flatten_render_information(const CLGlobalRenderInformation& globalRenderInformation, const CDataVector<CLGlobalRenderInformation>& globalList)
{
  CDataVector<CLLocalRenderInformation> empty;

  return dynamic_cast<CLGlobalRenderInformation*>(CLRenderFlattener::flatten(globalRenderInformation, globalList, empty));
}

/**
 * static method that takes a const reference to a local render
 * information object and resolves all references.
 * The returned object is a new local render information object and the
 * caller is responsible for freeing the memory once it is no longer used.
 * If references can not be resolved, an unresolved_reference_exception is
 * thrown.
 */
CLLocalRenderInformation* CLRenderFlattener::flatten_render_information(const CLLocalRenderInformation& localRenderInformation, const CDataVector<CLLocalRenderInformation>& localList, const CDataVector<CLGlobalRenderInformation>& globalList)
{
  return dynamic_cast<CLLocalRenderInformation*>(CLRenderFlattener::flatten(localRenderInformation, globalList, localList));
}

/**
 * Takes a reference to any type of render information and two lists. The
 * first list is a list of global render information objects, the second list is a list of local render information objects.
 * If the object that is passed in is a global render information object,
 * the second list is not considered.
 */
CLRenderInformationBase* CLRenderFlattener::flatten(const CLRenderInformationBase& renderInformation, const CDataVector<CLGlobalRenderInformation>& globalList, const CDataVector<CLLocalRenderInformation>& localList)
{
  CLRenderInformationBase* pResult = NULL;

  // the result should be of the same type as the type that is passed in
  bool local = dynamic_cast<const CLLocalRenderInformation*>(&renderInformation) != NULL;

  // create a list of referenced render information objects
  std::vector< const CLRenderInformationBase * > referenceChain;
  const CLRenderInformationBase* pCurrent = &renderInformation;
  const CLRenderInformationBase* pNext = NULL;

  while (pCurrent != NULL)
    {
      // check for reference loops in reference chain
      if (std::find(referenceChain.begin(), referenceChain.end(), pCurrent) != referenceChain.end())
        {
          // we have a loop
          CCopasiMessage(CCopasiMessage::EXCEPTION, "Fatal Error. Found a loop in the referenceRenderInformation attribute chain of the render information");
        }

      referenceChain.push_back(pCurrent);
      std::string referenceKey = pCurrent->getReferenceRenderInformationKey();

      // search the local list if we are dealing with local render information
      if (!referenceKey.empty())
        {
          if (local && localList.size() != 0)
            {
              size_t j = 0, jMax = localList.size();

              while (j < jMax)
                {
                  if (localList[j].getKey() == referenceKey)
                    {
                      pNext = dynamic_cast<const CLRenderInformationBase*>(&localList[j]);
                      break;
                    }

                  ++j;
                }
            }

          // search the global list if necessary
          if (!pNext && globalList.size() != 0)
            {
              size_t j = 0, jMax = globalList.size();

              while (j < jMax)
                {
                  if (globalList[j].getKey() == referenceKey)
                    {
                      pNext = dynamic_cast<const CLRenderInformationBase*>(&globalList[j]);
                      break;
                    }

                  ++j;
                }
            }

          // make sure, we actually find the referenced render information
          if (pNext)
            {
              pCurrent = pNext;
              pNext = NULL;
            }
          else
            {
              throw CLUnresolvedReferenceException(referenceKey);
            }
        }
      else
        {
          // we are at the end
          pCurrent = NULL;
        }
    }

  // no we have to create a flattened version of the list.
  std::map<std::string, const CLStyle*> keyMap;
  std::map<std::string, const CLStyle*> typeMap;
  std::map<std::string, const CLStyle*> roleMap;
  std::map<std::string, const CLColorDefinition*> colors;
  std::map<std::string, const CLLineEnding*> lineEndings;
  std::map<std::string, const CLGradientBase*> gradients;
  std::vector< const CLRenderInformationBase * >::const_iterator it = referenceChain.begin(), endit = referenceChain.end();
  size_t i, iMax;
  const CLColorDefinition* pColorDefinition = NULL;
  const CLGradientBase* pGradientBase = NULL;
  const CLLineEnding* pLineEnding = NULL;

  while (it != endit)
    {
      // go through all styles in the current render information
      // and add each style to one or more maps, depending on whether it
      // specifies an id, a role and/or a type list
      // it is only added to the list, if the list doesn't already contain
      // an item for the id, role or type
      iMax = (*it)->getListOfColorDefinitions()->size();

      for (i = 0; i < iMax; ++i)
        {
          pColorDefinition = (*it)->getColorDefinition(i);

          if (colors.find(pColorDefinition->getId()) == colors.end())
            {
              colors.insert(std::pair<std::string, const CLColorDefinition*>(pColorDefinition->getId(), pColorDefinition));
            }
        }

      iMax = (*it)->getListOfGradientDefinitions()->size();

      for (i = 0; i < iMax; ++i)
        {
          pGradientBase = (*it)->getGradientDefinition(i);

          if (gradients.find(pGradientBase->getId()) == gradients.end())
            {
              gradients.insert(std::pair<std::string, const CLGradientBase*>(pGradientBase->getId(), pGradientBase));
            }
        }

      iMax = (*it)->getListOfLineEndings()->size();

      for (i = 0; i < iMax; ++i)
        {
          pLineEnding = (*it)->getLineEnding(i);

          if (lineEndings.find(pLineEnding->getId()) == lineEndings.end())
            {
              lineEndings.insert(std::pair<std::string, const CLLineEnding*>(pLineEnding->getId(), pLineEnding));
            }
        }

      const CLLocalRenderInformation* pRenderInformation = dynamic_cast<const CLLocalRenderInformation*>(*it);

      if (pRenderInformation)
        {
          const CLLocalStyle* pStyle = NULL;
          iMax = pRenderInformation->getListOfStyles()->size();

          for (i = 0; i < iMax; ++i)
            {
              pStyle = pRenderInformation->getStyle(i);
              const std::set<std::string>& idSet = pStyle->getKeyList();
              std::set<std::string>::const_iterator sIt = idSet.begin(), sEndit = idSet.end();

              while (sIt != sEndit)
                {
                  if (keyMap.find(*sIt) == keyMap.end())
                    {
                      keyMap.insert(std::pair<std::string, const CLStyle*>(*sIt, pStyle));
                    }

                  ++sIt;
                }

              const std::set<std::string>& roleSet = pStyle->getRoleList();

              sIt = roleSet.begin();

              sEndit = roleSet.end();

              while (sIt != sEndit)
                {
                  if (roleMap.find(*sIt) == roleMap.end())
                    {
                      roleMap.insert(std::pair<std::string, const CLStyle*>(*sIt, pStyle));
                    }

                  ++sIt;
                }

              const std::set<std::string>& typeSet = pStyle->getTypeList();

              sIt = typeSet.begin();

              sEndit = typeSet.end();

              while (sIt != sEndit)
                {
                  if (typeMap.find(*sIt) == typeMap.end())
                    {
                      typeMap.insert(std::pair<std::string, const CLStyle*>(*sIt, pStyle));
                    }

                  ++sIt;
                }
            }
        }
      else
        {
          const CLGlobalRenderInformation* pGlobalRenderInformation = dynamic_cast<const CLGlobalRenderInformation*>(*it);
          assert(pGlobalRenderInformation);
          const CLStyle* pStyle = NULL;
          iMax = pGlobalRenderInformation->getListOfStyles()->size();

          for (i = 0; i < iMax; ++i)
            {
              pStyle = pGlobalRenderInformation->getStyle(i);
              const std::set<std::string>& roleSet = pStyle->getRoleList();
              std::set<std::string>::const_iterator sIt = roleSet.begin(), sEndit = roleSet.end();

              while (sIt != sEndit)
                {
                  if (roleMap.find(*sIt) == roleMap.end())
                    {
                      roleMap.insert(std::pair<std::string, const CLStyle*>(*sIt, pStyle));
                    }

                  ++sIt;
                }

              const std::set<std::string>& typeSet = pStyle->getTypeList();

              sIt = typeSet.begin();

              sEndit = typeSet.end();

              while (sIt != sEndit)
                {
                  if (typeMap.find(*sIt) == typeMap.end())
                    {
                      typeMap.insert(std::pair<std::string, const CLStyle*>(*sIt, pStyle));
                    }

                  ++sIt;
                }
            }
        }

      ++it;
    }

  // first we collect all styles
  std::map<const CLStyle*, std::vector<std::set<std::string> > > styles;
  std::map<std::string, const CLStyle*>::const_iterator mapIt = keyMap.begin(), mapEndit = keyMap.end();

  while (mapIt != mapEndit)
    {
      if (styles.find(mapIt->second) == styles.end())
        {
          // add a new vector of sets to the map
          // the first set is for ids, the esecond for roles and  the third
          // for types
          styles[mapIt->second] = std::vector<std::set<std::string> >(3);
        }

      styles[mapIt->second][0].insert(mapIt->first);
      ++mapIt;
    }

  mapIt = roleMap.begin();
  mapEndit = roleMap.end();

  while (mapIt != mapEndit)
    {
      if (styles.find(mapIt->second) == styles.end())
        {
          // add a new vector of sets to the map
          // the first set is for ids, the esecond for roles and  the third
          // for types
          styles[mapIt->second] = std::vector<std::set<std::string> >(3);
        }

      styles[mapIt->second][1].insert(mapIt->first);
      ++mapIt;
    }

  mapIt = typeMap.begin();
  mapEndit = typeMap.end();

  while (mapIt != mapEndit)
    {
      if (styles.find(mapIt->second) == styles.end())
        {
          // add a new vector of sets to the map
          // the first set is for ids, the esecond for roles and  the third
          // for types
          styles[mapIt->second] = std::vector<std::set<std::string> >(3);
        }

      styles[mapIt->second][2].insert(mapIt->first);
      ++mapIt;
    }

  // now we create and fill the result render information
  if (local)
    {
      pResult = new CLLocalRenderInformation();
      std::map<const CLStyle*, std::vector<std::set<std::string> > >::const_iterator styleIt = styles.begin(), styleEndit = styles.end();
      CLLocalStyle* pLocalStyle = NULL;

      while (styleIt != styleEndit)
        {
          // check if the style is a local style
          // if yes, we can just clone it,
          // else it gets more complicated
          if (dynamic_cast<const CLLocalStyle*>(styleIt->first))
            {
              dynamic_cast<CLLocalRenderInformation*>(pResult)->addStyle(static_cast<const CLLocalStyle*>(styleIt->first));
            }
          else
            {
              pLocalStyle = convertGlobalToLocalStyle(static_cast<const CLGlobalStyle*>(styleIt->first));
              dynamic_cast<CLLocalRenderInformation*>(pResult)->addStyle(pLocalStyle);
              delete pLocalStyle;
            }

          ++styleIt;
        }
    }
  else
    {
      pResult = new CLGlobalRenderInformation();
      std::map<const CLStyle*, std::vector<std::set<std::string> > >::const_iterator styleIt = styles.begin(), styleEndit = styles.end();

      while (styleIt != styleEndit)
        {
          static_cast<CLGlobalRenderInformation*>(pResult)->addStyle(dynamic_cast<const CLGlobalStyle*>(styleIt->first));
          ++styleIt;
        }
    }

  // fill the color, gradients and line endings
  std::map<std::string, const CLColorDefinition*>::const_iterator colorIt = colors.begin(), colorEndit = colors.end();

  while (colorIt != colorEndit)
    {
      pResult->addColorDefinition(colorIt->second);
      ++colorIt;
    }

  std::map<std::string, const CLGradientBase*>::const_iterator gradientIt = gradients.begin(), gradientEndit = gradients.end();

  while (gradientIt != gradientEndit)
    {
      pResult->addGradientDefinition(gradientIt->second);
      ++gradientIt;
    }

  std::map<std::string, const CLLineEnding*>::const_iterator lineIt = lineEndings.begin(), lineEndit = lineEndings.end();

  while (lineIt != lineEndit)
    {
      pResult->addLineEnding(lineIt->second);
      ++lineIt;
    }

  pResult->setBackgroundColor(renderInformation.getBackgroundColor());
  return pResult;
}

CLLocalStyle* CLRenderFlattener::convertGlobalToLocalStyle(const CLGlobalStyle* pGlobal)
{
  CLLocalStyle* pResult = new CLLocalStyle();
  // we need to copy  all elements from Style
  // mGroup, mRoleList, mTypeList
  pResult->setGroup(pGlobal->getGroup());
  pResult->setRoleList(pGlobal->getRoleList());
  pResult->setTypeList(pGlobal->getTypeList());
  // we need to copy all elements from SBase
  // for our purposes here, all we need is the name and the id
  //pResult->setId(pGlobal->getKey());
  pResult->setObjectName(pGlobal->getObjectName());
  return pResult;
}
