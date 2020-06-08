// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/packages/render/extension/RenderListOfLayoutsPlugin.h>
#include <sbml/packages/render/sbml/GlobalRenderInformation.h>

#include <sbml/ListOf.h>
#include <sbml/packages/layout/extension/LayoutExtension.h>
#include <sbml/packages/layout/sbml/Layout.h>

#include "CListOfLayouts.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "SBMLDocumentLoader.h"

// the following is taken from libsbml 5.5 if a lower version is used then
// these defines will become active
#ifndef EXTENSION_CREATE_NS
#define EXTENSION_CREATE_NS(type,variable,sbmlns)\
  type* variable;\
  {\
    XMLNamespaces* xmlns = sbmlns->getNamespaces();\
    variable = dynamic_cast<type*>(sbmlns);\
    if (variable == NULL)\
      {\
        variable = new type(sbmlns->getLevel(), sbmlns->getVersion());\
        for (int i = 0; i < xmlns->getNumNamespaces(); i++)\
          {\
            if (!variable->getNamespaces()->hasURI(xmlns->getURI(i)))\
              variable->getNamespaces()->add(xmlns->getURI(i), xmlns->getPrefix(i));\
          }\
      }\
  }
#endif

#ifndef LAYOUT_CREATE_NS
#define LAYOUT_CREATE_NS(variable,sbmlns)\
  EXTENSION_CREATE_NS(LayoutPkgNamespaces,variable,sbmlns);
#endif

CListOfLayouts::CListOfLayouts(const std::string & name,
                               const CDataContainer * pParent):
  CDataVectorN< CLayout >(name, pParent),
  mKey(CRootContainer::getKeyFactory()->add("Layout", this))
  , mvGlobalRenderInformationObjects("ListOfGlobalRenderInformationObjects", this)
{}

CListOfLayouts::~CListOfLayouts()
{
  CRootContainer::getKeyFactory()->remove(mKey);
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

void CListOfLayouts::exportToSBML(ListOf * lol, std::map<const CDataObject*, SBase*> & copasimodelmap,
                                  const std::map<std::string, const SBase*>& idMap, unsigned int level, unsigned int version) const
{
  if (!lol) return;

  size_t i, imax;
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

  RenderListOfLayoutsPlugin* rlolPlugin = (RenderListOfLayoutsPlugin*) lol->getPlugin("render");

  if (rlolPlugin == NULL)
    {
      // we do not yet have a render layout plugin so let us enable it
      const std::string uri = (lol->getLevel() < 3 ? RenderExtension::getXmlnsL2() : RenderExtension::getXmlnsL3V1V1());
      lol->enablePackage(uri, "render", true);
      rlolPlugin = (RenderListOfLayoutsPlugin*) lol->getPlugin("render");

      if (lol->getLevel() > 2)
        lol->getSBMLDocument()->setPackageRequired("render", false);
    }

  assert(rlolPlugin != NULL);

  for (i = 0; i < imax; ++i)
    {
      //colorKeyToIdMap.clear();
      //gradientKeyToIdMap.clear();
      //lineEndingKeyToIdMap.clear();
      //pGRI=this->mvGlobalRenderInformationObjects[i]->toSBML(colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
      pGRI = rlolPlugin->createGlobalRenderInformation();
      this->mvGlobalRenderInformationObjects[i].toSBML(pGRI, pLoL->getLevel(), pLoL->getVersion());
      // add the id and key to the map
      assert(pGRI != NULL);
      keyToIdMap.insert(std::pair<std::string, std::string>(this->mvGlobalRenderInformationObjects[i].getKey(), pGRI->getId()));
      //colorKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getId(),colorKeyToIdMap));
      //gradientKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getId(),gradientKeyToIdMap));
      //lineEndingKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getId(),lineEndingKeyToIdMap));
    }

  // fix the references
  // we need to pass the ListOfGlobalRenderInformation objects as the first argument
  SBMLDocumentLoader::convertRenderInformationReferencesKeys<GlobalRenderInformation>(*(rlolPlugin->getListOfGlobalRenderInformation()), keyToIdMap);
  // fix the color ids, gradient ids and line ending ids.

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
      const CLayout * tmp = &this->operator[](i);

      //check if the layout exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      Layout * pLayout;

      if (it == copasimodelmap.end()) //not found
        {
          //create new object and add to libsbml data structures
          // the layout needs to be created with the correct level and version
          // otherwise the render infromation is not correctly exported
          // because newer version is libsbml set the level to 3 per default
          //pLayout = new Layout(level, version);

          // the issue with the above is that the render package is not automatically
          // instantiated (we really ought to simply call ->createLayout on the plugin object)
          // until then we simply take all the namespaces from the parent element with us
          LAYOUT_CREATE_NS(layoutns, lol->getSBMLNamespaces());
          pLayout = new Layout(layoutns);

          lol->appendAndOwn(pLayout);

          //add object to map
          //copasimodelmap[tmp] = pLayout; should not really be done in export
        }
      else
        {
          pLayout = dynamic_cast<Layout*>(it->second);
        }

      //tmp->exportToSBML(pLayout, copasimodelmap, sbmlIDs,keyToIdMap,colorKeyToIdMapMap,gradientKeyToIdMapMap,lineEndingKeyToIdMapMap);
      tmp->exportToSBML(pLayout, copasimodelmap, sbmlIDs, keyToIdMap);
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
      return &this->mvGlobalRenderInformationObjects[index];
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
      return &this->mvGlobalRenderInformationObjects[index];
    }

  return NULL;
}
