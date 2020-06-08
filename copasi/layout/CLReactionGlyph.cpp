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

//#include<iostream>

#define USE_LAYOUT 1

#include <sbml/packages/layout/sbml/ReactionGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceGlyph.h>

#include <sbml/packages/layout/sbml/GraphicalObject.h>
#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/CompartmentGlyph.h>
#include <sbml/packages/layout/sbml/GeneralGlyph.h>
#include <sbml/packages/layout/sbml/ReferenceGlyph.h>

#include "copasi/copasi.h"

#include "CLReactionGlyph.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

CLGlyphWithCurve::CLGlyphWithCurve(const std::string & name,
                                   const CDataContainer * pParent)
  : CLGraphicalObject(name, pParent),
    mCurve()
{}

CLGlyphWithCurve::CLGlyphWithCurve(const CLGlyphWithCurve & src,
                                   const CDataContainer * pParent)
  : CLGraphicalObject(src, pParent),
    mCurve(src.mCurve)
{}

CLGlyphWithCurve::CLGlyphWithCurve(const GraphicalObject & sbml,
                                   const std::map<std::string, std::string> & modelmap,
                                   std::map<std::string, std::string> & layoutmap,
                                   const CDataContainer * pParent)
  : CLGraphicalObject(sbml, layoutmap, pParent),
    mCurve() //initialized in the body below
{
  const GeneralGlyph* general = dynamic_cast<const GeneralGlyph *>(&sbml);

  if (general && general->isSetCurve())
    {
      CLCurve copy(*general->getCurve());
      mCurve = copy;
    }

  const ReferenceGlyph* rG = dynamic_cast<const ReferenceGlyph *>(&sbml);

  if (rG && rG->isSetCurve())
    {
      CLCurve copy(*rG->getCurve());
      mCurve = copy;
    }
}

CLGlyphWithCurve & CLGlyphWithCurve::operator= (const CLGlyphWithCurve & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGraphicalObject::operator=(rhs);

  //handle the specific glyph stuff:
  mCurve = rhs.mCurve;

  return *this;
}

const CLCurve &
CLGlyphWithCurve::getCurve() const
{
  return mCurve;
}

CLCurve &
CLGlyphWithCurve::getCurve()
{
  return mCurve;
}

void
CLGlyphWithCurve::setCurve(const CLCurve &c)
{
  mCurve = c;
}

void CLGlyphWithCurve::moveBy(const CLPoint &p)
{
  CLGraphicalObject::moveBy(p);
  mCurve.moveBy(p);
}

std::ostream & operator<<(std::ostream &os, const CLGlyphWithCurve & g)
{
  //TODO: bounding box?
  os << g.mCurve;

  return os;
}

void CLGlyphWithCurve::print(std::ostream * ostream) const
{*ostream << *this;}

//***************************

// static
CLReferenceGlyph * CLReferenceGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLReferenceGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                              NO_PARENT);
}

// virtual
CData CLReferenceGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLReferenceGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLReferenceGlyph::CLReferenceGlyph(const std::string & name,
                                   const CDataContainer * pParent)
  : CLGlyphWithCurve(name, pParent)
  , mGlyphKey()
  , mRole()
{}

CLReferenceGlyph::CLReferenceGlyph(const CLReferenceGlyph & src,
                                   const CDataContainer * pParent)
  : CLGlyphWithCurve(src, pParent)
  , mGlyphKey(src.mGlyphKey)
  , mRole(src.mRole)
{}

CLReferenceGlyph::CLReferenceGlyph(const ReferenceGlyph & sbml,
                                   const std::map<std::string, std::string> & modelmap,
                                   std::map<std::string, std::string> & layoutmap,
                                   const CDataContainer * pParent)
  : CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent)
  , mGlyphKey() //initialized in the body below
  , mRole() //initialized in the body below
{
  //get the copasi key corresponding to the sbml id for the species reference
  if (sbml.isSetReferenceId())
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getReferenceId());

      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //get the copasi key corresponding to the sbml id for the species glyph
  if (sbml.isSetGlyphId())
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getGlyphId());

      if (it != layoutmap.end())
        mGlyphKey = it->second;
    }

  if (sbml.isSetRole())
    mRole = sbml.getRole();
}

