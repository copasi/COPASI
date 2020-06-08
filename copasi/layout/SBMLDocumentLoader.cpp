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

#include <assert.h>

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/ListOf.h>
#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/ReactionGlyph.h>

#include <sbml/packages/layout/sbml/SpeciesReferenceGlyph.h>
#include <sbml/packages/layout/sbml/TextGlyph.h>
#include <sbml/packages/render/sbml/Text.h>
#include <sbml/packages/render/sbml/LocalStyle.h>

#include "copasi/copasi.h"

#include "SBMLDocumentLoader.h"
#include "CListOfLayouts.h"
#include "CLayout.h"
#include "CLReactionGlyph.h"
#include "CLGlyphs.h"

#include "CLRenderCurve.h"
#include <sbml/packages/render/extension/RenderListOfLayoutsPlugin.h>
#include <sbml/packages/render/extension/RenderLayoutPlugin.h>

#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/sbml/SBMLUtils.h" //from the copasi sbml dir

//static
void SBMLDocumentLoader::readListOfLayouts(CListOfLayouts & lol,
    const ListOf & sbmlList,
    const std::map<const CDataObject*, SBase*> & copasimodelmap)
{
  unsigned C_INT32 i, iMax;

  // read the global render information
  const ListOfLayouts* pLoL = dynamic_cast<const ListOfLayouts*>(&sbmlList);
  assert(pLoL != NULL);
  RenderListOfLayoutsPlugin* rlolPlugin = (RenderListOfLayoutsPlugin*) pLoL ->getPlugin("render");

  if (rlolPlugin == NULL)
    {
      const_cast<SBMLDocument *>(pLoL->getSBMLDocument())->enablePackage(RenderExtension::getXmlnsL3V1V1(), "render", true);
      rlolPlugin = (RenderListOfLayoutsPlugin*) pLoL ->getPlugin("render");
    }

  iMax = rlolPlugin->getNumGlobalRenderInformationObjects();
  std::map<std::string, std::string> idToKeyMap;
  CLGlobalRenderInformation* pGRI = NULL;

  /*
  std::map<std::string,std::string> colorIdToKeyMap;
  std::map<std::string,std::string> gradientIdToKeyMap;
  std::map<std::string,std::string> lineEndingIdToKeyMap;
  std::map<std::string,std::map<std::string,std::string> > colorIdToKeyMapMap;
  std::map<std::string,std::map<std::string,std::string> > gradientIdToKeyMapMap;
  std::map<std::string,std::map<std::string,std::string> > lineEndingIdToKeyMapMap;
  */
  for (i = 0; i < iMax; ++i)
    {
      //colorIdToKeyMap.clear();
      //gradientIdToKeyMap.clear();
      //lineEndingIdToKeyMap.clear();
      //pGRI=new CLGlobalRenderInformation(*pLoL->getRenderInformation(i),colorIdToKeyMap,gradientIdToKeyMap,lineEndingIdToKeyMap,&lol);
      pGRI = new CLGlobalRenderInformation(*rlolPlugin->getRenderInformation(i), &lol);

      if (rlolPlugin->getRenderInformation(i)->isSetId())
        idToKeyMap.insert(std::pair<std::string, std::string>(rlolPlugin->getRenderInformation(i)->getId(), pGRI->getKey()));
      else
        idToKeyMap.insert(std::pair<std::string, std::string>(pGRI->getKey(), pGRI->getKey()));

      //colorIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getKey(),colorIdToKeyMap));
      //gradientIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getKey(),gradientIdToKeyMap));
      //lineEndingIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pGRI->getKey(),lineEndingIdToKeyMap));
      lol.addGlobalRenderInformation(pGRI);
    }

  // fix the references
  SBMLDocumentLoader::convertRenderInformationReferencesIds<CLGlobalRenderInformation>(lol.getListOfGlobalRenderInformationObjects(), idToKeyMap);
  // fix the color ids, gradient ids and line ending ids.

  //convert the map as used by the CLxxx constructors
  std::map<std::string, std::string> modelmap;

  std::string s1, s2;
  std::map<const CDataObject*, SBase*>::const_iterator it;
  std::map<const CDataObject*, SBase*>::const_iterator itEnd = copasimodelmap.end();

  for (it = copasimodelmap.begin(); it != itEnd; ++it)
    {
      s1 = SBMLUtils::getIdFromSBase(it->second);

      if (it->first)
        s2 = it->first->getKey();
      else
        s2 = "";

      if ((s1 != "") && (s2 != ""))
        modelmap[s1] = s2;
    }

  //iterate through list of layouts
  iMax = sbmlList.size();

  for (i = 0; i < iMax; ++i)
    {
      std::map<std::string, std::string> layoutmap;
      const Layout* tmp
        = dynamic_cast<const Layout*>(sbmlList.get(i));

      if (tmp)
        {
          //CLayout * pLayout = createLayout(*tmp, modelmap, layoutmap,idToKeyMap,expandedColorIdToKeyMapMap,expandedGradientIdToKeyMapMap,expandedLineEndingIdToKeyMapMap);
          CLayout * pLayout = createLayout(*tmp, modelmap, layoutmap, idToKeyMap);
          lol.addLayout(pLayout, layoutmap);
        }
    }

  //TODO: the layout object should be added to the copasimodelmap. However,
  //if this is done, the object also need to be removed if necessary in the
  //sbml exporter (see comment in CListOfLayouts::exportToSBML()).
}

