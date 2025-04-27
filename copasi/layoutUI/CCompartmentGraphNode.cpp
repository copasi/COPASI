// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CCompartmentGraphNode.h"

CCompartmentGraphNode::CCompartmentGraphNode(const std::string & name,
    const CDataContainer * pParent)
  : CLCompartmentGlyph(name, pParent)
{
  mOrigNodeKey = "";
  mObjectKey = "";
}

CCompartmentGraphNode::CCompartmentGraphNode(const CLCompartmentGlyph & src,
    const CDataContainer * pParent)
  : CLCompartmentGlyph(src, pParent)
{
  mOrigNodeKey = src.getKey();
  mObjectKey = src.getModelObjectKey();
}

CCompartmentGraphNode::CCompartmentGraphNode(const CCompartmentGraphNode & src,
    const CDataContainer * pParent)
  : CLCompartmentGlyph(src, pParent)
{
  mOrigNodeKey = src.mOrigNodeKey;
  mObjectKey = src.mObjectKey;
}

std::ostream & operator<<(std::ostream &os, const CCompartmentGraphNode & gn)
{
  os << "node key: " << gn.mOrigNodeKey << "\n";
  os << "object key: " << gn.mObjectKey << "\n";
  os << "bounding box: " << gn.mBBox << "\n";
  return os;
}