CLReferenceGlyph & CLReferenceGlyph::operator= (const CLReferenceGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGlyphWithCurve::operator=(rhs);

  //handle the specific glyph stuff:
  mGlyphKey = rhs.mGlyphKey;
  mRole = rhs.mRole;

  return *this;
}

const std::string &
CLReferenceGlyph::getRole() const
{
  return mRole;
}

void
CLReferenceGlyph::setRole(const std::string &r)
{
  mRole = r;
}

const std::string &
CLReferenceGlyph::getTargetGlyphKey() const
{
  return mGlyphKey;
}

CLGraphicalObject* CLReferenceGlyph::getTargetGlyph() const
{
  CDataObject* tmp = CRootContainer::getKeyFactory()->get(mGlyphKey);
  return dynamic_cast<CLMetabGlyph*>(tmp);
}

void
CLReferenceGlyph::setTargetGlyphKey(const std::string &k)
{
  mGlyphKey = k;
}

CLGraphicalObject *
CLReferenceGlyph::clone() const
{
  return new CLReferenceGlyph(*this, NULL);
}

void CLReferenceGlyph::exportToSBML(ReferenceGlyph * g, //TODO
                                    const std::map<const CDataObject*, SBase*> & copasimodelmap,
                                    std::map<std::string, const SBase*>& sbmlIDs,
                                    const std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //call the coresponding method of the base class
  CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

  //reference to species glyph
  CLGraphicalObject* tmp = getTargetGlyph();

  if (tmp)
    {
      std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);

      if (it != layoutmap.end())
        {
          if (it->second)
            {
              //we need to cast here since layout objects in libsbml don´t inherit the getId() method
              //from SBase
              const GraphicalObject* pGO = dynamic_cast<const GraphicalObject*>(it->second);

              if (pGO)
                g->setGlyphId(pGO->getId());
            }
        }
    }

  g->setRole(mRole);

  //curve
  mCurve.exportToSBML(g->getCurve(), copasimodelmap);
}

std::ostream & operator<<(std::ostream &os, const CLReferenceGlyph & g)
{
  os << "    ReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  const CLGraphicalObject* tmp = g.getTargetGlyph();

  if (tmp)
    os << "      refers to a Glyph that refers to "
       << tmp->getModelObjectDisplayName() << std::endl;

  os << g.mCurve; //TODO refer to base class?

  return os;
}

void CLReferenceGlyph::print(std::ostream * ostream) const
{*ostream << *this;}

//*********************************************************************

const std::string CLMetabReferenceGlyph::RoleName[] =
{
  "undefined role",
  "substrate",
  "product",
  "side substrate",
  "side product",
  "modifier",
  "activator",
  "inhibitor"
  ""
};

const std::string CLMetabReferenceGlyph::XMLRole[] =
{
  "undefinedRole",
  "substrate",
  "product",
  "sideSubstrate",
  "sideProduct",
  "modifier",
  "activator",
  "inhibitor",
  ""
};

// static
CLMetabReferenceGlyph * CLMetabReferenceGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLMetabReferenceGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                                   NO_PARENT);
}