//static
CLayout * SBMLDocumentLoader::createLayout(const Layout & sbmlLayout,
    const std::map<std::string, std::string> & modelmap,
    std::map<std::string, std::string> & layoutmap
    , const std::map<std::string, std::string>& globalIdToKeyMap
    , const CDataContainer * pParent
                                          )
{
  CLayout* layout = new CLayout(sbmlLayout, layoutmap, pParent);

  //compartments
  unsigned C_INT32 i, iMax = sbmlLayout.getListOfCompartmentGlyphs()->size();

  for (i = 0; i < iMax; ++i)
    {
      const CompartmentGlyph* tmp
        = dynamic_cast<const CompartmentGlyph*>(sbmlLayout.getListOfCompartmentGlyphs()->get(i));

      if (tmp)
        layout->addCompartmentGlyph(new CLCompartmentGlyph(*tmp, modelmap, layoutmap));
    }

  //species
  iMax = sbmlLayout.getListOfSpeciesGlyphs()->size();

  for (i = 0; i < iMax; ++i)
    {
      const SpeciesGlyph* tmp
        = dynamic_cast<const SpeciesGlyph*>(sbmlLayout.getListOfSpeciesGlyphs()->get(i));

      if (tmp)
        layout->addMetaboliteGlyph(new CLMetabGlyph(*tmp, modelmap, layoutmap));
    }

  //reactions
  iMax = sbmlLayout.getListOfReactionGlyphs()->size();

  for (i = 0; i < iMax; ++i)
    {
      const ReactionGlyph* tmp
        = dynamic_cast<const ReactionGlyph*>(sbmlLayout.getListOfReactionGlyphs()->get(i));

      if (tmp)
        layout->addReactionGlyph(new CLReactionGlyph(*tmp, modelmap, layoutmap));
    }

  //text
  iMax = sbmlLayout.getListOfTextGlyphs()->size();

  for (i = 0; i < iMax; ++i)
    {
      const TextGlyph* tmp
        = dynamic_cast<const TextGlyph*>(sbmlLayout.getListOfTextGlyphs()->get(i));

      if (tmp)
        layout->addTextGlyph(new CLTextGlyph(*tmp, modelmap, layoutmap));
    }

  //additional
  iMax = sbmlLayout.getListOfAdditionalGraphicalObjects()->size();

  for (i = 0; i < iMax; ++i)
    {
      const GraphicalObject* graphical
        = dynamic_cast<const GraphicalObject*>(sbmlLayout.getListOfAdditionalGraphicalObjects()->get(i));

      if (graphical)
        layout->addGeneralGlyph(new CLGeneralGlyph(*graphical, modelmap, layoutmap));
    }

  //second pass text (the text glyph can refer to other glyphs. These references can)
  //only be resolved after all glyphs are created).
  iMax = sbmlLayout.getListOfTextGlyphs()->size();

  for (i = 0; i < iMax; ++i)
    {
      const TextGlyph* tmp
        = dynamic_cast<const TextGlyph*>(sbmlLayout.getListOfTextGlyphs()->get(i));

      if (tmp)
        postprocessTextGlyph(*tmp, layoutmap);
    }

  RenderLayoutPlugin* rlPlugin = (RenderLayoutPlugin*) sbmlLayout.getPlugin("render");
  assert(rlPlugin != NULL);

  // import the local render information
  iMax = rlPlugin->getNumLocalRenderInformationObjects();
  std::map<std::string, std::string> idToKeyMap;
  CLLocalRenderInformation* pLRI = NULL;

  for (i = 0; i < iMax; ++i)
    {
      //colorIdToKeyMap.clear();
      //gradientIdToKeyMap.clear();
      //lineEndingIdToKeyMap.clear();
      //pLRI=new CLLocalRenderInformation(*sbmlLayout.getRenderInformation(i),colorIdToKeyMap,gradientIdToKeyMap,lineEndingIdToKeyMap,layout);
      pLRI = new CLLocalRenderInformation(*rlPlugin->getRenderInformation(i), layout);

      if (rlPlugin->getRenderInformation(i)->isSetId())
        idToKeyMap.insert(std::pair<std::string, std::string>(rlPlugin->getRenderInformation(i)->getId(), pLRI->getKey()));
      else
        idToKeyMap.insert(std::pair<std::string, std::string>(pLRI->getKey(), pLRI->getKey()));

      //colorIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pLRI->getKey(),colorIdToKeyMap));
      //gradientIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pLRI->getKey(),gradientIdToKeyMap));
      //lineEndingIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pLRI->getKey(),lineEndingIdToKeyMap));
      // fix the references to layout objects in id lists
      size_t j, jMax = pLRI->getNumStyles();

      for (j = 0; j < jMax; j++)
        {
          SBMLDocumentLoader::convertLayoutObjectIds(*(pLRI->getStyle(j)), layoutmap);
        }

      layout->addLocalRenderInformation(pLRI);
    }

  // fix the references
  // we have to consider the global ids as well
  // since all ids in these two map should be unique, we can just combine them
  size_t count = idToKeyMap.size() + globalIdToKeyMap.size();
  idToKeyMap.insert(globalIdToKeyMap.begin(), globalIdToKeyMap.end());
  // make sure the ids were really unique
  assert(idToKeyMap.size() == count);
  SBMLDocumentLoader::convertRenderInformationReferencesIds<CLLocalRenderInformation>(layout->getListOfLocalRenderInformationObjects(), idToKeyMap);
  // fix the color ids, gradient ids and line ending ids.

  return layout;
}

