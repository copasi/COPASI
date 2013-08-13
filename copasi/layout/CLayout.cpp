// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#define USE_LAYOUT 1

#ifdef USE_CRENDER_EXTENSION
#define USE_RENDER 1
#endif // USE_CRENDER_EXTENSION

#include "iostream"
#include "sbml/packages/layout/sbml/Layout.h"
#include "sbml/packages/render/sbml/LocalRenderInformation.h"
#include "sbml/packages/render/extension/RenderLayoutPlugin.h"
#include "sbml/packages/render/extension/RenderListOfLayoutsPlugin.h"

#if LIBSBML_VERSION >= 50800
#include "sbml/packages/layout/sbml/GeneralGlyph.h"
#endif // LIBSBML_VERSION >= 50800

#include "copasi.h"

#include "CLayout.h"
#include "CLReactionGlyph.h"
#include "SBMLDocumentLoader.h"

#include "report/CKeyFactory.h"
#include "sbml/CSBMLExporter.h"
#include "copasi/report/CCopasiRootContainer.h"

CLayout::CLayout(const std::string & name,
                 const CCopasiContainer * pParent)
  : CLBase(),
    CCopasiContainer(name, pParent, "Layout"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this)),
    mDimensions(),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
#ifdef USE_CRENDER_EXTENSION
    , mvLocalRenderInformationObjects("ListOfLocalRenderInformationObjects", this)
#endif /* USE_CRENDER_EXTENSION */
{}

CLayout::CLayout(const CLayout & src,
                 const CCopasiContainer * pParent)
  : CLBase(src),
    CCopasiContainer(src, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this)),
    mDimensions(src.mDimensions),
    mvCompartments(src.mvCompartments, this),
    mvMetabs(src.mvMetabs, this),
    mvReactions(src.mvReactions, this),
    mvLabels(src.mvLabels, this),
    mvGraphicalObjects(src.mvGraphicalObjects, this)
#ifdef USE_CRENDER_EXTENSION
    , mvLocalRenderInformationObjects(src.mvLocalRenderInformationObjects, this)
#endif /* USE_CRENDER_EXTENSION */
{
  //TODO references from one glyph to another have to be reconstructed after
  //     copying. This applies to Labels and species reference glyphs
}

CLayout::CLayout(const Layout & sbml,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent)
  : CLBase(sbml),
    CCopasiContainer(sbml.getId(), pParent, "Layout"),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Layout", this)),
    mDimensions(*sbml.getDimensions()),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
#ifdef USE_CRENDER_EXTENSION
    , mvLocalRenderInformationObjects("ListOfLocalRenderInformationObjects", this)
#endif /* USE_CRENDER_EXTENSION */
{
  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
}

CLayout::~CLayout()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

void CLayout::addCompartmentGlyph(CLCompartmentGlyph * glyph)
{
  if (glyph)
    mvCompartments.add(glyph, true); //true means vector takes ownership
}

void CLayout::addMetaboliteGlyph(CLMetabGlyph * glyph)
{
  if (glyph)
    mvMetabs.add(glyph, true); //true means vector takes ownership
}

void CLayout::addReactionGlyph(CLReactionGlyph * glyph)
{
  if (glyph)
    mvReactions.add(glyph, true); //true means vector takes ownership
}

void CLayout::addTextGlyph(CLTextGlyph * glyph)
{
  if (glyph)
    mvLabels.add(glyph, true); //true means vector takes ownership
}

void CLayout::addGeneralGlyph(CLGeneralGlyph* glyph)
{
  if (glyph)
    mvGraphicalObjects.add(glyph, true); //true means vector takes ownership
}

std::ostream & operator<<(std::ostream &os, const CLayout & l)
{
  size_t i, imax;

  os << "Layout  \"" << l.getObjectName() << "\" " << l.mDimensions << "\n\n";

  imax = l.mvCompartments.size();

  if (imax)
    {
      os << "List of compartment glyphs: \n\n";

      for (i = 0; i < imax; ++i)
        os << *l.mvCompartments[i];
    }

  imax = l.mvMetabs.size();

  if (imax)
    {
      os << "\nList of species glyphs: \n\n";

      for (i = 0; i < imax; ++i)
        os << *l.mvMetabs[i];
    }

  imax = l.mvReactions.size();

  if (imax)
    {
      os << "\nList of reaction glyphs: \n\n";

      for (i = 0; i < imax; ++i)
        os << *l.mvReactions[i];
    }

  imax = l.mvLabels.size();

  if (imax)
    {
      os << "\nList of labels: \n\n";

      for (i = 0; i < imax; ++i)
        os << *l.mvLabels[i];
    }

  imax = l.mvGraphicalObjects.size();

  if (imax)
    {
      os << "\nList of graphical objects: \n\n";

      for (i = 0; i < imax; ++i)
        os << *l.mvGraphicalObjects[i];
    }

  return os;
}

void CLayout::print(std::ostream * os) const
{*os << *this;}

