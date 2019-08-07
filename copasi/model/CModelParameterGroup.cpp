// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <map>
#include <iostream>

#include "CModelParameterGroup.h"
#include "CModel.h"
#include "copasi/utilities/CUnitValidator.h"
#include "copasi/math/CMathExpression.h"

// Uncoment the line below to debug undo processing
// #define DEBUG_UNDO 1

void CModelParameterGroup::updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject)
{
  const CModelParameter * pParameter = dynamic_cast< const CModelParameter * >(pUndoObject);

  std::vector< CModelParameter * >::iterator itParameter = mModelParameters.begin();
  std::vector< CModelParameter * >::iterator endParameter = mModelParameters.end();
  size_t Index = 0;

  for (; itParameter != endParameter; ++itParameter, Index++)
    if (pParameter == *itParameter)
      {
        break;
      }

  if (Index != index)
    {
      if (Index < mModelParameters.size())
        {
          mModelParameters.erase(itParameter);
        }

      mModelParameters.insert(mModelParameters.begin() + std::min(index, mModelParameters.size()), const_cast< CModelParameter * >(pParameter));
    }
}

CUndoObjectInterface * CModelParameterGroup::insert(const CData & data)
{
  CModelParameter * pParameter = CModelParameter::fromData(data, this);

  if (pParameter != NULL)
    {
      size_t Index = data.getProperty(CData::OBJECT_INDEX).toSizeT();
      mModelParameters.insert(mModelParameters.begin() + std::min(Index, mModelParameters.size()), pParameter);
      pParameter->setParent(this);
    }

  return pParameter;
}

// virtual
CData CModelParameterGroup::toData() const
{
  CData Data(CModelParameter::toData());

  std::vector< CModelParameter * >::const_iterator itParameter = mModelParameters.begin();
  std::vector< CModelParameter * >::const_iterator endParameter = mModelParameters.end();
  std::vector< CData > Value;

  for (; itParameter != endParameter; ++itParameter)
    {
      Value.push_back((*itParameter)->toData());
    }

  Data.addProperty(CData::PARAMETER_VALUE, Value);

  return Data;
}

// virtual
bool CModelParameterGroup::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CModelParameter::applyData(data, changes);

  if (data.isSetProperty(CData::PARAMETER_VALUE) &&
      data.getProperty(CData::PARAMETER_VALUE).getType() == CDataValue::DATA_VECTOR)
    {
      const std::vector< CData > & Value = data.getProperty(CData::PARAMETER_VALUE).toDataVector();

      std::vector< CData >::const_iterator it = Value.begin();
      std::vector< CData >::const_iterator end = Value.end();

      for (; it != end; ++it)
        {
          CModelParameter * pParameter = getModelParameter(it->getProperty(CData::OBJECT_NAME).toString());

          if (pParameter == NULL &&
              getSet() != NULL)
            {
              pParameter = dynamic_cast< CModelParameter * >(getSet()->insert(*it));
            }

          if (pParameter == NULL)
            {
              pParameter = dynamic_cast< CModelParameter * >(insert(*it));
            }

          if (pParameter != NULL)
            {
              success &= pParameter->applyData(*it, changes);
            }
          else
            {
              success = false;
            }
        }
    }

  return success;
}

