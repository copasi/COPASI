// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * GlobalQuantityDataChangeCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef GLOBALQUANTITYDATACHANGECOMMAND_H_
#define GLOBALQUANTITYDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class GlobalQuantityDataChangeCommand: public CCopasiUndoCommand
{
public:
  GlobalQuantityDataChangeCommand(QModelIndex index, const QVariant value, int role, CQGlobalQuantityDM *pGlobalQuantityDM);
  void redo();
  void undo();
  QString globalQuantityDataChangeText() const;

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQGlobalQuantityDM *mpGlobalQuantityDM;
  int mRole;
  Path mPathIndex;

  virtual ~GlobalQuantityDataChangeCommand();
};

#endif /* GLOBALQUANTITYDATACHANGECOMMAND_H_ */
