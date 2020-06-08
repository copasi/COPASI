// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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
                               const CEvaluationTree & tree)
  : mMathContainer(*const_cast< CMathContainer * >(&math))
  , mTree(tree)
  , mTargetUnit()
  , mProvidedVariableUnits()
  , mVariableUnits()
  , mObjectUnits()
  , mNodeUnits()
{
  switch (mTree.getType())
    {
      case CEvaluationTree::Function:
      case CEvaluationTree::MassAction:
      case CEvaluationTree::PreDefined:
      case CEvaluationTree::UserDefined:
        mVariableUnits.resize(static_cast< const CFunction *>(&mTree)->getVariables().size());
        break;

      case CEvaluationTree::Expression:
      case CEvaluationTree::MathExpression:
        break;
    }
}

CUnitValidator::CUnitValidator(const CUnitValidator & src)
  : mMathContainer(src.mMathContainer)
  , mTree(src.mTree)
  , mTargetUnit(src.mTargetUnit)
  , mProvidedVariableUnits(src.mProvidedVariableUnits)
  , mVariableUnits(src.mVariableUnits)
  , mObjectUnits(src.mObjectUnits)
  , mNodeUnits(src.mNodeUnits)
{}

CUnitValidator::~CUnitValidator()
{}

bool CUnitValidator::validateUnits(const CUnit & unit,
                                   const std::vector< CUnit > & variableUnits)
{
  mTargetUnit = CValidatedUnit(unit, false);
  mProvidedVariableUnits.resize(variableUnits.size());
  std::vector< CUnit >::const_iterator itSrc = variableUnits.begin();
  std::vector< CUnit >::const_iterator endSrc = variableUnits.end();
  std::vector< CValidatedUnit >::iterator itTarget = mProvidedVariableUnits.begin();

  for (; itSrc != endSrc; ++itSrc, ++itTarget)
    {
      *itTarget = CValidatedUnit(*itSrc, false);
    }

  return validate();
}

bool CUnitValidator::validateUnits(const CValidatedUnit & unit,
                                   const std::vector< CValidatedUnit > & variableUnits)
{
  mTargetUnit = unit;
  mProvidedVariableUnits = variableUnits;

  return validate();
}

bool CUnitValidator::validate()
{
  if (mVariableUnits.size() != mProvidedVariableUnits.size())
    {
      mVariableUnits = std::vector< CValidatedUnit >(mVariableUnits.size(), CValidatedUnit());
      return false;
    }

  mVariableUnits = mProvidedVariableUnits;

  if (mTree.getType() == CEvaluationTree::MassAction)
    {
      // Unit validation is not supported in for the Mass Action family of function.
      // We need an explicit function.
      return false;
    }

  mObjectUnits.clear();
  mNodeUnits.clear();

  do
    {
      getUnits();
    }
  while (setUnits());

  bool conflict = false;

  std::map < CEvaluationNode *, CValidatedUnit >::const_iterator itMap = mNodeUnits.begin();
  std::map < CEvaluationNode *, CValidatedUnit >::const_iterator endMap = mNodeUnits.end();

  for (; itMap != endMap && !conflict; ++itMap)
    if (itMap->second.conflict())
      {
        conflict = true;
      }

  std::map < CObjectInterface *, CValidatedUnit >::iterator itObject = mObjectUnits.begin();
  std::map < CObjectInterface *, CValidatedUnit >::iterator endObject = mObjectUnits.end();

  for (; itObject != endObject; ++itObject)
    {
      itObject->second.buildExpression();

      if (itObject->second.conflict())
        {
          conflict = true;
        }
    }

  std::vector< CValidatedUnit >::iterator it = mVariableUnits.begin();
  std::vector< CValidatedUnit >::iterator end = mVariableUnits.end();

  for (; it != end; ++it)
    {
      it->buildExpression();

      if (it->conflict())
        {
          conflict = true;
        }
    }

  std::map < CEvaluationNode *, CValidatedUnit >::iterator found = mNodeUnits.find(const_cast< CEvaluationNode * >(mTree.getRoot()));

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
          switch (it->mainType())
            {
              case CEvaluationNode::MainType::VARIABLE:
                tmpUnit = it->getUnit(mMathContainer, mVariableUnits);
                break;

              case CEvaluationNode::MainType::OBJECT:
              {
                CObjectInterface * pObject = const_cast< CObjectInterface * >(static_cast< CEvaluationNodeObject * >(*it)->getObjectInterfacePtr());
                std::vector< CValidatedUnit > ObjectUnit;

                if (pObject != NULL)
                  {
                    std::map < CObjectInterface *, CValidatedUnit >::iterator found = mObjectUnits.find(pObject);

                    if (found == mObjectUnits.end())
                      {
                        found = mObjectUnits.insert(std::make_pair(pObject, CValidatedUnit(CBaseUnit::undefined, false))).first;
                      }

                    ObjectUnit.push_back(found->second);
                  }
                else
                  {
                    ObjectUnit.push_back(CValidatedUnit(CBaseUnit::undefined, false));
                  }

                tmpUnit = it->getUnit(mMathContainer, ObjectUnit);
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

          // tmpUnit.buildExpression();
          // std::cout << "getUnit: " << it->getData() << ", " << tmpUnit.conflict() << ", " << tmpUnit.getExpression() << std::endl;

          mNodeUnits[*it] = tmpUnit;
        }
    }
}

