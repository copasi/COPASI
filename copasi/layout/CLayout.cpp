// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayout.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/15 08:44:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CLayout.h"
#include "sbml/layout/Layout.h"

CLayout::CLayout(const std::string & name,
                 const CCopasiContainer * pParent)
    : CLBase(),
    CCopasiContainer(name, pParent, "Layout"),
    mDimensions(),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
{}

CLayout::CLayout(const CLayout & src,
                 const CCopasiContainer * pParent)
    : CLBase(src),
    CCopasiContainer(src, pParent),
    mDimensions(src.mDimensions),
    mvCompartments(src.mvCompartments, this),
    mvMetabs(src.mvMetabs, this),
    mvReactions(src.mvReactions, this),
    mvLabels(src.mvLabels, this),
    mvGraphicalObjects(src.mvGraphicalObjects, this)
{
  //TODO references from one glyph to another have to be reconstructed after
  //     copying. This applies to Labels and metab reference glyphs
}

CLayout::CLayout(const Layout & sbml,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent)
    : CLBase(sbml),
    CCopasiContainer(sbml.getId(), pParent, "Layout"),
    mDimensions(sbml.getDimensions()),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
{
  //TODO add to map
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
  C_INT32 i, imax;

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
      os << "\nList of metabolite glyphs: \n\n";
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

void CLayout::print(std::ostream * ostream) const
{*ostream << *this;}
