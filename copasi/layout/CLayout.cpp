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

#define USE_LAYOUT 1
#define USE_RENDER 1

#include "iostream"
#include "sbml/packages/layout/sbml/Layout.h"
#include "sbml/packages/render/sbml/LocalRenderInformation.h"
#include "sbml/packages/render/extension/RenderLayoutPlugin.h"
#include "sbml/packages/render/extension/RenderListOfLayoutsPlugin.h"

#include "sbml/packages/layout/sbml/GeneralGlyph.h"

#include "copasi/copasi.h"

#include "CLayout.h"
#include "CLReactionGlyph.h"
#include "SBMLDocumentLoader.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/sbml/CSBMLExporter.h"
#include "copasi/core/CRootContainer.h"

// static
CLayout * CLayout::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLayout(data.getProperty(CData::OBJECT_NAME).toString(),
                     NO_PARENT);
}

// virtual
CData CLayout::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLayout::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLayout::CLayout(const std::string & name,
                 const CDataContainer * pParent)
  : CLBase(),
    CDataContainer(name, pParent, "Layout"),
    mKey(CRootContainer::getKeyFactory()->add("Layout", this)),
    mDimensions(),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
    , mvLocalRenderInformationObjects("ListOfLocalRenderInformationObjects", this)
{}

CLayout::CLayout(const CLayout & src,
                 const CDataContainer * pParent)
  : CLBase(src),
    CDataContainer(src, pParent),
    mKey(CRootContainer::getKeyFactory()->add("Layout", this)),
    mDimensions(src.mDimensions),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
    , mvLocalRenderInformationObjects(src.mvLocalRenderInformationObjects, this)
{
  //TODO references from one glyph to another have to be reconstructed after
  //     copying. This applies to Labels and species reference glyphs

  std::map<std::string, std::string> forward;
  std::map<std::string, std::string> reverse;

  CDataVector<CLCompartmentGlyph>::const_iterator compIt = src.mvCompartments.begin();

  for (; compIt != src.mvCompartments.end(); ++compIt)
    {
      CLCompartmentGlyph *comp = new CLCompartmentGlyph(*compIt, NO_PARENT);
      mvCompartments.add(comp, true);
      forward[compIt->getKey()] = comp->getKey();
      reverse[comp->getKey()] = compIt->getKey();
    }

  CDataVector<CLMetabGlyph>::const_iterator metabIt = src.mvMetabs.begin();

  for (; metabIt != src.mvMetabs.end(); ++metabIt)
    {
      CLMetabGlyph *metab = new CLMetabGlyph(*metabIt, NO_PARENT);
      mvMetabs.add(metab, true);
      forward[metabIt->getKey()] = metab->getKey();
      reverse[metab->getKey()] = metabIt->getKey();
    }

  CDataVector<CLReactionGlyph>::const_iterator reactIt = src.mvReactions.begin();

  for (; reactIt != src.mvReactions.end(); ++reactIt)
    {
      CLReactionGlyph *r = new CLReactionGlyph(*reactIt, NO_PARENT);
      mvReactions.add(r, true);
      forward[reactIt->getKey()] = r->getKey();
      reverse[r->getKey()] = reactIt->getKey();

      for (size_t i = 0; i < r->getListOfMetabReferenceGlyphs().size(); ++i)
        {
          forward[reactIt->getListOfMetabReferenceGlyphs()[i].getKey()]
            = r->getListOfMetabReferenceGlyphs()[i].getKey();
          reverse[r->getListOfMetabReferenceGlyphs()[i].getKey()]
            = reactIt->getListOfMetabReferenceGlyphs()[i].getKey();
        }
    }

  CDataVector<CLTextGlyph>::const_iterator textIt = src.mvLabels.begin();

  for (; textIt != src.mvLabels.end(); ++textIt)
    {
      CLTextGlyph *text = new CLTextGlyph(*textIt, NO_PARENT);
      mvLabels.add(text, true);
      forward[textIt->getKey()] = text->getKey();
      reverse[text->getKey()] = textIt->getKey();
    }

  CDataVector<CLGeneralGlyph>::const_iterator generalIt = src.mvGraphicalObjects.begin();

  for (; generalIt != src.mvGraphicalObjects.end(); ++generalIt)
    {
      CLGeneralGlyph *general = new CLGeneralGlyph(*generalIt, NO_PARENT);
      mvGraphicalObjects.add(general, true);
      forward[generalIt->getKey()] = general->getKey();
      reverse[general->getKey()] = generalIt->getKey();

      for (size_t i = 0; i < general->getListOfReferenceGlyphs().size(); ++i)
        {
          forward[generalIt->getListOfReferenceGlyphs()[i].getKey()]
            = general->getListOfReferenceGlyphs()[i].getKey();
          reverse[general->getListOfReferenceGlyphs()[i].getKey()]
            = generalIt->getListOfReferenceGlyphs()[i].getKey();
        }

      for (size_t i = 0; i < general->getListOfSubglyphs().size(); ++i)
        {
          forward[generalIt->getListOfSubglyphs()[i].getKey()]
            = general->getListOfSubglyphs()[i].getKey();
          reverse[general->getListOfSubglyphs()[i].getKey()]
            = generalIt->getListOfSubglyphs()[i].getKey();
        }
    }

  {

    // by now we have collected all keys, now we need to replace them
    std::map<std::string, std::string>::const_iterator constIt;
    CDataVector<CLTextGlyph>::iterator textIt = mvLabels.begin();

    for (; textIt != mvLabels.end(); ++textIt)
      {
        CLTextGlyph *text = textIt;
        const std::string& key = text->getGraphicalObjectKey();
        constIt = forward.find(key);

        if (constIt == forward.end())
          continue;

        text->setGraphicalObjectKey(constIt->second);
      }

    CDataVector<CLReactionGlyph>::iterator reactIt = mvReactions.begin();

    for (; reactIt != mvReactions.end(); ++reactIt)
      {
        CLReactionGlyph *r = reactIt;
        CDataVector<CLMetabReferenceGlyph>::iterator refIt = r->getListOfMetabReferenceGlyphs().begin();

        for (; refIt != r->getListOfMetabReferenceGlyphs().end(); ++refIt)
          {
            CLMetabReferenceGlyph* current = refIt;
            const std::string& key = current->getMetabGlyphKey();
            constIt = forward.find(key);

            if (constIt == forward.end())
              continue;

            current->setMetabGlyphKey(constIt->second);
          }
      }

    CDataVector<CLGeneralGlyph>::iterator generalIt = mvGraphicalObjects.begin();

    for (; generalIt != mvGraphicalObjects.end(); ++generalIt)
      {
        CLGeneralGlyph *g = generalIt;
        CDataVector<CLReferenceGlyph>::iterator refIt = g->getListOfReferenceGlyphs().begin();

        for (; refIt != g->getListOfReferenceGlyphs().end(); ++refIt)
          {
            CLReferenceGlyph* current = refIt;
            const std::string& key = current->getTargetGlyphKey();
            constIt = forward.find(key);

            if (constIt == forward.end())
              continue;

            current->setTargetGlyphKey(constIt->second);
          }

        //CDataVector<CLGraphicalObject>::iterator refIt = g->getListOfSubglyphs().begin();
        //for(;refIt != g->getListOfReferenceGlyphs().end(); ++refIt)
        //{
        //  CLGraphicalObject* current = *refIt;
        //  const std::string& key = current->getTargetGlyphKey();
        //  constIt = forward.find(key);
        //  if (constIt == forward.end())
        //    continue;
        //  current->setTargetGlyphKey(constIt->second);
        //}
      }
  }
}

