// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.cpp,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/01/24 11:33:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <math.h>

#include "copasi.h"

#include "CGraphNode.h"
#include "CVisParameters.h"
#include "layout/CLBase.h"

CGraphNode::CGraphNode(const std::string & name,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(name, pParent)
    , msize(CVisParameters::DEFAULT_NODE_SIZE)
    , morigNodeKey("")
    , mObjectKey("")
    , mLabelText("")
{
}

CGraphNode::CGraphNode(const CLMetabGlyph & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
    , msize(CVisParameters::DEFAULT_NODE_SIZE)
    , morigNodeKey(src.getKey())
    , mObjectKey(src.getModelObjectKey())
    , mLabelText("")
{
}

CGraphNode::CGraphNode(const CGraphNode & src,
                       const CCopasiContainer * pParent)
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
