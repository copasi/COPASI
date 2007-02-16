// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLReactionGlyph.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 00:09:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include<iostream>
#include "report/CKeyFactory.h"
#include "CLReactionGlyph.h"

#include "sbml/layout/ReactionGlyph.h"
#include "sbml/layout/SpeciesReferenceGlyph.h"

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const std::string & name,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mMetabGlyphKey(),
    mCurve()
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mMetabGlyphKey(src.mMetabGlyphKey),
    mCurve(src.mCurve)
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const SpeciesReferenceGlyph & sbml,
    const std::map<std::string, std::string> & /*modelmap*/,
    std::map<std::string, std::string> & layoutmap,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent),
    mMetabGlyphKey(), //initialized in the body below
    mCurve(sbml.getCurve())
{
  //TODO problem: how to translate the sbml species reference id to a copasi key

  //get the copasi key corresponding to the sbml id for the species glyph
  if (sbml.getSpeciesGlyphId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = layoutmap.find(sbml.getSpeciesGlyphId());
      if (it != layoutmap.end())
        mMetabGlyphKey = it->second;
    }
}

CLMetabGlyph* CLMetabReferenceGlyph::getMetabGlyph() const
  {
    CCopasiObject* tmp = GlobalKeys.get(mMetabGlyphKey);
    return dynamic_cast<CLMetabGlyph*>(tmp);
  }

std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g)
{
  os << "    MetabReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  const CLMetabGlyph* tmp = g.getMetabGlyph();
  if (tmp)
    os << "      refers to a MetabGlyph that refers to "
    << tmp->getModelObjectDisplayName() << std::endl;

  return os;
}

//*********** CLReactionGlyph ****************************************

CLReactionGlyph::CLReactionGlyph(const std::string & name,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent)
{}

CLReactionGlyph::CLReactionGlyph(const CLReactionGlyph & src,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent)
{}

CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & sbml,
                                 const std::map<std::string, std::string> & modelmap,
                                 std::map<std::string, std::string> & layoutmap,
                                 const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent)
{
  //get the copasi key corresponding to the sbml id for the reaction
  if (sbml.getReactionId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getReactionId());
      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }

  //species reference glyphs
  C_INT32 i, imax = sbml.getListOfSpeciesReferenceGlyphs().getNumItems();
  for (i = 0; i < imax; ++i)
    {
      const SpeciesReferenceGlyph* tmp
      = dynamic_cast<const SpeciesReferenceGlyph*>(sbml.getListOfSpeciesReferenceGlyphs().get(i));
      if (tmp)
        addMetabReferenceGlyph(new CLMetabReferenceGlyph(*tmp, modelmap, layoutmap));
    }
}

void CLReactionGlyph::addMetabReferenceGlyph(CLMetabReferenceGlyph * glyph)
{
  if (glyph)
    mvMetabReferences.add(glyph, true); //true means vector takes ownership
}

std::ostream & operator<<(std::ostream &os, const CLReactionGlyph & g)
{
  os << "ReactionGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  C_INT32 i, imax = g.mvMetabReferences.size();
  if (imax)
    {
      os << "  List of metab reference glyphs: \n";
      for (i = 0; i < imax; ++i)
        os << *g.mvMetabReferences[i];
    }

  return os;
}