CLayout::CLayout(const Layout & sbml,
                 std::map<std::string, std::string> & layoutmap,
                 const CDataContainer * pParent)
  : CLBase(sbml),
    CDataContainer(sbml.getId(), pParent, "Layout"),
    mKey(CRootContainer::getKeyFactory()->add("Layout", this)),
    mDimensions(*sbml.getDimensions()),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
    , mvLocalRenderInformationObjects("ListOfLocalRenderInformationObjects", this)
{
  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;

  if (sbml.isSetName())
    setObjectName(sbml.getName());
}

CLayout::~CLayout()
{
  CRootContainer::getKeyFactory()->remove(mKey);
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
        os << l.mvCompartments[i];
    }

  imax = l.mvMetabs.size();

  if (imax)
    {
      os << "\nList of species glyphs: \n\n";

      for (i = 0; i < imax; ++i)
        os << l.mvMetabs[i];
    }

  imax = l.mvReactions.size();

  if (imax)
    {
      os << "\nList of reaction glyphs: \n\n";

      for (i = 0; i < imax; ++i)
        os << l.mvReactions[i];
    }

  imax = l.mvLabels.size();

  if (imax)
    {
      os << "\nList of labels: \n\n";

      for (i = 0; i < imax; ++i)
        os << l.mvLabels[i];
    }

  imax = l.mvGraphicalObjects.size();

  if (imax)
    {
      os << "\nList of graphical objects: \n\n";

      for (i = 0; i < imax; ++i)
        os << l.mvGraphicalObjects[i];
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
      writeDotNode(os, mvMetabs[i].getKey(), mvMetabs[i].getModelObjectDisplayName());
    }

  //reaction glyphs
  imax = mvReactions.size();

  for (i = 0; i < imax; ++i)
    {
      writeDotNode(os, mvReactions[i].getKey() + "_S", "", 1);
      writeDotNode(os, mvReactions[i].getKey() + "_P", "", 1);
      writeDotEdge(os, mvReactions[i].getKey() + "_S", mvReactions[i].getKey() + "_P", 1);

      size_t j, jmax = mvReactions[i].getListOfMetabReferenceGlyphs().size();

      for (j = 0; j < jmax; ++j)
        {
          const CLMetabReferenceGlyph* mrg = &mvReactions[i].getListOfMetabReferenceGlyphs()[j];

          if (mrg->getRole() == CLMetabReferenceGlyph::SUBSTRATE)
            writeDotEdge(os, mrg->getMetabGlyphKey(), mvReactions[i].getKey() + "_S");
          else if (mrg->getRole() == CLMetabReferenceGlyph::PRODUCT)
            writeDotEdge(os, mvReactions[i].getKey() + "_P", mrg->getMetabGlyphKey());
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

void CLayout::exportToSBML(Layout * layout, const std::map<const CDataObject*, SBase*> & copasimodelmap,
                           std::map<std::string, const SBase*>& sbmlIDs
                           , const std::map<std::string, std::string>& globalKeyToIdMap
                           //,const std::map<std::string,std::map<std::string,std::string> >& globalColorKeyToIdMapMap
                           //,const std::map<std::string,std::map<std::string,std::string> >& globalGradientKeyToIdMapMap
                           //,const std::map<std::string,std::map<std::string,std::string> >& globalLineEndingKeyToIdMapMap
                          ) const
{
  if (!layout) return;

  //Name and ID
  std::string id = CSBMLExporter::createUniqueId(sbmlIDs, "layout", true);
  layout->setId(id);
  layout->setName(getObjectName());
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
      const CLCompartmentGlyph * tmp = &mvCompartments[i];

      //check if the compartment glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
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
      const CLMetabGlyph * tmp = &mvMetabs[i];

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
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
      const CLReactionGlyph * tmp = &mvReactions[i];

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
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
      const CLTextGlyph * tmp = &mvLabels[i];

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
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
      const CLGeneralGlyph * tmp = &mvGraphicalObjects[i];

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      GraphicalObject * pG;

      if (it == copasimodelmap.end()) //not found
        {
          if (tmp->getListOfReferenceGlyphs().size() > 0)
            pG = layout->createGeneralGlyph();
          else
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
      const CLTextGlyph * tmp = &mvLabels[i];

      //find the corresponding SBML object
      std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);

      if (it != layoutmap.end() && it->second && dynamic_cast<const TextGlyph*>(it->second))
        {
          tmp->exportReferenceToSBML(const_cast<TextGlyph*>(dynamic_cast<const TextGlyph*>(it->second)), layoutmap);
        }
    }

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
      //pLRI=this->mvLocalRenderInformationObjects[i].toSBML(colorKeyToIdMap,gradientKeyToIdMap,lineEndingKeyToIdMap);
      pLRI = this->mvLocalRenderInformationObjects[i].toSBML(layout->getLevel(), layout->getVersion());
      keyToIdMap.insert(std::pair<std::string, std::string>(this->mvLocalRenderInformationObjects[i].getKey(), pLRI->getId()));
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
}

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

  return &this->mvLocalRenderInformationObjects[index];
}

