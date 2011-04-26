// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CListOfLayouts.cpp,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/26 16:10:42 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.


#include "copasi.h"

#define USE_LAYOUT 1

#ifdef USE_CRENDER_EXTENSION
#define USE_RENDER 1
#endif // USE_CRENDER_EXTENSION

#include <sbml/ListOf.h>
#include <sbml/layout/Layout.h>

#include "CListOfLayouts.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "SBMLDocumentLoader.h"

CListOfLayouts::CListOfLayouts(const std::string & name,
                               const CCopasiContainer * pParent):
    CCopasiVector<CLayout>(name, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this))
#ifdef USE_CRENDER_EXTENSION
    , mvGlobalRenderInformationObjects("ListOfGlobalRenderInformationObjects", this)
#endif /* USE_CRENDER_EXTENSION */
{}

CListOfLayouts::~CListOfLayouts()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

const std::string& CListOfLayouts::getKey()
{
  return mKey;
}

void CListOfLayouts::addLayout(CLayout * layout, const std::map<std::string, std::string> & /* m */)
{
  if (layout)
    add(layout, true);

  //TODO: store map
}

void CListOfLayouts::exportToSBML(ListOf * lol, std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                                  const std::map<std::string, const SBase*>& idMap, unsigned int level, unsigned int version) const
{
  if (!lol) return;

  size_t i, imax;
#ifdef USE_CRENDER_EXTENSION
  // the global render information has to be handled first, because we might need
  // some of the maps for the export of the local render information in the layout
  ListOfLayouts* pLoL = dynamic_cast<ListOfLayouts*>(lol);
  assert(pLoL != NULL);
  imax = this->mvGlobalRenderInformationObjects.size();
  GlobalRenderInformation* pGRI = NULL;
  std::map<std::string, std::string> keyToIdMap;

  /*
  std::map<std::string,std::string> colorKeyToIdMap;
  std::map<std::string,std::string> gradientKeyToIdMap;
  std::map<std::string,std::string> lineEndingKeyToIdMap;
  std::map<std::string,std::map<std::string,std::string> > colorKeyToIdMapMap;
  std::map<std::string,std::map<std::string,std::string> > gradientKeyToIdMapMap;
  std::map<std::string,std::map<std::string,std::string> > lineEndingKeyToIdMapMap;
  */
  for (i = 0; i < imax; ++i)
    {
      //colorKeyToIdMap.clear();
      //gradientKeyToIdMap.clear();
      //lineEndingKeyToIdMap.clear();
      //pGRI=this->mvGlobalRenderInformationObjects[i]->toSBML(colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
      pGRI = pLoL->createGlobalRenderInformation();
      this->mvGlobalRenderInformationObjects[i]->toSBML(pGRI, pLoL->getLevel(), pLoL->getVersion());
      // add the id and key to the map
      assert(pGRI != NULL);
      keyToIdMap.insert(std::pair<std::string, std::string>(this->mvGlobalRenderInformationObjects[i]->getKey(), pGRI->getId()));
      //colorKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getId(),colorKeyToIdMap));
      //gradientKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getId(),gradientKeyToIdMap));
      //lineEndingKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getId(),lineEndingKeyToIdMap));
    }

  // fix the references
  // we need to pass the ListOfGlobalRenderInformation objects as the first argument
  SBMLDocumentLoader::convertRenderInformationReferencesKeys<GlobalRenderInformation>(*(pLoL->getListOfGlobalRenderInformation()), keyToIdMap);
  // fix the color ids, gradient ids and line ending ids.
  /*
  std::map<std::string,std::map<std::string,std::string> >::const_iterator mapPos;
  std::map<std::string,std::map<std::string,std::string> > expandedColorKeyToIdMapMap, expandedGradientKeyToIdMapMap, expandedLineEndingKeyToIdMapMap;
  std::map<std::string,std::map<std::string,std::string> > tmpMap1,tmpMap2,tmpMap3;
  for(i=0;i < imax; ++i)
  {
      pGRI=dynamic_cast<GlobalRenderInformation*>(pLoL->get(i));
      assert(pGRI != NULL);
      std::set<std::string> chain;
      SBMLDocumentLoader::expandKeyToIdMaps(pGRI,
              *pLoL,
              expandedColorKeyToIdMapMap,
              expandedGradientKeyToIdMapMap,
              expandedLineEndingKeyToIdMapMap,
              colorKeyToIdMapMap,
              gradientKeyToIdMapMap,
              lineEndingKeyToIdMapMap,
              chain,
              tmpMap1,
              tmpMap2,
              tmpMap3
              );
      SBMLDocumentLoader::convertPropertyKeys<GlobalRenderInformation>(pGRI,expandedColorKeyToIdMapMap[pGRI->getId()],expandedGradientKeyToIdMapMap[pGRI->getId()],expandedLineEndingKeyToIdMapMap[pGRI->getId()]);
  }
  */
#endif /* USE_CRENDER_EXTENSION */
  // we will generate sbml ids that are unique within the sbml file (although
  // this may not be strictly necessary for the layouts). Therefore we will keep only
  // one set of IDs:
  std::map<std::string, const SBase*> sbmlIDs = idMap;

  //this will contain the SBML objects that were touched by this method.
  std::set<SBase*> writtenToSBML;

  //some of the following code is currently useless: Layouts are never part of
  //the copasimodelmap.

  //write all COPASI object to corresponding libsbml objects
  imax = this->size();

  for (i = 0; i < imax; ++i)
    {
      CLayout * tmp = (*this)[i];

      //check if the layout exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      Layout * pLayout;

      if (it == copasimodelmap.end()) //not found
        {
          //create new object and add to libsbml data structures
          // the layout needs to be created with the correct level and version
          // otherwise the render infromation is not correctly exported
          // because newer version is libsbml set the level to 3 per default
          pLayout = new Layout(level, version);
          lol->appendAndOwn(pLayout);

          //add object to map
          //copasimodelmap[tmp] = pLayout; should not really be done in export
        }
      else
        {
          pLayout = dynamic_cast<Layout*>(it->second);
        }

#ifdef USE_CRENDER_EXTENSION
      //tmp->exportToSBML(pLayout, copasimodelmap, sbmlIDs,keyToIdMap,colorKeyToIdMapMap,gradientKeyToIdMapMap,lineEndingKeyToIdMapMap);
      tmp->exportToSBML(pLayout, copasimodelmap, sbmlIDs, keyToIdMap);
#else
      tmp->exportToSBML(pLayout, copasimodelmap, sbmlIDs);
#endif /* USE_CRENDER_EXTENSION */
      writtenToSBML.insert(pLayout);
    }

  //check if a something needs to be deleted from the SBML data structures
  for (i = lol->size(); i > 0; --i)
    {
      SBase* object = lol->get((unsigned int) i - 1);

      if (writtenToSBML.find(object) == writtenToSBML.end())
        {
          lol->remove((unsigned int) i - 1);
          pdelete(object);

          //TODO: delete from map
          //the object and every object it contains need to be removed from the
          //map.
          //For now I do not implement this since layout object are not added to the
          //map in the first place.
        }
    }
}

#ifdef USE_CRENDER_EXTENSION
void CListOfLayouts::addGlobalRenderInformation(CLGlobalRenderInformation * pRenderInfo)
{
  if (pRenderInfo)
    {
      this->mvGlobalRenderInformationObjects.add(pRenderInfo, true); //true means vector takes ownership
    }
}

/**
 *  Returns a pointer to the global render information object with the given index.
 *  If the index is invalid, NULL is returned.
 */
CLGlobalRenderInformation* CListOfLayouts::getRenderInformation(size_t index)
{
  if (index < this->mvGlobalRenderInformationObjects.size())
    {
      return this->mvGlobalRenderInformationObjects[index];
    }

  return NULL;
}

/**
 *  Returns a const pointer to the global render information object with the given index.
 *  If the index is invalid, NULL is returned.
 */
const CLGlobalRenderInformation* CListOfLayouts::getRenderInformation(size_t index) const
{
  if (index < this->mvGlobalRenderInformationObjects.size())
    {
      return this->mvGlobalRenderInformationObjects[index];
    }

  return NULL;
}

#endif /* USE_CRENDER_EXTENSION */