void CLayout::exportToDotFile(std::ostream & os) const
{
  os << "digraph G {\n";

  //species glyphs
  size_t i, imax = mvMetabs.size();

  for (i = 0; i < imax; ++i)
    {
      writeDotNode(os, mvMetabs[i]->getKey(), mvMetabs[i]->getModelObjectDisplayName());
    }

  //reaction glyphs
  imax = mvReactions.size();

  for (i = 0; i < imax; ++i)
    {
      writeDotNode(os, mvReactions[i]->getKey() + "_S", "", 1);
      writeDotNode(os, mvReactions[i]->getKey() + "_P", "", 1);
      writeDotEdge(os, mvReactions[i]->getKey() + "_S", mvReactions[i]->getKey() + "_P", 1);

      size_t j, jmax = mvReactions[i]->getListOfMetabReferenceGlyphs().size();

      for (j = 0; j < jmax; ++j)
        {
          CLMetabReferenceGlyph* mrg = mvReactions[i]->getListOfMetabReferenceGlyphs()[j];

          if (mrg->getRole() == CLMetabReferenceGlyph::SUBSTRATE)
            writeDotEdge(os, mrg->getMetabGlyphKey(), mvReactions[i]->getKey() + "_S");
          else if (mrg->getRole() == CLMetabReferenceGlyph::PRODUCT)
            writeDotEdge(os, mvReactions[i]->getKey() + "_P", mrg->getMetabGlyphKey());
        }
    }

  os << "}" << std::endl;
}

void CLayout::writeDotNode(std::ostream & os, const std::string & id,
                           const std::string & label,
                           int t) const
{
  std::string tmp;

  if (t == 1)
    tmp = " shape=point ";

  os << id << " [" << tmp << " label=\"" << label << "\"] \n";
}

void CLayout::writeDotEdge(std::ostream & os, const std::string & id1,
                           const std::string & id2,
                           int t) const
{
  std::string tmp;

  if (t == 1)
    tmp = " [len=0.2] ";

  os << id1 << " -> " << id2 << tmp << "\n"; //[label=\"" << label << "\"] \n";
}

void CLayout::exportToSBML(Layout * layout, const std::map<const CCopasiObject*, SBase*> & copasimodelmap,
                           std::map<std::string, const SBase*>& sbmlIDs
#ifdef USE_CRENDER_EXTENSION
                           , const std::map<std::string, std::string>& globalKeyToIdMap
                           //,const std::map<std::string,std::map<std::string,std::string> >& globalColorKeyToIdMapMap
                           //,const std::map<std::string,std::map<std::string,std::string> >& globalGradientKeyToIdMapMap
                           //,const std::map<std::string,std::map<std::string,std::string> >& globalLineEndingKeyToIdMapMap
#endif /* USE_CRENDER_EXTENSION */
                          ) const
{
  if (!layout) return;

  //Name and ID
  std::string id = CSBMLExporter::createUniqueId(sbmlIDs, "layout", true);
  layout->setId(id);
  sbmlIDs.insert(std::pair<const std::string, const SBase*>(id, layout));
  //we do not check if the layout is already present in the libsbml data
  //structures. This is no big deal since at the moment no software
  //relies on persistent IDs for layout elements.

  //Dimensions
  Dimensions tmpDim = mDimensions.getSBMLDimensions();
  layout->setDimensions(&tmpDim);

  //some of the following code is not used at the moment:  the COPASI model map
  //does not contain glyphs. Since this may change in the future I leave the code
  //below.

  // create a map from COPASI layout object to SBML objects. We do not put
  //the layout objects into the global map (copasimodelmap) but we need to have
  //access to all objects in the current layout since speciesReferenceGlyph and
  //textGlyph need to reference other graphical objects.
  std::map<const CLBase*, const SBase*> layoutmap;

  //Compartment glyphs
  size_t i, imax = mvCompartments.size();

  for (i = 0; i < imax; ++i)
    {
      CLCompartmentGlyph * tmp = mvCompartments[i];

      //check if the compartment glyph exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      CompartmentGlyph * pCG;

      if (it == copasimodelmap.end()) //not found
        {
          pCG = layout->createCompartmentGlyph();
        }
      else
        {
          pCG = dynamic_cast<CompartmentGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pCG));
      tmp->exportToSBML(pCG, copasimodelmap, sbmlIDs);
    }

  //Species glyphs
  imax = mvMetabs.size();

  for (i = 0; i < imax; ++i)
    {
      CLMetabGlyph * tmp = mvMetabs[i];

      //check if the glyph exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      SpeciesGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = layout->createSpeciesGlyph();
        }
      else
        {
          pG = dynamic_cast<SpeciesGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs);
    }

  //Reaction glyphs
  imax = mvReactions.size();

  for (i = 0; i < imax; ++i)
    {
      CLReactionGlyph * tmp = mvReactions[i];

      //check if the glyph exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      ReactionGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = layout->createReactionGlyph();
        }
      else
        {
          pG = dynamic_cast<ReactionGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      //we need to pass the layoutmap here for 2 reasons:
      //1. the metabreferenceglyphs need to be added
      //2. the metabreferenceglyphs need to resolve the reference to the metabglyph
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
    }

  //Text glyphs
  imax = mvLabels.size();

  for (i = 0; i < imax; ++i)
    {
      CLTextGlyph * tmp = mvLabels[i];

      //check if the glyph exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      TextGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = layout->createTextGlyph();
        }
      else
        {
          pG = dynamic_cast<TextGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs);
    }

  //generic glyphs
  imax = mvGraphicalObjects.size();

  for (i = 0; i < imax; ++i)
    {
      CLGeneralGlyph * tmp = mvGraphicalObjects[i];

      //check if the glyph exists in the libsbml data
      std::map<const CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      GraphicalObject * pG;

      if (it == copasimodelmap.end()) //not found
        {
#if LIBSBML_VERSION >= 50800

          if (tmp->getListOfReferenceGlyphs().size() > 0)
            pG = layout->createGeneralGlyph();
          else
#endif // LIBSBML_VERSION >= 50800
            pG = layout->createAdditionalGraphicalObject();
        }
      else
        {
          pG = dynamic_cast<GraphicalObject*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
    }

  //now that we have all graphical objects in the layoutmap we can resolve the references
  //in the text glyphs
  imax = mvLabels.size();

  for (i = 0; i < imax; ++i)
    {
      const CLTextGlyph * tmp = mvLabels[i];

      //find the corresponding SBML object
      std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);

      if (it != layoutmap.end() && it->second && dynamic_cast<const TextGlyph*>(it->second))
        {
          tmp->exportReferenceToSBML(const_cast<TextGlyph*>(dynamic_cast<const TextGlyph*>(it->second)), layoutmap);
        }
    }

