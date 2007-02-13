// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalObject.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/13 17:14:30 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CLGraphicalObject.h"

#include "sbml/layout/GraphicalObject.h"

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
    CCopasiContainer("Graphical object", pParent, "LayoutElement"),
    mKey(GlobalKeys.add("Layout", this)),
    mModelObjectKey(""),
    mBBox()
{
  //add the copasi key to the map
  layoutmap[sbml.getId()] = mKey;
};

CLGraphicalObject::~CLGraphicalObject()
{
  GlobalKeys.remove(mKey);
}

CCopasiObject * CLGraphicalObject::modelObject() const
  {
    return GlobalKeys.get(mModelObjectKey);
  }

std::string CLGraphicalObject::modelObjectName() const
  {
    CCopasiObject * tmp = modelObject();
    if (tmp)
      return tmp->getObjectName();
    else
      return "";
  }

std::string CLGraphicalObject::modelObjectDisplayName(bool regular, bool richtext) const
  {
    CCopasiObject * tmp = modelObject();
    if (tmp)
      return tmp->getObjectDisplayName(regular, richtext);
    else
      return "";
  }

std::ostream & operator<<(std::ostream &os, const CLGraphicalObject & g)
{
  os << "GraphicalObject " << g.mBBox << std::endl;
  std::string tmp = g.modelObjectDisplayName();
  if (tmp != "")
    os << "  refers to " << tmp << std::endl;
  return os;
}

void CLGraphicalObject::print(std::ostream * ostream) const
{*ostream << *this;}
