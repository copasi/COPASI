// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CModelParameterSet.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiStaticString.h"

CModelParameterSet::CModelParameterSet(const std::string & name,
                                       const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent),
  CModelParameterGroup(NULL, CModelParameter::Set),
  CAnnotation(),
  mKey(CCopasiRootContainer::getKeyFactory()->add("ModelParameterSet", this)),
  mpModel(NULL)
{
  setObjectParent(pParent);
}

CModelParameterSet::CModelParameterSet(const CModelParameterSet & src,
                                       const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  CModelParameterGroup(src, NULL),
  CAnnotation(src),
  mKey(CCopasiRootContainer::getKeyFactory()->add("ModelParameterSet", this)),
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
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

// virtual
const std::string & CModelParameterSet::getKey() const
{
  return mKey;
}

// virtual
bool CModelParameterSet::setObjectParent(const CCopasiContainer * pParent)
{
  bool success = CCopasiObject::setObjectParent(pParent);

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

  // TODO CRITICAL Create the proper structure that fits the parameter overview in the GUI
  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Initial Time").getCN());

  pParameter = pGroup->add(Model);
  pParameter->setCN(mpModel->getCN());
  pParameter->setValue(mpModel->getInitialTime());

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Initial Compartment Sizes").getCN());

  CCopasiVector< CCompartment >::const_iterator itCompartment = mpModel->getCompartments().begin();
  CCopasiVector< CCompartment >::const_iterator endCompartment = mpModel->getCompartments().end();

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      pParameter = pGroup->add(Compartment);
      pParameter->setCN((*itCompartment)->getCN());
      pParameter->setSimulationType((*itCompartment)->getStatus());
      pParameter->setValue((*itCompartment)->getInitialValue());
      pParameter->setInitialExpression((*itCompartment)->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Initial Species Values").getCN());

  CCopasiVector< CMetab >::const_iterator itSpecies = mpModel->getMetabolites().begin();
  CCopasiVector< CMetab >::const_iterator endSpecies = mpModel->getMetabolites().end();

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      pParameter = pGroup->add(Species);
      pParameter->setCN((*itSpecies)->getCN());
      pParameter->setSimulationType((*itSpecies)->getStatus());
      pParameter->setValue((*itSpecies)->getInitialValue());
      pParameter->setInitialExpression((*itSpecies)->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Initial Global Quantities").getCN());

  CCopasiVector< CModelValue >::const_iterator itModelValue = mpModel->getModelValues().begin();
  CCopasiVector< CModelValue >::const_iterator endModelValue = mpModel->getModelValues().end();

  for (; itModelValue != endModelValue; ++itModelValue)
    {
      pParameter = pGroup->add(ModelValue);
      pParameter->setCN((*itModelValue)->getCN());
      pParameter->setSimulationType((*itModelValue)->getStatus());
      pParameter->setValue((*itModelValue)->getInitialValue());
      pParameter->setInitialExpression((*itModelValue)->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Kinetic Parameters").getCN());

  CCopasiVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  for (; itReaction != endReaction; ++itReaction)
    {
      CModelParameterGroup * pReaction = static_cast< CModelParameterGroup *>(pGroup->add(Group));
      pReaction->setCN((*itReaction)->getCN());

      CCopasiParameterGroup::index_iterator itParameter = (*itReaction)->getParameters().beginIndex();
      CCopasiParameterGroup::index_iterator endParameter = (*itReaction)->getParameters().endIndex();

      for (; itParameter != endParameter; ++itParameter)
        {
          pParameter = pReaction->add(ReactionParameter);
          pParameter->setCN((*itParameter)->getCN());

          // Check whether this refers to a global quantity.
          if ((*itReaction)->isLocalParameter((*itParameter)->getObjectName()))
            {
              pParameter->setSimulationType(CModelEntity::FIXED);
              pParameter->setValue(*(*itParameter)->getValue().pDOUBLE);
            }
          else
            {
              pParameter->setSimulationType(CModelEntity::ASSIGNMENT);
              const std::vector<std::string> ModelValue = (*itReaction)->getParameterMapping((*itParameter)->getObjectName());

              assert(ModelValue.size() == 1);

              const CModelValue * pModelValue = static_cast< CModelValue * >(CCopasiRootContainer::getKeyFactory()->get(ModelValue[0]));
              pParameter->setValue(pModelValue->getInitialValue());
              pParameter->setInitialExpression("<" + pModelValue->getInitialValueReference()->getCN() + ">");
            }
        }
    }

  compile();
}

bool CModelParameterSet::compareWithModel()
{
  if (mpModel == NULL)
    {
      return false;
    }

  CModelParameterSet Tmp("Current", mpModel);
  Tmp.createFromModel();

  return (diff(Tmp) == CModelParameter::Identical);
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

  return CModelParameterGroup::updateModel();
}

bool CModelParameterSet::isActive() const
{
  if (mpModel == NULL)
    {
      return false;
    }

  return (mpModel->getModelParameterSet().getKey() == mKey);
}

void CModelParameterSet::assignSetContent(const CModelParameterSet & src)
{
  assignGroupContent(src);
  compile();
}
