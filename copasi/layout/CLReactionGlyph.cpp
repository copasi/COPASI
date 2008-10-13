// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLReactionGlyph.cpp,v $
//   $Revision: 1.18.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/13 09:48:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include<iostream>

#define USE_LAYOUT 1

#include <sbml/layout/ReactionGlyph.h>
#include <sbml/layout/SpeciesReferenceGlyph.h>

#include "copasi.h"

#include "CLReactionGlyph.h"
#include "report/CKeyFactory.h"

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

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const std::string & name,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mMetabGlyphKey(),
    mCurve(),
    mRole(UNDEFINED)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mMetabGlyphKey(src.mMetabGlyphKey),
    mCurve(src.mCurve),
    mRole(src.mRole)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
    const std::map<std::string, std::string> & /*modelmap*/,
    std::map<std::string, std::string> & layoutmap,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent),
    mMetabGlyphKey(), //initialized in the body below
    mCurve(), //initialized in the body below
    mRole((Role)sbml.getRole())
{
  //TODO problem: how to translate the sbml species reference id to a copasi key

  //get the copasi key corresponding to the sbml id for the species glyph
  if (sbml.getSpeciesGlyphId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getSpeciesGlyphId());
      if (it != layoutmap.end())
        mMetabGlyphKey = it->second;
    }

  //curve
  if (sbml.getCurve())
    mCurve = CLCurve(*sbml.getCurve());
}

CLMetabReferenceGlyph & CLMetabReferenceGlyph::operator= (const CLMetabReferenceGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGraphicalObject::operator=(rhs);

  //handle the specific glyph stuff:
  mMetabGlyphKey = rhs.mMetabGlyphKey;
  mCurve = rhs.mCurve;
  mRole = rhs.mRole;

  return *this;
}

CLMetabGlyph* CLMetabReferenceGlyph::getMetabGlyph() const
  {
    CCopasiObject* tmp = GlobalKeys.get(mMetabGlyphKey);
    return dynamic_cast<CLMetabGlyph*>(tmp);
  }

void CLMetabReferenceGlyph::exportToSBML(SpeciesReferenceGlyph * g,
    const std::map<CCopasiObject*, SBase*> & copasimodelmap,
    std::map<std::string, const SBase*>& sbmlIDs) const
  {
    if (!g) return;

    //call the coresponding method of the base class
    CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

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

//*********** CLReactionGlyph ****************************************

CLReactionGlyph::CLReactionGlyph(const std::string & name,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mCurve(),
    mvMetabReferences("ListOfMetabReferenceGlyphs", this)
{}

CLReactionGlyph::CLReactionGlyph(const CLReactionGlyph & src,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mCurve(src.mCurve),
    mvMetabReferences(src.mvMetabReferences, this)
{
  //TODO
}

CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & sbml,
                                 const std::map<std::string, std::string> & modelmap,
                                 std::map<std::string, std::string> & layoutmap,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent),
    mCurve(),
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
    mCurve = CLCurve(*sbml.getCurve());
}

CLReactionGlyph & CLReactionGlyph::operator= (const CLReactionGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGraphicalObject::operator=(rhs);

  //handle the specific glyph stuff:
  mCurve = rhs.mCurve;

  unsigned C_INT32 i, imax = rhs.mvMetabReferences.size();
  for (i = 0; i < imax; ++i)
    addMetabReferenceGlyph(new CLMetabReferenceGlyph(*rhs.mvMetabReferences[i]));

  return *this;
}

void CLReactionGlyph::addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph)
{
  if (glyph)
    mvMetabReferences.add(glyph, true); //true means vector takes ownership
}

void CLReactionGlyph::exportToSBML(ReactionGlyph * g,
                                   const std::map<CCopasiObject*, SBase*> & copasimodelmap,
                                   std::map<std::string, const SBase*>& sbmlIDs) const
  {
    if (!g) return;

    //call the coresponding method of the base class
    CLGraphicalObject::exportToSBML(g, copasimodelmap, sbmlIDs);

    //reference to model objects
    CCopasiObject* tmp = getModelObject();
    if (tmp)
      {
        std::map<CCopasiObject*, SBase*>::const_iterator it = copasimodelmap.find(tmp);
        if (it != copasimodelmap.end())
          {
            if (it->second)
              g->setReactionId(it->second->getId());
          }
      }

    //curve
    mCurve.exportToSBML(g->getCurve(), copasimodelmap);

    //Metab reference  glyphs
    unsigned C_INT32 i, imax = mvMetabReferences.size();
    for (i = 0; i < imax; ++i)
      {
        CLMetabReferenceGlyph * tmp = mvMetabReferences[i];

        //check if the glyph exists in the libsbml data
        std::map<CCopasiObject*, SBase*>::const_iterator it;
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

        tmp->exportToSBML(pG, copasimodelmap, sbmlIDs);
      }
  }

std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g)
{
  os << "ReactionGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  os << g.mCurve;

  C_INT32 i, imax = g.mvMetabReferences.size();
  if (imax)
    {
      os << "  List of metab reference glyphs: \n";
      for (i = 0; i < imax; ++i)
        os << *g.mvMetabReferences[i];
    }

  return os;
}

void CLReactionGlyph::print(std::ostream * ostream) const
{*ostream << *this;}
