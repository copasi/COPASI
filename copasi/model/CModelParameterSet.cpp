// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CModelParameterSet.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CDataString.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/utilities/CValidatedUnit.h"

// static
CModelParameterSet * CModelParameterSet::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CModelParameterSet(data.getProperty(CData::OBJECT_NAME).toString(),
                                NO_PARENT);
}

// virtual
void CModelParameterSet::destruct()
{
  delete this;
}

// virtual
CData CModelParameterSet::toData() const
{
  CData Data;

  // This works since the appended data overwrites the existing, i.e., we have the required object information
  Data.appendData(CModelParameterGroup::toData());
  Data.appendData(CAnnotation::toData());
  Data.appendData(CDataContainer::toData());

  return Data;
}

// virtual
bool CModelParameterSet::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  success &= CDataContainer::applyData(data, changes);
  success &= CAnnotation::applyData(data, changes);
  success &= CModelParameterGroup::applyData(data, changes);

  return success;
}

void CModelParameterSet::createUndoData(CUndoData & undoData,
                                        const CUndoData::Type & type,
                                        const CData & oldData,
                                        const CCore::Framework & framework) const
{
  // This works since the appended data overwrites the existing, i.e., we have the required object information
  CModelParameterGroup::createUndoData(undoData, type, oldData, framework);
  CAnnotation::createUndoData(undoData, type, oldData, framework);
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  return;
}

// virtual
CUndoObjectInterface * CModelParameterSet::insert(const CData & data)
{
  CModelParameter * pParameter = CModelParameter::fromData(data, dynamic_cast< CDataObject * >(this));

  switch (CModelParameter::TypeNames.toEnum(data.getProperty(CData::OBJECT_TYPE).toString(), CModelParameter::Type::unknown))
    {
      case CModelParameter::Type::Model:
        mpTimes->add(pParameter);
        break;

      case CModelParameter::Type::Compartment:
        mpCompartments->add(pParameter);
        break;

      case CModelParameter::Type::Species:
        mpSpecies->add(pParameter);
        break;

      case CModelParameter::Type::ModelValue:
        mpModelValues->add(pParameter);
        break;

      case CModelParameter::Type::ReactionParameter:
      {
        CCommonName ReactionCN = CModelParameterReactionParameter::getReactionCN(data.getProperty(CData::OBJECT_NAME).toString());
        CModelParameterGroup * pReaction = static_cast< CModelParameterGroup * >(mpReactions->getModelParameter(ReactionCN));

        if (pReaction == NULL)
          {
            pReaction = static_cast< CModelParameterGroup * >(mpReactions->add(CModelParameter::Type::Reaction));
            pReaction->setCN(ReactionCN);
          }

        if (pReaction != NULL)
          {
            pReaction->add(pParameter);
          }
      }
      break;

      case CModelParameter::Type::Reaction:
        mpReactions->add(pParameter);
        break;

      case CModelParameter::Type::Group:
      case CModelParameter::Type::Set:
      case CModelParameter::Type::unknown:
        break;
    }

  return pParameter;
}

// virtual
void CModelParameterSet::updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject)
{
  CDataContainer::updateIndex(index, pUndoObject);
}

