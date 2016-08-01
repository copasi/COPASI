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
  mVariableUnits(variableUnits.size()),
  mObjectUnits(),
  mNodeUnits()
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
  mVariableUnits(variableUnits),
  mObjectUnits(),
  mNodeUnits()
{}

CUnitValidator::CUnitValidator(const CUnitValidator &src):
  mMathContainer(src.mMathContainer),
  mTree(src.mTree),
  mVariableUnits(src.mVariableUnits),
  mObjectUnits(src.mObjectUnits),
  mNodeUnits(src.mNodeUnits)
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

  std::map < CObjectInterface *, CValidatedUnit >::const_iterator itObject = mObjectUnits.begin();
  std::map < CObjectInterface *, CValidatedUnit >::const_iterator endObject = mObjectUnits.end();

  for (; itObject != endObject && !conflict; ++itObject)
    if (itObject->second.conflict())
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
          switch (it->getType())
            {
              case CEvaluationNode::VARIABLE:
                tmpUnit = it->getUnit(mMathContainer, mVariableUnits);
                break;

              case CEvaluationNode::OBJECT:
                tmpUnit = it->getUnit(mMathContainer, it.context());

                {
                  CObjectInterface * pObject = const_cast< CObjectInterface * >(static_cast< CEvaluationNodeObject * >(*it)->getObjectInterfacePtr());

                  if (pObject != NULL)
                    {
                      std::map < CObjectInterface *, CValidatedUnit >::iterator found = mObjectUnits.find(pObject);

                      if (found == mObjectUnits.end())
                        {
                          found = mObjectUnits.insert(std::make_pair(pObject, CValidatedUnit(CBaseUnit::undefined, false))).first;
                        }

                      found->second = CValidatedUnit::merge(found->second, tmpUnit);
                    }
                }
                break;

              default:
                tmpUnit = it->getUnit(mMathContainer, it.context());
                break;
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
  bool UnitDetermined = false;
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

          switch (it->getType())
            {
              case CEvaluationNode::VARIABLE:
              {
                size_t Index = static_cast< CEvaluationNodeVariable * >(*it)->getIndex();

                if (Index >= mVariableUnits.size())
                  {
                    CValidatedUnit Default;
                    mVariableUnits.resize(Index, Default);
                  }

                bool Undefined = mVariableUnits[Index] == CBaseUnit::undefined;

                mVariableUnits[Index] = CValidatedUnit::merge(mVariableUnits[Index], tmpUnit);

                UnitDetermined = Undefined && !(mVariableUnits[Index] == CBaseUnit::undefined);
              }
              break;

              case CEvaluationNode::OBJECT:
                mNodeUnits.insert(std::make_pair(*it, tmpUnit));

                {
                  CObjectInterface * pObject = const_cast< CObjectInterface * >(static_cast< CEvaluationNodeObject * >(*it)->getObjectInterfacePtr());

                  if (pObject != NULL)
                    {
                      std::map < CObjectInterface *, CValidatedUnit >::iterator found = mObjectUnits.find(pObject);

                      if (found == mObjectUnits.end())
                        {
                          found = mObjectUnits.insert(std::make_pair(pObject, CValidatedUnit(CBaseUnit::undefined, false))).first;
                        }

                      bool Undefined = found->second == CBaseUnit::undefined;

                      found->second = CValidatedUnit::merge(found->second, tmpUnit);

                      UnitDetermined = Undefined && !(found->second == CBaseUnit::undefined);
                    }
                }
                break;

              default:
                mNodeUnits.insert(std::make_pair(*it, tmpUnit));
                break;
            }
        }
    }

  return UnitDetermined;
}

const std::vector< CValidatedUnit > & CUnitValidator::getVariableUnits() const
{
  return  mVariableUnits;
}

const std::map< CObjectInterface *, CValidatedUnit > & CUnitValidator::getObjectUnits() const
{
  return  mObjectUnits;
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
