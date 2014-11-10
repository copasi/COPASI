// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertCompartmentRowsCommand.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef INSERTCOMPARTMENTROWSCOMMAND_H_
#define INSERTCOMPARTMENTROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoCompartmentData;

class InsertCompartmentRowsCommand: public CCopasiUndoCommand
{
public:
  InsertCompartmentRowsCommand(int position, int rows, CQCompartmentDM *pCompartmentDM, const QModelIndex&);

  void redo();
  void undo();
  QString insertRowsText() const;

  virtual ~InsertCompartmentRowsCommand();

private:
  CQCompartmentDM* mpCompartmentDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoCompartmentData* mpCompartmentData;
  int firstTime;
};

#endif /* INSERTCOMPARTMENTROWSCOMMAND_H_ */