//static
void SBMLDocumentLoader::postprocessTextGlyph(const TextGlyph & sbml,
    const std::map<std::string, std::string> & layoutmap)
{
  //the corresponding CLTextGlyph should already exist. Let's find it...
  CLTextGlyph * pTg = NULL;

  if (sbml.getId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getId());

      if (it != layoutmap.end())
        pTg = dynamic_cast<CLTextGlyph *>(CRootContainer::getKeyFactory()->get(it->second));

      if (!pTg)
        {
          //error?
          return;
        }
    }
  else
    {
      //error?
      return;
    }

  //resolve the graphical object reference
  assert(pTg);

  if (sbml.getGraphicalObjectId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getGraphicalObjectId());

      if (it != layoutmap.end())
        pTg->setGraphicalObjectKey(it->second);
    }
}

/**
 * Converts references to ids of layout objects to the corresponding key.
 */
void SBMLDocumentLoader::convertLayoutObjectIds(CLLocalStyle& style, const std::map<std::string, std::string>& idToKeyMap)
{
  std::set<std::string> keys;
  std::map<std::string, std::string>::const_iterator pos;
  std::set<std::string>::const_iterator it = style.getKeyList().begin(), endit = style.getKeyList().end();

  while (it != endit)
    {
      pos = idToKeyMap.find(*it);

      if (pos != idToKeyMap.end())
        {
          keys.insert(pos->second);
        }

      ++it;
    }

  style.setKeyList(keys);
}

