// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CBitPatternTree.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/01/29 21:59:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CBitPatternTree.h"

CBitPatternTree::CBitPatternTree():
    mpRoot(NULL)
{}

CBitPatternTree::CBitPatternTree(const std::vector< CStepMatrixColumn * > & patterns):
    mpRoot(NULL)
{
  if (!patterns.empty())
    {
      mpRoot = new CBitPatternTreeNode(0, patterns);
    }
}

CBitPatternTree::~CBitPatternTree()
{
  pdelete(mpRoot);
}

const CBitPatternTreeNode * CBitPatternTree::getRoot() const
{
  return mpRoot;
}

bool CBitPatternTree::isExtremeRay(const CZeroSet & set) const
{
  if (mpRoot != NULL)
    {
      return !mpRoot->hasSuperset(set);
    }

  return true;
}

size_t CBitPatternTree::size() const
{
  if (mpRoot != NULL)
    {
      return mpRoot->getChildrenCount();
    }

  return 0;
}