// virtual
CData CLMetabReferenceGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLMetabReferenceGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const std::string & name,
    const CDataContainer * pParent)
  : CLGlyphWithCurve(name, pParent),
    mMetabGlyphKey(),
    mRole(UNDEFINED),
    mFunctionalRole(UNDEFINED)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
    const CDataContainer * pParent)
  : CLGlyphWithCurve(src, pParent),
    mMetabGlyphKey(src.mMetabGlyphKey),
    mRole(src.mRole),
    mFunctionalRole(src.mFunctionalRole)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
    const std::map<std::string, std::string> & modelmap,
    std::map<std::string, std::string> & layoutmap,
    const CDataContainer * pParent)
  : CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent),
    mMetabGlyphKey(), //initialized in the body below
    mRole((Role)sbml.getRole()),
    mFunctionalRole(UNDEFINED) //initialized in the body below TODO!!!
{
  //get the copasi key corresponding to the sbml id for the species reference
  if (sbml.getSpeciesReferenceId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getSpeciesReferenceId());

      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //get the copasi key corresponding to the sbml id for the species glyph
  if (sbml.getSpeciesGlyphId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getSpeciesGlyphId());

      if (it != layoutmap.end())
        mMetabGlyphKey = it->second;
    }

  //curve
  if (sbml.getCurve())
    {
      CLCurve copy(*sbml.getCurve());
      mCurve = copy;
    }
}

CLMetabReferenceGlyph & CLMetabReferenceGlyph::operator= (const CLMetabReferenceGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGlyphWithCurve::operator=(rhs);

  //handle the specific glyph stuff:
  mMetabGlyphKey = rhs.mMetabGlyphKey;
  mRole = rhs.mRole;

  return *this;
}

const std::string &
CLMetabReferenceGlyph::getMetabGlyphKey() const
{
  return mMetabGlyphKey;
}

CLMetabGlyph* CLMetabReferenceGlyph::getMetabGlyph() const
{
  CDataObject* tmp = CRootContainer::getKeyFactory()->get(mMetabGlyphKey);
  return dynamic_cast<CLMetabGlyph*>(tmp);
}

void
CLMetabReferenceGlyph::setMetabGlyphKey(const std::string &k)
{
  mMetabGlyphKey = k;
}

CLMetabReferenceGlyph::Role
CLMetabReferenceGlyph::getRole() const
{
  return mRole;
}

void
CLMetabReferenceGlyph::setRole(CLMetabReferenceGlyph::Role r)
{
  mRole = r;
}

CLMetabReferenceGlyph::Role
CLMetabReferenceGlyph::getFunctionalRole() const
{
  if (mFunctionalRole == CLMetabReferenceGlyph::UNDEFINED)
    return getRole();

  return mFunctionalRole;
}

void
CLMetabReferenceGlyph::setFunctionalRole(CLMetabReferenceGlyph::Role r)
{
  mFunctionalRole = r;
}

const std::string &
CLMetabReferenceGlyph::getRoleDisplayName() const
{
  return RoleName[mRole];
}

CLGraphicalObject *
CLMetabReferenceGlyph::clone() const
{
  return new CLMetabReferenceGlyph(*this, NULL);
}

void CLMetabReferenceGlyph::exportToSBML(SpeciesReferenceGlyph * g,
    const std::map<const CDataObject*, SBase*> & copasimodelmap,
    std::map<std::string, const SBase*>& sbmlIDs,
    const std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //call the coresponding method of the base class
  CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

  //reference to species glyph
  CLMetabGlyph* tmp = getMetabGlyph();

  if (tmp)
    {
      std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);

      if (it != layoutmap.end())
        {
          if (it->second)
            {
              //we need to cast here since layout objects in libsbml don´t inherit the getId() method
              //from SBase
              const GraphicalObject* pGO = dynamic_cast<const GraphicalObject*>(it->second);

              if (pGO)
                g->setSpeciesGlyphId(pGO->getId());
            }
        }
    }

  //curve
  mCurve.exportToSBML(g->getCurve(), copasimodelmap);

  //Role
  g->setRole((SpeciesReferenceRole_t)mRole);
  //this depends on the copasi role enum being synchronous to the sbml one
}

