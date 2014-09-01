/*
 * RemoveAllSpecieRowsCommand.h
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#ifndef REMOVEALLSPECIEROWSCOMMAND_H_
#define REMOVEALLSPECIEROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class UndoSpecieData;
class UndoReactionData;

class RemoveAllSpecieRowsCommand: public CCopasiUndoCommand {
public:
	RemoveAllSpecieRowsCommand(CQSpecieDM * pSpecieDM, const QModelIndex&);
	void redo();
	void undo();

	/**
	 * Method for handling the species dependency objects
	 */
	void setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects, QList<UndoReactionData*> *dependencyObjects);

	QString removeAllSpecieRowsText() const;

	private:
		CQSpecieDM *mpSpecieDM;
		QList <UndoSpecieData *> mpSpecieData;
		QList <UndoReactionData *> mpReactionData;
	virtual ~RemoveAllSpecieRowsCommand();
};

#endif /* REMOVEALLSPECIEROWSCOMMAND_H_ */