/**
 * converts references to color ids, gradient ids and/or line ending ids in graphical primitives
 * to references to the corresponding keys.
void SBMLDocumentLoader::convertPropertyIds(CLTransformation2D* pObject,
        const std::map<std::string,std::string>& colorIdToKeyMap,
        const std::map<std::string,std::string>& gradientIdToKeyMap,
        const std::map<std::string,std::string>& lineEndingIdToKeyMap)
{
    CLGraphicalPrimitive1D* pGP1=dynamic_cast<CLGraphicalPrimitive1D*>(pObject);
    if(pGP1 != NULL)
    {
        std::map<std::string,std::string>::const_iterator pos;
        // fix the stroke color
        std::string s=pGP1->getStroke();
        if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none" && s[0] != '#')
        {
          pos=colorIdToKeyMap.find(s);
          // check if we found the color, else it must be a gradient
          if(pos==colorIdToKeyMap.end())
          {
            pos=gradientIdToKeyMap.find(s);
            assert(pos != gradientIdToKeyMap.end());
            pGP1->setStroke(pos->second);
          }
          else
          {
            pGP1->setStroke(pos->second);
          }
        }
        CLGraphicalPrimitive2D* pGP2=dynamic_cast<CLGraphicalPrimitive2D*>(pObject);
        if(pGP2 != NULL)
        {
            // fix the fill color
            std::string s=pGP2->getFillColor();
            if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none" && s[0] != '#')
            {
                pos=colorIdToKeyMap.find(s);
                // check if we found the color, else it must be a gradient
                if(pos==colorIdToKeyMap.end())
                {
                    pos=gradientIdToKeyMap.find(s);
                    assert(pos != gradientIdToKeyMap.end());
                    pGP2->setFillColor(pos->second);
                }
                else
                {
                    pGP2->setFillColor(pos->second);
                }
            }
            CLGroup* pG=dynamic_cast<CLGroup*>(pObject);
            if(pG != NULL)
            {
               // fix the line endings
               s=pG->getStartHead();
               if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
               {
                 pos=lineEndingIdToKeyMap.find(s);
                 assert(pos != lineEndingIdToKeyMap.end());
                 pG->setStartHead(pos->second);
               }
               s=pG->getEndHead();
               if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
               {
                 pos=lineEndingIdToKeyMap.find(s);
                 assert(pos != lineEndingIdToKeyMap.end());
                 pG->setEndHead(pos->second);
               }
               // call this method for all children
               size_t i,iMax=pG->getNumElements();
               for(i=0; i < iMax; ++i)
               {
                   SBMLDocumentLoader::convertPropertyIds(dynamic_cast<CLTransformation2D*>(pG->getElement(i)),colorIdToKeyMap,gradientIdToKeyMap,lineEndingIdToKeyMap);
               }
            }
        }
        else
        {
          CLRenderCurve* pC=dynamic_cast<CLRenderCurve*>(pObject);
          if(pC != NULL)
          {
              // fix the line endings
              s=pC->getStartHead();
              if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
              {
                pos=lineEndingIdToKeyMap.find(s);
                assert(pos != lineEndingIdToKeyMap.end());
                pC->setStartHead(pos->second);
              }
              s=pC->getEndHead();
              if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
              {
                pos=lineEndingIdToKeyMap.find(s);
                assert(pos != lineEndingIdToKeyMap.end());
                pC->setEndHead(pos->second);
              }
          }
        }
    }
}
 */

/**
 * converts references to color ids in gradient stops
 * to references to the corresponding keys.
void SBMLDocumentLoader::convertColorIds(CLGradientBase& gradient,
        const std::map<std::string,std::string>& colorIdToKeyMap)
{
    size_t i,iMax=gradient.getNumGradientStops();
    CLGradientStop* pStop=NULL;
    std::map<std::string,std::string>::const_iterator pos;
    for(i=0; i < iMax; ++i)
    {
        pStop=gradient.getGradientStop(i);
        std::string color=pStop->getStopColor();
        if(color.find_first_not_of(" \t\n\r") != std::string::npos && color != "none" && color[0] != '#')
        {
            pos=colorIdToKeyMap.find(color);
            assert(pos!=colorIdToKeyMap.end());
            pStop->setStopColor(pos->second);
        }
    }
}
 */