/**
 * Returns a pointer to the local render information with the given index or NULL
 * if the index is invalid.
 */
CLLocalRenderInformation* CLayout::getRenderInformation(size_t index)
{
  if (index >= this->mvLocalRenderInformationObjects.size()) return NULL;

  return &this->mvLocalRenderInformationObjects[index];
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
      pObject = &this->getListOfCompartmentGlyphs()[i];
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
      pObject = &this->getListOfMetaboliteGlyphs()[i];
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
      pObject = &this->getListOfTextGlyphs()[i];
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
      pGG = &this->getListOfGeneralGlyphs()[i];

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
          pRefG = &pGG->getListOfReferenceGlyphs()[j];

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
      pRG = &this->getListOfReactionGlyphs()[i];

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
          pSRG = &pRG->getListOfMetabReferenceGlyphs()[j];

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

void CLayout::moveBy(const CLPoint &p)
{
  if (p.isEmpty()) return;

  CLGraphicalObject* pObject = NULL;
  size_t i, iMax = this->getListOfCompartmentGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = &this->getListOfCompartmentGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfMetaboliteGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = &this->getListOfMetaboliteGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfReactionGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = &this->getListOfReactionGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfTextGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = &this->getListOfTextGlyphs()[i];
      pObject->moveBy(p);
    }

  iMax = this->getListOfGeneralGlyphs().size();

  for (i = 0; i < iMax; ++i)
    {
      pObject = &this->getListOfGeneralGlyphs()[i];
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
    , -bb.getPosition().getZ()
  );
  moveBy(differenceToOrigin);
  setDimensions(bb.getDimensions());
}
