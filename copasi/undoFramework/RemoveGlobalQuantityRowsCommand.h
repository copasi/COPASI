// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveGlobalQuantityRowsCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef REMOVEGLOBALQUANTITYROWSCOMMAND_H_
#define REMOVEGLOBALQUANTITYROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class RemoveGlobalQuantityRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveGlobalQuantityRowsCommand(QModelIndexList rows, CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeGlobalQuantityRowsText() const;
  virtual ~RemoveGlobalQuantityRowsCommand();

private:
  CQGlobalQuantityDM *mpGlobalQuantityDM;
  QModelIndexList mRows;
  QList <UndoGlobalQuantityData *> mpGlobalQuantityData;

  QList <UndoReactionData *> mpReactionData;
  bool mFirstTime;
};

#endif /* REMOVEGLOBALQUANTITYROWSCOMMAND_H_ */
