// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertGlobalQuantityRowsCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef INSERTGLOBALQUANTITYROWSCOMMAND_H_
#define INSERTGLOBALQUANTITYROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoGlobalQuantityData;
class CQGlobalQuantityDM;

class InsertGlobalQuantityRowsCommand: public CCopasiUndoCommand
{
public:
  InsertGlobalQuantityRowsCommand(int position, int rows, CQGlobalQuantityDM *pGlobalQuantityDM);
  InsertGlobalQuantityRowsCommand(int position, int rows, CQGlobalQuantityDM *pGlobalQuantityDM, const QModelIndex& index, const QVariant& value);
  virtual ~InsertGlobalQuantityRowsCommand();

  void redo();
  void undo();

private:
  CQGlobalQuantityDM* mpGlobalQuantityDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoGlobalQuantityData* mpGlobalQuantityData;
  QVariant mValue;
};

#endif /* INSERTGLOBALQUANTITYROWSCOMMAND_H_ */
