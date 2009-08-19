// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CBitPatternTreeNode.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/19 01:44:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CBitPatternTreeNode
#define COPASI_CBitPatternTreeNode

#include <vector>

#include "copasi/utilities/CCopasiNode.h"

class CZeroSet;
class CStepMatrixColumn;

class CBitPatternTreeNode: public CCopasiNode<void>
{
  // Operations
private:
  CBitPatternTreeNode();

public:
  CBitPatternTreeNode(const CBitPatternTreeNode & src);

  CBitPatternTreeNode(const std::vector<CStepMatrixColumn *> &);

  virtual ~CBitPatternTreeNode(void);

private:

  // Attributes
private:
  size_t mIndex;

  CZeroSet * mpZeroSet;

  CStepMatrixColumn * mpStepMatrixColumn;
};

#endif // COPASI_CBitPatternTreeNode
