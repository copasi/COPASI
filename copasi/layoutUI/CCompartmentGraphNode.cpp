// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CCompartmentGraphNode.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/15 15:03:13 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CCompartmentGraphNode.h"

CCompartmentGraphNode::CCompartmentGraphNode(const std::string & name,
    const CCopasiContainer * pParent)
    : CLCompartmentGlyph(name, pParent)
{
  mOrigNodeKey = "";
  mObjectKey = "";
}

CCompartmentGraphNode::CCompartmentGraphNode(const CLCompartmentGlyph & src,
    const CCopasiContainer * pParent)
    : CLCompartmentGlyph(src, pParent)
{
  mOrigNodeKey = src.getKey();
  mObjectKey = src.getModelObjectKey();
}

CCompartmentGraphNode::CCompartmentGraphNode(const CCompartmentGraphNode & src,
    const CCopasiContainer * pParent)
    : CLCompartmentGlyph(src, pParent)
{
  mOrigNodeKey = src.mOrigNodeKey;
  mObjectKey = src.mObjectKey;
}

std::ostream & operator<<(std::ostream &os, const CCompartmentGraphNode & gn)
{
  os << "node key: " << gn.mOrigNodeKey << std::endl;
  os << "object key: " << gn.mObjectKey << std::endl;
  os << "bounding box: " << gn.mBBox << std::endl;
  return os;
}