std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g)
{
  os << "    MetabReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  os << "      Role: " << CLMetabReferenceGlyph::RoleName[g.getRole()] << "\n";

  const CLMetabGlyph* tmp = g.getMetabGlyph();

  if (tmp)
    os << "      refers to a MetabGlyph that refers to "
       << tmp->getModelObjectDisplayName() << std::endl;

  os << g.mCurve;

  return os;
}

void CLMetabReferenceGlyph::print(std::ostream * ostream) const
{*ostream << *this;}

//*********** CLGeneralGlyph ****************************************

// static
CLGeneralGlyph * CLGeneralGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLGeneralGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                            NO_PARENT);
}

// virtual
CData CLGeneralGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLGeneralGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLGeneralGlyph::CLGeneralGlyph(const std::string & name,
                               const CDataContainer * pParent)
  : CLGlyphWithCurve(name, pParent)
  , mvReferences("ListOfReferenceGlyphs", this)
  , mvSubglyphs("ListOfSubglyphs", this)
{}

CLGeneralGlyph::CLGeneralGlyph(const CLGeneralGlyph & src,
                               const CDataContainer * pParent)
  : CLGlyphWithCurve(src, pParent)
  , mvReferences(src.mvReferences, this)
  , mvSubglyphs("ListOfSubglyphs", this)
{
  size_t i, imax = src.mvSubglyphs.size();

  for (i = 0; i < imax; ++i)
    addSubglyph(src.mvSubglyphs[i].clone());
}

//TODO this is a placeholder for the upcoming sbml generalGlyph handling
CLGeneralGlyph::CLGeneralGlyph(const GraphicalObject & sbml,
                               const std::map<std::string, std::string> & modelmap,
                               std::map<std::string, std::string> & layoutmap,
                               const CDataContainer * pParent)
  : CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent)
  , mvReferences("ListOfReferenceGlyphs", this)
  , mvSubglyphs("ListOfSubglyphs", this)
{
  const GeneralGlyph* general = dynamic_cast<const GeneralGlyph *>(&sbml);

  if (!general)
    return;

  //get the copasi key corresponding to the sbml id for the reaction
  if (general->isSetReferenceId())
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(general->getReferenceId());

      if (it != modelmap.end())
        setModelObjectKey(it->second);

      it = layoutmap.find(general->getReferenceId());

      if (it != layoutmap.end())
        setModelObjectKey(it->second);
    }

  //species reference glyphs
  C_INT32 i, imax = general->getListOfReferenceGlyphs()->size();

  for (i = 0; i < imax; ++i)
    {
      const ReferenceGlyph* tmp
        = dynamic_cast<const ReferenceGlyph*>(general->getListOfReferenceGlyphs()->get(i));

      if (tmp)
        addReferenceGlyph(new CLReferenceGlyph(*tmp, modelmap, layoutmap));
    }

  imax = general->getListOfSubGlyphs()->size();

  for (i = 0; i < imax; ++i)
    {
      const GraphicalObject* graphical = general->getListOfSubGlyphs()->get(i);
      const TextGlyph* text = dynamic_cast<const TextGlyph*>(graphical);
      const SpeciesGlyph* species = dynamic_cast<const SpeciesGlyph*>(graphical);
      const CompartmentGlyph* comp = dynamic_cast<const CompartmentGlyph*>(graphical);

      if (text)
        addSubglyph(new CLTextGlyph(*text, modelmap, layoutmap));
      else if (species)
        addSubglyph(new CLMetabGlyph(*species, modelmap, layoutmap));
      else if (comp)
        addSubglyph(new CLCompartmentGlyph(*comp, modelmap, layoutmap));
      else
        addSubglyph(new CLGeneralGlyph(*graphical, modelmap, layoutmap));
    }
}

