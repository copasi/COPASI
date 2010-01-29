// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CStepMatrixColumn.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/01/29 21:59:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CStepMatrixColumn
#define COPASI_CStepMatrixColumn

#include <vector>

#include "copasi/elementaryFluxModes/CZeroSet.h"

class CStepMatrixColumn
{
public:
  friend std::ostream & operator << (std::ostream &, const CStepMatrixColumn &);

  // Operations
public:
  CStepMatrixColumn(const size_t & size = 0);

  CStepMatrixColumn(const CZeroSet & set,
                    CStepMatrixColumn const * pPositive,
                    CStepMatrixColumn const * pNegative);

  ~CStepMatrixColumn();

  const CZeroSet & getZeroSet() const;

  void convert(const CZeroSet::CIndex & bit);

  inline void unsetBit(const CZeroSet::CIndex & index)
  {
    mZeroSet.unsetBit(index);
  }

  inline const C_INT32 & getMultiplier() const
  {
    return mReaction.back();
  }

  std::vector< C_INT32 > & getReaction();

  void push_front(const C_INT32 & value);

  void truncate();

  inline void setIterator(CStepMatrixColumn **it)
  {
    mIterator = it;
  }

  // Attributes
private:
  CZeroSet mZeroSet;

  std::vector< C_INT32 > mReaction;

  CStepMatrixColumn ** mIterator;
};

std::ostream & operator << (std::ostream &, const CStepMatrixColumn &);

#endif // COPASI_CStepMatrixColumn
