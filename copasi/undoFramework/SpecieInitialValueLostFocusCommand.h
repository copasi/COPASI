/*
 * SpecieInitialValueLostFocusCommand.h
 *
 *  Created on: 19 Sep 2014
 *      Author: dada
 */

#ifndef SPECIEINITIALVALUELOSTFOCUSCOMMAND_H_
#define SPECIEINITIALVALUELOSTFOCUSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQSpeciesDetail;
class UndoSpecieData;

class SpecieInitialValueLostFocusCommand: public CCopasiUndoCommand {
public:
	SpecieInitialValueLostFocusCommand(CQSpeciesDetail *pSpecieDetail);
	void redo();
	void undo();
	QString specieInitialValueLostFocusText(std::string &name) const;

	virtual ~SpecieInitialValueLostFocusCommand();

private:
	CQSpeciesDetail* mpSpecieDetail;
	UndoSpecieData *mpSpecieData;
	bool mFirstTime;

};

#endif /* SPECIEINITIALVALUELOSTFOCUSCOMMAND_H_ */
