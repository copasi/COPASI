// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
class CQGlobalQuantityDM;
class RemoveGlobalQuantityRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveGlobalQuantityRowsCommand(QModelIndexList rows, CQGlobalQuantityDM * pGlobalQuantityDM);
  virtual ~RemoveGlobalQuantityRowsCommand();

  void redo();
  void undo();

private:
  CQGlobalQuantityDM *mpGlobalQuantityDM;
  QModelIndexList mRows;
  QList <UndoGlobalQuantityData *> mpGlobalQuantityData;
  bool mFirstTime;
};

#endif /* REMOVEGLOBALQUANTITYROWSCOMMAND_H_ */