// virtual
void CModelParameterGroup::createUndoData(CUndoData & undoData,
    const CUndoData::Type & type,
    const CData & oldData,
    const CCore::Framework & framework) const
{
  CModelParameter::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  const std::vector< CData > & OldParameters = oldData.getProperty(CData::PARAMETER_VALUE).toDataVector();
  std::vector< CData >::const_iterator itOld = OldParameters.begin();
  std::vector< CData >::const_iterator endOld = OldParameters.end();
  const_iterator itNew = mModelParameters.begin();
  const_iterator endNew = mModelParameters.end();

  std::vector< CData > OldModelParametersData;
  std::vector< CData > NewModelParametersData;

  for (; itOld != endOld && itNew != endNew; ++itOld, ++itNew)
    {
      CUndoData ParameterUndoData;
      (*itNew)->createUndoData(ParameterUndoData, CUndoData::Type::CHANGE, *itOld, framework);

      if (!ParameterUndoData.empty())
        {
          switch ((*itNew)->getType())
            {
              case Type::Model:
              case Type::Compartment:
              case Type::Species:
              case Type::ModelValue:
              case Type::ReactionParameter:
              {
                OldModelParametersData.push_back(ParameterUndoData.getOldData());
                NewModelParametersData.push_back(ParameterUndoData.getNewData());
              }
              break;

              default:
              {
                const std::vector< CData > & OldParameterData = ParameterUndoData.getOldData().getProperty(CData::PARAMETER_VALUE).toDataVector();
                OldModelParametersData.insert(OldModelParametersData.end(), OldParameterData.begin(), OldParameterData.end());

                const std::vector< CData > & NewParameterData = ParameterUndoData.getNewData().getProperty(CData::PARAMETER_VALUE).toDataVector();
                NewModelParametersData.insert(NewModelParametersData.end(), NewParameterData.begin(), NewParameterData.end());
              }
              break;
            }

#ifdef DEBUG_UNDO
          std::cout << "Old PARAMETER_VALUE: " <<  CDataValue(OldModelParametersData) << std::endl;
          std::cout << "New PARAMETER_VALUE: " <<  CDataValue(NewModelParametersData) << std::endl;
#endif // DEBUG_UNDO
        }
    }

  undoData.addProperty(CData::PARAMETER_VALUE, OldModelParametersData, NewModelParametersData);

  for (; itOld != endOld; ++itOld)
    {
#ifdef DEBUG_UNDO
      std::cout << "REMOVE: " << itOld->getProperty(CData::OBJECT_NAME).toString() << std::endl;
#endif // DEBUG_UNDO

      undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *itOld));
    }

  for (; itNew != endNew; ++itNew)
    {
#ifdef DEBUG_UNDO
      std::cout << "INSERT: " << itOld->getProperty(CData::OBJECT_NAME).toString() << std::endl;
#endif // DEBUG_UNDO

      undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, (*itNew)->toData()));
    }

  return;
}

CModelParameterGroup::CModelParameterGroup(CModelParameterGroup * pParent, const CModelParameter::Type & type):
  CModelParameter(pParent, type),
  mModelParameters(),
  mValidatedUnits()
{}

CModelParameterGroup::CModelParameterGroup(const CModelParameterGroup & src,
    CModelParameterGroup * pParent,
    const bool & createMissing):
  CModelParameter(src, pParent),
  mModelParameters(),
  mValidatedUnits()
{
  assignGroupContent(src, createMissing);
}

// virtual
CModelParameterGroup::~CModelParameterGroup()
{
  clear();
}

void CModelParameterGroup::assignGroupContent(const CModelParameterGroup & src,
    const bool & createMissing)
{
  clear();

  const_iterator itSrc = src.begin();
  const_iterator endSrc = src.end();

  for (; itSrc != endSrc; ++itSrc)
    {
      if (createMissing ||
          (*itSrc)->getCompareResult() != CompareResult::Missing)
        {
          copy(**itSrc, createMissing);
        }
    }
}

/**
 * Copy the existing parameter and add it to the group
 * @param const CModelParameter & src
 * @return CModelParameter * pCopy
 */
CModelParameter * CModelParameterGroup::copy(const CModelParameter & src,
    const bool & createMissing)
{
  CModelParameter * pCopy = NULL;

  switch (src.getType())
    {
      case Type::Compartment:
        pCopy = new CModelParameterCompartment(*static_cast< const  CModelParameterCompartment * >(&src), this);
        break;

      case Type::Species:
        pCopy = new CModelParameterSpecies(*static_cast< const CModelParameterSpecies * >(&src), this);
        break;

      case Type::ReactionParameter:
        pCopy = new CModelParameterReactionParameter(*static_cast< const  CModelParameterReactionParameter * >(&src), this);
        break;

      case Type::Model:
      case Type::ModelValue:
        pCopy = new CModelParameter(src, this);
        break;

      case Type::Reaction:
      case Type::Group:
        pCopy = new CModelParameterGroup(*static_cast< const  CModelParameterGroup * >(&src), this, createMissing);
        break;

      default:
        break;
    }

  if (pCopy)
    {
      mModelParameters.push_back(pCopy);
    }

  return pCopy;
}

CModelParameter * CModelParameterGroup::add(const CModelParameter::Type & type)
{
  CModelParameter * pModelParameter = NULL;

  switch (type)
    {
      case Type::Compartment:
        pModelParameter = new CModelParameterCompartment(this);
        break;

      case Type::Species:
        pModelParameter = new CModelParameterSpecies(this);
        break;

      case Type::ReactionParameter:
        pModelParameter = new CModelParameterReactionParameter(this, type);
        break;

      case Type::Model:
      case Type::ModelValue:
        pModelParameter = new CModelParameter(this, type);
        break;

      case Type::Reaction:
      case Type::Group:
        pModelParameter = new CModelParameterGroup(this, type);
        break;

      default:
        return pModelParameter;
        break;
    }

  add(pModelParameter);

  return pModelParameter;
}