CModelParameterSet::CModelParameterSet(const std::string & name,
                                       const CDataContainer * pParent):
  CDataContainer(name, pParent, "ModelParameterSet"),
  CAnnotation(),
  CModelParameterGroup(NULL, CModelParameter::Type::Set),
  mKey(CRootContainer::getKeyFactory()->add("ModelParameterSet", this)),
  mpModel(NULL),
  mpTimes(NULL),
  mpCompartments(NULL),
  mpSpecies(NULL),
  mpModelValues(NULL),
  mpReactions(NULL)
{
  initMiriamAnnotation(mKey);

  // Create the proper structure that fits the parameter overview in the GUI
  mpTimes = static_cast< CModelParameterGroup * >(CModelParameterGroup::add(Type::Group));
  mpTimes->setCN(CDataString("Initial Time").getCN());

  mpCompartments = static_cast< CModelParameterGroup * >(CModelParameterGroup::add(Type::Group));
  mpCompartments->setCN(CDataString("Initial Compartment Sizes").getCN());

  mpSpecies = static_cast< CModelParameterGroup * >(CModelParameterGroup::add(Type::Group));
  mpSpecies->setCN(CDataString("Initial Species Values").getCN());

  mpModelValues = static_cast< CModelParameterGroup * >(CModelParameterGroup::add(Type::Group));
  mpModelValues->setCN(CDataString("Initial Global Quantities").getCN());

  mpReactions = static_cast< CModelParameterGroup * >(CModelParameterGroup::add(Type::Group));
  mpReactions->setCN(CDataString("Kinetic Parameters").getCN());

  setObjectParent(pParent);
}

CModelParameterSet::CModelParameterSet(const CModelParameterSet & src,
                                       const CDataContainer * pParent,
                                       const bool & createMissing):
  CDataContainer(src, pParent),
  CAnnotation(src),
  CModelParameterGroup(src, NULL, createMissing),
  mKey(CRootContainer::getKeyFactory()->add("ModelParameterSet", this)),
  mpModel(NULL),
  mpTimes(NULL),
  mpCompartments(NULL),
  mpSpecies(NULL),
  mpModelValues(NULL),
  mpReactions(NULL)
{
  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);

  // Create the proper structure that fits the parameter overview in the GUI
  mpTimes = static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Time").getCN()));
  mpCompartments = static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Compartment Sizes").getCN()));
  mpSpecies = static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Species Values").getCN()));
  mpModelValues = static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Global Quantities").getCN()));
  mpReactions = static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Kinetic Parameters").getCN()));

  setObjectParent(pParent);

  if (mpModel == NULL)
    {
      mpModel = src.getModel();
    }

  compile();
}

// virtual
CModelParameterSet::~CModelParameterSet()
{
  mType = Type::Group;
  CRootContainer::getKeyFactory()->remove(mKey);
}

// virtual
CCommonName CModelParameterSet::getCN() const
{
  return CDataContainer::getCN();
}

CModelParameterGroup * CModelParameterSet::toGroup()
{
  return this;
};

const CModelParameterGroup * CModelParameterSet::toGroup() const
{
  return this;
};

// virtual
CModelParameterSet * CModelParameterSet::toSet()
{
  return this;
};

// virtual
const CModelParameterSet * CModelParameterSet::toSet() const
{
  return this;
};

void CModelParameterSet::init()
{
}

void CModelParameterSet::add(CModelParameter * pModelParameter)
{

  CModelParameterGroup::add(pModelParameter);

  if (pModelParameter->getType() != CModelParameter::Type::Group)
    return;

  auto& cn = pModelParameter->getCN();

  if (cn == CDataString("Initial Time").getCN())
    {
      pdelete(mpTimes);
      mpTimes = static_cast<CModelParameterGroup *>(pModelParameter);
      return;
    }

  if (cn == CDataString("Initial Compartment Sizes").getCN())
    {
      pdelete(mpCompartments);
      mpCompartments = static_cast<CModelParameterGroup *>(pModelParameter);
      return;
    }

  if (cn == CDataString("Initial Species Values").getCN())
    {
      pdelete(mpSpecies);
      mpSpecies = static_cast<CModelParameterGroup *>(pModelParameter);
      return;
    }

  if (cn == CDataString("Initial Global Quantities").getCN())
    {
      pdelete(mpModelValues);
      mpModelValues = static_cast<CModelParameterGroup *>(pModelParameter);
      return;
    }

  if (cn == CDataString("Kinetic Parameters").getCN())
    {
      pdelete(mpReactions);
      mpReactions = static_cast<CModelParameterGroup *>(pModelParameter);
      return;
    }
}

// virtual
const std::string & CModelParameterSet::getKey() const
{
  return mKey;
}

