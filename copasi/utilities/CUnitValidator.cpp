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
                               const std::vector< CUnit > & variableUnits):
  mMathContainer(math),
  mTree(tree),
  mVariableUnits(variableUnits.size())
{
  std::vector< CUnit >::const_iterator itSrc = variableUnits.begin();
  std::vector< CUnit >::const_iterator endSrc = variableUnits.end();
  std::vector< CValidatedUnit >::iterator itTarget = mVariableUnits.begin();

  for (; itSrc != endSrc; ++itSrc, ++itTarget)
    {
      *itTarget = CValidatedUnit(*itSrc, false);
    }
}

CUnitValidator::CUnitValidator(const CMathContainer & math,
                               const CEvaluationTree & tree,
                               const std::vector < CValidatedUnit > & variableUnits):
  mMathContainer(math),
  mTree(tree),
  mVariableUnits(variableUnits)
{}

CUnitValidator::CUnitValidator(const CUnitValidator &src):
  mMathContainer(src.mMathContainer),
  mTree(src.mTree),
  mVariableUnits(src.mVariableUnits)
{}

CUnitValidator::~CUnitValidator()
{
}

bool CUnitValidator::validateUnits(const CUnit & unit)
{
  do
    {
      getUnits();
    }
  while (setUnits(unit));

  bool conflict = false;

  std::map < CEvaluationNode * , CValidatedUnit >::const_iterator itMap = mNodeUnits.begin();
  std::map < CEvaluationNode * , CValidatedUnit >::const_iterator endMap = mNodeUnits.end();

  for (; itMap != endMap && !conflict; ++itMap)
    if (itMap->second.conflict())
      {
        conflict = true;
      }

  std::vector< CValidatedUnit >::const_iterator it = mVariableUnits.begin();
  std::vector< CValidatedUnit >::const_iterator end = mVariableUnits.end();

  for (; it != end && !conflict; ++it)
    if (it->conflict())
      {
        conflict = true;
      }

  std::map < CEvaluationNode * , CValidatedUnit >::iterator found = mNodeUnits.find(const_cast< CEvaluationNode * >(mTree.getRoot()));

  if (found != mNodeUnits.end())
    {
      found->second.setConflict(conflict);
    }

  return !conflict;
}

void CUnitValidator::getUnits()
{
  CValidatedUnit tmpUnit;
  CNodeContextIterator< CEvaluationNode, std::vector< CValidatedUnit > > it(const_cast< CEvaluationNode * >(mTree.getRoot()));

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

bool CUnitValidator::setUnits(const CUnit & unit)
{
  bool VariableUnitDetermined = false;
  CValidatedUnit tmpUnit;
  std::map < CEvaluationNode * , CValidatedUnit > CurrentNodeUnits(mNodeUnits);
  std::map < CEvaluationNode * , CValidatedUnit > TargetNodeUnits;
  mNodeUnits.clear();

  std::map < CEvaluationNode * , CValidatedUnit >::iterator found;

  CNodeIterator< CEvaluationNode > it(const_cast< CEvaluationNode * >(mTree.getRoot()));
  it.setProcessingModes(CNodeIteratorMode::Before);

  TargetNodeUnits.insert(std::make_pair(*it, CValidatedUnit(unit, false)));

  while (it.next() != it.end())
    {
      if (*it != NULL)
        {
          tmpUnit = it->setUnit(mMathContainer, CurrentNodeUnits, TargetNodeUnits);

          if (it->getType() != CEvaluationNode::VARIABLE)
            {
              mNodeUnits.insert(std::make_pair(*it, tmpUnit));
            }
          else
            {
              size_t Index = static_cast< CEvaluationNodeVariable * >(*it)->getIndex();

              if (Index >= mVariableUnits.size())
                {
                  CValidatedUnit Default;
                  mVariableUnits.resize(Index, Default);
                }

              bool Undefined = mVariableUnits[Index] == CBaseUnit::undefined;

              mVariableUnits[Index] = CValidatedUnit::merge(mVariableUnits[Index], tmpUnit);

              VariableUnitDetermined = Undefined && !(mVariableUnits[Index] == CBaseUnit::undefined);
            }
        }
    }

  return VariableUnitDetermined;
}

const std::vector< CValidatedUnit > & CUnitValidator::getVariableUnits() const
{
  return  mVariableUnits;
}

const CValidatedUnit & CUnitValidator::getUnit() const
{
  std::map < CEvaluationNode * , CValidatedUnit >::const_iterator found = mNodeUnits.find(const_cast< CEvaluationNode * >(mTree.getRoot()));

  if (found != mNodeUnits.end())
    {
      return found->second;
    }

  static CValidatedUnit Unit;

  return Unit;
}
