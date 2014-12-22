// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieTypeChangeCommand.cpp
 *
 *  Created on: 4 Sep 2014
 *      Author: dada
 */

#include "qtUtilities.h"

#include "model/CMetab.h"
#include "UI/CQSpeciesDetail.h"
#include "model/CCompartment.h"

#include "UndoSpecieData.h"

#include "SpecieTypeChangeCommand.h"

SpecieTypeChangeCommand::SpecieTypeChangeCommand(int type, int currentType, CQSpeciesDetail *pSpecieDetail)
{
  mpSpecieDetail = pSpecieDetail;
  mOldType = currentType;
  mNewType = type;
  mFirstTime = true;

  mpSpecieData = new UndoSpecieData();
  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpecieData->setName(sName);
  mpSpecieData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
  mpSpecieData->setCompartment(mpSpecieDetail->mpMetab->getCompartment()->getObjectName());
  //mpSpecieData->setInitialExpression(mpSpecieDetail->mpInitialExpressionEMW->mpExpressionWidget->getExpression());
  //mpSpecieData->setExpression(mpSpecieDetail->mpExpressionEMW->mpExpressionWidget->getExpression());
  mpSpecieData->setStatus((CModelEntity::Status)type);

  this->setText(specieTypeChangeText(sName));

  //set the data for UNDO history
  mType = SPECIESTYPECHANGE;
  setEntityType("Species");
  setAction("Change");
  setName(mpSpecieData->getName());

  switch ((CModelEntity::Status) mNewType)
    {
      case CModelEntity::FIXED:
        setNewValue("fixed");
        break;

      case CModelEntity::REACTIONS:
        setNewValue("reactions");
        break;

      case CModelEntity::ASSIGNMENT:
        setNewValue("assignment");
        break;

      case CModelEntity::ODE:
        setNewValue("ode");
        break;
    }

  switch ((CModelEntity::Status) mOldType)
    {
      case CModelEntity::FIXED:
        setOldValue("fixed");
        break;

      case CModelEntity::REACTIONS:
        setOldValue("reactions");
        break;

      case CModelEntity::ASSIGNMENT:
        setOldValue("assignment");
        break;

      case CModelEntity::ODE:
        setOldValue("ode");
        break;
    }

  setProperty("Type");
}
void SpecieTypeChangeCommand::redo()
{
  if (mFirstTime)
    {
      mpSpecieDetail->specieTypeChanged(mpSpecieDetail->mpComboBoxType->currentIndex());
      mFirstTime = false;
    }
  else
    {
      mpSpecieDetail->specieTypeChanged(mpSpecieData, mNewType);
    }
}
void SpecieTypeChangeCommand::undo()
{
  mpSpecieDetail->specieTypeChanged(mpSpecieData, mOldType);
  setAction("Unchange");
}
QString SpecieTypeChangeCommand::specieTypeChangeText(std::string &name) const
{
  std::string myEntityName(": Species Type Change for " + name);
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}
SpecieTypeChangeCommand::~SpecieTypeChangeCommand()
{
  // TODO Auto-generated destructor stub
}
