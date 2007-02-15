// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGlyphs.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/15 08:44:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include<iostream>
#include<CLGlyphs.h>

#include "sbml/layout/SpeciesGlyph.h"
#include "sbml/layout/CompartmentGlyph.h"
#include "sbml/layout/TextGlyph.h"

// void node::markAsCopy(){
//  this->id = this->id + "_copy";
//}

// bool node::hasID(string s){
//  string idstring = id.substr(3); // get rid of trailing "nd_"
//
//  //cout << idstring << "  :  " << s << endl;
//  //cout << "result compare: " << idstring.compare(s) << endl;
//  //cout << "result find: " << s.find(idstring) << endl;
//  if (((idstring.compare(s)) == 0) ||
//   ((s.find(idstring)) != string::npos)) // find id (only number, do not compare with "nd_xxx"
//   return true;
//  else
//   return false;
//}

//bool node::hasID(){
// string s = "abc";
// string idstring = id;
// if (((idstring.compare(s)) == 0) ||
//  ((idstring.find(s)) == string::npos))
//  return true;
// else
//  return false;
//}

// void node::printObject(){
//  cout << "x: "
//       << this->getX()
//       << "  y: "
//       << this->getY()
//       << "  id:  "
//       << this->getID()
//       << endl;
//}

//   int testNode ()
//   {
//    node n1,n2;
//
//    node *n3 = new node(100.0,100.0);
//
//     n1.printObject();
//     n2.printObject();
//     n3->printObject();
//
//     return 0;
//}

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

std::ostream & operator<<(std::ostream &os, const CLMetabGlyph & g)
{
  os << "MetabGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  return os;
}

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

std::ostream & operator<<(std::ostream &os, const CLCompartmentGlyph & g)
{
  os << "CompartmentGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  return os;
}

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

std::string CLTextGlyph::text() const
  {
    if (mIsTextSet)
      return mText;
    else
      return modelObjectDisplayName();
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

std::ostream & operator<<(std::ostream &os, const CLTextGlyph & g)
{
  os << "TextGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  if (g.mIsTextSet)
    os << "  Explicit text is: \"" << g.mText << "\"\n";
  return os;
}