#ifdef USE_CRENDER_EXTENSION
  // export the local render information
  imax = this->mvLocalRenderInformationObjects.size();
  LocalRenderInformation* pLRI = NULL;
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
      //pLRI=this->mvLocalRenderInformationObjects[i]->toSBML(colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
      pLRI = this->mvLocalRenderInformationObjects[i]->toSBML(layout->getLevel(), layout->getVersion());
      keyToIdMap.insert(std::pair<std::string, std::string>(this->mvLocalRenderInformationObjects[i]->getKey(), pLRI->getId()));
      //colorKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pLRI->getId(),colorKeyToIdMap));
      //gradientKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pLRI->getId(),gradientKeyToIdMap));
      //lineEndingKeyToIdMapMap.insert(std::pair<std::string,std::map<std::string,std::string> >(pLRI->getId(),lineEndingKeyToIdMap));
      // fix the references to layout objects in id lists
      std::map<const CLBase*, const SBase*>::const_iterator layoutMapIt = layoutmap.begin(), layoutMapEndit = layoutmap.end();
      std::map<std::string, std::string> layoutObjectKeyToIdMap;
      const CLGraphicalObject* pGObject = NULL;

      while (layoutMapIt != layoutMapEndit)
        {
          pGObject = dynamic_cast<const CLGraphicalObject*>(layoutMapIt->first);

          if (pGObject != NULL)
            {
              layoutObjectKeyToIdMap.insert(std::pair<std::string, std::string>(pGObject->getKey(), layoutMapIt->second->getId()));
            }

          ++layoutMapIt;
        }

      size_t j, jMax = pLRI->getNumStyles();

      for (j = 0; j < jMax; ++j)
        {
          SBMLDocumentLoader::convertLayoutObjectKeys(*(pLRI->getStyle((unsigned int) j)), layoutObjectKeyToIdMap);
        }

      RenderLayoutPlugin* rlolPlugin = (RenderLayoutPlugin*) layout->getPlugin("render");

      if (rlolPlugin == NULL)
        {
          const std::string uri = (layout->getLevel() < 3 ? RenderExtension::getXmlnsL2() : RenderExtension::getXmlnsL3V1V1());
          layout->enablePackage(uri, "render", true);

          if (layout->getLevel() > 2)
            layout->getSBMLDocument()->setPackageRequired("render", false);

          rlolPlugin = (RenderLayoutPlugin*) layout->getPlugin("render");
        }

      if (rlolPlugin != NULL)
        rlolPlugin->getListOfLocalRenderInformation()->appendAndOwn(pLRI);
    }

  // we need to add the ids from the global render information object to the keyToIdMap
  SBMLDocumentLoader::combineMaps(globalKeyToIdMap, keyToIdMap);
  // fix the references
  /*
  SBMLDocumentLoader::convertRenderInformationReferencesKeys<LocalRenderInformation>(*layout->getListOfLocalRenderInformation(),keyToIdMap);
  // fix the color ids, gradient ids and line ending ids.
  std::map<std::string,std::map<std::string,std::string> >::const_iterator mapPos;
  std::map<std::string,std::map<std::string,std::string> > expandedColorKeyToIdMapMap, expandedGradientKeyToIdMapMap, expandedLineEndingKeyToIdMapMap;
  for(i=0;i < imax; ++i)
  {
      // a set to check for endless loops
      std::set<std::string> ids;
      colorKeyToIdMap.clear();
      gradientKeyToIdMap.clear();
      lineEndingKeyToIdMap.clear();
      pLRI=dynamic_cast<LocalRenderInformation*>(layout->getRenderInformation(i));
      assert(pLRI != NULL);
      std::string s=pLRI->getId();
      // replace this with the expansion code from SBMLDocumentLoader
      std::set<std::string> chain;
      SBMLDocumentLoader::expandKeyToIdMaps(pLRI,
              *(layout->getListOfLocalRenderInformation()),
              expandedColorKeyToIdMapMap,
              expandedGradientKeyToIdMapMap,
              expandedLineEndingKeyToIdMapMap,
              colorKeyToIdMapMap,
              gradientKeyToIdMapMap,
              lineEndingKeyToIdMapMap,
              chain,
              globalColorKeyToIdMapMap,
              globalGradientKeyToIdMapMap,
              globalLineEndingKeyToIdMapMap
         );
      SBMLDocumentLoader::convertPropertyKeys<LocalRenderInformation>(pLRI,colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
  }
  */
#endif /* USE_CRENDER_EXTENSION */
}

#ifdef USE_CRENDER_EXTENSION
void CLayout::addLocalRenderInformation(CLLocalRenderInformation * pRenderInfo)
{
  if (pRenderInfo)
    {
      this->mvLocalRenderInformationObjects.add(pRenderInfo, true); //true means vector takes ownership
    }
}

