/*
 * SpecieTypeChangeCommand.cpp
 *
 *  Created on: 4 Sep 2014
 *      Author: dada
 */

#include "model/CMetab.h"
#include "UI/CQSpeciesDetail.h"

#include "SpecieTypeChangeCommand.h"

SpecieTypeChangeCommand::SpecieTypeChangeCommand(int type, CQSpeciesDetail *pSpecieDetail) {
	mpSpecieDetail = pSpecieDetail;
	mOldType = mpSpecieDetail->mpMetab->getStatus();
	mNewType = type;

	std::string sName = mpSpecieDetail->mpMetab->getObjectName();
	this->setText(specieTypeChangeText(sName));
}
void SpecieTypeChangeCommand::redo(){
	mpSpecieDetail->specieTypeChanged(mNewType);
	mpSpecieDetail->mpMetab->setStatus((CModelEntity::Status) mpSpecieDetail->mItemToType[mNewType]);
	mpSpecieDetail->mChanged = true;
}

void SpecieTypeChangeCommand::undo(){
	mpSpecieDetail->specieTypeChanged(mOldType);
	mpSpecieDetail->mpMetab->setStatus((CModelEntity::Status) mpSpecieDetail->mItemToType[mOldType]);
	mpSpecieDetail->mChanged = true;
}

QString SpecieTypeChangeCommand::specieTypeChangeText(std::string &name) const {
	std::string myEntityName (": Species Type Change for "+name);
	char* entityName = (char*)myEntityName.c_str();
	return QObject::tr(entityName);
}
SpecieTypeChangeCommand::~SpecieTypeChangeCommand() {
	// TODO Auto-generated destructor stub
}

