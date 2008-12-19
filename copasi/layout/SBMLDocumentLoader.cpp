// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/SBMLDocumentLoader.cpp,v $
//   $Revision: 1.11.6.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/13 09:48:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "SBMLDocumentLoader.h"

#include <sbml/layout/Layout.h>
#include <sbml/layout/SpeciesGlyph.h>
#include <sbml/layout/ReactionGlyph.h>
#include <sbml/layout/SpeciesReferenceGlyph.h>
#include <sbml/layout/TextGlyph.h>
#include <sbml/ListOf.h>

#include "report/CKeyFactory.h"

#include "CListOfLayouts.h"
#include "CLayout.h"
#include "CLReactionGlyph.h"
#include "CLGlyphs.h"

#include "sbml/SBMLUtils.h" //from the copasi sbml dir

//static
void SBMLDocumentLoader::readListOfLayouts(CListOfLayouts & lol,
    const ListOf & sbmlList,
    const std::map<CCopasiObject*, SBase*> & copasimodelmap)
{
  //convert the map as used by the CLxxx constructors
  std::map<std::string, std::string> modelmap;

  std::string s1, s2;
  std::map<CCopasiObject*, SBase*>::const_iterator it;
  std::map<CCopasiObject*, SBase*>::const_iterator itEnd = copasimodelmap.end();
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
  C_INT32 i, imax = sbmlList.size();
  for (i = 0; i < imax; ++i)
    {
      std::map<std::string, std::string> layoutmap;
      const Layout* tmp
      = dynamic_cast<const Layout*>(sbmlList.get(i));
      if (tmp)
        {
          CLayout * pLayout = createLayout(*tmp, modelmap, layoutmap);
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
    std::map<std::string, std::string> & layoutmap,
    const CCopasiContainer * pParent)
{
  CLayout* layout = new CLayout(sbmlLayout, layoutmap, pParent);

  C_INT32 i, imax;

  //compartments
  imax = sbmlLayout.getListOfCompartmentGlyphs()->size();
  for (i = 0; i < imax; ++i)
    {
      const CompartmentGlyph* tmp
      = dynamic_cast<const CompartmentGlyph*>(sbmlLayout.getListOfCompartmentGlyphs()->get(i));
      if (tmp)
        layout->addCompartmentGlyph(new CLCompartmentGlyph(*tmp, modelmap, layoutmap));
    }

  //species
  imax = sbmlLayout.getListOfSpeciesGlyphs()->size();
  for (i = 0; i < imax; ++i)
    {
      const SpeciesGlyph* tmp
      = dynamic_cast<const SpeciesGlyph*>(sbmlLayout.getListOfSpeciesGlyphs()->get(i));
      if (tmp)
        layout->addMetaboliteGlyph(new CLMetabGlyph(*tmp, modelmap, layoutmap));
    }

  //reactions
  imax = sbmlLayout.getListOfReactionGlyphs()->size();
  for (i = 0; i < imax; ++i)
    {
      const ReactionGlyph* tmp
      = dynamic_cast<const ReactionGlyph*>(sbmlLayout.getListOfReactionGlyphs()->get(i));
      if (tmp)
        layout->addReactionGlyph(new CLReactionGlyph(*tmp, modelmap, layoutmap));
    }

  //text
  imax = sbmlLayout.getListOfTextGlyphs()->size();
  for (i = 0; i < imax; ++i)
    {
      const TextGlyph* tmp
      = dynamic_cast<const TextGlyph*>(sbmlLayout.getListOfTextGlyphs()->get(i));
      if (tmp)
        layout->addTextGlyph(new CLTextGlyph(*tmp, modelmap, layoutmap));
    }

  //additional
  imax = sbmlLayout.getListOfAdditionalGraphicalObjects()->size();
  for (i = 0; i < imax; ++i)
    {
      const GraphicalObject* tmp
      = dynamic_cast<const GraphicalObject*>(sbmlLayout.getListOfAdditionalGraphicalObjects()->get(i));
      if (tmp)
        layout->addGraphicalObject(new CLGraphicalObject(*tmp, layoutmap));
    }

  //second pass text (the text glyph can refer to other glyphs. These references can)
  //only be resolved after all glyphs are created).
  imax = sbmlLayout.getListOfTextGlyphs()->size();
  for (i = 0; i < imax; ++i)
    {
      const TextGlyph* tmp
      = dynamic_cast<const TextGlyph*>(sbmlLayout.getListOfTextGlyphs()->get(i));
      if (tmp)
        postprocessTextGlyph(*tmp, layoutmap);
    }

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
        pTg = dynamic_cast<CLTextGlyph *>(GlobalKeys.get(it->second));
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
