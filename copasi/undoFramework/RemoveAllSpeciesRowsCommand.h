// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

class UndoSpeciesData;
class UndoReactionData;
class CQSpecieDM;

class RemoveAllSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllSpecieRowsCommand(CQSpecieDM * pSpecieDM, const QModelIndex&);
  virtual ~RemoveAllSpecieRowsCommand();

  void redo();
  void undo();

private:
  CQSpecieDM *mpSpecieDM;
  QList <UndoSpeciesData *> mpSpeciesData;

};

#endif /* REMOVEALLSPECIEROWSCOMMAND_H_ */
