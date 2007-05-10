// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/10 18:14:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <math.h>

#include "copasi.h"

#include "CGraphNode.h"
#include "layout/CLBase.h"

CGraphNode::CGraphNode(const std::string & name,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(name, pParent)
{
  msize = 20.0;
  morigNodeKey = "";
  mObjectKey = "";
}

CGraphNode::CGraphNode(const CLMetabGlyph & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
{
  msize = 20.0;
  morigNodeKey = src.getKey();
  mObjectKey = src.getModelObjectKey();
}

CGraphNode::CGraphNode(const CGraphNode & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
{
  msize = src.msize;
  morigNodeKey = src.morigNodeKey;
  mObjectKey = src.mObjectKey;
}

void CGraphNode::setSize(C_FLOAT64 newSize)
{
  this->msize = newSize;
  // now change corresponding end point(s) of attached curves)
}

std::ostream & operator<<(std::ostream &os, const CGraphNode & gn)
{
  os << "node key: " << gn.morigNodeKey << "  size: " << gn.msize << std::endl;
  //for (int i=0;i<gn.mConnectedCurveIndices.size();i++)
  // os << gn.mConnectedCurveIndices[i] << std::endl;;

  return os;
}
