// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameterSet.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/08 19:04:39 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
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
}

// virtual
CModelParameterSet::~CModelParameterSet()
{}

// virtual
const std::string & CModelParameterSet::getKey() const
{
  return mKey;
}

// virtual
bool CModelParameterSet::setObjectParent(const CCopasiContainer * pParent)
{
  bool success = CCopasiObject::setObjectParent(pParent);

  mpModel = dynamic_cast< CModel * >(getObjectAncestor("CModel"));

  return success;
}


// virtual
CModel * CModelParameterSet::getModel()
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

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Initial Compartment Sizes").getCN());

  CCopasiVector< CCompartment >::const_iterator itCompartment = mpModel->getCompartments().begin();
  CCopasiVector< CCompartment >::const_iterator endCompartment = mpModel->getCompartments().end();

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      pParameter = pGroup->add(Compartment);
      pParameter->setCN((*itCompartment)->getCN());
      pParameter->setValue((*itCompartment)->getInitialValue());
      pParameter->setInitialExpression((*itCompartment)->getInitialExpression());
    }

  pGroup = static_cast< CModelParameterGroup *>(CModelParameterGroup::add(Group));
  pGroup->setCN(CCopasiStaticString("Initial Species Concentrations").getCN());

  CCopasiVector< CMetab >::const_iterator itSpecies = mpModel->getMetabolites().begin();
  CCopasiVector< CMetab >::const_iterator endSpecies = mpModel->getMetabolites().end();

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      pParameter = pGroup->add(Species);
      pParameter->setCN((*itSpecies)->getCN());
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

      for (size_t i = 0; itParameter != endParameter; ++itParameter, ++i)
        {
          pParameter = pReaction->add(ReactionParameter);
          pParameter->setCN((*itParameter)->getCN());

          // Check whether this refers to a global quantity.
          if ((*itReaction)->isLocalParameter(i))
            {
              pParameter->setValue(*(*itParameter)->getValue().pDOUBLE);
            }
          else
            {
              const std::vector<std::string> ModelValue = (*itReaction)->getParameterMapping((*itParameter)->getObjectName());

              assert(ModelValue.size() == 1);

              const CModelValue * pModelValue = static_cast< CModelValue * >(CCopasiRootContainer::getKeyFactory()->get(ModelValue[0]));
              pParameter->setValue(pModelValue->getInitialValue());
              pParameter->setInitialExpression("<" + pModelValue->getInitialValueReference()->getCN() + ">");
            }
        }
    }
}

bool CModelParameterSet::compareWithModel()
{
  if (mpModel == NULL)
    {
      return false;
    }

  CModelParameterSet Tmp("Current", mpModel);
  Tmp.createFromModel();

  return diff(Tmp);
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