/**
 * Converts references to keys of layout objects to the corresponding id.
 */
void SBMLDocumentLoader::convertLayoutObjectKeys(LocalStyle& style, const std::map<std::string, std::string>& keyToIdMap)
{
  std::set<std::string> ids;
  std::map<std::string, std::string>::const_iterator pos;
  std::set<std::string>::const_iterator it = style.getIdList().begin(), endit = style.getIdList().end();

  while (it != endit)
    {
      pos = keyToIdMap.find(*it);
      assert(pos != keyToIdMap.end());
      ids.insert(pos->second);
      ++it;
    }

  style.setIdList(ids);
}

/**
 * converts references to color keys, gradient keys and/or line ending keys in graphical primitives
 * to references to the corresponding Ids.
void SBMLDocumentLoader::convertPropertyKeys(Transformation2D* pObject,
        const std::map<std::string,std::string>& colorKeyToIdMap,
        const std::map<std::string,std::string>& gradientKeyToIdMap,
        const std::map<std::string,std::string>& lineEndingKeyToIdMap)
{
    GraphicalPrimitive1D* pGP1=dynamic_cast<GraphicalPrimitive1D*>(pObject);
    if(pGP1 != NULL)
    {
        std::map<std::string,std::string>::const_iterator pos;
        // fix the stroke color
        std::string s=pGP1->getStroke();
        if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none" && s[0] != '#')
        {
          pos=colorKeyToIdMap.find(s);
          // check if we found the color, else it must be a gradient
          if(pos==colorKeyToIdMap.end())
          {
            pos=gradientKeyToIdMap.find(s);
            assert(pos != gradientKeyToIdMap.end());
            pGP1->setStroke(pos->second);
          }
          else
          {
            pGP1->setStroke(pos->second);
          }
        }
        GraphicalPrimitive2D* pGP2=dynamic_cast<GraphicalPrimitive2D*>(pObject);
        if(pGP2 != NULL)
        {
            // fix the fill color
            std::string s=pGP2->getFillColor();
            if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none" && s[0] != '#')
            {
                pos=colorKeyToIdMap.find(s);
                // check if we found the color, else it must be a gradient
                if(pos==colorKeyToIdMap.end())
                {
                    pos=gradientKeyToIdMap.find(s);
                    assert(pos != gradientKeyToIdMap.end());
                    pGP2->setFillColor(pos->second);
                }
                else
                {
                    pGP2->setFillColor(pos->second);
                }
            }
            Group* pG=dynamic_cast<Group*>(pObject);
            if(pG != NULL)
            {
               // fix the line endings
               s=pG->getStartHead();
               if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
               {
                 pos=lineEndingKeyToIdMap.find(s);
                 assert(pos != lineEndingKeyToIdMap.end());
                 pG->setStartHead(pos->second);
               }
               s=pG->getEndHead();
               if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
               {
                 pos=lineEndingKeyToIdMap.find(s);
                 assert(pos != lineEndingKeyToIdMap.end());
                 pG->setEndHead(pos->second);
               }
               // call this method for all children
               size_t i,iMax=pG->getNumElements();
               for(i=0; i < iMax; ++i)
               {
                   SBMLDocumentLoader::convertPropertyKeys(dynamic_cast<Transformation2D*>(pG->getElement(i)),colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
               }
            }
        }
        else
        {
          RenderCurve* pC=dynamic_cast<RenderCurve*>(pObject);
          if(pC != NULL)
          {
              // fix the line endings
              s=pC->getStartHead();
              if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
              {
                pos=lineEndingKeyToIdMap.find(s);
                assert(pos != lineEndingKeyToIdMap.end());
                pC->setStartHead(pos->second);
              }
              s=pC->getEndHead();
              if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none")
              {
                pos=lineEndingKeyToIdMap.find(s);
                assert(pos != lineEndingKeyToIdMap.end());
                pC->setEndHead(pos->second);
              }
          }
        }
    }
}
 */

