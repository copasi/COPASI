// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CUnitValidator.h"
#include "copasi/utilities/CNodeIterator.h"

//CUnitValidator::CUnitValidator():
//  mMathContainer(),
//  mTree(),
//  mVariableUnits()
//{
//}

CUnitValidator::CUnitValidator(const CMathContainer & math,
                               const CEvaluationTree & tree,
                               const std::vector < CUnit > & variableUnits):
  mMathContainer(math),
  mTree(tree),
  mVariableUnits(variableUnits)
{
}

CUnitValidator::CUnitValidator(const CUnitValidator &src):
  mMathContainer(src.mMathContainer),
  mTree(src.mTree),
  mVariableUnits(src.mVariableUnits)
{
}

CUnitValidator::~CUnitValidator()
{
}

bool CUnitValidator::validateUnits(const CUnit & unit)
{
  getUnits();
  setUnits(unit);

  bool conflict = false;

  std::map < CEvaluationNode * , CUnit >::const_iterator itMap = mNodeUnits.begin();
  std::map < CEvaluationNode * , CUnit >::const_iterator endMap = mNodeUnits.end();

  for (; itMap != endMap && !conflict; ++itMap)
    if (itMap->second.conflict())
      {
        conflict = true;
      }

  std::vector< CUnit >::const_iterator it = mVariableUnits.begin();
  std::vector< CUnit >::const_iterator end = mVariableUnits.end();

  for (; it != end && !conflict; ++it)
    if (it->conflict())
      {
        conflict = true;
      }

  std::map < CEvaluationNode * , CUnit >::iterator found = mNodeUnits.find(const_cast< CEvaluationNode * >(mTree.getRoot()));

  if (found != mNodeUnits.end())
    {
      found->second.setConflict(conflict);
    }

  return !conflict;
}

void CUnitValidator::getUnits()
{
  CUnit tmpUnit;
  CNodeContextIterator< CEvaluationNode, std::vector< CUnit > > it(const_cast< CEvaluationNode * >(mTree.getRoot()));

  while (it.next() != it.end())
    {
      if (*it != NULL)
        {
          if (it->getType() != CEvaluationNode::VARIABLE)
            {
              tmpUnit = it->getUnit(mMathContainer, it.context());
            }
          else
            {
              tmpUnit = it->getUnit(mMathContainer, mVariableUnits);
            }

          if (it.parentContextPtr() != NULL)
            {
              it.parentContextPtr()->push_back(tmpUnit);
            }

          mNodeUnits.insert(std::make_pair(*it, tmpUnit));
        }
    }
}

void CUnitValidator::setUnits(const CUnit & unit)
{
  CUnit tmpUnit;
  std::map < CEvaluationNode * , CUnit > CurrentNodeUnits(mNodeUnits);
  std::map < CEvaluationNode * , CUnit > TargetNodeUnits;
  mNodeUnits.clear();

  std::map < CEvaluationNode * , CUnit >::iterator found;

  CNodeIterator< CEvaluationNode > it(const_cast< CEvaluationNode * >(mTree.getRoot()));
  it.setProcessingModes(CNodeIteratorMode::Before);

  TargetNodeUnits.insert(std::make_pair(*it, unit));

  while (it.next() != it.end())
    {
      if (*it != NULL)
        {
          tmpUnit = it->setUnit(mMathContainer, TargetNodeUnits[*it], CurrentNodeUnits[*it], TargetNodeUnits);

          if (it->getType() != CEvaluationNode::VARIABLE)
            {
              mNodeUnits.insert(std::make_pair(*it, tmpUnit));
            }
          else
            {
              size_t Index = static_cast< CEvaluationNodeVariable * >(*it)->getIndex();

              if (Index >= mVariableUnits.size())
                {
                  CUnit Default;
                  Default.setConflict(true);
                  mVariableUnits.resize(Index, Default);
                }

              CUnit & VariableUnit = mVariableUnits[Index];

              if (VariableUnit == CUnit(CBaseUnit::undefined))
                {
                  tmpUnit.setConflict(tmpUnit.conflict() || VariableUnit.conflict());
                  VariableUnit = tmpUnit;
                }
              else if (!(VariableUnit == tmpUnit))
                {
                  VariableUnit.setConflict(true);
                }
            }
        }
    }
}

const std::vector< CUnit > & CUnitValidator::getVariableUnits() const
{
  return  mVariableUnits;
}

const CUnit & CUnitValidator::getUnit() const
{
  std::map < CEvaluationNode * , CUnit >::const_iterator found = mNodeUnits.find(const_cast< CEvaluationNode * >(mTree.getRoot()));

  if (found != mNodeUnits.end())
    {
      return found->second;
    }

  static CUnit Unit;
  Unit.setConflict(true);

  return Unit;
}
