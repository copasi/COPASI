/*
 * RemoveAllSpecieRowsCommand.cpp
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "UI/CQSpecieDM.h"
#include "function/CFunctionDB.h"

#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "RemoveAllSpecieRowsCommand.h"
#include "UndoSpecieData.h"
#include "UndoReactionData.h"

RemoveAllSpecieRowsCommand::RemoveAllSpecieRowsCommand(CQSpecieDM * pSpecieDM, const QModelIndex&) {
	mpSpecieDM = pSpecieDM;

	assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
	CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
	assert(pDataModel != NULL);
	CModel * pModel = pDataModel->getModel();

	assert(pModel != NULL);

	for (int i = 0; i != pSpecieDM->rowCount()-1; ++i)
	{

		UndoSpecieData *data = new UndoSpecieData();


		if (pModel->getMetabolites()[i]){
			data->setName(pModel->getMetabolites()[i]->getObjectName());
		//	data->setSpecie(pModel->getMetabolites()[i]);
			data->setIConc(pModel->getMetabolites()[i]->getInitialConcentration());
			data->setCompartment(pModel->getMetabolites()[i]->getCompartment()->getObjectName());
			data->setStatus(pModel->getMetabolites()[i]->getStatus());

			QList<UndoReactionData*> dependencyObjects;
			setDependentObjects(pModel->getMetabolites()[i]->getDeletedObjects(), &dependencyObjects);
			data->setDependencyObjects(dependencyObjects);

			mpSpecieData.append(data);
		}


	}

	this->setText(removeAllSpecieRowsText());
}

void RemoveAllSpecieRowsCommand::redo(){
	mpSpecieDM->removeAllSpecieRows();
}

void RemoveAllSpecieRowsCommand::undo(){
	mpSpecieDM->insertSpecieRows(mpSpecieData);
}

QString RemoveAllSpecieRowsCommand::removeAllSpecieRowsText() const {
	return QObject::tr(": Removed All Specie Rows");
}

void RemoveAllSpecieRowsCommand::setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects, QList<UndoReactionData*> *dependencyObjects)
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

RemoveAllSpecieRowsCommand::~RemoveAllSpecieRowsCommand() {
	// TODO Auto-generated destructor stub
}

