// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllGlobalQuantityRowsCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef REMOVEALLGLOBALQUANTITYROWSCOMMAND_H_
#define REMOVEALLGLOBALQUANTITYROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class UndoReactionData;

class RemoveAllGlobalQuantityRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllGlobalQuantityRowsCommand(CQGlobalQuantityDM * pGlobalQuantityDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeAllGlobalQuantityRowsText() const;

  virtual ~RemoveAllGlobalQuantityRowsCommand();

private:
  CQGlobalQuantityDM *mpGlobalQuantityDM;
  QList <UndoGlobalQuantityData *> mpGlobalQuantityData;
};

#endif /* REMOVEALLGLOBALQUANTITYROWSCOMMAND_H_ */
