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

#include "CLayoutInitializer.h"

#include "copasi/model/CModel.h"
#include "CLayout.h"

//static
/*CLayout * CLayoutInitializer::createLayoutFromCModel(const CModel* model)
{
  if (!model) return NULL;

  CLayout * layout = new CLayout("dummy layout");

  size_t i, imax;

  //compartments
  imax = model->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      CLCompartmentGlyph * comp = createCompartmentGlyph(model->getCompartments()[i]);
      layout->addCompartmentGlyph(comp);
    }

  //metabs
  std::map<std::string, std::string> metabMap; //maps from metab key to metab glyph key
  imax = model->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CLMetabGlyph * comp = createMetabGlyph(model->getMetabolites()[i]);
      layout->addMetaboliteGlyph(comp);
      metabMap[comp->getModelObjectKey()] = comp->getKey();
    }

  //reactions
  imax = model->getReactions().size();

  for (i = 0; i < imax; ++i)
    {
      CLReactionGlyph * reac = createReactionGlyph(model->getReactions()[i], metabMap);
      layout->addReactionGlyph(reac);
    }

  //temporary
  //std::ofstream ofs; ofs.open("CopasiModel.dot");
  //layout->exportToDotFile(ofs);
  //ofs.close();

  return layout;
}*/

CLCompartmentGlyph * CLayoutInitializer::createCompartmentGlyph(const CCompartment * c)
{
  if (!c) return NULL;

  CLCompartmentGlyph* cg = new CLCompartmentGlyph();
  cg->setModelObjectKey(c->getKey());

  return cg;
}

CLMetabGlyph * CLayoutInitializer::createMetabGlyph(const CMetab * m)
{
  if (!m) return NULL;

  CLMetabGlyph* cg = new CLMetabGlyph();
  cg->setModelObjectKey(m->getKey());

  return cg;
}

CLReactionGlyph * CLayoutInitializer::createReactionGlyph(const CReaction * r,
    const std::map<std::string, std::string> & mm)
{
  if (!r) return NULL;

  CLReactionGlyph* rg = new CLReactionGlyph();
  rg->setModelObjectKey(r->getKey());

  const CChemEq & ce = r->getChemEq();
  size_t i, imax;

  //substrates
  imax = ce.getSubstrates().size();

  for (i = 0; i < imax; ++i)
    {
      //create metab reference glyph and add to reaction glyph
      CLMetabReferenceGlyph * tmpMRG = new CLMetabReferenceGlyph();
      tmpMRG->setRole(CLMetabReferenceGlyph::SUBSTRATE);
      rg->addMetabReferenceGlyph(tmpMRG);

      //get the metab key from the copasi reaction
      std::string metabKey = ce.getSubstrates()[i].getMetaboliteKey();

      //set the corresponding metab glyph key
      const std::map<std::string, std::string>::const_iterator it = mm.find(metabKey);

      if (it != mm.end())
        tmpMRG->setMetabGlyphKey(it->second);
    }

  //products
  imax = ce.getProducts().size();

  for (i = 0; i < imax; ++i)
    {
      //create metab reference glyph and add to reaction glyph
      CLMetabReferenceGlyph * tmpMRG = new CLMetabReferenceGlyph();
      tmpMRG->setRole(CLMetabReferenceGlyph::PRODUCT);
      rg->addMetabReferenceGlyph(tmpMRG);

      //get the metab key from the copasi reaction
      std::string metabKey = ce.getProducts()[i].getMetaboliteKey();

      //set the corresponding metab glyph key
      const std::map<std::string, std::string>::const_iterator it = mm.find(metabKey);

      if (it != mm.end())
        tmpMRG->setMetabGlyphKey(it->second);
    }

  //modifier
  imax = ce.getModifiers().size();

  for (i = 0; i < imax; ++i)
    {
      //create metab reference glyph and add to reaction glyph
      CLMetabReferenceGlyph * tmpMRG = new CLMetabReferenceGlyph();
      tmpMRG->setRole(CLMetabReferenceGlyph::MODIFIER);
      rg->addMetabReferenceGlyph(tmpMRG);

      //get the metab key from the copasi reaction
      std::string metabKey = ce.getModifiers()[i].getMetaboliteKey();

      //set the corresponding metab glyph key
      const std::map<std::string, std::string>::const_iterator it = mm.find(metabKey);

      if (it != mm.end())
        tmpMRG->setMetabGlyphKey(it->second);
    }

  return rg;
}
