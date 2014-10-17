/*
 * RemoveEventRowsCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef REMOVEEVENTROWSCOMMAND_H_
#define REMOVEEVENTROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQEventDM;

class RemoveEventRowsCommand: public CCopasiUndoCommand {
public:
	RemoveEventRowsCommand(QModelIndexList rows, CQEventDM * pEventDM, const QModelIndex&);
	void redo();
	void undo();

	QString removeEventRowsText() const;

	virtual ~RemoveEventRowsCommand();

private:
	CQEventDM *mpEventDM;
	QModelIndexList mRows;
	QList <UndoEventData *> mpEventData;

	bool mFirstTime;
};

#endif /* REMOVEEVENTROWSCOMMAND_H_ */