CLGeneralGlyph & CLGeneralGlyph::operator= (const CLGeneralGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGlyphWithCurve::operator=(rhs);

  //handle the specific glyph stuff:

  size_t i, imax = rhs.mvReferences.size();

  mvReferences.clear();

  for (i = 0; i < imax; ++i)
    addReferenceGlyph(new CLReferenceGlyph(rhs.mvReferences[i], NO_PARENT));

  imax = rhs.mvSubglyphs.size();
  mvSubglyphs.clear();

  for (i = 0; i < imax; ++i)
    addSubglyph(rhs.mvSubglyphs[i].clone());

  return *this;
}

const CDataVector<CLReferenceGlyph> &
CLGeneralGlyph::getListOfReferenceGlyphs() const
{
  return mvReferences;
}

CDataVector<CLReferenceGlyph> &
CLGeneralGlyph::getListOfReferenceGlyphs()
{
  return mvReferences;
}

const CDataVector<CLGraphicalObject> &
CLGeneralGlyph::getListOfSubglyphs() const
{
  return mvSubglyphs;
}

CDataVector<CLGraphicalObject> &
CLGeneralGlyph::getListOfSubglyphs()
{
  return mvSubglyphs;
}

void CLGeneralGlyph::addSubglyph(CLGraphicalObject * glyph)
{
  if (glyph)
    mvSubglyphs.add(glyph, true); //true means vector takes ownership
}

void CLGeneralGlyph::addReferenceGlyph(CLReferenceGlyph * glyph)
{
  if (glyph)
    mvReferences.add(glyph, true); //true means vector takes ownership
}

void CLGeneralGlyph::moveBy(const CLPoint &p)
{
  CLGlyphWithCurve::moveBy(p);

  size_t i, imax = mvReferences.size();

  for (i = 0; i < imax; ++i)
    mvReferences[i].moveBy(p);

  imax = mvSubglyphs.size();

  for (i = 0; i < imax; ++i)
    mvSubglyphs[i].moveBy(p);
}

CLGraphicalObject *
CLGeneralGlyph::clone() const
{
  return new CLGeneralGlyph(*this, NULL);
}

void CLGeneralGlyph::exportToSBML(GraphicalObject * g, //TODO
                                  const std::map<const CDataObject*, SBase*> & copasimodelmap,
                                  std::map<std::string, const SBase*>& sbmlIDs,
                                  std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //call the corresponding method of the base class
  CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

  GeneralGlyph *general = dynamic_cast<GeneralGlyph *>(g);

  if (!general) return;

  //reference to model objects
  CDataObject* tmp = getModelObject();

  if (tmp)
    {
      std::map<const CDataObject*, SBase*>::const_iterator it = copasimodelmap.find(tmp);

      if (it != copasimodelmap.end())
        {
          if (it->second)
            general->setReferenceId(it->second->getId());
        }

      const CLBase* base = dynamic_cast<const CLBase*>(tmp);

      if (base)
        {
          std::map<const CLBase*, const SBase*>::const_iterator it2 = layoutmap.find(base);

          if (it2 != layoutmap.end())
            {
              if (it2->second)
                general->setReferenceId(it2->second->getId());
            }
        }
    }

  //curve
  mCurve.exportToSBML(general->getCurve(), copasimodelmap);

  //reference  glyphs
  size_t i, imax = mvReferences.size();

  for (i = 0; i < imax; ++i)
    {
      const CLReferenceGlyph * tmp = &mvReferences[i];

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      ReferenceGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = general->createReferenceGlyph();
        }
      else
        {
          pG = dynamic_cast<ReferenceGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
    }

  imax = mvSubglyphs.size();

  for (i = 0; i < imax; ++i)
    {
      CLGraphicalObject * tmp = const_cast< CLGraphicalObject * >(&mvSubglyphs[i]);
      CLMetabGlyph * metab =  dynamic_cast<CLMetabGlyph*>(tmp);
      CLCompartmentGlyph* comp =  dynamic_cast<CLCompartmentGlyph*>(tmp);
      CLGeneralGlyph* gg =  dynamic_cast<CLGeneralGlyph*>(tmp);
      CLTextGlyph* text =  dynamic_cast<CLTextGlyph*>(tmp);

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      GraphicalObject * pG;

      if (it == copasimodelmap.end()) //not found
        {
          if (metab)
            pG = ((Layout*)g->getParentSBMLObject()->getParentSBMLObject())->createSpeciesGlyph();
          else if (comp)
            pG = ((Layout*)g->getParentSBMLObject()->getParentSBMLObject())->createCompartmentGlyph();
          else if (gg)
            pG = ((Layout*)g->getParentSBMLObject()->getParentSBMLObject())->createGeneralGlyph();
          else if (text)
            pG = ((Layout*)g->getParentSBMLObject()->getParentSBMLObject())->createTextGlyph();
          else
            pG = ((Layout*)g->getParentSBMLObject()->getParentSBMLObject())->createAdditionalGraphicalObject();
        }
      else
        {
          pG = dynamic_cast<GraphicalObject*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));

      if (metab)
        metab->exportToSBML(static_cast<SpeciesGlyph*>(pG), copasimodelmap, sbmlIDs);
      else if (comp)
        comp->exportToSBML(static_cast<CompartmentGlyph*>(pG), copasimodelmap, sbmlIDs);
      else if (text)
        text->exportToSBML(static_cast<TextGlyph*>(pG), copasimodelmap, sbmlIDs);
      else if (gg)
        gg->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
      else
        tmp->exportToSBML(pG, copasimodelmap, sbmlIDs);
    }
}

