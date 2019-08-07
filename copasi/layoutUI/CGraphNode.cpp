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

#include <cmath>

#include "copasi/copasi.h"

#include "CGraphNode.h"
#include "CVisParameters.h"
#include "copasi/layout/CLBase.h"

CGraphNode::CGraphNode(const std::string & name,
                       const CDataContainer * pParent)
  : CLMetabGlyph(name, pParent)
  , msize(CVisParameters::DEFAULT_NODE_SIZE)
  , morigNodeKey("")
  , mObjectKey("")
  , mLabelText("")
{
}

CGraphNode::CGraphNode(const CLMetabGlyph & src,
                       const CDataContainer * pParent)
  : CLMetabGlyph(src, pParent)
  , msize(CVisParameters::DEFAULT_NODE_SIZE)
  , morigNodeKey(src.getKey())
  , mObjectKey(src.getModelObjectKey())
  , mLabelText("")
{
}

CGraphNode::CGraphNode(const CGraphNode & src,
                       const CDataContainer * pParent)
  : CLMetabGlyph(src, pParent)
  , msize(src.msize)
  , morigNodeKey(src.morigNodeKey)
  , mObjectKey(src.mObjectKey)
  , mLabelText(src.mLabelText)
{
}

void CGraphNode::setSize(C_FLOAT64 newSize)
{
  this->msize = newSize;
  // now change corresponding end point(s) of attached curves)
}

std::ostream & operator<<(std::ostream &os, const CGraphNode & gn)
{
  os << "node key: " << gn.morigNodeKey << "  size: " << gn.msize << std::endl;
  os << "object key: " << gn.mObjectKey << std::endl;
  os << "bounding box: " << gn.mBBox << std::endl;
  os << "label: " << gn.mLabelText << std::endl;
  //for (int i=0;i<gn.mConnectedCurveIndices.size();i++)
  // os << gn.mConnectedCurveIndices[i] << std::endl;;

  return os;
}

void CGraphNode::setLabelText(std::string name)
{
  this->mLabelText = name;
}
