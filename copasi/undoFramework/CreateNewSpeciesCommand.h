// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewSpecieCommand.h
 *
 *  Created on: 2 Sep 2014
 *      Author: dada
 */

#ifndef CREATENEWSPECIECOMMAND_H_
#define CREATENEWSPECIECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQSpeciesDetail;
class UndoSpeciesData;

class CreateNewSpeciesCommand: public CCopasiUndoCommand
{
public:
  CreateNewSpeciesCommand(CQSpeciesDetail *pSpecieDetail);
  void redo();
  void undo();
  QString createNewSpecieText() const;
  UndoData *getUndoData() const;

  virtual ~CreateNewSpeciesCommand();

private:
  UndoSpeciesData *mpSpeciesData;
  CQSpeciesDetail* mpSpecieDetail;
};

#endif /* CREATENEWSPECIECOMMAND_H_ */
