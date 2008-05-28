// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGlyphs.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/05/28 11:48:59 $
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

#include <sbml/layout/SpeciesGlyph.h>
#include <sbml/layout/CompartmentGlyph.h>
#include <sbml/layout/TextGlyph.h>

#include "CLGlyphs.h"

#include "report/CKeyFactory.h"

CLMetabGlyph::CLMetabGlyph(const std::string & name,
                           const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent)
{}

CLMetabGlyph::CLMetabGlyph(const CLMetabGlyph & src,
                           const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent)
{}

CLMetabGlyph::CLMetabGlyph(const SpeciesGlyph & sbml,
                           const std::map<std::string, std::string> & modelmap,
                           std::map<std::string, std::string> & layoutmap,
                           const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent)
{
  //get the copasi key corresponding to the sbml id for the species
  if (sbml.getSpeciesId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getSpeciesId());
      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }
}

CLMetabGlyph & CLMetabGlyph::operator= (const CLMetabGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGraphicalObject::operator=(rhs);

  //nothing to be done here

  return *this;
}

std::ostream & operator<<(std::ostream &os, const CLMetabGlyph & g)
{
  os << "MetabGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  return os;
}

void CLMetabGlyph::print(std::ostream * ostream) const
  {*ostream << *this;}

//********* CLCompartmentGlyph ************************************************

CLCompartmentGlyph::CLCompartmentGlyph(const std::string & name,
                                       const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent)
{}

CLCompartmentGlyph::CLCompartmentGlyph(const CLCompartmentGlyph & src,
                                       const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent)
{}

CLCompartmentGlyph::CLCompartmentGlyph(const CompartmentGlyph & sbml,
                                       const std::map<std::string, std::string> & modelmap,
                                       std::map<std::string, std::string> & layoutmap,
                                       const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent)
{
  //get the copasi key corresponding to the sbml id for the compartment
  if (sbml.getCompartmentId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getCompartmentId());
      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }
}

CLCompartmentGlyph & CLCompartmentGlyph::operator= (const CLCompartmentGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGraphicalObject::operator=(rhs);

  //nothing to be done here

  return *this;
}

std::ostream & operator<<(std::ostream &os, const CLCompartmentGlyph & g)
{
  os << "CompartmentGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  return os;
}

void CLCompartmentGlyph::print(std::ostream * ostream) const
  {*ostream << *this;}

//********** CLTextGlyph ******************************************************

CLTextGlyph::CLTextGlyph(const std::string & name,
                         const CCopasiContainer * pParent)
    : CLGraphicalObject(name, pParent),
    mIsTextSet(false),
    mText(""),
    mGraphicalObjectKey("")
{}

CLTextGlyph::CLTextGlyph(const CLTextGlyph & src,
                         const CCopasiContainer * pParent)
    : CLGraphicalObject(src, pParent),
    mIsTextSet(src.mIsTextSet),
    mText(src.mText),
    mGraphicalObjectKey(src.mGraphicalObjectKey)
{}

CLTextGlyph::CLTextGlyph(const TextGlyph & sbml,
                         const std::map<std::string, std::string> & modelmap,
                         std::map<std::string, std::string> & layoutmap,
                         const CCopasiContainer * pParent)
    : CLGraphicalObject(sbml, layoutmap, pParent),
    mIsTextSet(sbml.isSetText()),
    mText(sbml.getText()),
    mGraphicalObjectKey("")
{
  //get the copasi key corresponding to the sbml id for the graphical object
  /*  if (sbml.getGraphicalObjectId() != "")
      {
        std::map<std::string, std::string>::const_iterator it = m.find(sbml.getGraphicalObjectId());
        if (it != m.end())
          mGraphicalObjectKey = it->second;
      }*/

  //get the copasi key corresponding to the sbml id for the model element (OriginOfText)
  if (sbml.getOriginOfTextId() != "")
    {
      std::map<std::string, std::string>::const_iterator it = modelmap.find(sbml.getOriginOfTextId());
      if (it != modelmap.end())
        setModelObjectKey(it->second);
    }
}

CLTextGlyph & CLTextGlyph::operator= (const CLTextGlyph & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLGraphicalObject::operator=(rhs);

  //handle the specific text glyph stuff:
  mIsTextSet = rhs.mIsTextSet;
  mText = rhs.mText;

  mGraphicalObjectKey = rhs.mGraphicalObjectKey;

  return *this;
}

std::string CLTextGlyph::getText() const
  {
    if (mIsTextSet)
      return mText;
    else
      return getModelObjectDisplayName();
  }

void CLTextGlyph::setText(const std::string & t)
{
  mIsTextSet = true;
  mText = t;
}

void CLTextGlyph::clearText()
{
  mIsTextSet = false;
  mText = "";
}

CLGraphicalObject* CLTextGlyph::getGraphicalObject() const
  {
    return dynamic_cast<CLGraphicalObject*>(GlobalKeys.get(mGraphicalObjectKey));
  }

std::ostream & operator<<(std::ostream &os, const CLTextGlyph & g)
{
  os << "TextGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  if (g.mIsTextSet)
    os << "  Explicit text is: \"" << g.mText << "\"\n";

  CLGraphicalObject* tmp = g.getGraphicalObject();
  if (tmp)
    os << "  Label for: \"" << tmp->getObjectName() << "\"\n";
  return os;
}

void CLTextGlyph::print(std::ostream * ostream) const
{*ostream << *this;}
