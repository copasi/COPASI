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

#include "CBitPatternTreeNode.h"
#include "CStepMatrixColumn.h"

CBitPatternTreeNode::CBitPatternTreeNode(void):
  mIndex(0),
  mpZeroSet(NULL),
  mIgnoreCheck(false),
  mpUnsetChild(NULL),
  mpSetChild(NULL),
  mpStepMatrixColumn(NULL)
{}

CBitPatternTreeNode::CBitPatternTreeNode(const size_t & index,
    const std::vector< CStepMatrixColumn * > & patterns):
  mIndex(index),
  mpZeroSet(NULL),
  mIgnoreCheck(false),
  mpUnsetChild(NULL),
  mpSetChild(NULL),
  mpStepMatrixColumn(NULL)
{
  // Note: patterns may contain NULL pointers
  switch (patterns.size())
    {
      case 0:
        assert(false);
        break;

      case 1:
      {
        std::vector< CStepMatrixColumn * >::const_iterator it = patterns.begin();

        // This should never happen.
        assert(*it != NULL);

        mpZeroSet = new CZeroSet((*it)->getZeroSet());
        mpStepMatrixColumn = *it;
      }
      break;

      default:
      {
        std::vector< CStepMatrixColumn * >::const_iterator it = patterns.begin();
        std::vector< CStepMatrixColumn * >::const_iterator end = patterns.end();

        // This should never happen.

        for (; it != end; ++it)
          {
            if (*it != NULL)
              {
                break;
              }
          }

        // This should never happen.
        assert(*it != NULL);

        CStepMatrixColumn * pFirstColumn = *it;

        mpZeroSet = new CZeroSet(pFirstColumn->getZeroSet());
        size_t Count = 1;

        for (++it; it != end; ++it)
          {
            if (*it != NULL)
              {
                *mpZeroSet |= (*it)->getZeroSet();
                Count++;
              }
          }

        if (Count != 1)
          {
            splitPatterns(patterns);
          }
        else
          {
            mpStepMatrixColumn = pFirstColumn;
          }
      }
      break;
    }
}

CBitPatternTreeNode::~CBitPatternTreeNode(void)
{
  pdelete(mpZeroSet);
  pdelete(mpUnsetChild);
  pdelete(mpSetChild);
}

const CStepMatrixColumn * CBitPatternTreeNode::getStepMatrixColumn() const
{
  return mpStepMatrixColumn;
}

void CBitPatternTreeNode::splitPatterns(const std::vector< CStepMatrixColumn * > & patterns)
{
  size_t Index = mIndex;
  CZeroSet::CIndex Bit(mIndex);

  std::vector< CStepMatrixColumn * > SetPatterns;
  std::vector< CStepMatrixColumn * > UnsetPatterns;

  while (UnsetPatterns.empty() || SetPatterns.empty())
    {
      SetPatterns.clear();
      UnsetPatterns.clear();

      mIndex = Index;
      Bit = mIndex;

      std::vector< CStepMatrixColumn * >::const_iterator it = patterns.begin();
      std::vector< CStepMatrixColumn * >::const_iterator end = patterns.end();

      for (; it != end; ++it)
        {
          if (*it != NULL)
            {
              if ((*it)->getZeroSet().isSet(Bit))
                {
                  SetPatterns.push_back((*it));
                }
              else
                {
                  UnsetPatterns.push_back((*it));
                }
            }
        }

      Index = nextAvailableIndex();
    }

  mpUnsetChild = new CBitPatternTreeNode(Index, UnsetPatterns);

  if (mpUnsetChild->getZeroSet() == *mpZeroSet)
    {
      mpUnsetChild->mIgnoreCheck = true;
    }

  mpSetChild = new CBitPatternTreeNode(Index, SetPatterns);

  if (mpSetChild->getZeroSet() == *mpZeroSet)
    {
      mpSetChild->mIgnoreCheck = true;
    }
}

size_t CBitPatternTreeNode::nextAvailableIndex() const
{
  return mIndex + 1;
}

size_t CBitPatternTreeNode::getChildrenCount() const
{
  if (mpStepMatrixColumn != NULL)
    {
      return 1;
    }

  size_t Count = 0;

  if (mpUnsetChild != NULL)
    {
      Count = mpUnsetChild->getChildrenCount();
    }

  if (mpSetChild != NULL)
    {
      Count += mpSetChild->getChildrenCount();
    }

  return Count;
}
