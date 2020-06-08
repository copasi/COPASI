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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

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
