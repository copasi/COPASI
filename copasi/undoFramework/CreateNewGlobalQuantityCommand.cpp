/*
 * CreateNewGlobalQuantityCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "model/CModelValue.h"
#include "UI/CQModelValue.h"
#include "UndoGlobalQuantityData.h"

#include "CreateNewGlobalQuantityCommand.h"

CreateNewGlobalQuantityCommand::CreateNewGlobalQuantityCommand(CQModelValue *pModelValue)
{
	mpModelValue = pModelValue;
	mpGlobalQuantityData = new UndoGlobalQuantityData();
	this->setText(createNewGlobalQuantityText());
}
void CreateNewGlobalQuantityCommand::redo(){
	mpModelValue->createNewGlobalQuantity();

	std::string sName = mpModelValue->mpModelValue->getObjectName();
	mpGlobalQuantityData->setName(sName);
	mpGlobalQuantityData->setInitialValue(mpModelValue->mpModelValue->getInitialValue());
	mpGlobalQuantityData->setStatus(mpModelValue->mpModelValue->getStatus());
}

void CreateNewGlobalQuantityCommand::undo(){
	mpModelValue->deleteGlobalQuantity(mpGlobalQuantityData);
}

QString CreateNewGlobalQuantityCommand::createNewGlobalQuantityText() const {
	std::string myEntityName (": Create New Global Quantity ");
	char* entityName = (char*)myEntityName.c_str();
	return QObject::tr(entityName);
}


CreateNewGlobalQuantityCommand::~CreateNewGlobalQuantityCommand() {
	// TODO Auto-generated destructor stub
}

