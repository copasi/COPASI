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

#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/CompartmentGlyph.h>
#include <sbml/packages/layout/sbml/TextGlyph.h>

#include "copasi/copasi.h"

#include "CLGlyphs.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CData.h"

// static
CLMetabGlyph * CLMetabGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLMetabGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                          NO_PARENT);
}

// virtual
CData CLMetabGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLMetabGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLMetabGlyph::CLMetabGlyph(const std::string & name,
                           const CDataContainer * pParent)
  : CLGraphicalObject(name, pParent)
{}

CLMetabGlyph::CLMetabGlyph(const CLMetabGlyph & src,
                           const CDataContainer * pParent)
  : CLGraphicalObject(src, pParent)
{}

CLMetabGlyph::CLMetabGlyph(const SpeciesGlyph & sbml,
                           const std::map<std::string, std::string> & modelmap,
                           std::map<std::string, std::string> & layoutmap,
                           const CDataContainer * pParent)
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

void CLMetabGlyph::exportToSBML(SpeciesGlyph * g,
                                const std::map<const CDataObject*, SBase*> & copasimodelmap,
                                std::map<std::string, const SBase*>& sbmlIDs) const
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
            g->setSpeciesId(it->second->getId());
        }
    }
}

std::ostream & operator<<(std::ostream &os, const CLMetabGlyph & g)
{
  os << "MetabGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  return os;
}

void CLMetabGlyph::print(std::ostream * ostream) const
{*ostream << *this;}

//********* CLCompartmentGlyph ************************************************

// static
CLCompartmentGlyph * CLCompartmentGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLCompartmentGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                                NO_PARENT);
}

// virtual
CData CLCompartmentGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLCompartmentGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLCompartmentGlyph::CLCompartmentGlyph(const std::string & name,
                                       const CDataContainer * pParent)
  : CLGraphicalObject(name, pParent)
{}

CLCompartmentGlyph::CLCompartmentGlyph(const CLCompartmentGlyph & src,
                                       const CDataContainer * pParent)
  : CLGraphicalObject(src, pParent)
{}

CLCompartmentGlyph::CLCompartmentGlyph(const CompartmentGlyph & sbml,
                                       const std::map<std::string, std::string> & modelmap,
                                       std::map<std::string, std::string> & layoutmap,
                                       const CDataContainer * pParent)
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

void CLCompartmentGlyph::exportToSBML(CompartmentGlyph * cg,
                                      const std::map<const CDataObject*, SBase*> & copasimodelmap,
                                      std::map<std::string, const SBase*>& sbmlIDs) const
{
  if (!cg) return;

  //call the coresponding method of the base class
  CLGraphicalObject::exportToSBML(cg, copasimodelmap, sbmlIDs);

  //reference to model objects
  CDataObject* tmp = getModelObject();

  if (tmp)
    {
      std::map<const CDataObject*, SBase*>::const_iterator it = copasimodelmap.find(tmp);

      if (it != copasimodelmap.end())
        {
          if (it->second)
            cg->setCompartmentId(it->second->getId());
        }
    }
}

std::ostream & operator<<(std::ostream &os, const CLCompartmentGlyph & g)
{
  os << "CompartmentGlyph: " << dynamic_cast<const CLGraphicalObject&>(g);
  return os;
}

void CLCompartmentGlyph::print(std::ostream * ostream) const
{*ostream << *this;}

//********** CLTextGlyph ******************************************************

// static
CLTextGlyph * CLTextGlyph::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLTextGlyph(data.getProperty(CData::OBJECT_NAME).toString(),
                         NO_PARENT);
}

// virtual
CData CLTextGlyph::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLTextGlyph::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CLTextGlyph::CLTextGlyph(const std::string & name,
                         const CDataContainer * pParent)
  : CLGraphicalObject(name, pParent),
    mIsTextSet(false),
    mText(""),
    mGraphicalObjectKey("")
{}

CLTextGlyph::CLTextGlyph(const CLTextGlyph & src,
                         const CDataContainer * pParent)
  : CLGraphicalObject(src, pParent),
    mIsTextSet(src.mIsTextSet),
    mText(src.mText),
    mGraphicalObjectKey(src.mGraphicalObjectKey)
{}

CLTextGlyph::CLTextGlyph(const TextGlyph & sbml,
                         const std::map<std::string, std::string> & modelmap,
                         std::map<std::string, std::string> & layoutmap,
                         const CDataContainer * pParent)
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
    {
      return mText;
    }
  else
    {
      return getModelObjectDisplayName();
    }
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
  return dynamic_cast<CLGraphicalObject*>(CRootContainer::getKeyFactory()->get(mGraphicalObjectKey));
}

void CLTextGlyph::exportToSBML(TextGlyph * g,
                               const std::map<const CDataObject*, SBase*> & copasimodelmap,
                               std::map<std::string, const SBase*>& sbmlIDs) const
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
            g->setOriginOfTextId(it->second->getId());
        }
    }

  //explicit text
  if (isTextSet())
    {
      g->setText(mText);
    }
}

void CLTextGlyph::exportReferenceToSBML(TextGlyph * g, const std::map<const CLBase*, const SBase*> & layoutmap) const
{
  if (!g) return;

  //reference to layout object
  CLGraphicalObject* tmp = getGraphicalObject();

  if (tmp)
    {
      std::map<const CLBase*, const SBase*>::const_iterator it = layoutmap.find(tmp);

      if (it != layoutmap.end() && it->second)
        {
          //we need to cast here since layout objects in libsbml don´t inherit the getId() method
          //from SBase
          const GraphicalObject* pGO = dynamic_cast<const GraphicalObject*>(it->second);

          if (pGO)
            g->setGraphicalObjectId(pGO->getId());
        }
    }
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

void CLTextGlyph::setGraphicalObjectKey(const std::string & k)
{
  mGraphicalObjectKey = k;
}
