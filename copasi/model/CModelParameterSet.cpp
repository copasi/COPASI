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

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "copasi/core/CRootContainer.h"
#include "report/CKeyFactory.h"
#include "core/CDataString.h"
#include "utilities/CNodeIterator.h"

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

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CModelParameterSet::applyData(const CData & data)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CModelParameterSet::CModelParameterSet(const std::string & name,
                                       const CDataContainer * pParent):
  CDataContainer(name, pParent, "ModelParameterSet"),
  CModelParameterGroup(NULL, CModelParameter::Set),
  CAnnotation(),
  mKey(CRootContainer::getKeyFactory()->add("ModelParameterSet", this)),
  mpModel(NULL)
{
  setObjectParent(pParent);
}

CModelParameterSet::CModelParameterSet(const CModelParameterSet & src,
                                       const CDataContainer * pParent,
                                       const bool & createMissing):
  CDataContainer(src, pParent),
  CModelParameterGroup(src, NULL, createMissing),
  CAnnotation(src),
  mKey(CRootContainer::getKeyFactory()->add("ModelParameterSet", this)),
  mpModel(NULL)
{
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
  CRootContainer::getKeyFactory()->remove(mKey);
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
  clear();

  if (mpModel == NULL)
    {
      return;
    }

  CModelParameter * pParameter;
  CModelParameterGroup * pGroup;

  // Create the proper structure that fits the parameter overview in the GUI
  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CDataString("Initial Time").getCN());

  pParameter = pGroup->add(Model);
  pParameter->setCN(mpModel->getCN());
  pParameter->setValue(mpModel->getInitialTime(), CCore::Framework::ParticleNumbers);

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CDataString("Initial Compartment Sizes").getCN());

  CDataVector< CCompartment >::const_iterator itCompartment = mpModel->getCompartments().begin();
  CDataVector< CCompartment >::const_iterator endCompartment = mpModel->getCompartments().end();

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      pParameter = pGroup->add(Compartment);
      pParameter->setCN(itCompartment->getCN());
      pParameter->setSimulationType(itCompartment->getStatus());
      pParameter->setValue(itCompartment->getInitialValue(), CCore::Framework::ParticleNumbers);
      pParameter->setInitialExpression(itCompartment->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CDataString("Initial Species Values").getCN());

  CDataVector< CMetab >::const_iterator itSpecies = mpModel->getMetabolites().begin();
  CDataVector< CMetab >::const_iterator endSpecies = mpModel->getMetabolites().end();

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      pParameter = pGroup->add(Species);
      pParameter->setCN(itSpecies->getCN());
      pParameter->setSimulationType(itSpecies->getStatus());
      pParameter->setValue(itSpecies->getInitialValue(), CCore::Framework::ParticleNumbers);
      pParameter->setInitialExpression(itSpecies->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CDataString("Initial Global Quantities").getCN());

  CDataVector< CModelValue >::const_iterator itModelValue = mpModel->getModelValues().begin();
  CDataVector< CModelValue >::const_iterator endModelValue = mpModel->getModelValues().end();

  for (; itModelValue != endModelValue; ++itModelValue)
    {
      pParameter = pGroup->add(ModelValue);
      pParameter->setCN(itModelValue->getCN());
      pParameter->setSimulationType(itModelValue->getStatus());
      pParameter->setValue(itModelValue->getInitialValue(), CCore::Framework::ParticleNumbers);
      pParameter->setInitialExpression(itModelValue->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CDataString("Kinetic Parameters").getCN());

  CDataVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CDataVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  for (; itReaction != endReaction; ++itReaction)
    {
      CModelParameterGroup * pReaction = static_cast< CModelParameterGroup *>(pGroup->add(Reaction));
      pReaction->setCN(itReaction->getCN());

      CCopasiParameterGroup::index_iterator itParameter = itReaction->getParameters().beginIndex();
      CCopasiParameterGroup::index_iterator endParameter = itReaction->getParameters().endIndex();

      for (; itParameter != endParameter; ++itParameter)
        {
          pParameter = pReaction->add(ReactionParameter);
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
              const std::vector<std::string> ModelValue = itReaction->getParameterMapping((*itParameter)->getObjectName());

              if (ModelValue.size() != 1) fatalError();

              const CModelValue * pModelValue = static_cast< CModelValue * >(CRootContainer::getKeyFactory()->get(ModelValue[0]));

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

  return (diff(Tmp, framework, true) == CModelParameter::Identical);
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
  assignGroupContent(src, createMissing);
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

              if (itNode->getType() != Group &&
                  itNode->getType() != Set)
                {
                  os << itNode->getValue(framework) << " " << itNode->getUnit(framework);
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
              if (itNode->getType() != Group &&
                  itNode->getType() != Set)
                {
                  os << itNode->getName() << " " << itNode->getUnit(framework) << separator;
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
              if (itNode->getType() != Group &&
                  itNode->getType() != Set)
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
