// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayout.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/29 13:17:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include "iostream"
#include "sbml/layout/Layout.h"

#include "copasi.h"
#include "report/CKeyFactory.h"

#include "CLayout.h"

CLayout::CLayout(const std::string & name,
                 const CCopasiContainer * pParent)
    : CLBase(),
    CCopasiContainer(name, pParent, "Layout"),
    mKey(GlobalKeys.add("Layout", this)),
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
    mKey(GlobalKeys.add("Layout", this)),
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
    mKey(GlobalKeys.add("Layout", this)),
    mDimensions(*sbml.getDimensions()),
    mvCompartments("ListOfCompartmentGlyphs", this),
    mvMetabs("ListOfMetaboliteGlyphs", this),
    mvReactions("ListOfReactionGlyphs", this),
    mvLabels("ListOfTextGlyphs", this),
    mvGraphicalObjects("ListOfGraphicalObjects", this)
{
  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
}

CLayout::~CLayout()
{
  GlobalKeys.remove(mKey);
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

void CLayout::print(std::ostream * os) const
{*os << *this;}

void CLayout::exportToDotFile(std::ostream & os) const
  {
    os << "digraph G {\n";

    //metab glyphs
    unsigned C_INT32 i, imax = mvMetabs.size();
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

        unsigned C_INT j, jmax = mvReactions[i]->getListOfMetabReferenceGlyphs().size();
        for (j = 0; j < jmax; ++j)
          {
            CLMetabReferenceGlyph* mrg = mvReactions[i]->getListOfMetabReferenceGlyphs()[j];

            if (mrg->getRole() == CLMetabReferenceGlyph::SUBSTRATE)
              writeDotEdge(os, mrg->getMetabGlyphKey(), mvReactions[i]->getKey() + "_S");
            else if (mrg->getRole() == CLMetabReferenceGlyph::PRODUCT)
              writeDotEdge(os, mvReactions[i]->getKey() + "_P", mrg->getMetabGlyphKey());
            else
              std::cout << "!!!!" << std::endl;
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

void CLayout::exportToSBML(Layout * layout, const std::map<CCopasiObject*, SBase*> & copasimodelmap) const
  {
    if (!layout) return;

    //Dimensions
    //layout->setDimensions(mDimensions.getSBMLDimensions());

    //Compartment glyphs
    unsigned C_INT32 i, imax = mvCompartments.size();
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
            layout->getListOfCompartmentGlyphs().append(pCG);
          }
        else
          {
            pCG = dynamic_cast<CompartmentGlyph*>(it->second);
          }

        //tmp->exportToSBML(pCG, copasimodelmap);
      }
  }
