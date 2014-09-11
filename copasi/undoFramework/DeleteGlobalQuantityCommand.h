/*
 * DeleteGlobalQuantityCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef DELETEGLOBALQUANTITYCOMMAND_H_
#define DELETEGLOBALQUANTITYCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class UndoGlobalQuantityData;
class UndoReactionData;
class CQModelValue;

class DeleteGlobalQuantityCommand: public CCopasiUndoCommand {
public:
	DeleteGlobalQuantityCommand(CQModelValue *pModelValue);
	void redo();
	void undo();
	QString deleteGlobalQuantityText(std::string &name) const;

	void setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects, QList<UndoReactionData*> *dependencyObjects);

	virtual ~DeleteGlobalQuantityCommand();

private:
	bool mFirstTime;
	UndoGlobalQuantityData *mpGlobalQuantityData;
	CQModelValue* mpModelValue;
};

#endif /* DELETEGLOBALQUANTITYCOMMAND_H_ */