void CModelParameterGroup::add(CModelParameter * pModelParameter)
{
  if (pModelParameter != NULL)
    {
      mModelParameters.push_back(pModelParameter);
      pModelParameter->setParent(this);
    }
}

void CModelParameterGroup::remove(CModelParameter * pModelParameter)
{
  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      if (*it == pModelParameter)
        {
          mModelParameters.erase(it);
          break;
        }
    }
}

void CModelParameterGroup::remove(const size_t & index)
{
  if (index < mModelParameters.size())
    {
      iterator it = mModelParameters.begin() + index;
      pdelete(*it);

      mModelParameters.erase(it);
    }
}

size_t CModelParameterGroup::size() const
{
  return mModelParameters.size();
}

CModelParameterGroup::iterator CModelParameterGroup::begin()
{
  return mModelParameters.begin();
}

CModelParameterGroup::iterator CModelParameterGroup::end()
{
  return mModelParameters.end();
}

CModelParameterGroup::const_iterator CModelParameterGroup::begin() const
{
  return mModelParameters.begin();
}

CModelParameterGroup::const_iterator CModelParameterGroup::end() const
{
  return mModelParameters.end();
}

void CModelParameterGroup::compile()
{
  CModelParameter::compile();

  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      (*it)->compile();
    }

  mValidatedUnits.clear();
}

void CModelParameterGroup::clear()
{
  if (mModelParameters.empty())
    {
      return;
    }

  assert(mType != Type::Set);

  // Clear existing model parameters.
  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      (*it)->setParent(NULL);
      pdelete(*it);
    }

  mModelParameters.clear();
}

// virtual
const CModelParameter::CompareResult & CModelParameterGroup::diff(const CModelParameter & other,
    const CCore::Framework & framework,
    const bool & createMissing)
{
  // We can only work on reactions, groups or sets.
  assert(other.getType() == Type::Reaction ||
         other.getType() == Type::Group ||
         other.getType() == Type::Set);

  if (mCompareResult == CompareResult::Missing ||
      mCompareResult == CompareResult::Obsolete)
    {
      return mCompareResult;
    }

  mCompareResult = CompareResult::Identical;

  const CModelParameterGroup * pOther = dynamic_cast< const CModelParameterGroup * >(&other);

  const_iterator itConst = pOther->begin();
  const_iterator endConst = pOther->end();

  std::map< CCommonName, CModelParameter * > Map;

  for (; itConst != endConst; ++itConst)
    {
      Map[(*itConst)->getCN()] = *itConst;
    }

  iterator itThis = begin();
  iterator endThis = end();

  for (; itThis != endThis; ++itThis)
    {
      std::map< CCommonName, CModelParameter * >::const_iterator itOther = Map.find((*itThis)->getCN());

      if (itOther == Map.end())
        {
          (*itThis)->setCompareResult(CompareResult::Obsolete);
          mCompareResult = CompareResult::Modified;

          continue;
        }

      if ((*itThis)->diff(*itOther->second, framework, createMissing) != CompareResult::Identical)
        {
          mCompareResult = CompareResult::Modified;
        }

      Map.erase(itOther->first);
    }

  if (createMissing)
    {
      std::map< CCommonName, CModelParameter * >::const_iterator itMissing = Map.begin();
      std::map< CCommonName, CModelParameter * >::const_iterator endMissing = Map.end();

      for (; itMissing != endMissing; ++itMissing)
        {
          CModelParameter * pMissing = copy(*itMissing->second, createMissing);

          if (pMissing != NULL)
            {
              pMissing->setCompareResult(CompareResult::Missing);
            }

          mCompareResult = CompareResult::Modified;
        }
    }
  else if (Map.size() > 0)
    {
      std::map< CCommonName, CModelParameter * >::const_iterator itMissing = Map.begin();
      std::map< CCommonName, CModelParameter * >::const_iterator endMissing = Map.end();

      for (; itMissing != endMissing; ++itMissing)
        {
          if (itMissing->second->getCompareResult() != CModelParameter::CompareResult::Missing)
            {
              mCompareResult = CompareResult::Modified;
              break;
            }
        }
    }

  return mCompareResult;
}

// virtual
bool CModelParameterGroup::updateModel()
{
  bool success = true;

  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      success &= (*it)->updateModel();
    }

  return success;
}

