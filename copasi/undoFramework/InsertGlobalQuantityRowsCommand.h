// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class InsertGlobalQuantityRowsCommand: public CCopasiUndoCommand
{
public:
  InsertGlobalQuantityRowsCommand(int position, int rows, CQGlobalQuantityDM *pGlobalQuantityDM, const QModelIndex&);
  virtual ~InsertGlobalQuantityRowsCommand();
  void redo();
  void undo();
  QString insertRowsText() const;

private:
  CQGlobalQuantityDM* mpGlobalQuantityDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoGlobalQuantityData* mpGlobalQuantityData;
  int firstTime;
};

#endif /* INSERTGLOBALQUANTITYROWSCOMMAND_H_ */
