// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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
CModelParameterSet * CModelParameterSet::fromData(const CData & data)
{
  return new CModelParameterSet(data.getProperty(CData::OBJECT_NAME).toString(),
                                NO_PARENT);
}

// virtual
CData CModelParameterSet::toData() const
{
  CData Data;

  // This works since the appended data overwrites the existing, i.e., we have the required object information
  Data.appendData(CModelParameterGroup::toData());
  Data.appendData(CDataContainer::toData());
  Data.appendData(CAnnotation::toData());

  return Data;
}

// virtual
bool CModelParameterSet::applyData(const CData & data, CUndoData::ChangeSet & changes)
{
  bool success = true;

  success &= CModelParameterGroup::applyData(data, changes);
  success &= CDataContainer::applyData(data, changes);
  success &= CAnnotation::applyData(data, changes);

  return success;
}

void CModelParameterSet::createUndoData(CUndoData & undoData,
                                        const CUndoData::Type & type,
                                        const CData & oldData,
                                        const CCore::Framework & framework) const
{
  // This works since the appended data overwrites the existing, i.e., we have the required object information
  CModelParameterGroup::createUndoData(undoData, type, oldData, framework);
  CDataContainer::createUndoData(undoData, type, oldData, framework);
  CAnnotation::createUndoData(undoData, type, oldData, framework);

  return;
}

// virtual
CUndoObjectInterface * CModelParameterSet::insert(const CData & data)
{
  CModelParameter * pParameter = CModelParameter::fromData(data);

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
        // We need assure that the reaction exist
      {
        CModelParameterGroup * pReaction = static_cast< CModelParameterGroup * >(mpReactions->getModelParameter(static_cast< CModelParameterReactionParameter * >(pParameter)->getReactionCN()));

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
  CModelParameterGroup * pGroup;

  pParameter = mpTimes->add(Type::Model);
  pParameter->setCN(mpModel->getCN());
  pParameter->setValue(mpModel->getInitialTime(), CCore::Framework::ParticleNumbers);

  CDataVector< CCompartment >::const_iterator itCompartment = mpModel->getCompartments().begin();
  CDataVector< CCompartment >::const_iterator endCompartment = mpModel->getCompartments().end();

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      pParameter = mpCompartments->add(Type::Compartment);
      pParameter->setCN(itCompartment->getCN());
      pParameter->setSimulationType(itCompartment->getStatus());
      pParameter->setValue(itCompartment->getInitialValue(), CCore::Framework::ParticleNumbers);
      pParameter->setInitialExpression(itCompartment->getInitialExpression());
    }

  CDataVector< CMetab >::const_iterator itSpecies = mpModel->getMetabolites().begin();
  CDataVector< CMetab >::const_iterator endSpecies = mpModel->getMetabolites().end();

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      pParameter = mpSpecies->add(Type::Species);
      pParameter->setCN(itSpecies->getCN());
      pParameter->setSimulationType(itSpecies->getStatus());
      pParameter->setValue(itSpecies->getInitialValue(), CCore::Framework::ParticleNumbers);
      pParameter->setInitialExpression(itSpecies->getInitialExpression());
    }

  CDataVector< CModelValue >::const_iterator itModelValue = mpModel->getModelValues().begin();
  CDataVector< CModelValue >::const_iterator endModelValue = mpModel->getModelValues().end();

  for (; itModelValue != endModelValue; ++itModelValue)
    {
      pParameter = mpModelValues->add(Type::ModelValue);
      pParameter->setCN(itModelValue->getCN());
      pParameter->setSimulationType(itModelValue->getStatus());
      pParameter->setValue(itModelValue->getInitialValue(), CCore::Framework::ParticleNumbers);
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
          pParameter = pReaction->add(Type::ReactionParameter);
          pParameter->setCN((*itParameter)->getCN());

          // Check whether this refers to a global quantity.
          if (itReaction->isLocalParameter((*itParameter)->getObjectName()))
            {
              pParameter->setSimulationType(CModelEntity::Status::FIXED);
              pParameter->setValue((*itParameter)->getValue< C_FLOAT64 >(), CCore::Framework::ParticleNumbers);
            }
          else
            {
              pParameter->setSimulationType(CModelEntity::Status::ASSIGNMENT);
              const std::vector< const CDataObject * > & ModelValue = itReaction->getParameterObjects((*itParameter)->getObjectName());

              if (ModelValue.size() != 1) fatalError();

              const CModelValue * pModelValue = dynamic_cast< const CModelValue * >(ModelValue[0]);

              if (pModelValue == NULL) fatalError();

              pParameter->setValue(pModelValue->getInitialValue(), CCore::Framework::ParticleNumbers);
              pParameter->setInitialExpression("<" + pModelValue->getInitialValueReference()->getCN() + ">");
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
  mpTimes->assignGroupContent(*static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Time").getCN())), createMissing);
  mpCompartments->assignGroupContent(*static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Compartment Sizes").getCN())), createMissing);
  mpSpecies->assignGroupContent(*static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Species Values").getCN())), createMissing);
  mpModelValues->assignGroupContent(*static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Initial Global Quantities").getCN())), createMissing);
  mpReactions->assignGroupContent(*static_cast< CModelParameterGroup * >(CModelParameterGroup::getModelParameter(CDataString("Kinetic Parameters").getCN())), createMissing);

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
              for (unsigned int i = 1; i < itNode.level(); i++)
                {
                  os << separator;
                }

              os << itNode->getName();

              for (size_t i = itNode.level(); i < 6; i++)
                {
                  os << separator;
                }

              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set)
                {
                  os << itNode->getValue(framework) << " " << itNode->getUnit(framework).getExpression();
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
              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set)
                {
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
              if (itNode->getType() != Type::Group &&
                  itNode->getType() != Type::Set)
                {
                  os << itNode->getValue(framework) << separator;
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