/**
 * Returns a const pointer to the local render information with the given index or NULL
 * if the index is invalid.
 */
const CLLocalRenderInformation* CLayout::getRenderInformation(size_t index) const
{
  if (index >= this->mvLocalRenderInformationObjects.size()) return NULL;

  return this->mvLocalRenderInformationObjects[index];
}

/**
 * Returns a pointer to the local render information with the given index or NULL
 * if the index is invalid.
 */
CLLocalRenderInformation* CLayout::getRenderInformation(size_t index)
{
  if (index >= this->mvLocalRenderInformationObjects.size()) return NULL;

  return this->mvLocalRenderInformationObjects[index];
}

/**
 * This methods calculates the bounding box of the layout.
 * It traverses all layout objects and looks for the minimal and maximal x
 * and y values that occur in the layout.
 * These values are returned in the form of a bounding box where the minimal
 * values are stored in the position and the maxima are given as the minimal
 * values plus the corresponding dimension.
 */
CLBoundingBox CLayout::calculateBoundingBox() const
{
  double minX = std::numeric_limits<double>::max();
  double minY = minX;
  double maxX = -minX;
  double maxY = -minX;

  const CLGraphicalObject* pObject = NULL;
  const CLCurve* pCurve = NULL;
  const CLBoundingBox* pBB;
  const CLPoint* pP = NULL;
  const CLDimensions* pDim;
  size_t i, iMax = this->getListOfCompartmentGlyphs().size();
  double x, y, x2, y2;

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfCompartmentGlyphs()[i];
      pBB = &pObject->getBoundingBox();
      pP = &pBB->getPosition();
      x = pP->getX();
      y = pP->getY();
      pDim = &pBB->getDimensions();
      x2 = x + pDim->getWidth();
      y2 = y + pDim->getHeight();
      minX = (minX < x) ? minX : x;
      minY = (minY < y) ? minY : y;
      maxX = (maxX > x2) ? maxX : x2;
      maxY = (maxY > y2) ? maxY : y2;
    }

  iMax = this->getListOfMetaboliteGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfMetaboliteGlyphs()[i];
      pBB = &pObject->getBoundingBox();
      pP = &pBB->getPosition();
      x = pP->getX();
      y = pP->getY();
      pDim = &pBB->getDimensions();
      x2 = x + pDim->getWidth();
      y2 = y + pDim->getHeight();
      minX = (minX < x) ? minX : x;
      minY = (minY < y) ? minY : y;
      maxX = (maxX > x2) ? maxX : x2;
      maxY = (maxY > y2) ? maxY : y2;
    }

  iMax = this->getListOfTextGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfTextGlyphs()[i];
      pBB = &pObject->getBoundingBox();
      pP = &pBB->getPosition();
      x = pP->getX();
      y = pP->getY();
      pDim = &pBB->getDimensions();
      x2 = x + pDim->getWidth();
      y2 = y + pDim->getHeight();
      minX = (minX < x) ? minX : x;
      minY = (minY < y) ? minY : y;
      maxX = (maxX > x2) ? maxX : x2;
      maxY = (maxY > y2) ? maxY : y2;
    }

  size_t j, jMax;
  const CLGeneralGlyph* pGG = NULL;
  const CLReferenceGlyph* pRefG = NULL;
  iMax = this->getListOfGeneralGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pGG = this->getListOfGeneralGlyphs()[i];

      if (pGG->getCurve().getNumCurveSegments() > 0)
        {
          pCurve = &pGG->getCurve();
          CLBoundingBox bb = pCurve->calculateBoundingBox();
          pP = &bb.getPosition();
          x = pP->getX();
          y = pP->getY();
          pDim = &bb.getDimensions();
          x2 = x + pDim->getWidth();
          y2 = y + pDim->getHeight();
          minX = (minX < x) ? minX : x;
          minY = (minY < y) ? minY : y;
          maxX = (maxX > x2) ? maxX : x2;
          maxY = (maxY > y2) ? maxY : y2;
        }
      else
        {
          pBB = &pGG->getBoundingBox();
          pP = &pBB->getPosition();
          x = pP->getX();
          y = pP->getY();
          pDim = &pBB->getDimensions();
          x2 = x + pDim->getWidth();
          y2 = y + pDim->getHeight();
          minX = (minX < x) ? minX : x;
          minY = (minY < y) ? minY : y;
          maxX = (maxX > x2) ? maxX : x2;
          maxY = (maxY > y2) ? maxY : y2;
        }

      jMax = pGG->getListOfReferenceGlyphs().size();

      for (j = 0; j < jMax; ++j)
        {
          pRefG = pGG->getListOfReferenceGlyphs()[j];

          if (pRefG->getCurve().getNumCurveSegments() > 0)
            {
              pCurve = &pRefG->getCurve();
              CLBoundingBox bb = pCurve->calculateBoundingBox();
              pP = &bb.getPosition();
              x = pP->getX();
              y = pP->getY();
              pDim = &bb.getDimensions();
              x2 = x + pDim->getWidth();
              y2 = y + pDim->getHeight();
              minX = (minX < x) ? minX : x;
              minY = (minY < y) ? minY : y;
              maxX = (maxX > x2) ? maxX : x2;
              maxY = (maxY > y2) ? maxY : y2;
            }
          else
            {
              pBB = &pRefG->getBoundingBox();
              pP = &pBB->getPosition();
              x = pP->getX();
              y = pP->getY();
              pDim = &pBB->getDimensions();
              x2 = x + pDim->getWidth();
              y2 = y + pDim->getHeight();
              minX = (minX < x) ? minX : x;
              minY = (minY < y) ? minY : y;
              maxX = (maxX > x2) ? maxX : x2;
              maxY = (maxY > y2) ? maxY : y2;
            }
        }
    }

  const CLReactionGlyph* pRG = NULL;

  const CLMetabReferenceGlyph* pSRG = NULL;

  iMax = this->getListOfReactionGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pRG = this->getListOfReactionGlyphs()[i];

      if (pRG->getCurve().getNumCurveSegments() > 0)
        {
          pCurve = &pRG->getCurve();
          CLBoundingBox bb = pCurve->calculateBoundingBox();
          pP = &bb.getPosition();
          x = pP->getX();
          y = pP->getY();
          pDim = &bb.getDimensions();
          x2 = x + pDim->getWidth();
          y2 = y + pDim->getHeight();
          minX = (minX < x) ? minX : x;
          minY = (minY < y) ? minY : y;
          maxX = (maxX > x2) ? maxX : x2;
          maxY = (maxY > y2) ? maxY : y2;
        }
      else
        {
          pBB = &pRG->getBoundingBox();
          pP = &pBB->getPosition();
          x = pP->getX();
          y = pP->getY();
          pDim = &pBB->getDimensions();
          x2 = x + pDim->getWidth();
          y2 = y + pDim->getHeight();
          minX = (minX < x) ? minX : x;
          minY = (minY < y) ? minY : y;
          maxX = (maxX > x2) ? maxX : x2;
          maxY = (maxY > y2) ? maxY : y2;
        }

      jMax = pRG->getListOfMetabReferenceGlyphs().size();

      for (j = 0; j < jMax; ++j)
        {
          pSRG = pRG->getListOfMetabReferenceGlyphs()[j];

          if (pSRG->getCurve().getNumCurveSegments() > 0)
            {
              pCurve = &pSRG->getCurve();
              CLBoundingBox bb = pCurve->calculateBoundingBox();
              pP = &bb.getPosition();
              x = pP->getX();
              y = pP->getY();
              pDim = &bb.getDimensions();
              x2 = x + pDim->getWidth();
              y2 = y + pDim->getHeight();
              minX = (minX < x) ? minX : x;
              minY = (minY < y) ? minY : y;
              maxX = (maxX > x2) ? maxX : x2;
              maxY = (maxY > y2) ? maxY : y2;
            }
          else
            {
              pBB = &pSRG->getBoundingBox();
              pP = &pBB->getPosition();
              x = pP->getX();
              y = pP->getY();
              pDim = &pBB->getDimensions();
              x2 = x + pDim->getWidth();
              y2 = y + pDim->getHeight();
              minX = (minX < x) ? minX : x;
              minY = (minY < y) ? minY : y;
              maxX = (maxX > x2) ? maxX : x2;
              maxY = (maxY > y2) ? maxY : y2;
            }
        }
    }

  return CLBoundingBox(CLPoint(minX, minY), CLDimensions(maxX - minX, maxY - minY));
}