// virtual
bool CModelParameterGroup::refreshFromModel(const bool & modifyExistence)
{
  bool success = true;

  if (modifyExistence)
    {
      if (mCompareResult == CModelParameter::CompareResult::Obsolete)
        {
          delete this;

          return true;
        }

      if (mCompareResult == CModelParameter::CompareResult::Missing)
        {
          mCompareResult = CModelParameter::CompareResult::Identical;
        }
    }

  iterator it = begin();
  iterator End = end();

  std::vector< CModelParameter * > ToBeDeleted;

  for (; it != End; ++it)
    {
      if (modifyExistence &&
          (*it)->getCompareResult() == CModelParameter::CompareResult::Obsolete)
        {
          ToBeDeleted.push_back(*it);
        }
      else
        {
          success &= (*it)->refreshFromModel(modifyExistence);
        }
    }

  std::vector< CModelParameter * >::iterator itDelete = ToBeDeleted.begin();
  std::vector< CModelParameter * >::iterator endDelete = ToBeDeleted.end();

  for (; itDelete != endDelete; ++itDelete)
    {
      success &= (*itDelete)->refreshFromModel(modifyExistence);
    }

  return success;
}

CModelParameter * CModelParameterGroup::getModelParameter(const std::string & cn) const
{
  CModelParameter * pModelParameter = NULL;

  const_iterator it = begin();
  const_iterator End = end();

  for (; it != End && pModelParameter == NULL; ++it)
    {
      if (cn == (*it)->getCN())
        {
          pModelParameter = *it;
        }
      else if (dynamic_cast< const CModelParameterGroup * >(*it) != NULL)
        {
          pModelParameter = static_cast< const CModelParameterGroup * >(*it)->getModelParameter(cn);
        }
    }

  return pModelParameter;
}

CModelParameter * CModelParameterGroup::getModelParameter(const std::string & name,
    const CModelParameter::Type & type) const
{
  CModelParameter * pModelParameter = NULL;

  const_iterator it = begin();
  const_iterator End = end();

  for (; it != End && pModelParameter == NULL; ++it)
    {
      if (type == (*it)->getType() &&
          name == (*it)->getName())
        {
          pModelParameter = *it;
        }
      else if (dynamic_cast< const CModelParameterGroup * >(*it) != NULL)
        {
          pModelParameter = static_cast< const CModelParameterGroup * >(*it)->getModelParameter(name, type);
        }
    }

  return pModelParameter;
}

// virtual
size_t CModelParameterGroup::getNumChildren() const
{
  return size();
}

// virtual
const CModelParameter * CModelParameterGroup::getChild(const size_t & index) const
{
  if (index < size())
    {
      return mModelParameters[index];
    }

  return NULL;
}

const CValidatedUnit & CModelParameterGroup::getObjectUnit(const CModelParameter * pModelParameter) const
{
  static const CValidatedUnit Default;

  if (getType() == Type::Reaction &&
      mpObject != NULL)
    {
      const CModel * pModel = getModel();

      if (pModel != NULL)
        {
          const CMathContainer & Container = pModel->getMathContainer();
          CReaction * pReaction = static_cast< CReaction * >(mpObject);

          if (mValidatedUnits.empty())
            {
              const CDataObject * pFluxObject = pReaction->getFluxReference();
              CMathObject * pObject = Container.getMathObject(pFluxObject);
              CUnitValidator Validator(Container, *pObject->getExpressionPtr());

              Validator.validateUnits(pFluxObject->getUnits());
              mValidatedUnits = Validator.getObjectUnits();
            }

          CObjectInterface * pValueReference = NULL;
          size_t index = pReaction->getParameterIndex(pModelParameter->getName());

          if (pReaction->isLocalParameter(index))
            {
              CCopasiParameter *pParam = dynamic_cast<CCopasiParameter *>(pModelParameter->getObject());

              if (!pParam)
                return Default;

              pValueReference = pParam->getValueReference();
            }
          else
            {
              const CModelValue* pMV = dynamic_cast<const CModelValue *>(Container.getObject(static_cast<const CModelParameterReactionParameter *>(pModelParameter)->getGlobalQuantityCN()));

              if (!pMV)
                return Default;

              pValueReference = pMV->getValueReference();
            }

          std::map< CObjectInterface *, CValidatedUnit >::const_iterator found = mValidatedUnits.find(Container.getMathObject(pValueReference));

          if (found == mValidatedUnits.end() &&
              mpObject != NULL)
            {
              const CModel * pModel = getModel();

              if (pModel)
                {
                  CMathObject * pMathObject = pModel->getMathContainer().getMathObject(pValueReference);
                  found = mValidatedUnits.find(static_cast< CObjectInterface * >(pMathObject));
                }
            }

          if (found != mValidatedUnits.end())
            {
              return found->second;
            }
        }
    }

  return Default;
}
