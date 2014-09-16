/*
 * CreateNewCompartmentCommand.h
 *
 *  Created on: 16 Sep 2014
 *      Author: dada
 */

#ifndef CREATENEWCOMPARTMENTCOMMAND_H_
#define CREATENEWCOMPARTMENTCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQCompartment;
class UndoCompartmentData;

class CreateNewCompartmentCommand: public CCopasiUndoCommand {
public:
	CreateNewCompartmentCommand(CQCompartment *pCompartment);
	void redo();
	void undo();
	QString createNewCompartmentText() const;
	virtual ~CreateNewCompartmentCommand();

private:
	UndoCompartmentData *mpCompartmentData;
	CQCompartment* mpCompartment;
};

#endif /* CREATENEWCOMPARTMENTCOMMAND_H_ */
