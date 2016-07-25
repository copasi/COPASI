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

  return tmpUnit == unit;
}
