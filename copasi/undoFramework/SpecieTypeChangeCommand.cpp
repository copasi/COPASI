/*
 * SpecieTypeChangeCommand.cpp
 *
 *  Created on: 4 Sep 2014
 *      Author: dada
 */

#include "qtUtilities.h"

#include "model/CMetab.h"
#include "UI/CQSpeciesDetail.h"

#include "SpecieTypeChangeCommand.h"

SpecieTypeChangeCommand::SpecieTypeChangeCommand(int type, int currentType, CQSpeciesDetail *pSpecieDetail) {
	mpSpecieDetail = pSpecieDetail;
	mOldType = currentType;
	//std::cout<<"Old Type 1: "<<mOldType<<" === "<<CModelEntity::StatusName[mOldType]<<std::endl;
	mNewType = type;
	mFirstTime = true;

	std::string sName = mpSpecieDetail->mpMetab->getObjectName();
	this->setText(specieTypeChangeText(sName));
}
void SpecieTypeChangeCommand::redo(){
	if(mFirstTime){
		mpSpecieDetail->mpComboBoxType->setCurrentIndex(mpSpecieDetail->mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mNewType])));
		mpSpecieDetail->specieTypeChanged(mNewType);
		mpSpecieDetail->mpMetab->setStatus((CModelEntity::Status)mNewType);
		//std::cout<<"New Type 1: "<<mNewType<<" === "<<CModelEntity::StatusName[mNewType]<<std::endl;
		mFirstTime = false;
	}else{
		//	std::cout<<"New Type 2: "<<mNewType<<" === "<<CModelEntity::StatusName[mNewType]<<std::endl;
		mpSpecieDetail->mpComboBoxType->setCurrentIndex(mpSpecieDetail->mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mNewType])));
		mpSpecieDetail->specieTypeChanged(mNewType);
		mpSpecieDetail->mpMetab->setStatus((CModelEntity::Status)mNewType);
	}
}

void SpecieTypeChangeCommand::undo(){

	//std::cout<<"Old Type 2: "<<mOldType<<" === "<<CModelEntity::StatusName[mOldType]<<std::endl;
	mpSpecieDetail->mpComboBoxType->setCurrentIndex(mpSpecieDetail->mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mOldType])));
	mpSpecieDetail->specieTypeChanged(mOldType);
	mpSpecieDetail->mpMetab->setStatus((CModelEntity::Status)mOldType);
}

QString SpecieTypeChangeCommand::specieTypeChangeText(std::string &name) const {
	std::string myEntityName (": Species Type Change for "+name);
	char* entityName = (char*)myEntityName.c_str();
	return QObject::tr(entityName);
}
SpecieTypeChangeCommand::~SpecieTypeChangeCommand() {
	// TODO Auto-generated destructor stub
}