#endif /* USE_CRENDER_EXTENSION */

void CLayout::moveBy(const CLPoint &p)
{
  if (p.isEmpty()) return;

  CLGraphicalObject* pObject = NULL;
  size_t i, iMax = this->getListOfCompartmentGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfCompartmentGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfMetaboliteGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfMetaboliteGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfReactionGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfReactionGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfTextGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfTextGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfGeneralGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfGeneralGlyphs()[i];
      pObject->moveBy(p);
    }
}


void CLayout::calculateAndAssignBounds()
{
  CLBoundingBox bb = calculateBoundingBox();
  // move into the origin
  CLPoint differenceToOrigin(
    -bb.getPosition().getX(),
    -bb.getPosition().getY()
#ifdef USE_CRENDER_EXTENSION
    , -bb.getPosition().getZ()
#endif
  );
  moveBy(differenceToOrigin);
  setDimensions(bb.getDimensions());
}

#include <randomGenerator/CRandom.h>
#include <model/CCompartment.h>
#include <model/CMetab.h>
#include <layout/CCopasiSpringLayout.h>

void randomlyPlaceGlyphInCompartmentGlyph(CLGraphicalObject* pGl, const CLGraphicalObject* pContainer, CRandom *pRandom)
{
  double x = pContainer->getPosition().getX()
           + pRandom->getRandomCC()*(pContainer->getDimensions().getWidth() -pGl->getDimensions().getWidth() );
  double y = pContainer->getPosition().getY()
           + pRandom->getRandomCC()*(pContainer->getDimensions().getHeight() -pGl->getDimensions().getHeight() );
  pGl->setPosition(CLPoint(x,y));
}

void randomlyPlaceGlyphInDimensions(CLGraphicalObject* pGl, const CLDimensions* pContainer,CRandom *pRandom)
{
  double x = pRandom->getRandomCC()*(pContainer->getWidth() -pGl->getDimensions().getWidth() );
  double y = pRandom->getRandomCC()*(pContainer->getHeight() -pGl->getDimensions().getHeight() );
  pGl->setPosition(CLPoint(x,y));
}

void placeTextGlyphs(CLayout* pLayout)
{
  size_t i;
  for (i=0; i<pLayout->getListOfTextGlyphs().size(); ++i)
    {
      CLTextGlyph* pTG = pLayout->getListOfTextGlyphs()[i];
      CLGraphicalObject* pGO = pTG->getGraphicalObject();
      if (!pGO)
        continue;
      pTG->setPosition(CLPoint(pGO->getX()+2, pGO->getY()+2));
    }
}

