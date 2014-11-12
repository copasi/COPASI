// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class RemoveSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveSpecieRowsCommand(QModelIndexList rows, CQSpecieDM * pSpecieDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeSpecieRowsText() const;
  virtual ~RemoveSpecieRowsCommand();

private:
  CQSpecieDM *mpSpecieDM;
  QModelIndexList mRows;
  QList <UndoSpecieData *> mpSpecieData;
  //QList <UndoReactionData *> mpReactionData;
  bool mFirstTime;
};

#endif /* REMOVESPECIEROWSCOMMAND_H_ */
