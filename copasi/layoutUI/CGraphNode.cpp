// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/05 11:06:02 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CgraphNode.h"

CGraphNode::CGraphNode(const std::string & name,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(name, pParent)
{
  msize = 20.0;
  morigNodeKey = "";
}

CGraphNode::CGraphNode(const CLMetabGlyph & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
{
  msize = 20.0;
  morigNodeKey = src.getKey();
}

CGraphNode::CGraphNode(const CGraphNode & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
{
  msize = src.msize;
  morigNodeKey = src.morigNodeKey;
}
