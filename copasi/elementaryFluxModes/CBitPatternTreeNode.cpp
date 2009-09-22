// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CBitPatternTreeNode.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/22 14:57:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

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
    const std::list< CStepMatrixColumn * > & patterns):
    mIndex(index),
    mpZeroSet(NULL),
    mIgnoreCheck(false),
    mpUnsetChild(NULL),
    mpSetChild(NULL),
    mpStepMatrixColumn(NULL)
{
  switch (patterns.size())
    {
      case 0:
        assert(false);
        break;

      case 1:
        mpZeroSet = new CZeroSet((*patterns.begin())->getZeroSet());
        mpStepMatrixColumn = *patterns.begin();
        break;

      default:
      {
        std::list<CStepMatrixColumn *>::const_iterator it = patterns.begin();
        std::list<CStepMatrixColumn *>::const_iterator end = patterns.end();
        mpZeroSet = new CZeroSet((*it)->getZeroSet());

        for (++it; it != end; ++it)
          {
            *mpZeroSet |= (*it)->getZeroSet();
          }

        splitPatterns(patterns);
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

void CBitPatternTreeNode::splitPatterns(const std::list<CStepMatrixColumn *> & patterns)
{
  size_t Index = mIndex;
  CZeroSet::CIndex Bit(mIndex);

  std::list<CStepMatrixColumn *> SetPatterns;
  std::list<CStepMatrixColumn *> UnsetPatterns;

  while (UnsetPatterns.empty() || SetPatterns.empty())
    {
      SetPatterns.clear();
      UnsetPatterns.clear();

      mIndex = Index;
      Bit = mIndex;

      std::list<CStepMatrixColumn *>::const_iterator it = patterns.begin();
      std::list<CStepMatrixColumn *>::const_iterator end = patterns.end();

      for (; it != end; ++it)
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
