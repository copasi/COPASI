// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

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