/**
 * converts references to color ids in gradient stops
 * to references to the corresponding keys.
void SBMLDocumentLoader::convertColorKeys(GradientBase& gradient,
        const std::map<std::string,std::string>& colorKeyToIdMap)
{
    size_t i,iMax=gradient.getNumGradientStops();
    GradientStop* pStop=NULL;
    std::map<std::string,std::string>::const_iterator pos;
    for(i=0; i < iMax; ++i)
    {
        pStop=gradient.getGradientStop(i);
        std::string color=pStop->getStopColor();
        if(color.find_first_not_of(" \t\n\r") != std::string::npos && color != "none" && color[0] != '#')
        {
            pos=colorKeyToIdMap.find(color);
            assert(pos!=colorKeyToIdMap.end());
            pStop->setStopColor(pos->second);
        }
    }
}
 */

/**
 * Adds all elements of the source map into the dest map if an element with the same key does not already exist in the dest map.
 */
void SBMLDocumentLoader::combineMaps(
  const std::map<std::string, std::string>& sourceMap,
  std::map<std::string, std::string>& destMap
)
{
  std::map<std::string, std::string>::const_iterator it = sourceMap.begin(), endit = sourceMap.end();

  while (it != endit)
    {
      if (destMap.find(it->first) == destMap.end())
        {
          destMap.insert(*it);
        }

      ++it;
    }
}

/**
 * converts references to color keys, gradient keys and/or line ending keys in graphical primitives
 * to references to the corresponding Ids.
template<typename RENDER_INFORMATION>
void SBMLDocumentLoader::convertPropertyKeys(RENDER_INFORMATION* pObject,
        const std::map<std::string,std::string>& colorKeyToIdMap,
        const std::map<std::string,std::string>& gradientKeyToIdMap,
        const std::map<std::string,std::string>& lineEndingKeyToIdMap)
{
    std::string s=pObject->getBackgroundColor();
    std::map<std::string,std::string>::const_iterator pos;
    if(s.find_first_not_of(" \t\n\r") != std::string::npos && s != "none" && s[0] != '#')
    {
        pos=colorKeyToIdMap.find(s);
        assert(pos!=colorKeyToIdMap.end());
        pObject->setBackgroundColor(pos->second);
    }
    size_t i,iMax=pObject->getNumLineEndings();
    for(i=0;i < iMax; ++i)
    {
        SBMLDocumentLoader::convertPropertyIds(dynamic_cast<CLTransformation2D*>(pObject->getLineEnding(i)->getGroup()),colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
    }
    iMax=pObject->getNumStyles();
    for(i=0; i < iMax; ++i)
    {
        SBMLDocumentLoader::convertPropertyIds(dynamic_cast<CLTransformation2D*>(pObject->getStyle(i)->getGroup()),colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
    }
}
 */

