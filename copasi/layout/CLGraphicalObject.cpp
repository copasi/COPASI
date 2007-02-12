// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGraphicalObject.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/12 00:03:12 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CLGraphicalObject.h"

CLGraphicalObject::CLGraphicalObject(const std::string & name,
                                     const CCopasiContainer * pParent)
    : CCopasiContainer(name, pParent, "LayoutElement"),
    mKey(GlobalKeys.add("Layout", this)),
    mModelObjectKey(""),
    mBBox()
{};

CLGraphicalObject::CLGraphicalObject(const CLGraphicalObject & src,
                                     const CCopasiContainer * pParent)
    : CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Layout", this)),
    mModelObjectKey(src.mModelObjectKey),
    mBBox(src.mBBox)
{};

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
