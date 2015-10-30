// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveSpecieRowsCommand.h
 *
 *  Created on: 28 Aug 2014
 *      Author: dada
 */

#ifndef REMOVESPECIEROWSCOMMAND_H_
#define REMOVESPECIEROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class CCopasiObject;
class UndoReactionData;
class CQSpecieDM;

class RemoveSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveSpecieRowsCommand(QModelIndexList rows, CQSpecieDM * pSpecieDM, const QModelIndex&);
  virtual ~RemoveSpecieRowsCommand();

  void redo();
  void undo();

private:
  CQSpecieDM *mpSpecieDM;
  QModelIndexList mRows;
  QList <UndoSpeciesData *> mpSpeciesData;
  bool mFirstTime;
};

#endif /* REMOVESPECIEROWSCOMMAND_H_ */
