// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayout.cpp,v $
//   $Revision: 1.19.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:01:26 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#define USE_LAYOUT 1

#ifdef USE_CRENDER_EXTENSION
#define USE_RENDER 1
#endif // USE_CRENDER_EXTENSION

#include "iostream"
#include "sbml/layout/Layout.h"

#include "copasi.h"

#include "CLayout.h"
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

void CLayout::addGraphicalObject(CLGraphicalObject * glyph)
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

void CLayout::exportToSBML(Layout * layout, const std::map<CCopasiObject*, SBase*> & copasimodelmap,
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
  std::string id = CSBMLExporter::createUniqueId(sbmlIDs, "layout_");
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
      std::map<CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      CompartmentGlyph * pCG;

      if (it == copasimodelmap.end()) //not found
        {
          pCG = new CompartmentGlyph;
          layout->getListOfCompartmentGlyphs()->appendAndOwn(pCG);
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
      std::map<CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      SpeciesGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = new SpeciesGlyph;
          layout->getListOfSpeciesGlyphs()->appendAndOwn(pG);
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
      std::map<CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      ReactionGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = new ReactionGlyph;
          layout->getListOfReactionGlyphs()->appendAndOwn(pG);
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
      std::map<CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      TextGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = new TextGlyph;
          layout->getListOfTextGlyphs()->appendAndOwn(pG);
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
      CLGraphicalObject * tmp = mvGraphicalObjects[i];

      //check if the glyph exists in the libsbml data
      std::map<CCopasiObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      GraphicalObject * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = new GraphicalObject;
          layout->getListOfAdditionalGraphicalObjects()->appendAndOwn(pG);
        }
      else
        {
          pG = dynamic_cast<GraphicalObject*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs);
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

      layout->getListOfLocalRenderInformation()->appendAndOwn(pLRI);
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

  iMax = this->getListOfGraphicalObjects().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = this->getListOfGraphicalObjects()[i];
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

  const CLReactionGlyph* pRG = NULL;

  const CLMetabReferenceGlyph* pSRG = NULL;

  size_t j, jMax;

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
