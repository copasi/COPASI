// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalObject.cpp,v $
//   $Revision: 1.11.2.1 $
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

#define USE_LAYOUT 1

#include <sbml/layout/GraphicalObject.h>

#include "CLGraphicalObject.h"

#include "report/CKeyFactory.h"
#include "sbml/CSBMLExporter.h"

CLGraphicalObject::CLGraphicalObject(const std::string & name,
                                     const CCopasiContainer * pParent)
    : CLBase(),
    CCopasiContainer(name, pParent, "LayoutElement"),
    mKey(GlobalKeys.add("Layout", this)),
    mModelObjectKey(""),
    mBBox()
{};

CLGraphicalObject::CLGraphicalObject(const CLGraphicalObject & src,
                                     const CCopasiContainer * pParent)
    : CLBase(src),
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Layout", this)),
    mModelObjectKey(src.mModelObjectKey),
    mBBox(src.mBBox)
{};

CLGraphicalObject::CLGraphicalObject(const GraphicalObject & sbml,
                                     std::map<std::string, std::string> & layoutmap,
                                     const CCopasiContainer * pParent)
    : CLBase(sbml),
    CCopasiContainer(sbml.getId(), pParent, "LayoutElement"),
    mKey(GlobalKeys.add("Layout", this)),
    mModelObjectKey(""),
    mBBox(*sbml.getBoundingBox())
{
  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
};

CLGraphicalObject::~CLGraphicalObject()
{
  GlobalKeys.remove(mKey);
}

CLGraphicalObject & CLGraphicalObject::operator= (const CLGraphicalObject & rhs)
{
  if (this == &rhs) return * this; //do nothing if lhs and rhs are the same

  CLBase::operator=(rhs);

  //warning: in this place we should call the assignment operator of
  //CCopasiContainer (which does not exist).
  //We handle this explicitly instead.
  setObjectName(rhs.getObjectName());
  //object flag cannot be accessed, it is private.

  mModelObjectKey = rhs.mModelObjectKey;
  mBBox = rhs.mBBox;

  return *this;
}

CCopasiObject * CLGraphicalObject::getModelObject() const
  {
    return GlobalKeys.get(mModelObjectKey);
  }

std::string CLGraphicalObject::getModelObjectName() const
  {
    CCopasiObject * tmp = getModelObject();
    if (tmp)
      return tmp->getObjectName();
    else
      return "";
  }

std::string CLGraphicalObject::getModelObjectDisplayName(bool /* regular */, bool /* richtext */) const
  {
    CCopasiObject * tmp = getModelObject();
    if (tmp)
      return tmp->getObjectName();
    else
      return "";
  }

void CLGraphicalObject::exportToSBML(GraphicalObject * sbmlobject,
                                     const std::map<CCopasiObject*, SBase*> & copasimodelmap,
                                     std::map<std::string, const SBase*>& sbmlIDs) const
  {
    if (!sbmlobject) return;

    //Name and ID
    std::string id = CSBMLExporter::createUniqueId(sbmlIDs, "layout_glyph_");
    sbmlobject->setId(id);
    sbmlIDs.insert(std::pair<const std::string, const SBase*>(id, sbmlobject));

    //Bounding box
    BoundingBox tmpbox = mBBox.getSBMLBoundingBox();
    sbmlobject->setBoundingBox(&tmpbox);
  }

std::ostream & operator<<(std::ostream &os, const CLGraphicalObject & g)
{
  os << "GraphicalObject \"" << g.getObjectName() << "\" " << g.mBBox << std::endl;
  std::string tmp = g.getModelObjectDisplayName();
  if (tmp != "")
    os << "  refers to " << tmp << std::endl;
  return os;
}

void CLGraphicalObject::print(std::ostream * ostream) const
{*ostream << *this;}