std::ostream & operator<<(std::ostream &os, const CLGeneralGlyph & g)
{
  os << "GeneralGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  os << g.mCurve;

  size_t i, imax = g.mvReferences.size();

  if (imax)
    {
      os << "  List of reference glyphs: \n";

      for (i = 0; i < imax; ++i)
        os << g.mvReferences[i];
    }

  imax = g.mvSubglyphs.size();

  if (imax)
    {
      os << "  List of reference glyphs: \n";

      for (i = 0; i < imax; ++i)
        os << g.mvSubglyphs[i];
    }

  return os;
}

void CLGeneralGlyph::print(std::ostream * ostream) const
{*ostream << *this;}

//*********** CLReactionGlyph ****************************************

// static
CLReactionGlyph * CLReactionGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLReactionGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                             NO_PARENT);
}

// virtual
CData CLReactionGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLReactionGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLReactionGlyph::CLReactionGlyph(const std::string & name,
                                 const CDataContainer * pParent)
  : CLGlyphWithCurve(name, pParent),
    mvMetabReferences("ListOfMetabReferenceGlyphs", this)
{}

CLReactionGlyph::CLReactionGlyph(const CLReactionGlyph & src,
                                 const CDataContainer * pParent)
  : CLGlyphWithCurve(src, pParent),
    mvMetabReferences(src.mvMetabReferences, this)
{
  //TODO
}

CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & sbml,
                                 const std::map<std::string, std::string> & modelmap,
                                 std::map<std::string, std::string> & layoutmap,
                                 const CDataContainer * pParent)
  : CLGlyphWithCurve(sbml, modelmap, layoutmap, pParent),
    mvMetabReferences("ListOfMetabReferenceGlyphs", this)
{
  //get the copasi key corresponding to the sbml id for the reaction
  if (sbml.getReactionId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getReactionId());

      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //species reference glyphs
  C_INT32 i, imax = sbml.getListOfSpeciesReferenceGlyphs()->size();

  for (i = 0; i < imax; ++i)
    {
      const SpeciesReferenceGlyph* tmp
        = dynamic_cast<const SpeciesReferenceGlyph*>(sbml.getListOfSpeciesReferenceGlyphs()->get(i));

      if (tmp)
        addMetabReferenceGlyph(new CLMetabReferenceGlyph(*tmp, modelmap, layoutmap));
    }

  //curve
  if (sbml.getCurve())
    {
      CLCurve copy(*sbml.getCurve());
      mCurve = copy;
    }
}