/** 
 * This function produces a random layout. It first shufles around
 * metab glyphs and reaction centers, and finally corrects all ars
 */
void CLayout::randomize()
{
  CRandom* pRandom = CRandom::createGenerator(CRandom::mt19937, CRandom::getSystemSeed());

  size_t i;
  
  //compartment glyphs
  
  //metab glyphs
  for (i=0; i<getListOfMetaboliteGlyphs().size(); ++i)
    {
      CLMetabGlyph* pMetabGlyph = getListOfMetaboliteGlyphs()[i];
      const CMetab* pMetab = dynamic_cast<const CMetab*>( pMetabGlyph->getModelObject());
      if (!pMetab)
        continue;
    
      //find the compartment glyph
      const CCompartment* pComp = pMetab->getCompartment();
      if (!pComp)
        continue;
    
      const CLCompartmentGlyph* pCompGlyph=NULL;
      size_t j;
      for (j=0; j<getListOfCompartmentGlyphs().size(); ++j)
        if (getListOfCompartmentGlyphs()[j]->getModelObjectKey()
              ==pComp->getKey())
          {
            pCompGlyph = getListOfCompartmentGlyphs()[j];
            break;
          }
    
      if (pCompGlyph)
        randomlyPlaceGlyphInCompartmentGlyph(pMetabGlyph, pCompGlyph,pRandom);
      else
        randomlyPlaceGlyphInDimensions(pMetabGlyph, &getDimensions(),pRandom);
    }
  
  //reaction glyphs
  for (i=0; i<getListOfReactionGlyphs().size(); ++i)
    {
      CLReactionGlyph* pReactionGlyph = getListOfReactionGlyphs()[i];
      CLPoint center(0,0);
      size_t count;
      for (count = 0; count<pReactionGlyph->getListOfMetabReferenceGlyphs().size(); ++count)
        center = center + pReactionGlyph->getListOfMetabReferenceGlyphs()[count]
                        ->getMetabGlyph()->getBoundingBox().getCenter();
      center = center*(1.0/pReactionGlyph->getListOfMetabReferenceGlyphs().size());
      center = center + CLPoint( pRandom->getRandomCC()*20 -10,  pRandom->getRandomCC()*20 -10);
    
      pReactionGlyph->setPosition(center);
   
      /*if (pCompGlyph)
        randomlyPlaceGlyphInCompartmentGlyph(pMetabGlyph, pCompGlyph);
      else
        randomlyPlaceGlyphInDimensions(pMetabGlyph, &mpCurrentLayout->getDimensions());*/
    }
  
  placeTextGlyphs(this);
  delete pRandom;

  CCopasiSpringLayout l(this);
  l.createVariables();
  l.finalizeState();

}


class CompartmentInfo
{
public:
  unsigned int mNumItems;
  double mAreaSum;
  
  CompartmentInfo()
  :mNumItems(0),
  mAreaSum(0.0)
  {}
  
  void add(double area)
  {
    ++mNumItems;
    mAreaSum+=area;
  }
};

#include <map>

#include <model/CCompartment.h>
#include <model/CReaction.h>
#include <model/CMetab.h>