/**
 * Creates maps of maps for the colors, gradients and line endings of the given of render information
 * objects.
 * Those maps can than be used to convert the id of a color, gradient or lineEnding from the SBML model
 * to the key used in the COPASI model.
template<typename RENDER_INFORMATION>
void SBMLDocumentLoader::expandIdToKeyMaps(const CLRenderInformationBase* pRenderInfo,
            CDataVector<RENDER_INFORMATION>& renderInformationVector,
            std::map<std::string,std::map<std::string,std::string> >& colorIdToKeyMapMap,
            std::map<std::string,std::map<std::string,std::string> >& gradientIdToKeyMapMap,
            std::map<std::string,std::map<std::string,std::string> >& lineEndingIdToKeyMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& unexpandedColorIdToKeyMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& unexpandedGradientIdToKeyMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& unexpandedLineEndingIdToKeyMapMap,
            std::set<std::string>& chain,
            const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalColorIdToKeyMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalGradientIdToKeyMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalLineEndingIdToKeyMapMap
        )
{
    // first we check if there already is an entry in the map for this render info object
    if(chain.find(pRenderInfo->getId()) != chain.end())
    {
        // we have an endless loop
        fatalError();
    }
    else
    {
        chain.insert(pRenderInfo->getKey());
    }
    if(colorIdToKeyMapMap.find(pRenderInfo->getKey()) == colorIdToKeyMapMap.end())
    {
        assert(gradientIdToKeyMapMap.find(pRenderInfo->getKey()) == gradientIdToKeyMapMap.end());
        assert(lineEndingIdToKeyMapMap.find(pRenderInfo->getKey()) == lineEndingIdToKeyMapMap.end());
        std::string s=pRenderInfo->getReferenceRenderInformationKey();
        assert(unexpandedColorIdToKeyMapMap.find(pRenderInfo->getKey()) != unexpandedColorIdToKeyMapMap.end());
        assert(unexpandedGradientIdToKeyMapMap.find(pRenderInfo->getKey()) != unexpandedGradientIdToKeyMapMap.end());
        assert(unexpandedLineEndingIdToKeyMapMap.find(pRenderInfo->getKey()) != unexpandedLineEndingIdToKeyMapMap.end());
        // fill the id map with the ids from this render info only
        std::map<std::string,std::map<std::string,std::string> >::const_iterator mapPos=unexpandedColorIdToKeyMapMap.find(pRenderInfo->getKey());
        assert(mapPos!=unexpandedColorIdToKeyMapMap.end());
        colorIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pRenderInfo->getKey(),mapPos->second));
        mapPos=unexpandedGradientIdToKeyMapMap.find(pRenderInfo->getKey());
        assert(mapPos!=unexpandedGradientIdToKeyMapMap.end());
        gradientIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pRenderInfo->getKey(),mapPos->second));
        mapPos=unexpandedLineEndingIdToKeyMapMap.find(pRenderInfo->getKey());
        assert(mapPos!=unexpandedLineEndingIdToKeyMapMap.end());
        lineEndingIdToKeyMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pRenderInfo->getKey(),mapPos->second));
        if(s.find_first_not_of(" \t\n\r") != std::string::npos)
        {
            // we have to create the entry for the referenced render info
            size_t i,iMax=renderInformationVector.size();
            for(i=0; i < iMax; ++i)
            {
                if(renderInformationVector[i]->getKey() == "s")
                {
                    break;
                }
            }
            if(i != iMax)
            {
                // we found the render information that goes with the id
                SBMLDocumentLoader::expandIdToKeyMaps<RENDER_INFORMATION>(renderInformationVector[i],
                        renderInformationVector,
                        colorIdToKeyMapMap,
                        gradientIdToKeyMapMap,
                        lineEndingIdToKeyMapMap,
                        unexpandedColorIdToKeyMapMap,
                        unexpandedGradientIdToKeyMapMap,
                        unexpandedLineEndingIdToKeyMapMap,
                        chain,
                        expandedGlobalColorIdToKeyMapMap,
                        expandedGlobalGradientIdToKeyMapMap,
                        expandedGlobalLineEndingIdToKeyMapMap
                        );
            }
            // add the nonexistent ids from the references render info to this one
            SBMLDocumentLoader::combineMaps(colorIdToKeyMapMap[renderInformationVector[i]->getKey()],colorIdToKeyMapMap[pRenderInfo->getKey()]);
            SBMLDocumentLoader::combineMaps(gradientIdToKeyMapMap[renderInformationVector[i]->getKey()],gradientIdToKeyMapMap[pRenderInfo->getKey()]);
            SBMLDocumentLoader::combineMaps(lineEndingIdToKeyMapMap[renderInformationVector[i]->getKey()],lineEndingIdToKeyMapMap[pRenderInfo->getKey()]);
        }
    }
}
 */