// virtual
bool CModelParameterSet::setObjectParent(const CDataContainer * pParent)
{
  bool success = CDataObject::setObjectParent(pParent);

  mpModel = dynamic_cast< CModel * >(getObjectAncestor("Model"));

  return success;
}

// virtual
size_t CModelParameterSet::getIndex() const
{
  if (getObjectParent() != NULL)
    {
      return getObjectParent()->getIndex(this);
    }

  return C_INVALID_INDEX;
}

// virtual
CModel * CModelParameterSet::getModel() const
{
  assert(mpModel != NULL);

  return mpModel;
}

void CModelParameterSet::createFromModel()
{
  mpTimes->clear();
  mpCompartments->clear();
  mpSpecies->clear();
  mpModelValues->clear();
  mpReactions->clear();

  if (mpModel == NULL)
    {
      return;
    }

  CModelParameter * pParameter;

  pParameter = mpTimes->add(Type::Model);
  pParameter->setCN(mpModel->getCN());
  pParameter->setValue(mpModel->getInitialTime(), CCore::Framework::ParticleNumbers, false);

  CDataVector< CCompartment >::const_iterator itCompartment = mpModel->getCompartments().begin();
  CDataVector< CCompartment >::const_iterator endCompartment = mpModel->getCompartments().end();

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      pParameter = mpCompartments->add(Type::Compartment);
      pParameter->setCN(itCompartment->getCN());
      pParameter->setSimulationType(itCompartment->getStatus());
      pParameter->setValue(itCompartment->getInitialValue(), CCore::Framework::ParticleNumbers, false);
      pParameter->setInitialExpression(itCompartment->getInitialExpression());
    }

  CDataVector< CMetab >::const_iterator itSpecies = mpModel->getMetabolites().begin();
  CDataVector< CMetab >::const_iterator endSpecies = mpModel->getMetabolites().end();

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      pParameter = mpSpecies->add(Type::Species);
      pParameter->setCN(itSpecies->getCN());
      pParameter->setSimulationType(itSpecies->getStatus());
      pParameter->setValue(itSpecies->getInitialValue(), CCore::Framework::ParticleNumbers, false);
      pParameter->setInitialExpression(itSpecies->getInitialExpression());
    }

  CDataVector< CModelValue >::const_iterator itModelValue = mpModel->getModelValues().begin();
  CDataVector< CModelValue >::const_iterator endModelValue = mpModel->getModelValues().end();

  for (; itModelValue != endModelValue; ++itModelValue)
    {
      pParameter = mpModelValues->add(Type::ModelValue);
      pParameter->setCN(itModelValue->getCN());
      pParameter->setSimulationType(itModelValue->getStatus());
      pParameter->setValue(itModelValue->getInitialValue(), CCore::Framework::ParticleNumbers, false);
      pParameter->setInitialExpression(itModelValue->getInitialExpression());
    }

  CDataVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CDataVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  for (; itReaction != endReaction; ++itReaction)
    {
      CModelParameterGroup * pReaction = static_cast< CModelParameterGroup *>(mpReactions->add(Type::Reaction));
      pReaction->setCN(itReaction->getCN());

      CCopasiParameterGroup::index_iterator itParameter = itReaction->getParameters().beginIndex();
      CCopasiParameterGroup::index_iterator endParameter = itReaction->getParameters().endIndex();

      for (; itParameter != endParameter; ++itParameter)
        {
          const CFunctionParameter * pFunctionParameter = NULL;
          itReaction->getParameterIndex((*itParameter)->getObjectName(), &pFunctionParameter);

          if (pFunctionParameter == NULL ||
              pFunctionParameter->getUsage() != CFunctionParameter::Role::PARAMETER)
            {
              continue;
            }

          pParameter = pReaction->add(Type::ReactionParameter);
          pParameter->setCN((*itParameter)->getCN());

          // Check whether this refers to a global quantity.
          if (itReaction->isLocalParameter((*itParameter)->getObjectName()))
            {
              pParameter->setSimulationType(CModelEntity::Status::FIXED);
              pParameter->setValue((*itParameter)->getValue< C_FLOAT64 >(), CCore::Framework::ParticleNumbers, false);
            }
          else
            {
              pParameter->setSimulationType(CModelEntity::Status::ASSIGNMENT);
              const std::vector< const CDataObject * > & ModelValue = itReaction->getParameterObjects((*itParameter)->getObjectName());
              const CModelValue * pModelValue = NULL;

              if (ModelValue.size() == 1
                  && (pModelValue = dynamic_cast< const CModelValue * >(ModelValue[0])) != NULL)
                {
                  pParameter->setValue(pModelValue->getInitialValue(), CCore::Framework::ParticleNumbers, false);
                  pParameter->setInitialExpression("<" + pModelValue->getInitialValueReference()->getCN() + ">");
                }
              else
                {
                  pParameter->setValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN(), CCore::Framework::ParticleNumbers, false);
                  pParameter->setInitialExpression("");
                }
            }
        }
    }

  compile();
}

