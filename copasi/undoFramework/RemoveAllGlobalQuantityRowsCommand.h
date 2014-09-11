/*
 * RemoveAllGlobalQuantityRowsCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef REMOVEALLGLOBALQUANTITYROWSCOMMAND_H_
#define REMOVEALLGLOBALQUANTITYROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class UndoReactionData;

class RemoveAllGlobalQuantityRowsCommand: public CCopasiUndoCommand {
public:
	RemoveAllGlobalQuantityRowsCommand(CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&);
	void redo();
	void undo();

	/**
	 * Method for handling the GlobalQuantity dependency objects
	 */
	void setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects, QList<UndoReactionData*> *dependencyObjects);

	QString removeAllGlobalQuantityRowsText() const;

	virtual ~RemoveAllGlobalQuantityRowsCommand();

private:
	CQGlobalQuantityDM *mpGlobalQuantityDM;
	QList <UndoGlobalQuantityData *> mpGlobalQuantityData;
	QList <UndoReactionData *> mpReactionData;

};

#endif /* REMOVEALLGLOBALQUANTITYROWSCOMMAND_H_ */