bool CUnitValidator::setUnits()
{
  bool UnitDetermined = false;
  CValidatedUnit tmpUnit;
  std::map < CEvaluationNode *, CValidatedUnit > CurrentNodeUnits(mNodeUnits);
  std::map < CEvaluationNode *, CValidatedUnit > TargetNodeUnits;
  mNodeUnits.clear();

  std::map < CEvaluationNode *, CValidatedUnit >::iterator found;

  CNodeIterator< CEvaluationNode > it(const_cast< CEvaluationNode * >(mTree.getRoot()));
  it.setProcessingModes(CNodeIteratorMode::Before);

  TargetNodeUnits.insert(std::make_pair(*it, mTargetUnit));

  while (it.next() != it.end())
    {
      if (*it != NULL)
        {
          tmpUnit = it->setUnit(mMathContainer, CurrentNodeUnits, TargetNodeUnits);

          mNodeUnits[*it] = tmpUnit;

          // tmpUnit.buildExpression();
          // std::cout << "setUnit: " << it->getData() << ", " << tmpUnit.conflict() << ", " << tmpUnit.getExpression() << std::endl;

          switch (it->mainType())
            {
              case CEvaluationNode::MainType::VARIABLE:
              {
                size_t Index = static_cast< CEvaluationNodeVariable * >(*it)->getIndex();

                if (Index >= mVariableUnits.size())
                  {
                    CValidatedUnit Default;
                    mVariableUnits.resize(Index, Default);
                  }

                bool Undefined = mVariableUnits[Index] == CBaseUnit::undefined;

                mVariableUnits[Index] = CValidatedUnit::merge(tmpUnit, mVariableUnits[Index]);

                UnitDetermined |= Undefined && !(mVariableUnits[Index] == CBaseUnit::undefined);
              }
              break;

              case CEvaluationNode::MainType::OBJECT:
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

                    found->second = CValidatedUnit::merge(tmpUnit, found->second);

                    UnitDetermined |= Undefined && !(found->second == CBaseUnit::undefined);
                  }
              }
              break;

              default:
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

const CValidatedUnit & CUnitValidator::getObjectUnit(const CObjectInterface * pObject) const
{
  std::map< CObjectInterface *, CValidatedUnit >::const_iterator found = mObjectUnits.find(const_cast< CObjectInterface * >(pObject));

  if (found == mObjectUnits.end())
    {
      CMathObject * pMathObject = mMathContainer.getMathObject(pObject);

      found = mObjectUnits.find(static_cast< CObjectInterface * >(pMathObject));
    }

  if (found == mObjectUnits.end())
    {
      static const CValidatedUnit Default;
      return Default;
    }

  return found->second;
}

const CValidatedUnit & CUnitValidator::getUnit() const
{
  std::map < CEvaluationNode *, CValidatedUnit >::const_iterator found = mNodeUnits.find(const_cast< CEvaluationNode * >(mTree.getRoot()));

  if (found != mNodeUnits.end())
    {
      return found->second;
    }

  static CValidatedUnit Unit;

  return Unit;
}
