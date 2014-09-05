/*
 * SpecieTypeChangeCommand.h
 *
 *  Created on: 4 Sep 2014
 *      Author: dada
 */

#ifndef SPECIETYPECHANGECOMMAND_H_
#define SPECIETYPECHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQSpeciesDetail;

class SpecieTypeChangeCommand: public CCopasiUndoCommand {
public:
	SpecieTypeChangeCommand(int type, CQSpeciesDetail *pSpecieDetail);
	void redo();
	void undo();
	QString specieTypeChangeText(std::string &name) const;

	virtual ~SpecieTypeChangeCommand();

private:
	int mNewType, mOldType;
	CQSpeciesDetail* mpSpecieDetail;
};

#endif /* SPECIETYPECHANGECOMMAND_H_ */