/**
 * Creates maps of maps for the colors, gradients and line endings of the given of render information
 * objects.
 * Those maps can than be used to convert the id of a color, gradient or lineEnding from the SBML model
 * to the key used in the COPASI model.
void SBMLDocumentLoader::expandKeyToIdMaps(const RenderInformationBase* pRenderInfo,
            ListOf& renderInformationVector,
            std::map<std::string,std::map<std::string,std::string> >& colorKeyToIdMapMap,
            std::map<std::string,std::map<std::string,std::string> >& gradientKeyToIdMapMap,
            std::map<std::string,std::map<std::string,std::string> >& lineEndingKeyToIdMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& unexpandedColorKeyToIdMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& unexpandedGradientKeyToIdMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& unexpandedLineEndingKeyToIdMapMap,
            std::set<std::string>& chain,
            const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalColorKeyToIdMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalGradientKeyToIdMapMap,
            const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalLineEndingKeyToIdMapMap
            )
{
    // first we check if there already is an entry in the map for this render info object
    if(chain.find(pRenderInfo->getId()) != chain.end())
    {
        // we have an endless loop
        fatalError();
    }
    else
    {
        chain.insert(pRenderInfo->getId());
    }
    if(colorKeyToIdMapMap.find(pRenderInfo->getId()) == colorKeyToIdMapMap.end())
    {
        std::map<std::string,std::map<std::string,std::string> >::const_iterator mapPos;
        assert(gradientKeyToIdMapMap.find(pRenderInfo->getId()) == gradientKeyToIdMapMap.end());
        assert(lineEndingKeyToIdMapMap.find(pRenderInfo->getId()) == lineEndingKeyToIdMapMap.end());
        std::string s=pRenderInfo->getReferenceRenderInformationId();
        assert(unexpandedColorKeyToIdMapMap.find(pRenderInfo->getId()) != unexpandedColorKeyToIdMapMap.end());
        assert(unexpandedGradientKeyToIdMapMap.find(pRenderInfo->getId()) != unexpandedGradientKeyToIdMapMap.end());
        assert(unexpandedLineEndingKeyToIdMapMap.find(pRenderInfo->getId()) != unexpandedLineEndingKeyToIdMapMap.end());
        // fill the id map with the ids from this render info only
        mapPos=unexpandedColorKeyToIdMapMap.find(pRenderInfo->getId());
        assert(mapPos!=unexpandedColorKeyToIdMapMap.end());
        colorKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pRenderInfo->getId(),mapPos->second));
        mapPos=unexpandedGradientKeyToIdMapMap.find(pRenderInfo->getId());
        assert(mapPos!=unexpandedGradientKeyToIdMapMap.end());
        gradientKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pRenderInfo->getId(),mapPos->second));
        mapPos=unexpandedLineEndingKeyToIdMapMap.find(pRenderInfo->getId());
        assert(mapPos!=unexpandedLineEndingKeyToIdMapMap.end());
        lineEndingKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pRenderInfo->getId(),mapPos->second));
        if(s.find_first_not_of(" \t\n\r") != std::string::npos)
        {
            // we have to create the entry for the referenced render info
            size_t i,iMax=renderInformationVector.size();
            for(i=0; i < iMax; ++i)
            {
                if(renderInformationVector.get(i)->getId() == "s")
                {
                    break;
                }
            }
            if(i != iMax)
            {
                // we found the render information that goes with the id

                SBMLDocumentLoader::expandKeyToIdMaps(dynamic_cast<RenderInformationBase*>(renderInformationVector.get(i)),
                        renderInformationVector,
                        colorKeyToIdMapMap,
                        gradientKeyToIdMapMap,
                        lineEndingKeyToIdMapMap,
                        unexpandedColorKeyToIdMapMap,
                        unexpandedGradientKeyToIdMapMap,
                        unexpandedLineEndingKeyToIdMapMap,
                        chain,
                        expandedGlobalColorKeyToIdMapMap,
                        expandedGlobalGradientKeyToIdMapMap,
                        expandedGlobalLineEndingKeyToIdMapMap
                    );
            }
            // add the nonexistent ids from the references render info to this one
            SBMLDocumentLoader::combineMaps(colorKeyToIdMapMap[renderInformationVector.get(i)->getId()],colorKeyToIdMapMap[pRenderInfo->getId()]);
            SBMLDocumentLoader::combineMaps(gradientKeyToIdMapMap[renderInformationVector.get(i)->getId()],gradientKeyToIdMapMap[pRenderInfo->getId()]);
            SBMLDocumentLoader::combineMaps(lineEndingKeyToIdMapMap[renderInformationVector.get(i)->getId()],lineEndingKeyToIdMapMap[pRenderInfo->getId()]);
        }
    }
}
 */