CLReactionGlyph & CLReactionGlyph::operator= (const CLReactionGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGlyphWithCurve::operator=(rhs);

  //handle the specific glyph stuff:
  size_t i, imax = rhs.mvMetabReferences.size();

  for (i = 0; i < imax; ++i)
    addMetabReferenceGlyph(new CLMetabReferenceGlyph(rhs.mvMetabReferences[i], NO_PARENT));

  return *this;
}

const CDataVector<CLMetabReferenceGlyph> &
CLReactionGlyph::getListOfMetabReferenceGlyphs() const
{
  return mvMetabReferences;
}

CDataVector<CLMetabReferenceGlyph> &
CLReactionGlyph::getListOfMetabReferenceGlyphs()
{
  return mvMetabReferences;
}

/*const std::vector<CLMetabReferenceGlyph*> CLReactionGlyph::getListOfMetabReferenceGlyphs() const
{
    std::vector<CLMetabReferenceGlyph*> ret;
    size_t i, imax = mvReferences.size();

    for (i = 0; i < imax; ++i)
      {
        CLMetabReferenceGlyph * tmp = dynamic_cast<CLMetabReferenceGlyph*>(mvReferences[i]);
        if(tmp)
            ret.push_back(tmp);
      }
    return ret;
}*/

void CLReactionGlyph::addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph)
{
  if (glyph)
    mvMetabReferences.add(glyph, true); //true means vector takes ownership
}

void CLReactionGlyph::moveBy(const CLPoint &p)
{
  CLGlyphWithCurve::moveBy(p);

  size_t i, imax = mvMetabReferences.size();

  for (i = 0; i < imax; ++i)
    mvMetabReferences[i].moveBy(p);
}

CLGraphicalObject *
CLReactionGlyph::clone() const
{
  return new CLReactionGlyph(*this, NULL);
}

void CLReactionGlyph::exportToSBML(ReactionGlyph * g,
                                   const std::map<const CDataObject*, SBase*> & copasimodelmap,
                                   std::map<std::string, const SBase*>& sbmlIDs,
                                   std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //call the coresponding method of the base class
  CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

  //reference to model objects
  CDataObject* tmp = getModelObject();

  if (tmp)
    {
      std::map<const CDataObject*, SBase*>::const_iterator it = copasimodelmap.find(tmp);

      if (it != copasimodelmap.end())
        {
          if (it->second)
            g->setReactionId(it->second->getId());
        }
    }

  //curve
  mCurve.exportToSBML(g->getCurve(), copasimodelmap);

  //Metab reference  glyphs
  size_t i, imax = mvMetabReferences.size();

  for (i = 0; i < imax; ++i)
    {
      const CLMetabReferenceGlyph * tmp = &mvMetabReferences[i];

      //check if the glyph exists in the libsbml data
      std::map<const CDataObject*, SBase*>::const_iterator it;
      it = copasimodelmap.find(tmp);

      SpeciesReferenceGlyph * pG;

      if (it == copasimodelmap.end()) //not found
        {
          pG = new SpeciesReferenceGlyph;
          g->getListOfSpeciesReferenceGlyphs()->appendAndOwn(pG);
        }
      else
        {
          pG = dynamic_cast<SpeciesReferenceGlyph*>(it->second);
        }

      layoutmap.insert(std::pair<const CLBase*, const SBase*>(tmp, pG));
      tmp->exportToSBML(pG, copasimodelmap, sbmlIDs, layoutmap);
    }
}

std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g)
{
  os << "ReactionGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  os << g.mCurve;

  size_t i, imax = g.mvMetabReferences.size();

  if (imax)
    {
      os << "  List of metab reference glyphs: \n";

      for (i = 0; i < imax; ++i)
        os << g.mvMetabReferences[i];
    }

  return os;
}

void CLReactionGlyph::print(std::ostream * ostream) const
{*ostream << *this;}