bool CModelParameterSet::compareWithModel(const CCore::Framework & framework)
{
  if (mpModel == NULL)
    {
      return false;
    }

  CModelParameterSet Tmp("Current", mpModel);
  Tmp.createFromModel();

  return (diff(Tmp, framework, true) == CModelParameter::CompareResult::Identical);
}

// virtual
std::string CModelParameterSet::getName() const
{
  return getObjectName();
}

// virtual
bool CModelParameterSet::updateModel()
{
  if (mpModel == NULL)
    {
      return false;
    }

  compile();

  bool success = CModelParameterGroup::updateModel();

  mpModel->updateInitialValues(CCore::Framework::ParticleNumbers);

  return success;
}

// virtual
void CModelParameterSet::compile()
{
  CModelParameterGroup::compile();
}

const CModelParameter::CompareResult & CModelParameterSet::diff(const CModelParameterSet & other,
    const CCore::Framework & framework,
    const bool & createMissing)
{
  return CModelParameterGroup::diff(other, framework, createMissing);
}

const CModelParameter * CModelParameterSet::getModelParameter(const std::string & cn) const
{
  return CModelParameterGroup::getModelParameter(cn);
}

CModelParameterGroup::const_iterator CModelParameterSet::begin() const
{
  return CModelParameterGroup::begin();
}

CModelParameterGroup::const_iterator CModelParameterSet::end() const
{
  return CModelParameterGroup::end();
}

// virtual
bool CModelParameterSet::refreshFromModel(const bool & modifyExistence)
{
  return CModelParameterGroup::refreshFromModel(modifyExistence);
}

bool CModelParameterSet::isActive() const
{
  if (mpModel == NULL)
    {
      return false;
    }

  return (mpModel->getActiveModelParameterSet().getKey() == mKey);
}

void CModelParameterSet::assignSetContent(const CModelParameterSet & src,
    const bool & createMissing)
{
  // Create the proper structure that fits the parameter overview in the GUI
  mpTimes->assignGroupContent(*static_cast< const CModelParameterGroup * >(src.getModelParameter(CDataString("Initial Time").getCN())), createMissing);
  mpCompartments->assignGroupContent(*static_cast< const CModelParameterGroup * >(src.getModelParameter(CDataString("Initial Compartment Sizes").getCN())), createMissing);
  mpSpecies->assignGroupContent(*static_cast< const CModelParameterGroup * >(src.getModelParameter(CDataString("Initial Species Values").getCN())), createMissing);
  mpModelValues->assignGroupContent(*static_cast< const CModelParameterGroup * >(src.getModelParameter(CDataString("Initial Global Quantities").getCN())), createMissing);
  mpReactions->assignGroupContent(*static_cast< const CModelParameterGroup * >(src.getModelParameter(CDataString("Kinetic Parameters").getCN())), createMissing);

  compile();
}

