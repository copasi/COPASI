// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CBitPatternTreeNode.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/01/29 21:59:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CBitPatternTreeNode
#define COPASI_CBitPatternTreeNode

#include <list>

#include "copasi/elementaryFluxModes/CZeroSet.h"
#include "copasi/elementaryFluxModes/CStepMatrix.h"

class CStepMatrixColumn;

class CBitPatternTreeNode
{
  // Operations
private:
  CBitPatternTreeNode();

public:
  CBitPatternTreeNode(const CBitPatternTreeNode & src);

  CBitPatternTreeNode(const size_t & index,
                      const std::vector< CStepMatrixColumn * > & patterns);

  virtual ~CBitPatternTreeNode(void);

  const CStepMatrixColumn * getStepMatrixColumn() const;

  inline bool hasSuperset(const CZeroSet & set) const
  {
    if (mIgnoreCheck || *mpZeroSet >= set)
      {
        if (mpStepMatrixColumn != NULL)
          {
            return true;
          }

        if (mpUnsetChild->hasSuperset(set))
          {
            return true;
          }

        if (mpSetChild->hasSuperset(set))
          {
            return true;
          }
      }

    return false;
  }

  inline const CZeroSet & getZeroSet() const
  {
    return *mpZeroSet;
  }

  inline const CBitPatternTreeNode * getUnsetChild() const
  {
    return mpUnsetChild;
  }

  inline const CBitPatternTreeNode * getSetChild() const
  {
    return mpSetChild;
  }

  size_t getChildrenCount() const;

private:
  void splitPatterns(const std::vector< CStepMatrixColumn * > & patterns);

  size_t nextAvailableIndex() const;

  // Attributes
private:
  size_t mIndex;

  CZeroSet * mpZeroSet;

  bool mIgnoreCheck;

  CBitPatternTreeNode * mpUnsetChild;

  CBitPatternTreeNode * mpSetChild;

  CStepMatrixColumn * mpStepMatrixColumn;
};

#endif // COPASI_CBitPatternTreeNode
