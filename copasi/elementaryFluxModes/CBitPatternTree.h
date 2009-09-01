// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CBitPatternTree.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/01 15:58:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CBitPatternTree
#define COPASI_CBitPatternTree

#include "copasi/elementaryFluxModes/CBitPatternTreeNode.h"

class CBitPatternTree
{
  // Operations
private:
  CBitPatternTree();

public:
  CBitPatternTree(const std::list< CStepMatrixColumn * > & patterns);

  ~CBitPatternTree();

  const CBitPatternTreeNode * getRoot() const;

  bool isExtremeRay(const CZeroSet & ray) const;

  // Attributes
private:
  CBitPatternTreeNode * mpRoot;
};

#endif // COPASI_CBitPatternTree