bool CModelParameterSet::saveToStream(std::ostream & os,
                                      const CCore::Framework & framework,
                                      const std::string & mode,
                                      const std::string & separator)
{
  bool success = true;

  CNodeIterator< const CModelParameter > itNode(this);

  if (mode == "report")
    {
      itNode.setProcessingModes(CNodeIteratorMode::Before);

      while (itNode.next() != itNode.end())
        {
          if (*itNode != NULL)
            {
              unsigned int level = itNode.level();
              const CDataObject* current = itNode->getObject();
              const CReaction* pReaction = dynamic_cast<const CReaction*>(current);
              C_FLOAT64 value = itNode->getValue(framework);

              for (unsigned int i = 1; i < level; i++)
                {
                  os << separator;
                }

              os << itNode->getName();

              for (size_t i = level; i < 6; i++)
                {
                  os << separator;
                }

              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set)
                {
                  if (pReaction != NULL)
                    os << itNode->getUnit(framework).getExpression();
                  else
                    os << value << " " << itNode->getUnit(framework).getExpression();
                }

              os << std::endl;
            }
        }
    }
  else if (mode == "table")
    {
      itNode.setProcessingModes(CNodeIteratorMode::After);

      while (itNode.next() != itNode.end())
        {
          if (*itNode != NULL)
            {
              const CReaction* pReaction = dynamic_cast<const CReaction*>(itNode->getObject());
              const CModelEntity* pEntity = dynamic_cast<const CModelEntity*>(itNode->getObject());

              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set && pReaction == NULL)
                {
                  if (pEntity == NULL && itNode->getObject()) // local parameter
                    os << itNode->getObject()->getObjectDisplayName()
                       << " " << itNode->getUnit(framework).getExpression() << separator;
                  else
                    os << itNode->getName() << " " << itNode->getUnit(framework).getExpression() << separator;
                }
            }
        }

      os << std::endl;

      itNode = CNodeIterator< const CModelParameter >(this);
      itNode.setProcessingModes(CNodeIteratorMode::After);

      while (itNode.next() != itNode.end())
        {
          if (*itNode != NULL)
            {
              const CReaction* pReaction = dynamic_cast<const CReaction*>(itNode->getObject());

              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set && pReaction == NULL)
                {
                  os << itNode->getValue(framework) << separator;
                }
            }
        }

      os << std::endl;
    }
  else if (mode == "ini")
    {
      itNode.setProcessingModes(CNodeIteratorMode::After);

      while (itNode.next() != itNode.end())
        {
          if (*itNode != NULL)
            {
              const CDataObject* current = itNode->getObject();
              const CMetab* pMetab = dynamic_cast<const CMetab*>(current);
              const CCompartment* pComp = dynamic_cast<const CCompartment*>(current);
              const CModelValue* pParam = dynamic_cast<const CModelValue*>(current);
              const CModel* pModel = dynamic_cast<const CModel*>(current);
              const CReaction* pReaction = dynamic_cast<const CReaction*>(itNode->getObject());

              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set &&
                  pReaction == NULL)
                {

                  if (pModel != NULL) continue; // ignore time for now

                  if (pMetab != NULL)
                    {
                      if (framework == CCore::Framework::Concentration)
                        os << pMetab->getInitialConcentrationReference()->getObjectDisplayName()
                           << " = " << itNode->getValue(framework) << std::endl;
                      else
                        os << pMetab->getInitialValueReference()->getObjectDisplayName()
                           << " = " << itNode->getValue(framework) << std::endl;
                    }
                  else if (pComp != NULL)
                    {
                      os << pComp->getInitialValueReference()->getObjectDisplayName()
                         << " = " << itNode->getValue(framework) << std::endl;
                    }
                  else if (pParam != NULL)
                    {
                      os << pParam->getInitialValueReference()->getObjectDisplayName()
                         << " = " << itNode->getValue(framework) << std::endl;
                    }
                  else
                    {
                      os << current->getObjectDisplayName() << " = " << itNode->getValue(framework) << std::endl;
                    }
                }
            }
        }

      os << std::endl;
    }

  else
    {
      success = false;
    }

  return success;
}