CLayout* CLayout::createLayout(
  CCopasiContainer *parent,
  const std::set<const CCompartment*>& compartments,
  const std::set<const CReaction*>& reactions,
  const std::set<const CMetab*>& metabs,
  const std::set<const CMetab*>& sideMetabs
  )
{
  CLayout *pResult = new CLayout("Layout", parent);

  double fontSize = 16.0;
  double fontHeight = fontSize*1.5;

  // create a species glyph for each species in metabs

  std::map<const CCompartment*, CompartmentInfo> compInfo;
  std::map<const CMetab*, CLMetabGlyph*> metabMap;

  std::set<const CMetab*>::const_iterator metabIt;
  for(metabIt=metabs.begin(); metabIt != metabs.end(); ++metabIt)
  {
    //estimate the size of the glyph
    double width = (double)((*metabIt)->getObjectName().length()*fontSize);
    double height = (double)fontHeight;
    if (width < height)
    {
      width = height;
    }

    //create the glyph
    CLMetabGlyph* pMetabGlyph= new CLMetabGlyph;
    pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
    pMetabGlyph->setModelObjectKey((*metabIt)->getKey());

    pResult->addMetaboliteGlyph(pMetabGlyph);
    metabMap[*metabIt] = pMetabGlyph;

    //create the text glyph for the label
    CLTextGlyph* pTextGlyph = new CLTextGlyph;
    pTextGlyph->setDimensions(CLDimensions(width, height));
    pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
    pTextGlyph->setModelObjectKey((*metabIt)->getKey());

    pResult->addTextGlyph(pTextGlyph);

    //add up the sizes for the compartment
    const CCompartment* pComp=NULL;
    if (compartments.find((*metabIt)->getCompartment()) != compartments.end() )
      pComp = (*metabIt)->getCompartment();

    compInfo[pComp].add((width+4)*(height+4));
  }


  //now the reaction glyphs
  std::set<const CReaction*>::const_iterator reactIt;
  for (reactIt=reactions.begin(); reactIt != reactions.end(); ++reactIt)
  {
    CLReactionGlyph* pReactionGlyph = new CLReactionGlyph;
    //pResult->setDimensions(CLDimensions(width, height));
    pReactionGlyph->setModelObjectKey((*reactIt)->getKey());
    //pReactionGlyph->getCurve().addCurveSegment(CLLineSegment(CLPoint(x, y),
    //                                             CLPoint(x + length, y)));

    pResult->addReactionGlyph(pReactionGlyph);

    //now add the species reference glyphs.

    //substrates
    const CCopasiVector < CChemEqElement >& substrates = (*reactIt)->getChemEq().getSubstrates();
    // if we have no substrates, add a dummy / invisible node for now
    if (substrates.size()==0)
    {
      CLMetabGlyph* pMetabGlyph = new CLMetabGlyph;
      pMetabGlyph->setDimensions(CLDimensions(1, 1));
      pMetabGlyph->setObjectRole("invisible");
      pResult->addMetaboliteGlyph(pMetabGlyph);

      CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
      //pResult->setModelObjectKey(modelobjectkey);
      pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
      pRefGlyph->setRole(CLMetabReferenceGlyph::SUBSTRATE); //TODO side substr?
      pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
    }

    CCopasiVector<CChemEqElement>::const_iterator elIt;
    for (elIt = substrates.begin(); elIt != substrates.end(); ++elIt)
    {
      const CMetab* pMetab = (*elIt)->getMetabolite();
      if (!pMetab)
        continue;

      CLMetabGlyph* pMetabGlyph = NULL;
      CLMetabReferenceGlyph::Role role; // = CLMetabReferenceGlyph::SUBSTRATE;
      //is it a side reactant? If yes, create a new metab glyph
      if (sideMetabs.find(pMetab) != sideMetabs.end())
      {
        //estimate the size of the glyph
        double width = (double)(pMetab->getObjectName().length()*fontSize);
        double height = (double)fontHeight;
        if (width < height)
        {
          width = height;
        }

        //create the glyph
        pMetabGlyph= new CLMetabGlyph;
        pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
        pMetabGlyph->setModelObjectKey(pMetab->getKey());
        //TODO: mark as duplicate 
        pResult->addMetaboliteGlyph(pMetabGlyph);

        //create the text glyph for the label
        CLTextGlyph* pTextGlyph = new CLTextGlyph;
        pTextGlyph->setDimensions(CLDimensions(width, height));
        pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
        pTextGlyph->setModelObjectKey(pMetab->getKey());

        pResult->addTextGlyph(pTextGlyph);

        //add up the sizes for the compartment
        const CCompartment* pComp=NULL;
        if (compartments.find(pMetab->getCompartment()) != compartments.end() )
          pComp = pMetab->getCompartment();

        compInfo[pComp].add((width+4)*(height+4));

        role = CLMetabReferenceGlyph::SIDESUBSTRATE;
      }
      else
      {  //find the existing metab glyph
        std::map<const CMetab*, CLMetabGlyph*>::const_iterator mmIt;
        mmIt = metabMap.find(pMetab);
        if (mmIt != metabMap.end())
          pMetabGlyph = mmIt->second;

        role = CLMetabReferenceGlyph::SUBSTRATE;
      }

      if (!pMetabGlyph)
        continue;

      CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
      //pResult->setModelObjectKey(modelobjectkey);
      pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
      pRefGlyph->setRole(role); 
      pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);

    } //substrates

    //products
    const CCopasiVector < CChemEqElement >& products = (*reactIt)->getChemEq().getProducts();
    // if we have no substrates, add a dummy / invisible node for now
    if (products.size()==0)
    {
      CLMetabGlyph* pMetabGlyph = new CLMetabGlyph;
      pMetabGlyph->setDimensions(CLDimensions(1, 1));
      pMetabGlyph->setObjectRole("invisible");
      pResult->addMetaboliteGlyph(pMetabGlyph);

      CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
      //pResult->setModelObjectKey(modelobjectkey);
      pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
      pRefGlyph->setRole(CLMetabReferenceGlyph::PRODUCT); //TODO side substr?
      pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);
    }

    for (elIt = products.begin(); elIt != products.end(); ++elIt)
    {
      const CMetab* pMetab = (*elIt)->getMetabolite();
      if (!pMetab)
        continue;

      CLMetabGlyph* pMetabGlyph = NULL;
      CLMetabReferenceGlyph::Role role; // = CLMetabReferenceGlyph::SUBSTRATE;
      //is it a side reactant? If yes, create a new metab glyph
      if (sideMetabs.find(pMetab) != sideMetabs.end())
      {
        //estimate the size of the glyph
        double width = (double)(pMetab->getObjectName().length()*fontSize);
        double height = (double)fontHeight;
        if (width < height)
        {
          width = height;
        }

        //create the glyph
        pMetabGlyph= new CLMetabGlyph;
        pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
        pMetabGlyph->setModelObjectKey(pMetab->getKey());
        //TODO: mark as duplicate 
        pResult->addMetaboliteGlyph(pMetabGlyph);

        //create the text glyph for the label
        CLTextGlyph* pTextGlyph = new CLTextGlyph;
        pTextGlyph->setDimensions(CLDimensions(width, height));
        pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
        pTextGlyph->setModelObjectKey(pMetab->getKey());

        pResult->addTextGlyph(pTextGlyph);

        //add up the sizes for the compartment
        const CCompartment* pComp=NULL;
        if (compartments.find(pMetab->getCompartment()) != compartments.end() )
          pComp = pMetab->getCompartment();

        compInfo[pComp].add((width+4)*(height+4));

        role = CLMetabReferenceGlyph::SIDEPRODUCT;
      }
      else
      {  //find the existing metab glyph
        std::map<const CMetab*, CLMetabGlyph*>::const_iterator mmIt;
        mmIt = metabMap.find(pMetab);
        if (mmIt != metabMap.end())
          pMetabGlyph = mmIt->second;

        role = CLMetabReferenceGlyph::PRODUCT;
      }

      if (!pMetabGlyph)
        continue;

      CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
      //pResult->setModelObjectKey(modelobjectkey);
      pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
      pRefGlyph->setRole(role); 
      pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);

    } //products

    //modifiers
    const CCopasiVector < CChemEqElement >& modifiers = (*reactIt)->getChemEq().getModifiers();
    for (elIt = modifiers.begin(); elIt != modifiers.end(); ++elIt)
    {
      const CMetab* pMetab = (*elIt)->getMetabolite();
      if (!pMetab)
        continue;

      CLMetabGlyph* pMetabGlyph = NULL;
      CLMetabReferenceGlyph::Role role; // = CLMetabReferenceGlyph::SUBSTRATE;
      //is it a side reactant? If yes, create a new metab glyph
      if (sideMetabs.find(pMetab) != sideMetabs.end())
      {
        //estimate the size of the glyph
        double width = (double)(pMetab->getObjectName().length()*fontSize);
        double height = (double)fontHeight;
        if (width < height)
        {
          width = height;
        }

        //create the glyph
        pMetabGlyph= new CLMetabGlyph;
        pMetabGlyph->setDimensions(CLDimensions(width + 4, height + 4));
        pMetabGlyph->setModelObjectKey(pMetab->getKey());
        //TODO: mark as duplicate 
        pResult->addMetaboliteGlyph(pMetabGlyph);

        //create the text glyph for the label
        CLTextGlyph* pTextGlyph = new CLTextGlyph;
        pTextGlyph->setDimensions(CLDimensions(width, height));
        pTextGlyph->setGraphicalObjectKey(pMetabGlyph->getKey());
        pTextGlyph->setModelObjectKey(pMetab->getKey());

        pResult->addTextGlyph(pTextGlyph);

        //add up the sizes for the compartment
        const CCompartment* pComp=NULL;
        if (compartments.find(pMetab->getCompartment()) != compartments.end() )
          pComp = pMetab->getCompartment();

        compInfo[pComp].add((width+4)*(height+4));

        role = CLMetabReferenceGlyph::MODIFIER; //TODO SIDEMODIFIER???
      }
      else
      {  //find the existing metab glyph
        std::map<const CMetab*, CLMetabGlyph*>::const_iterator mmIt;
        mmIt = metabMap.find(pMetab);
        if (mmIt != metabMap.end())
          pMetabGlyph = mmIt->second;

        role = CLMetabReferenceGlyph::MODIFIER;
      }

      if (!pMetabGlyph)
        continue;

      CLMetabReferenceGlyph* pRefGlyph = new CLMetabReferenceGlyph;
      //pResult->setModelObjectKey(modelobjectkey);
      pRefGlyph->setMetabGlyphKey(pMetabGlyph->getKey());
      pRefGlyph->setRole(role); 
      pReactionGlyph->addMetabReferenceGlyph(pRefGlyph);

    } //modifiers


  } //reactions


  //rules
  size_t i;
  for (i=0; i<pResult->getListOfMetaboliteGlyphs().size(); ++i )
  {
    const CLMetabGlyph* pMetabGlyph = pResult->getListOfMetaboliteGlyphs()[i];
    const CMetab* pMetab = dynamic_cast<const CMetab*>(pMetabGlyph->getModelObject());
    if (!pMetab)
      continue;

    if (pMetab->getStatus() == CModelEntity::ODE || pMetab->getStatus() == CModelEntity::ASSIGNMENT)
    {
      CLGeneralGlyph* pGG = new CLGeneralGlyph;
      pGG->setDimensions(CLDimensions(10,10));
      pGG->setObjectRole("rule");

      pResult->addGeneralGlyph(pGG);

      CLReferenceGlyph* pRefGlyph = new CLReferenceGlyph;
      pRefGlyph->setTargetGlyphKey(pMetabGlyph->getKey());
      pRefGlyph->setRole("rule connection");
      pGG->addReferenceGlyph(pRefGlyph);

    }

  }

  //after all other glyphs are created, create the compartment glyphs
  double xxx = 0;
  std::set<const CCompartment*>::const_iterator compIt;
  for(compIt=compartments.begin(); compIt != compartments.end(); ++compIt)
  {
    double compSize = 10000;
    std::map<const CCompartment*, CompartmentInfo>::const_iterator ccIt;
    ccIt = compInfo.find(*compIt);
    if (ccIt != compInfo.end() )
    { //some glyphs are placed inside this compartment glyph
      compSize = ccIt->second.mAreaSum*40;
    }

    //create the glyph
    CLCompartmentGlyph* pCompGlyph= new CLCompartmentGlyph;
    pCompGlyph->setModelObjectKey((*compIt)->getKey());
    pCompGlyph->setDimensions(CLDimensions(CLDimensions(sqrt(compSize), sqrt(compSize))));
    pCompGlyph->setPosition(CLPoint(xxx, 5));
    xxx += sqrt(compSize) + 10;

    pResult->addCompartmentGlyph(pCompGlyph);
  }

  // randomize
  pResult->randomize();

  // determine and set the layout dimensions
  CLBoundingBox box = pResult->calculateBoundingBox();
  pResult->setDimensions(CLDimensions(box.getDimensions().getWidth() + 30.0, box.getDimensions().getHeight() + 30.0));

  return pResult;
}
