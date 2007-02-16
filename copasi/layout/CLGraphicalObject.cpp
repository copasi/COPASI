// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalObject.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/16 16:56:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/layout/GraphicalObject.h>

#include "CLGraphicalObject.h"

#include "report/CKeyFactory.h"

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
    mBBox(sbml.getBoundingBox())
{
  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
};

CLGraphicalObject::~CLGraphicalObject()
{
  GlobalKeys.remove(mKey);
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

std::string CLGraphicalObject::getModelObjectDisplayName(bool regular, bool richtext) const
  {
    CCopasiObject * tmp = getModelObject();
    if (tmp)
      return tmp->getObjectDisplayName(regular, richtext);
    else
      return "";
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
