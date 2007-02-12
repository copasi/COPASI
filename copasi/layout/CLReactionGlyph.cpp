// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLReactionGlyph.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/12 00:03:12 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include<iostream>
#include "report/CKeyFactory.h"
#include<CLReactionGlyph.h>

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const std::string & name,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mMetabGlyphKey()
{}

CLMetabReferenceGlyph::CLMetabReferenceGlyph(const CLMetabReferenceGlyph & src,
    const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mMetabGlyphKey(src.mMetabGlyphKey)
{}

CLMetabGlyph* CLMetabReferenceGlyph::metabGlyph() const
  {
    CCopasiObject* tmp = GlobalKeys.get(mMetabGlyphKey);
    return dynamic_cast<CLMetabGlyph*>(tmp);
  }

std::ostream & operator<<(std::ostream &os, const CLMetabReferenceGlyph & g)
{
  os << "    MetabReferenceGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);

  const CLMetabGlyph* tmp = g.metabGlyph();
  if (tmp)
    os << "      refers to a MetabGlyph that refers to "
    << tmp->modelObjectDisplayName() << std::endl;

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
