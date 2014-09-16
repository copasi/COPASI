/*
 * RemoveSpecieRowsCommand.cpp
 *
 *  Created on: 28 Aug 2014
 *      Author: dada
 */


#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"
#include "function/CFunctionDB.h"

#include "UndoSpecieData.h"
#include "UndoReactionData.h"
#include "RemoveSpecieRowsCommand.h"


RemoveSpecieRowsCommand::RemoveSpecieRowsCommand(QModelIndexList rows, CQSpecieDM * pSpecieDM, const QModelIndex&) {
	mpSpecieDM = pSpecieDM;
	mRows = rows;
	mFirstTime = true;

	assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
	CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
	assert(pDataModel != NULL);
	CModel * pModel = pDataModel->getModel();

	assert(pModel != NULL);

	QModelIndexList::const_iterator i;

	for (i = rows.begin(); i != rows.end(); ++i)
	{
		UndoSpecieData *data = new UndoSpecieData();

		if (!pSpecieDM->isDefaultRow(*i) && pModel->getMetabolites()[(*i).row()]){
			data->setName(pModel->getMetabolites()[(*i).row()]->getObjectName());
			data->setIConc(pModel->getMetabolites()[(*i).row()]->getInitialConcentration());
			data->setCompartment(pModel->getMetabolites()[(*i).row()]->getCompartment()->getObjectName());
			data->setStatus(pModel->getMetabolites()[(*i).row()]->getStatus());


		//	QList<UndoReactionData*> *dependencyObjects = new QList <UndoReactionData*>();

			setDependentObjects(pModel->getMetabolites()[(*i).row()]->getDeletedObjects()); //, dependencyObjects);
			data->setReactionDependencyObjects(getReactionData());
		//	data->setDependencyObjects(getReactionData());

			mpSpecieData.append(data);
		}
	}
	this->setText(removeSpecieRowsText());
}

void RemoveSpecieRowsCommand::redo(){
	if(mFirstTime){
		mpSpecieDM->removeSpecieRows(mRows, QModelIndex());
		mFirstTime = false;
	}
	else{
		mpSpecieDM->deleteSpecieRows(mpSpecieData);
	}
}

void RemoveSpecieRowsCommand::undo(){
	mpSpecieDM->insertSpecieRows(mpSpecieData);
}

QString RemoveSpecieRowsCommand::removeSpecieRowsText() const {
	return QObject::tr(": Removed Species");
}

RemoveSpecieRowsCommand::~RemoveSpecieRowsCommand() {
	// TODO Auto-generated destructor stub
}

