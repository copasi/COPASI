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


			QList<UndoReactionData*> dependencyObjects;
			setDependentObjects(pModel->getMetabolites()[(*i).row()]->getDeletedObjects(), &dependencyObjects);
			data->setDependencyObjects(dependencyObjects);

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
	return QObject::tr(": Removed Species Rows");
}

void RemoveSpecieRowsCommand::setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects, QList<UndoReactionData*> *dependencyObjects)
{


	if (deletedObjects.size() == 0)
		return;

	// Determine the affected data model
	const CCopasiDataModel * pDataModel = (*deletedObjects.begin())->getObjectDataModel();

	// Determine the affected function DB
	CFunctionDB * pFunctionDB =
			dynamic_cast< CFunctionDB * >((*deletedObjects.begin())->getObjectAncestor("FunctionDB"));

	if (pDataModel == NULL && pFunctionDB == NULL)
		return;

	if (pFunctionDB != NULL)
	{
		// TODO In case a function is deleted we need to loop through all data models
		pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
	}
	else
	{
		pFunctionDB = CCopasiRootContainer::getFunctionList();
	}

	//TODO presently assume only reaction objects can be deleted when species is deleted
	std::set< const CCopasiObject * > Functions;
	std::set< const CCopasiObject * > Reactions;
	std::set< const CCopasiObject * > Metabolites;
	std::set< const CCopasiObject * > Values;
	std::set< const CCopasiObject * > Compartments;
	std::set< const CCopasiObject * > Events;
	std::set< const CCopasiObject * > Tasks;

	bool Used = false;

	if (pFunctionDB != NULL)
	{
		Used |= pFunctionDB->appendDependentFunctions(deletedObjects, Functions);

		if (Functions.size() > 0)
		{
			std::set< const CCopasiObject * >::const_iterator it = Functions.begin();
			std::set< const CCopasiObject * >::const_iterator end = Functions.end();

			for (; it != end; ++it)
			{
				//TODO store the function data
			}
		}
	}


	const CModel * pModel = NULL;

	if (pDataModel != NULL)
	{
		pModel = pDataModel->getModel();

	}

	if (pModel != NULL)
	{
		Used |= pModel->appendDependentModelObjects(deletedObjects, Reactions, Metabolites,
				Compartments, Values, Events);

		if (Reactions.size() > 0)
		{
			std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
			std::set< const CCopasiObject * >::const_iterator end = Reactions.end();

			for (; it != end; ++it)
			{
				//store the Reactions data
				UndoReactionData *data = new UndoReactionData();
				CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
				ri->initFromReaction((*it)->getKey());
				data->setName((*it)->getObjectName());
				data->setRi(ri);
				dependencyObjects->append(data); //FROM_UTF8((*it)->getObjectName()));
			}

		}

	}
}


RemoveSpecieRowsCommand::~RemoveSpecieRowsCommand() {
	// TODO Auto-generated destructor stub
}

