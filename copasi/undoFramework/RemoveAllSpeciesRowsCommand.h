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

class RemoveAllSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllSpecieRowsCommand(CQSpecieDM * pSpecieDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeAllSpecieRowsText() const;

private:
  CQSpecieDM *mpSpecieDM;
  QList <UndoSpeciesData *> mpSpeciesData;
  //  QList <UndoReactionData *> mpReactionData;
  virtual ~RemoveAllSpecieRowsCommand();
};

#endif /* REMOVEALLSPECIEROWSCOMMAND_H_ */
